#include <Arduino.h>

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
Serial.println(  "PC Services Tone Test" );
tone( LED1, 1 );
tone( LED2, 2, 20000 );
#ifdef XMC_BOARD
#if XMC_BOARD == Boot_Kit
tone( LED5, 4, 1000 );
tone( LED6, 8, 6000 );
#endif
#endif
printstats();
}

void loop()
{
delay( 2000 );
printstats();
}
