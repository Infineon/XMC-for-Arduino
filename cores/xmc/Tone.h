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
};

extern Tone inst_Tone;

#endif
#endif