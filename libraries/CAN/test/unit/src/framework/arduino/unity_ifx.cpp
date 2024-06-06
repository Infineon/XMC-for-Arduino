// std includes

// Arduino includes
#include <Arduino.h>


// test includes
#include "unity_ifx.h"


extern "C" {  
    // Method used by Unity to output a single character 
    void putCharacter(char c) {
        Serial.print(c);
        Serial.flush();
    }

    // Method used by Unity to flush the output
    void flushCharacter() {
        Serial.flush();
    }
}
