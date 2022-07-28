/*  Simple LED library flashes on board LED Every second

   Demonstrates the use of the on board LED library

   Works with any XMC board that has TWO LEDs on board
*/
#include <LED.h>

/* Create an LED object */
LED Led;

void setup( )
{
Led.Add( LED1 );            // Configure the LEDs
Led.Add( LED2 );              

Led.On( LED2 );             // Set default state of LEDs
Led.Off( LED1 );
}


void loop( )
{
delay( 1000 );
Led.Off( LED2 );
Led.Toggle( LED1 );
}
