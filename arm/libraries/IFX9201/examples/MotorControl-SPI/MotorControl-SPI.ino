/*
 IFX9201 H-Bridge Motor Control Example for the H-Bridge 2GO Evaluation Board

        SPI Mode only

    NOTE    In SPI mode Duty cycle CANNOT be changed and is fixed at 100%

        Serial Baud Rate 115200
*/
#include "Arduino.h"
#include "IFX9201.h"
#include <LED.h>

// IFX9201 Object
IFX9201 IFX9201_HBridge = IFX9201( );

// Create an LED object
LED Led;

void setup( )
{
  // Initialize digital pin LED1 as an output and OFF
  Led.Add( LED1 );
  Led.Off( LED1 );

  Serial.begin( 115200 );

  // Use SPI Mode with H-Bridge 2GO Evaluation Board
  // Change the CSN, DIR, PWM, and DIS pins to custom ones for other boards
  IFX9201_HBridge.begin( SPI, CSN, DIR, PWM, DIS );

  delay( 1000 );
}


void loop( )
{
  Serial.println( "Forwards" );
  IFX9201_HBridge.forwards( );
  delay( 1000 );

  Serial.println( "Stop" );
  IFX9201_HBridge.stop( );
  delay( 1000 );

  Serial.println( "Backwards" );
  IFX9201_HBridge.backwards( );
  delay( 1000 );

  Serial.println( "Stop" );
  IFX9201_HBridge.stop( );
  delay( 1000 );

  Led.Toggle( LED1 );
}
