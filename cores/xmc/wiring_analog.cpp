//****************************************************************************
// @File: wiring_analog.cpp
// @Brief: Analog and PWM/DAC API implementation for XMC Arduino core
//****************************************************************************
#include "Arduino.h"

//****************************************************************************
// @Defines
//****************************************************************************
#define ADC_CONVERSION_GROUP 0
#define ADC_MIN_RESOLUTION 8
#define ADC_MAX_READ_RESOLUTION 12
#define ANALOG_MAX_WRITE_RESOLUTION 16

//****************************************************************************
// @Global Variables
//****************************************************************************
static XMC_VADC_CHANNEL_REF_t analog_reference = DEFAULT;
static uint8_t _readResolution = 10;
static uint8_t _writeResolution = 8;
uint16_t _readMaximum = 1023;
uint16_t _writeMaximum = 255;
static bool vadc_inited = false;

//****************************************************************************
// @Function: scan_map_table
// @Brief: Lookup table for pin to resource mapping
//****************************************************************************
int16_t scan_map_table(const uint8_t table[][2], uint8_t pin) {
    int16_t i = 0;
    while (table[i][0] != 255) {
        if (table[i][0] == pin)
            break;
        i++;
    }
    if (table[i][0] != 255)
        return table[i][1];
    return -1;
}

//****************************************************************************
// @Function: analogReference
// @Brief: Sets the ADC reference voltage type. Only default (Varef = Vdda) is available.
//****************************************************************************
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

//****************************************************************************
// @Function: analogWriteResolution
// @Brief: Sets the resolution for analogWrite (PWM/DAC)
//****************************************************************************
void analogWriteResolution(int res) {
    if (res > ANALOG_MAX_WRITE_RESOLUTION) {
        _writeResolution = ANALOG_MAX_WRITE_RESOLUTION;
    } else if (res < ADC_MIN_RESOLUTION) {
        _writeResolution = ADC_MIN_RESOLUTION;
    } else {
        _writeResolution = res;
    }
    _writeMaximum = (uint16_t)(((uint32_t)1U << _writeResolution) - 1);
}

//****************************************************************************
// @Function: analogWrite
// @Brief: Outputs PWM or DAC value to the specified pin
//****************************************************************************
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
            pwm4->enabled = true;
        }
        if (value != 0)
            compare_reg = ((value + 1) * (pwm4->period_timer_val + 1)) >> _writeResolution;
        XMC_CCU4_SLICE_SetTimerCompareMatch(pwm4->slice, compare_reg);
        XMC_CCU4_EnableShadowTransfer(pwm4->ccu, (CCU4_GCSS_S0SE_Msk << (4 * pwm4->slice_num)));
        XMC_GPIO_SetMode(pwm4->port_pin.port, pwm4->port_pin.pin,
                         (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm4->port_mode));
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
            pwm8->enabled = true;
        }
        if (value != 0)
            compare_reg = ((value + 1) * (pwm8->period_timer_val + 1)) >> _writeResolution;
        XMC_CCU8_SLICE_SetTimerCompareMatch(pwm8->slice, pwm8->slice_channel, compare_reg);
        XMC_CCU8_EnableShadowTransfer(pwm8->ccu, CCU8_GCSS_S0SE_Msk << (4 * pwm8->slice_num));
        XMC_GPIO_SetMode(pwm8->port_pin.port, pwm8->port_pin.pin,
                         (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm8->port_mode));
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

