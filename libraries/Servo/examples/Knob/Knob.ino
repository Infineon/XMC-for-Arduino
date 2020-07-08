/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob

 modified 7 Jul 2020
 by Daniel Stuart <daniel.stuart@pucpr.edu.br>
 Added analogWriteResolution()
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

const uint8_t potpin = 0;  // analog pin used to connect the potentiometer
uint16_t val;    // variable to read the value from the analog pin

void setup() {
    analogWriteResolution(16); // sets PWM resolution to 16 bits, for better servo accuracy
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
    val = analogRead(potpin); // reads the value of the potentiometer
    val = map(val, 0, getAnalogReadMaximum(), 0, 180); // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val); // sets the servo position according to the scaled value
    delay(20); // waits for the servo to get there
}
