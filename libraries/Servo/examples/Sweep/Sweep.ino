/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep

 modified 7 Jul 2020
 by Daniel Stuart <daniel.stuart@pucpr.edu.br>
 Added analogWriteResolution()
*/

#include <Servo.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
    analogWriteResolution(16); // sets PWM resolution to 16 bits, for better servo accuracy
    myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop() {
    int pos; // variable to store the servo position
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(20); // waits 20ms for the servo to reach the position
    }
    
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos); // tell servo to go to position in variable 'pos'
        delay(20); // waits 20ms for the servo to reach the position
    }
}
