#ifndef TONE_H
#define TONE_H

#include "Arduino.h"
// Expose C-compatible declarations for wiring_time.c
#ifdef __cplusplus
extern "C" {
#endif

// C-compatible function declaration for the callback
int tone_irq_action(int taskId, int16_t param);

#ifdef __cplusplus
} // End of extern "C"

class Tone {
public:
    Tone();
    ~Tone();

    void play(pin_size_t pin, unsigned int frequency);
    void play(pin_size_t pin, unsigned int frequency, unsigned long duration);
    void stop(pin_size_t pin);

    static int tone_irq_action(int taskId, int16_t param);

private:
    void configureTone(pin_size_t pin, unsigned int frequency);
    void scheduleToneTask(pin_size_t pin, unsigned long duration);
    int scanMapTable(const uint8_t table[][2], pin_size_t pin);

    static XMC_CCU4_SLICE_t *active_pwm4_slice; // Active CCU4 slice
    static XMC_CCU4_MODULE_t *active_pwm4_ccu;  // Active CCU4 module
    #if defined(CCU8V2) || defined(CCU8V1) || defined(CCU8V3)
    static XMC_CCU8_MODULE_t *active_pwm8_ccu;  // Active CCU8 module
    static XMC_CCU8_SLICE_t *active_pwm8_slice; // Active CCU8 slice
    #endif

    static uint8_t slice_number_ccu4;
    static uint8_t slice_number_ccu8;
};

extern Tone inst_Tone;

#endif
#endif