#include "Arduino.h"

XMC_PWM4_t *pwm4;

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
            // count pulses for stop the timer once reached required pulses
            // if (duration > 0) {
            //     uint32_t required_pulses = frequency * duration / 1000;
            //     for (uint32_t i = 0; i < required_pulses; i++) {
            //         while (
            //             !XMC_CCU4_SLICE_GetEvent(pwm4->slice,
            //             XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH)) {
            //         }
            //         XMC_CCU4_SLICE_ClearEvent(pwm4->slice, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
            //     }
            //     XMC_CCU4_SLICE_StopTimer(pwm4->slice);
            // }
            //    if(duration >0) {
            //     unsigned long start_time = millis();
            //     while(millis() - start_time < duration) {
            //         delay(1);
            //     }
            //     XMC_CCU4_SLICE_StopTimer(pwm4->slice);
            // }
            if (duration > 0) {
                configureTimerInterrupt(duration);
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
            // if (duration > 0) {
            //     uint32_t required_pulses = frequency * duration / 1000;
            //     for (uint32_t i = 0; i < required_pulses; i++) {
            //         while (
            //             !XMC_CCU8_SLICE_GetEvent(pwm8->slice,
            //             XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH)) {
            //         }
            //         XMC_CCU8_SLICE_ClearEvent(pwm8->slice, XMC_CCU8_SLICE_IRQ_ID_PERIOD_MATCH);
            //     }
            //     XMC_CCU8_SLICE_StopTimer(pwm8->slice);
            // }
            // if(duration >0) {
            //     unsigned long start_time = millis();
            //     while(millis() - start_time < duration) {
            //         delay(1);
            //     }
            //     XMC_CCU8_SLICE_StopTimer(pwm8->slice);
            // }
            if (duration > 0) {
                configureTimerInterrupt(duration);
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
            Serial.println("pin_index");
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
        }
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

    void configureTimerInterrupt(unsigned long duration_ms) {
        XMC_CCU4_SLICE_COMPARE_CONFIG_t timer_config;
        memset(&timer_config, 0, sizeof(timer_config));
        timer_config.prescaler_initval = XMC_CCU4_SLICE_PRESCALER_64;
        timer_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW;

        XMC_CCU4_SLICE_CompareInit(CCU40_CC42, &timer_config);

        // Calculate period for the timer based on the duration
        uint32_t timer_ticks = (PCLK / 64) * duration_ms / 1000;
        XMC_CCU4_SLICE_SetTimerPeriodMatch(CCU40_CC42, timer_ticks);

        XMC_CCU4_SLICE_EnableEvent(CCU40_CC42, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
        XMC_CCU4_SLICE_SetInterruptNode(CCU40_CC42, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH,
                                        XMC_CCU4_SLICE_SR_ID_0);

        // Enable the NVIC interrupt
        NVIC_EnableIRQ(CCU40_2_IRQn);

        // Start the timer
        XMC_CCU4_SLICE_StartTimer(CCU40_CC42);
    }
};

static Tone inst_Tone;

void tone(pin_size_t pin, unsigned int frequency) { inst_Tone.play(pin, frequency); }

void tone(pin_size_t pin, unsigned int frequency, unsigned long duration) {
    inst_Tone.play(pin, frequency, duration);
}

void noTone(pin_size_t pin) { inst_Tone.stop(pin); }
#ifdef __cplusplus
extern "C" {
#endif
void CCU40_2_IRQHandler(void) {
    XMC_CCU4_SLICE_StopTimer(CCU40_CC42);
    XMC_CCU4_SLICE_ClearEvent(CCU40_CC42, XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
}
#ifdef __cplusplus
}
#endif
