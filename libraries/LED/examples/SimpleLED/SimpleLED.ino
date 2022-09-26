/*  Simple LED library flashes on board LED Every second

   Demonstrates the use of the on board LED library

   Works with any XMC board that has at least ONE LED on board
   Better with two
*/
#include <LED.h>

/* Create an LED object */
LED Led;

void setup( )
{
Led.Add( LED1 );            // Configure the LEDs
Led.Off( LED1 );            // Set default state of LEDs

#if NUM_LEDS > 1
Led.Add( LED2 );
Led.On( LED2 );
#endif
}


void loop( )
{
delay( 1000 );
Led.Toggle( LED1 );

#if NUM_LEDS > 1
Led.Off( LED2 );
#endif
}
