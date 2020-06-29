/*  Two Port Multiple Serial test  XMC version
  Receives from the main serial port, sends to serial port 1.
  Receives from serial port 1, sends to the main serial (Serial 0).

  This example works only with boards with more than one serial like XMC4700 
  or others as 2 serial ports.

  The circuit:
  - Loopback RX to TX on Serial port 1 or another device
  - Serial Monitor open on Serial port 0

  In Loopback anything sent from Serial monitor or terminal window is echoed back
  after going via Serial 1. LEDs flash as data is received
    LED1 for Serial1
    LED2 for Serial (0)

  Created 8 Feb 2020  by Paul Carpenter

  This example code is in the public domain.
  Use at your OWN risk, supplied as is
*/
#if ( NUM_SERIAL < 2 )
  #error "Current Board does not support 2 serial ports"
#endif


void setup( )
{
// initialize both serial ports:
Serial.begin( 115200 );
Serial1.begin( 115200 );
pinMode( LED1, OUTPUT );
pinMode( LED2, OUTPUT );
Serial.println( "XMC example for boards with 2 serial ports" );
}

void loop( )
{
int inByte;

// read from port 1, send to port 0:
if( Serial1.available( ) )
  {
  inByte = Serial1.read( );
  Serial.write( inByte );
  digitalToggle( LED1 );
  }
// read from port 0, send to port 1:
if( Serial.available( ) )
  {
  inByte = Serial.read( );
  Serial1.write( inByte );
  digitalToggle( LED2 );
  }
delay( 25 );        // So LEDs flash visibly
}
