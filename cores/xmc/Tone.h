#ifndef _WIRING_TONE_
#define _WIRING_TONE_

//****************************************************************************
// @External Prototypes
//****************************************************************************
void digitalToggle(uint8_t pin);
#ifdef __cplusplus
extern "C" {
#endif
extern int tone_irq_action(int, int16_t);
#ifdef __cplusplus
}
#endif

#endif /* _WIRING_TONE_ */