//****************************************************************************
// @Function: wiring_analog_init
// @Brief: Initializes VADC and related analog resources (runs only once)
//****************************************************************************
void wiring_analog_init(void) {
    if (vadc_inited)
        return;
    vadc_inited = true;
    /* Initialization data of VADC Global resources */
    XMC_VADC_GLOBAL_CONFIG_t vadc_global_config;
    memset(&vadc_global_config, 0, sizeof(XMC_VADC_GLOBAL_CONFIG_t));
    vadc_global_config.class0.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;
    vadc_global_config.class1.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;

    XMC_VADC_BACKGROUND_CONFIG_t vadc_background_config = {0};

    /* Provide clock to VADC and initialize the VADC global registers. */
    XMC_VADC_GLOBAL_Init(VADC, &vadc_global_config);

#if (XMC_VADC_GROUP_AVAILABLE == 1U)
    // ADC grouping
    XMC_VADC_GROUP_CONFIG_t vadc_group_config;
    memset(&vadc_group_config, 0, sizeof(XMC_VADC_GROUP_CONFIG_t));
    vadc_group_config.class0.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;
    vadc_group_config.class1.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT;

    /* Initialize Group */
    XMC_VADC_GROUP_Init(VADC_G0, &vadc_group_config);
    XMC_VADC_GROUP_Init(VADC_G1, &vadc_group_config);

    /* Switch on the converter of the Group*/
    XMC_VADC_GROUP_SetPowerMode(VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL);
    XMC_VADC_GROUP_SetPowerMode(VADC_G1, XMC_VADC_GROUP_POWERMODE_NORMAL);

    #if (XMC_VADC_MAXIMUM_NUM_GROUPS > 2)
    /* Initialize Group */
    XMC_VADC_GROUP_Init(VADC_G2, &vadc_group_config);
    XMC_VADC_GROUP_Init(VADC_G3, &vadc_group_config);

    /* Switch on the converter of the Group*/
    XMC_VADC_GROUP_SetPowerMode(VADC_G2, XMC_VADC_GROUP_POWERMODE_NORMAL);
    XMC_VADC_GROUP_SetPowerMode(VADC_G3, XMC_VADC_GROUP_POWERMODE_NORMAL);
    #endif

#endif
    /* Calibrate the VADC. Make sure you do this after all used VADC groups
       are set to normal operation mode. */
    XMC_VADC_GLOBAL_StartupCalibration(VADC);

    /* Initialize the background source hardware. The gating mode is set to
       ignore to pass external triggers unconditionally.*/
    XMC_VADC_GLOBAL_BackgroundInit(VADC, &vadc_background_config);

    /* Dummy read of ALL analogue inputs to ensure ALL analogue channels are
       started in background scanning mode, otherwise first readings at least
       will always be zero on reading an analogue input. */
    for (uint8_t chan = 0; chan < NUM_ANALOG_INPUTS; chan++)
        analogRead(chan);

    // Additional Initialization of DAC starting here
}

//****************************************************************************
// @Function: analogReadResolution
// @Brief: Sets the resolution for analogRead (ADC)
//****************************************************************************
void analogReadResolution(int res) {
    if (res > ADC_MAX_READ_RESOLUTION) {
        _readResolution = ADC_MAX_READ_RESOLUTION;
    } else if (res < ADC_MIN_RESOLUTION) {
        _readResolution = ADC_MIN_RESOLUTION;
    } else {
        _readResolution = res;
    }
    _readMaximum = (uint16_t)(((uint32_t)1U << _readResolution) - 1);
}

//****************************************************************************
// @Function: analogRead
// @Brief: Reads the analog value from the specified pin
//****************************************************************************
int analogRead(pin_size_t pinNumber) {

    wiring_analog_init();
    uint32_t value;

    value = 0xFFFFFFFF;
    if (pinNumber < NUM_ANALOG_INPUTS) {
        XMC_ADC_t *adc = &mapping_adc[pinNumber];

#if (XMC_VADC_GROUP_AVAILABLE == 1U)
        // ADC grouping
        if (!(adc->enabled)) {
            XMC_VADC_CHANNEL_CONFIG_t vadc_gobal_channel_config;
            memset(&vadc_gobal_channel_config, 0, sizeof(XMC_VADC_CHANNEL_CONFIG_t));
            vadc_gobal_channel_config.input_class = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1;
            vadc_gobal_channel_config.result_reg_number = adc->result_reg_num;
            vadc_gobal_channel_config.alias_channel = XMC_VADC_CHANNEL_ALIAS_DISABLED;

            XMC_VADC_RESULT_CONFIG_t vadc_gobal_result_config = {.g_rcr = 0};
            /* Configure a channel belonging to the aforesaid conversion kernel */
            XMC_VADC_GROUP_ChannelInit(adc->group, adc->channel_num, &vadc_gobal_channel_config);
            /* Configure a result resource belonging to the aforesaid conversion kernel */
            XMC_VADC_GROUP_ResultInit(adc->group, adc->result_reg_num, &vadc_gobal_result_config);
            /* Add channel into the Background Request Source Channel Select Register */
            XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, (uint32_t)adc->group_num,
                                                           (uint32_t)adc->channel_num);
        }
        /* Start conversion manually using load event trigger*/
        XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);
        value = XMC_VADC_GROUP_GetResult(adc->group, adc->result_reg_num);
