#include "Arduino.h"

#define MIN_MICROS  10
#define MAX_MICROS  150
int i;
uint32_t old_time, new_time, calltime;


void setup( )
{
delay( 100 );
Serial.begin( 115200, SERIAL_8N1 );
Serial.println( "Time tests for microsecond delays" );
Serial.println( "Delay\tOld\t\tNew\t\tDifference" );
i = MIN_MICROS;
delay( 200 );
}

void loop()
{
old_time = micros();
delayMicroseconds( i );
new_time = micros();
Serial.print( i );
Serial.write( '\t' );
Serial.print( old_time );
Serial.write( '\t' );
Serial.print( new_time );
Serial.write( '\t' );
Serial.println( new_time - old_time );
if( ++i >= MAX_MICROS )
  {
  i = MIN_MICROS;
  delay( 5000 );
  }
else  
  // pause between outputs   
  delay( 5 );
}
