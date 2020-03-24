/* Ultrasonic distance sensor example Simple version
   Based on public domain code from
   http://www.pcserviceselectronics.co.uk/arduino/Ultrasonic/simpleecho.php

   Paul Carpenter, PC Services
   25-April-2018

   Uses HC-SR04 four pin ultrasonic sensor to continuously output
   distances found when in range (every second).

   Results output onto serial port at 115,200 baud

   Attached hardware
        HC-SR04 5V and GND connected to pins on board
          default Trigger pin connected to pin 5
                  Echo pin connected to pin 4

   Works on principle sound travels at 343 m/s in dry air at 20 deg C

   So time per cm is 29.15452 micro seconds / cm

   For round trip (there and back)  58.30904 micro seconds / cm

   In order to reduce code size and execution time values are kept as integers
   and factor of 58 to calculate distances
*/

/* Pin definitions */
#define echopin     4
#define trigpin     5

/* time between readings in ms
   Readings below 20ms interval could have residual echo issues */
#define INTERVAL    50

/* Timeout for distance sensing rather than 1 second
   Equivalent to about 5m */
#define MAX_ECHO    30000

/* Scale factor round trip micro seconds per cm */
#define SCALE_CM    58

/* calculated distance in centimetres */
unsigned long distance;

void setup( )
{
Serial.begin( 115200 );

/* Configure pins and ensure trigger is OFF */
pinMode( trigpin, OUTPUT );
digitalWrite( trigpin, LOW );       // Set trig pin LOW here NOT later
pinMode( echopin, INPUT );
delay( 50 );
/* Send signon message */
Serial.println( "PC Services - Simple Range test" );
}


void loop( )
{
delay( INTERVAL );  // loop delay time between readings

// Trigger Ultrasonic pulse out
digitalWrite( trigpin, HIGH );
delayMicroseconds( 10 );
digitalWrite( trigpin, LOW );

/* echo time in microseconds
    Maximum  MAX_ECHO
    Minimum  0      (NO ECHO)

Timeout for measurements set by MAX_ECHO define */
distance = pulseIn( echopin, HIGH, MAX_ECHO );

/* Calculate distance only for VALID readings 0 is no echo or timeout */
if( distance )
  distance /= SCALE_CM;
else
  Serial.print( "Error\t" );
Serial.write( ' ' );
Serial.println( (int)( distance ) );  // Output distance in whole cm
}
