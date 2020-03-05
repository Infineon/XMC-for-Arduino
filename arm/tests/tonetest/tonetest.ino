/* tonetest sketch tests wiring_time implementation

   Tests that the timing scheduler can handle multiple events at different
   timing intervals.

   The main ones it tests are as many pins to have tones on as possible
   by toggling on-board LEDs at different frequencies and using the delay (in ms)
   function that is also used by the same timed task scheduler. Uses as many LEDs
   as possible within the constraints of that board (unless used for RX and TX signals)

   Assumes board has at LEAST TWO LEDs compiler error for NO LEDs or TONE PINS
   available

   Main uses for timed task scheduling at 1 ms resolution are
        delay()     function to wait for ms time interval
        tone()      setup burst or continuous tone on a GPIO pin
        BGT24LTR11_CYCLE_TIMER_IRQ  Handler  scheduled task for radar sampling

 Author: Paul Carpenter, PC Services
 Version 2      Update for more XMC_BOARD types and more LEDs used
 Version 3      Updated to bring in line with correct XMC_BOARD usage as per PR
 */

#include <Arduino.h>

#if NUM_TONE_PINS < 2
#error Not enough Tone Pins available on this board
#endif
#if NUM_LEDS < 2
#error Not enough LEDs available on this board to run this test
#endif

// External variables for stats printing
extern uint8_t tone_pins[ NUM_TONE_PINS ];
extern volatile long timer_toggle_count[ NUM_TONE_PINS ];
extern int (* tasks[])( int, int ); 
extern struct TaskList taskTable[  ];

void printstats( )
{
Serial.println( "pin\tid\tCount" );
for( int i = 0; i < NUM_TONE_PINS; i++ )
  {
  Serial.print( tone_pins[ i ] );
  Serial.print( "\t" );
  Serial.print(  i );
  Serial.print( "\t" );
  Serial.println( timer_toggle_count[ i ] );
  }
Serial.println( "ID\tnext\tInterval Status\tParam\tfunction" );
for( int i = 0; i < NUM_TONE_PINS+1; i++ )
  {
  Serial.print( i );
  Serial.print( "\t" );
  Serial.print( taskTable[ i ].next );
  Serial.print( "\t" );
  Serial.print( taskTable[ i ].interval );
  Serial.print( "\t" );
  Serial.print(  taskTable[ i ].status );
  Serial.print( "\t" );
  Serial.print(  taskTable[ i ].param );
  Serial.print( "\t" );
  Serial.println(  (uint32_t)tasks[ i ], HEX );
  }
}

void setup()
{
Serial.begin( 115200 );
Serial.println(  "PC Services Tone Test V2" );
tone( LED1, 1 );
tone( LED2, 2, 20000 );

#if defined( XMC1100_Boot_Kit ) || defined( XMC1300_Boot_Kit )
tone( LED5, 4, 1000 );
tone( LED6, 8, 6000 );
#elif defined( XMC1300_Sense2GoL )
tone( LED3, 4, 1000 );
#endif

printstats();
}

void loop()
{
delay( 2000 );
printstats();
}
