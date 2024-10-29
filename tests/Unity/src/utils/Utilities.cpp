
// std includes
#include <stdint.h>

// Arduino includes
#include <Arduino.h>

// project cpp includes

void printArray(const char *title, volatile uint8_t *data, uint8_t quantity) {
    Serial.print(title);
    Serial.print(" : [");

    for (uint8_t i = 0; i < quantity; ++i) {
        Serial.print(data[i]);
        Serial.print(", ");
    }

    Serial.println("]");
    Serial.flush();
}
