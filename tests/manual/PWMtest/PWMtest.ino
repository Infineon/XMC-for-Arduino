/* PWM test (Duty) 
 Controlling TWO PWM positions using Fixed values
 Copyright (c) 2020 Paul Carpenter - PC Services.  All right reserved.

 Drive two PWMs for measurement purposes at fixed values

 If both LED1 and LED2 are permanently ON then an invalid pin for PWM has been
 attempted to be attached to a invalid pin

 Wiring
    Default PWM pins are 3 and 4

    Some Board variant PWM Pins
    XMC1100 Boot Kit    3, 4, 6, 9
    XMC1100 XMC2Go      8, 3, 2, 1
    XMC1300 Boot Kit    31, 26, 32, 33
    XMC4700 Relax       3, 10, 11, 95, 72, 96, 63, 36, 78, 90, 91,
                        5,  6, 9, 53, 39, 64, 38, 68, 79, 83, 82, 81
 */
#include <LED.h>

// Adjust the following defines to match your setup
// Pins for Servos and pot
//#define PWM_A_PIN 3
//#define PWM_B_PIN 4
// XMC1300 Boot Kit pins
#define PWM_A_PIN 31
#define PWM_B_PIN 26

#define RESOLUTION  16
#define REFRESH_FREQUENCY   50


LED Led;        /* Create an LED object */

int val;


void setup( )
{
Led.Add( LED1 );            // Configure the LEDs
Led.Add( LED2 );
Led.Off( LED1 );            // Set default state of LEDs
Led.Off( LED2 );

// Setup the PWM pins to the servo objects
analogWriteResolution( RESOLUTION );
val = 0;
if( setAnalogWriteFrequency( PWM_A_PIN, REFRESH_FREQUENCY ) < 0  )
  val++;
else
  if( setAnalogWriteFrequency( PWM_B_PIN, REFRESH_FREQUENCY ) < 0 ) 
    val++;

if( val )           // Invalid pin trap for non-PWM pin
  {
  Led.On( LED1 );
  Led.On( LED2 );
  while( 1 );       // Stick in error loop
  }

analogWrite( PWM_A_PIN, 4915 );             // Duty for mid (1500) = 4915
analogWrite( PWM_B_PIN, 1782 );             // Duty for Min (544) = 1782
}


void loop( )
{
// Do nothing loop}