#else
        // XMC1100 no ADC grouping
        if (!(adc->enabled))
            /* Add a channel to the background source. */
            VADC->BRSSEL[ADC_CONVERSION_GROUP] = (uint32_t)(1U << adc->channel_num);
        // Generates conversion request
        XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);

        // Wait until conversion is ready
        while (((value = XMC_VADC_GLOBAL_GetDetailedResult(VADC)) & VADC_GLOBRES_VF_Msk) == 0u)
            ;
#endif
        value = ((value & VADC_GLOBRES_RESULT_Msk) >> (ADC_MAX_READ_RESOLUTION - _readResolution));
    }
    return value;
}

//****************************************************************************
// @Function: setAnalogWriteFrequency
// @Brief: Sets the frequency for analogWrite PWM.
// @Param: pin - The pin number
// @Param: frequency - Frequency in Hz
// @Return: -2 if invalid pin, -1 if invalid frequency, 0 on success
//****************************************************************************
int16_t setAnalogWriteFrequency(uint8_t pin, uint32_t frequency) {
    // Constants for return codes
    constexpr int16_t SUCCESS = 0;
    constexpr int16_t ERROR_INVALID_FREQUENCY = -1;
    constexpr int16_t ERROR_NO_PWM_RESOURCE = -2;
    constexpr uint32_t MAX_16BIT_TIMER_COUNT = 65536U;

    // Variables for computation
    XMC_CCU4_SLICE_PRESCALER_t prescaler = XMC_CCU4_SLICE_PRESCALER_1;
    uint16_t period;
    int16_t resource;

    // Check if frequency is within a valid range
    if (frequency >= PCLK) {
        return ERROR_INVALID_FREQUENCY; // Frequency too high, cannot configure
    }

    // Calculate prescaler value
    while (prescaler <= XMC_CCU4_SLICE_PRESCALER_32768) {
        if (frequency > (PCLK / ((1U << prescaler) * MAX_16BIT_TIMER_COUNT))) {
            break;
        }
        prescaler = static_cast<XMC_CCU4_SLICE_PRESCALER_t>(static_cast<int>(prescaler) + 1);
    }

    // Calculate timer period for 16-bit resolution
    period = (PCLK / ((1U << prescaler) * frequency)) - 1;

    // Attempt to configure PWM4
    resource = scan_map_table(mapping_pin_PWM4, pin);
    if (resource >= 0) {
        XMC_PWM4_t *pwm4 = &mapping_pwm4[resource];

        pwm4->prescaler = static_cast<XMC_CCU4_SLICE_PRESCALER_t>(prescaler);
        pwm4->period_timer_val = period;

        // If PWM is already enabled, disable and restart it
        if (pwm4->enabled == ENABLED) {
            pwm4->enabled = DISABLED;
            XMC_CCU4_SLICE_StartTimer(pwm4->slice);
        }

        return SUCCESS; // Configuration successful
    }

#if defined(CCU8V2) || defined(CCU8V1)
    // Attempt to configure PWM8
    resource = scan_map_table(mapping_pin_PWM8, pin);
    if (resource >= 0) {
        XMC_PWM8_t *pwm8 = &mapping_pwm8[resource];

        pwm8->prescaler = static_cast<XMC_CCU8_SLICE_PRESCALER_t>(prescaler);
        pwm8->period_timer_val = period;

        // If PWM is already enabled, disable and restart it
        if (pwm8->enabled == ENABLED) {
            pwm8->enabled = DISABLED;
            XMC_CCU8_SLICE_StartTimer(pwm8->slice);
        }

        return SUCCESS; // Configuration successful
    }
#endif

    // No matching PWM resource found
    return ERROR_NO_PWM_RESOURCE;
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
