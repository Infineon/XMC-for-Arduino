/*
  Simple die temperature measurement for XMC devices
  Demonstrates the measure temperature of die using sensor.
  05 July 2017
  
  Amended July 2020 to allow negative die temperature
  
  Amended February 2020 in line with PR for XMC_BOARD tidy up

  Amended April 2018 Paul Carpenter, PC Services
  Needs first serial port to display results at 115,200 baud

  Add sign on message
  Take initial reading to avoid high reading as first reading
  Make board agnostic
  Simplify code
 */
#include <DeviceControlXMC.h>

// For library macro printing
#define str(x)  Serial.println( #x )
#define str1(x) str(x)

XMCClass devCtrl;

int32_t temperature = 0;


void setup( )
{
Serial.begin( 115200 );
delay( 100 );
Serial.println( "XMC Die Temperature in Degree C Demo  (V2.0)" );
Serial.print( "Running on " );
str1( XMC_BOARD );
// dummy read to ensure first value which may be erroneous is ignored
temperature = devCtrl.getTemperature();
}


void loop( )
{
delay( 1000 );

/* If UC_FAMILY = XMC4 you can also calibrate temperature for finer measurements */
temperature = devCtrl.getTemperature();

Serial.print( "Die Temperature\t" );
Serial.println( temperature );
}
