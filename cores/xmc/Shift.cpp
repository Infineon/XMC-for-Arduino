#include "Arduino.h"

void shiftOut(pin_size_t ulDataPin, pin_size_t ulClockPin, BitOrder ulBitOrder, uint8_t ulVal) {
    uint8_t i;

    for (i = 0; i < 8; i++) {
        if (ulBitOrder == LSBFIRST) {
            digitalWrite(ulDataPin, !!(ulVal & (1 << i)));
        } else {
            digitalWrite(ulDataPin, !!(ulVal & (1 << (7 - i))));
        }

        digitalWrite(ulClockPin, HIGH);
        digitalWrite(ulClockPin, LOW);
    }
}

uint8_t shiftIn(pin_size_t ulDataPin, pin_size_t ulClockPin, BitOrder ulBitOrder) {
    uint8_t value = 0;
    uint8_t i;

    for (i = 0; i < 8; ++i) {
        digitalWrite(ulClockPin, HIGH);

        if (ulBitOrder == LSBFIRST) {
            value |= digitalRead(ulDataPin) << i;
        } else {
            value |= digitalRead(ulDataPin) << (7 - i);
        }

        digitalWrite(ulClockPin, LOW);
    }

    return value;
}
