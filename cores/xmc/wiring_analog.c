//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
//****************************************************************************
// @Defines
//****************************************************************************
#define ADC_CONVERSION_GROUP 0
#define ADC_MIN_RESOLUTION 8
#define ADC_MAX_READ_RESOLUTION 12
#define ANALOG_MAX_WRITE_RESOLUTION 16

#define map(x, in_min, in_max, out_min, out_max) \
    (((x - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min)

//****************************************************************************
// @Global Variables
//****************************************************************************
static XMC_VADC_CHANNEL_REF_t analog_reference = XMC_VADC_CHANNEL_REF_INTREF;
static uint8_t _readResolution = 10;
static uint8_t _writeResolution = 8;
uint16_t _readMaximum = 1023;
uint16_t _writeMaximum = 255;

/* Sets the ADC reference voltage type. For the current XMC board, only the default (internal
   reference, Varef = Vdda) is available. Other reference modes are not supported and will be
   ignored. This function is provided for API compatibility and future extension.
*/
void analogReference(uint8_t mode) {
    switch (mode) {
    case DEFAULT:
        analog_reference = XMC_VADC_CHANNEL_REF_INTREF;
        break;
    default:
        // Invalid mode, do nothing
        break;
    }
}

uint8_t analogWriteResolution(uint8_t res) {
    if (res > ANALOG_MAX_WRITE_RESOLUTION || res < ADC_MIN_RESOLUTION)
        return 255;

    _writeResolution = res;
    _writeMaximum = (uint16_t)(((uint32_t)1U << res) - 1);
    return res;
}

int16_t scan_map_table(const uint8_t table[][2], uint8_t pin) {
    int16_t i;

    i = 0;
    while (table[i][0] != 255) {
        if (table[i][0] == pin)
            break;
        i++;
    }
    if (table[i][0] != 255)
        return table[i][1];
    return -1;
}

void analogWrite(pin_size_t pinNumber, int value) {
    uint32_t compare_reg = 0;
    int16_t resource;
    if (value < 0 || value > _writeMaximum)
        return;
    // Check if the pin supports PWM4
    resource = scan_map_table(mapping_pin_PWM4, pinNumber);
    if (resource >= 0) {
        XMC_PWM4_t *pwm4 = &mapping_pwm4[resource];
        if (!(pwm4->enabled)) {
            // Slice not yet initialized
            XMC_CCU4_SLICE_COMPARE_CONFIG_t pwm_config;
            memset(&pwm_config, 0, sizeof(XMC_CCU4_SLICE_COMPARE_CONFIG_t));
            pwm_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.prescaler_initval = pwm4->prescaler;
            XMC_CCU4_Init(pwm4->ccu, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
            XMC_CCU4_SLICE_CompareInit(pwm4->slice, &pwm_config);
            XMC_CCU4_EnableClock(pwm4->ccu, pwm4->slice_num);
            XMC_CCU4_SLICE_SetTimerPeriodMatch(pwm4->slice, pwm4->period_timer_val);
            pwm4->enabled = ENABLED;
        }
        if (value != 0)
            compare_reg = ((value + 1) * (pwm4->period_timer_val + 1)) >> _writeResolution;
        XMC_CCU4_SLICE_SetTimerCompareMatch(pwm4->slice, compare_reg);
        XMC_CCU4_EnableShadowTransfer(pwm4->ccu, (CCU4_GCSS_S0SE_Msk << (4 * pwm4->slice_num)));
        XMC_GPIO_SetMode(pwm4->port_pin.port, pwm4->port_pin.pin,
                         (XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm4->port_mode));
        XMC_CCU4_SLICE_StartTimer(pwm4->slice);

        return;
    }
#if defined(CCU8V2) || defined(CCU8V1)
    // Check if the pin supports PWM8
    else if ((resource = scan_map_table(mapping_pin_PWM8, pinNumber)) >= 0) {
        XMC_PWM8_t *pwm8 = &mapping_pwm8[resource];
        if (!(pwm8->enabled)) {
            // Slice not yet initialized
            XMC_CCU8_SLICE_COMPARE_CONFIG_t pwm_config;
            memset(&pwm_config, 0, sizeof(XMC_CCU8_SLICE_COMPARE_CONFIG_t));
            pwm_config.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
            pwm_config.prescaler_initval = pwm8->prescaler;
            XMC_CCU8_Init(pwm8->ccu, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
            XMC_CCU8_SLICE_CompareInit(pwm8->slice, &pwm_config);
            XMC_CCU8_EnableClock(pwm8->ccu, pwm8->slice_num);
            XMC_CCU8_SLICE_SetTimerPeriodMatch(pwm8->slice, pwm8->period_timer_val);
            pwm8->enabled = ENABLED;
        }
        if (value != 0)
            compare_reg = ((value + 1) * (pwm8->period_timer_val + 1)) >> _writeResolution;
        XMC_CCU8_SLICE_SetTimerCompareMatch(pwm8->slice, pwm8->slice_channel, compare_reg);
        XMC_CCU8_EnableShadowTransfer(pwm8->ccu, CCU8_GCSS_S0SE_Msk << (4 * pwm8->slice_num));
        XMC_GPIO_SetMode(pwm8->port_pin.port, pwm8->port_pin.pin,
                         XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm8->port_mode);
        XMC_CCU8_SLICE_StartTimer(pwm8->slice);
        return;
    }
#endif
#ifdef DAC
    // Check if the pin supports DAC
    else if ((resource = scan_map_table(mapping_pin_DAC, pinNumber)) >= 0) {
        XMC_ARD_DAC_t *dac = &(mapping_dac[resource]);
        XMC_DAC_Enable(dac->group);
        XMC_DAC_CH_EnableOutput(dac->group, dac->channel);
        XMC_DAC_CH_StartSingleValueMode(dac->group, dac->channel);
        uint16_t dacValue =
            map(value, 0, (0b10 << _writeResolution) - 1, 0, (0b10 << dac->resolution) - 1);
        XMC_DAC_CH_Write(dac->group, dac->channel, dacValue);
        return;
    }
#endif
    // If not found, do nothing
    return;
}

#ifdef __cplusplus
}
#endif
//****************************************************************************
//                                 END OF FILE
//****************************************************************************
