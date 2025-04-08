#include "Arduino.h"
int val = 0;
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); 
    pinMode(23, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(23, val);
    delay(1000);
    digitalWrite(LED_BUILTIN, 1);
    digitalWrite(23, 1);
    delay(1000);
}