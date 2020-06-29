/* Ultrasonic distance sensor example - Better Version
   Based on public domain code from
   http://www.pcserviceselectronics.co.uk/arduino/Ultrasonic/betterecho.php

   Modified to use on board LED library to work better over all boards
   Paul Carpenter, PC Services
   22-July-2018

   Paul Carpenter, PC Services
   25-April-2018

   Uses HC-SR04 four pin ultrasonic sensor to continuously output distances
   found when in range (every second).

   Range valid readings are - 4 cm to 5 m.

   Results WHEN valid output onto serial port at 115,200 baud

   Attached hardware
        LEDs are for XMC boards on board LEDs - LED1 and LED2
        HC-SR04 5V and GND connected to pins on board
          default Trigger pin connected to pin 4
                  Echo pin connected to pin 5

   Use TWO LEDs to indicate on board mainly error conditions as follows -

    Both LEDs ON when program starts and any other time for no start of echo
    received (probably bad wiring or faulty unit) on start up also serial port
    error string

    Lights LED1 when No Reading received or out of range

    Lights LED2 when too close (less than 5 cm)

   Works on principle sound travels at 343 m/s in dry air at 20 deg C

   So time per cm is 29.15452 micro seconds / cm

   For round trip (there and back)  58.30904 micro seconds / cm

   In order to reduce code size and execution time values are kept as integers
   and factor of 58 to calculate distances
*/
/* For on board LEDs */
#include <LED.h>

/* Create an LED object */
LED Led;

/* Pin definitions */
#define echopin    4
#define trigpin    5
/* LED on board */
#define noReading  LED1
#define closeled   LED2

/* time between readings in ms
   Readings below 20ms interval could have residual echo issues */
#define INTERVAL    50

/* Scale factor round trip micro seconds per cm */
#define SCALE_CM    58

/* Timeout for distance sensing rather than 1 second in us
   30000 approximately  5m */
#define MAX_ECHO    30000
#define MIN_ECHO    (3 * SCALE_CM)

/* Timeout for start of ECHO pulse being received in us */
#define MAX_START_ECHO  1000

/* Limits for application ranges in cm */
#define MIN_RANGE   4
#define MAX_RANGE   500

#define MAX_ERROR   10

/* calculated distance in centimetres */
unsigned long distance;
unsigned long echotime;
/* time values to determine WHEN to do a ping */
unsigned long next_time, new_time;


/* Distance sensor function to get echo time
   Note most ultrasonic distance sensors are only usable beyond 3 cm
   So usable range is 3 * SCALE_CM to MAX_ECHO, therefore anything below
   3 * SCALE_CM should be treated as error

   Returns echo time in microseconds
        Maximum MAX_ECHO
        Minimum 3 * SCALE_CM    (minimum usable)
   error codes
        Error   2   Echo HIGH before start
        Error   1   Echo did not start
        Error   0   NO ECHO (Timeout)

   Timeout for measurements set by MAX_ECHO
*/
unsigned long GetEchoTime( )
{
unsigned long start_time;
unsigned long end_time;

/* check Echo if high return error */
if( digitalRead( echopin ) )
  return( 2 );

/* note start time */
start_time = micros( );

/* send the trigger pulse */
digitalWrite( trigpin, HIGH );
delayMicroseconds( 10 );
digitalWrite( trigpin, LOW );

/* Set timeout for start of echo pulse */
end_time = start_time + MAX_START_ECHO;

/* check ECHO pin goes high within MAX_START_ECHO
   if not return error of 1  */
while( !digitalRead( echopin ) )
   if( micros( ) > end_time )
     return 1;

/* Check for Length of echo occurred or timeout */
start_time = micros( );
end_time = start_time + MAX_ECHO;
while( digitalRead( echopin ) )
   if( micros( ) > end_time )
     return 0;
end_time = micros( );

/* Return time  */
return( end_time - start_time );
}


void setup( )
{
/* set time from reset */
next_time = INTERVAL;

Serial.begin( 115200 );

/* Configure pins and ensure trigger is OFF */
pinMode( trigpin, OUTPUT );
digitalWrite( trigpin, LOW );
pinMode( echopin, INPUT );

/* Configure LED drive and both LEDs On at start up */
Led.Add( noReading );
Led.Add( closeled );
Led.On( noReading );
Led.On( closeled );

/* Send signon message */
Serial.println( "PC Services - Better Range test" );

/* Do test reading to check if unit connected */
distance = GetEchoTime( );
if( distance > 0 && distance <= 10 )
  {
  Serial.println( "No unit found - Error = " );
  Serial.println( distance );
  }
}


void loop( )
{
new_time = millis( );           // check if to run this time
if( new_time >= next_time )
  {
  /* Turn LEDs Off */
  Led.Off( noReading );
  Led.Off( closeled );
  
  /* Calculate distance */
  echotime = GetEchoTime( );
  /* only scale valid readings 0 is timeout or 1 is no echo
     realistically minimum accurate or physical range is 3cm */
  if( echotime > MAX_ERROR )
    {
    // Valid number convert to cm
    distance = echotime / SCALE_CM;
    if( distance <= MAX_RANGE || distance >= MIN_RANGE )
      {
      Serial.write( ' ' );
      Serial.println( int( distance ) );       // In range output distance
      }
    }
  else
    {  // Display errors
    Serial.print( "Error\t" );
    Serial.println( int( distance ) );
    distance = 0;
    }

  /* catch errors on LEDs */
  if( distance > MAX_RANGE || echotime <= MAX_ERROR )
    {
    Led.On( noReading );            // Range error too large
    if( echotime <= MAX_ERROR )
      Led.On( closeled );           // Light 2nd LED for timeout etc error
    }
  if( distance < MIN_RANGE )
    Led.On( closeled );             // Range too close

  next_time = new_time + INTERVAL;       // save next time to run
  }
}
