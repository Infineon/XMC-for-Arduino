/* PulseIn test
 *  Requirements
 *   -  External Waveform generator set to produce at least 100 Hz square wave of
 *      variable duty cycle down to On for a couple of microseconds, max 10ms.
 *   -  Oscilloscope to check timings being measured in software
 *   -  Serial port at 115,200 baud
 *   -  Default pin 4 for the TTL input
 *   
 *   Operation
 *     Configures inputs
 *     Loops
 *       Get 10 PulseIn readings to array
 *       Works out statistics on readings
 *       Prints on serial port statistics table
 *       waits 2 seconds
 *
 * Statistics show Minimum, Maximum, Average measurements (of valid readings)
 *          Number of valid and timeout readings
 *
 *  Due to asynchronous nature of waveform generator to software the important
 *  factors to watch on statistics are how many timeouts occur and the average 
 *  reading. In tests using a 100 Hz to 10 kHz frequency average readings were 
 *  noted as being within +/- 1 microsecond from 10 to 50 micros second pulses.
 */
#include <Arduino.h>

// Pin to use for input
#define PIN 4

uint32_t readings[ 10 ];
uint32_t min, max, avg;
int     count, timeouts;


void setup()
{
Serial.begin( 115200 );

/* Configure pins and ensure trigger is OFF */
pinMode( PIN, INPUT );
delay( 50 );
/* Send signon message */
Serial.println( "PC Services - PulseIn accuracy test" );
}


void loop()
{
// Reset statistics    
min = 100000;
avg = 0;
timeouts = 0;
max = 0;

// get readings and basic stats
for( count = 0; count < 10; count++ )
   {
   readings[ count ] = pulseIn( PIN, HIGH, 12000 );
   if( readings[ count ] == 0 )
     timeouts++;
   else
     {
     if( readings[ count ] < min )
       min = readings[ count ];
     if( readings[ count ] > max )
       max = readings[ count ];
     }
   }

// Calculate statistics for non-timeout readings
for( count = 0; count < 10; count++ )
   if( readings[ count ] )
     avg += readings[ count ];
avg /= 10 - timeouts;

// display statistics
Serial.print( "\nValid Readings\t" );
Serial.println( 10 - timeouts );
Serial.print( "Timeouts\t" );
Serial.println( timeouts );
Serial.print( "Minimum\t\t" );
Serial.println( min );
Serial.print( "Maximum\t\t" );
Serial.println( max );
Serial.print( "Valid Average\t" );
Serial.println( avg );

// Pause before next set
delay( 2000 );
}
