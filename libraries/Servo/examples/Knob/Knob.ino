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

#define RESOLUTION 16 // sets PWM resolution to 16 bits (max value: 2^16 - 1 = 65535)

Servo myservo;  // create servo object to control a servo

const uint8_t potpin = 0;  // analog pin used to connect the potentiometer
const uint16_t maxAnalog = (1 << RESOLUTION) - 1; //Uses bitshift for efficient compile-time calculation

uint16_t val;    // variable to read the value from the analog pin

void setup() {
  analogWriteResolution(RESOLUTION); //Needed for better accuracy when driving a Servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 2^RESOLUTION - 1)
  val = map(val, 0, maxAnalog, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
