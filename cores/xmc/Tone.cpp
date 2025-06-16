#include "Arduino.h"

XMC_PWM4_t *pwm4;
static volatile bool timer_interrupt_ccu4 =  false;
static volatile bool timer_interrupt_ccu8 =  false;

#ifdef __cplusplus
extern "C" {
#endif
void CCU43_0_IRQHandler(void) {

    XMC_CCU4_SLICE_StopTimer(CCU43_CC40);
    XMC_CCU4_SLICE_ClearEvent(CCU43_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
    timer_interrupt_ccu4 = true;

}

void CCU81_0_IRQHandler(void) {
  XMC_CCU8_SLICE_StopTimer(CCU81_CC80);
    XMC_CCU8_SLICE_ClearEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
    timer_interrupt_ccu8 = true;
}
#ifdef __cplusplus
}
#endif

class Tone {
public:
    Tone() {}

    ~Tone() {}

    void play(pin_size_t pin, unsigned int frequency) { play(pin, frequency, 0); }

    void play(pin_size_t pin, unsigned int frequency, unsigned long duration) {
        int pin_index;
        if ((pin_index = scanMapTable(mapping_pin_PWM4, pin)) >= 0) {
            XMC_PWM4_t *pwm4 = &mapping_pwm4[pin_index];
            configureTone(pin, frequency);
            XMC_GPIO_SetMode(pwm4->port_pin.port, pwm4->port_pin.pin,
                             (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm4->port_mode));
            XMC_CCU4_SLICE_StartTimer(pwm4->slice);
            if(duration >0) {
                configureTimerInterrupt(duration);
                if(timer_interrupt_ccu4 == true)
                {
                    XMC_CCU4_SLICE_StopTimer(pwm4->slice);
                    timer_interrupt_ccu4 = false;

                }
            }
        }
#if defined(CCU8V2) || defined(CCU8V1)
        else if ((pin_index = scanMapTable(mapping_pin_PWM8, pin)) >= 0) {
            XMC_PWM8_t *pwm8 = &mapping_pwm8[pin_index];
            configureTone(pin, frequency);
            XMC_GPIO_SetMode(pwm8->port_pin.port, pwm8->port_pin.pin,
                             (XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | pwm8->port_mode));
            XMC_CCU8_SLICE_StartTimer(pwm8->slice);
            // calculate pulses
          if(duration >0) {
                configureTimerInterrupt(duration);
                if(timer_interrupt_ccu8 == true)
                {
                    XMC_CCU8_SLICE_StopTimer(pwm8->slice);
                    timer_interrupt_ccu8 = false;

                }
            }
        }
#endif

    }

    void stop(pin_size_t pin) {
        int pin_index;
        if ((pin_index = scanMapTable(mapping_pin_PWM4, pin)) >= 0) {
            XMC_PWM4_t *_XMC_pwm4_config = &mapping_pwm4[pin_index];
            XMC_CCU4_SLICE_StopTimer(_XMC_pwm4_config->slice); // stop the timer
            XMC_CCU4_DisableClock(_XMC_pwm4_config->ccu,
                                  _XMC_pwm4_config->slice_num); // Disable the clock
        }
#if defined(CCU8V2) || defined(CCU8V1)
        else if ((pin_index = scanMapTable(mapping_pin_PWM8, pin)) >= 0) {
            XMC_PWM8_t *pwm8 = &mapping_pwm8[pin_index];
            XMC_CCU8_SLICE_StopTimer(pwm8->slice);             // stop the timer
            XMC_CCU8_DisableClock(pwm8->ccu, pwm8->slice_num); // Disable the clock
        }
#endif
    }

private:
    void configureTone(pin_size_t pin, unsigned int frequency) {
        int pin_index;
        timer_interrupt_ccu4 = false;

        if ((pin_index = scanMapTable(mapping_pin_PWM4, pin)) >= 0) {
            XMC_PWM4_t *pwm4 = &mapping_pwm4[pin_index];
            XMC_CCU4_SLICE_COMPARE_CONFIG_t compare_config;
            memset(&compare_config, 0, sizeof(compare_config));
            compare_config.prescaler_initval = pwm4->prescaler;
            compare_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;

            XMC_CCU4_Init(pwm4->ccu, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
            XMC_CCU4_SLICE_CompareInit(pwm4->slice, &compare_config);
            XMC_CCU4_EnableClock(pwm4->ccu, pwm4->slice_num);

            uint32_t period = (PCLK / 64) / frequency; // calculate period
            XMC_CCU4_SLICE_SetTimerPeriodMatch(pwm4->slice, period);
            XMC_CCU4_SLICE_SetTimerCompareMatch(pwm4->slice, period / 2);

            XMC_CCU4_EnableShadowTransfer(
                pwm4->ccu, XMC_CCU4_SHADOW_TRANSFER_SLICE_0 | XMC_CCU4_SHADOW_TRANSFER_SLICE_2 |
                               XMC_CCU4_SHADOW_TRANSFER_SLICE_3 | XMC_CCU4_SHADOW_TRANSFER_SLICE_1);
        }
#if defined(CCU8V2) || defined(CCU8V1)
        else if ((pin_index = scanMapTable(mapping_pin_PWM8, pin)) >= 0) {
            XMC_PWM8_t *pwm8 = &mapping_pwm8[pin_index];
            XMC_CCU8_SLICE_COMPARE_CONFIG_t compare_config;
            memset(&compare_config, 0, sizeof(compare_config));

            compare_config.prescaler_initval = pwm8->prescaler;
            compare_config.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
            compare_config.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
            compare_config.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
            compare_config.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;

            XMC_CCU8_Init(pwm8->ccu, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
            XMC_CCU8_SLICE_CompareInit(pwm8->slice, &compare_config);
            XMC_CCU8_EnableClock(pwm8->ccu, pwm8->slice_num);

            uint32_t period = (PCLK / 64) / frequency; // calculate period
            XMC_CCU8_SLICE_SetTimerPeriodMatch(pwm8->slice, period);
            XMC_CCU8_SLICE_SetTimerCompareMatch(pwm8->slice, pwm8->slice_channel, period / 2);

            XMC_CCU8_EnableShadowTransfer(
                pwm8->ccu, XMC_CCU8_SHADOW_TRANSFER_SLICE_0 | XMC_CCU8_SHADOW_TRANSFER_SLICE_2 |
                               XMC_CCU8_SHADOW_TRANSFER_SLICE_3 | XMC_CCU8_SHADOW_TRANSFER_SLICE_1);
                    timer_interrupt_ccu8 = false;

        }
#endif
    }

    void configureTimerInterrupt(unsigned long duration_ms) {
        timer_interrupt_ccu4 = false;
        XMC_CCU4_Init(CCU43, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
        XMC_CCU4_SLICE_COMPARE_CONFIG_t timer_config;
            timer_config.timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA;
            timer_config.monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_SINGLE;
            timer_config.prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL;
            timer_config.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_32768;
            timer_config.float_limit = XMC_CCU4_SLICE_PRESCALER_32768;
            timer_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
        XMC_CCU4_SLICE_CompareInit(CCU43_CC40, &timer_config);

        // Calculate period for the timer based on the duration
        uint32_t timer_ticks = (PCLK / 32768) * duration_ms / 1000;
        XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU43_CC40, timer_ticks);
        XMC_CCU4_SetMultiChannelShadowTransferMode(CCU43, XMC_CCU4_MULTI_CHANNEL_SHADOW_TRANSFER_SW_SLICE0);
        XMC_CCU4_EnableShadowTransfer(CCU43,XMC_CCU4_SHADOW_TRANSFER_SLICE_0);
        XMC_CCU4_SLICE_SetInterruptNode(CCU43_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU4_SLICE_SR_ID_0);
        XMC_CCU4_SLICE_EnableEvent(CCU43_CC40, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
        XMC_CCU4_EnableClock(CCU43, 0);

        // Enable the NVIC interrupt
        XMC_CCU4_SLICE_SetTimerValue(CCU43_CC40, 0U);

        // Start the timer
        XMC_CCU4_SLICE_StartTimer(CCU43_CC40);
        NVIC_SetPriority(CCU43_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));

        NVIC_EnableIRQ(CCU43_0_IRQn);

    #if defined(CCU8V2) || defined(CCU8V1)
        timer_interrupt_ccu8 = false;
        XMC_CCU8_Init(CCU81, XMC_CCU8_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
        XMC_CCU8_SLICE_COMPARE_CONFIG_t timer_config_ccu8;
            timer_config_ccu8.timer_mode = XMC_CCU8_SLICE_TIMER_COUNT_MODE_EA;
            timer_config_ccu8.monoshot = XMC_CCU8_SLICE_TIMER_REPEAT_MODE_SINGLE;
            timer_config_ccu8.prescaler_mode = XMC_CCU8_SLICE_PRESCALER_MODE_NORMAL;
            timer_config_ccu8.prescaler_initval = XMC_CCU8_SLICE_PRESCALER_32768;
            timer_config_ccu8.float_limit = XMC_CCU8_SLICE_PRESCALER_32768;
            timer_config_ccu8.passive_level_out0 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
            timer_config_ccu8.passive_level_out1 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
            timer_config_ccu8.passive_level_out2 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;
            timer_config_ccu8.passive_level_out3 = XMC_CCU8_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;

        XMC_CCU8_SLICE_CompareInit(CCU81_CC80, &timer_config_ccu8);

        // Calculate period for the timer based on the duration
        uint32_t timer_ticks_ccu8 = (PCLK / 32768) * duration_ms / 1000;
        XMC_CCU8_SLICE_SetTimerPeriodMatch(CCU81_CC80, timer_ticks_ccu8);
        XMC_CCU8_SetMultiChannelShadowTransferMode(CCU81, XMC_CCU8_MULTI_CHANNEL_SHADOW_TRANSFER_SW_SLICE0);
        XMC_CCU8_EnableShadowTransfer(CCU81,XMC_CCU8_SHADOW_TRANSFER_SLICE_0);
        XMC_CCU8_SLICE_SetInterruptNode(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH, XMC_CCU8_SLICE_SR_ID_0);
        XMC_CCU8_SLICE_EnableEvent(CCU81_CC80, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
        XMC_CCU8_EnableClock(CCU81, 0);

        // Enable the NVIC interrupt
        XMC_CCU8_SLICE_SetTimerValue(CCU81_CC80, 0U);

        // Start the timer
        XMC_CCU8_SLICE_StartTimer(CCU81_CC80);
        NVIC_SetPriority(CCU81_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));

        NVIC_EnableIRQ(CCU81_0_IRQn);
    #endif
    }

    // Scan the pwm pin mapping table
    int16_t scanMapTable(const uint8_t table[][2], uint8_t pin) {
        int16_t i = 0;
        while (table[i][0] != 255) {
            if (table[i][0] == pin) {
                return table[i][1];
            }
            i++;
        }
        return -1;
    }
};

static Tone inst_Tone;

void tone(pin_size_t pin, unsigned int frequency) { inst_Tone.play(pin, frequency); }

void tone(pin_size_t pin, unsigned int frequency, unsigned long duration) {
    inst_Tone.play(pin, frequency, duration);
}

void noTone(pin_size_t pin) { inst_Tone.stop(pin); }

