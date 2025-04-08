#include "Arduino.h"
int ledPin = 22;  // LED connected to digital pin 13
    int inPin = 25;    // pushbutton connected to digital pin 7
    int val;      // variable to store the read value

    void setup() {
      pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
      pinMode(inPin, INPUT_PULLDOWN);    // sets the digital pin 7 as input
    }

    void loop() {
      val = digitalRead(inPin);   // read the input pin
      digitalWrite(ledPin, val);  // sets the LED to the button's value
    }
    