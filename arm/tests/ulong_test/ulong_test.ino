#include <stdint.h>
#include <limits.h>

unsigned long old, newt, diff;
int i;

void setup() {
newt = micros();
delay(60);
Serial.begin( 115200);
diff = ULONG_MAX;
old = diff;

Serial.println( "PC Services ulong test" );
Serial.print( "Microseconds to setup routine = " );
Serial.println( newt, DEC ); 
Serial.print( "Total milliseconds = " ); 
Serial.print( diff, DEC ); 
diff /= ( 60000 * 60 * 24 );     // days
newt = old - ( diff * 60000 * 60 * 24  ); // days fraction
old = newt / ( 60000 * 60 );    // hours
Serial.print( "\nIn " ); 
Serial.print( diff, DEC ); 
Serial.print( " days " ); 
Serial.print( old, DEC ); 
Serial.print( " hours " ); 
newt -= ( old *  60000 * 60 );  // hours fraction
old = newt / 60000;        // minutes
diff = newt - (old * 60000 );  //miutes fraction
newt = diff / 1000;     // seconds
i = diff - (newt * 1000 );
Serial.print( old, DEC ); 
Serial.print( " minutes " ); 
Serial.print( newt, DEC ); 
Serial.print( " seconds " ); 
Serial.print( i, DEC ); 
Serial.println( " milliseconds " ); 

old = ULONG_MAX - 5;
newt = old;
for( i = 0; i < 20; i++, newt++ )
   {
   Serial.print( " Old = " ); 
   Serial.print( old, HEX ); 
   Serial.print( "\tnew = " ); 
   Serial.print( newt, HEX ); 
   Serial.print( "\tdiff = " ); 
   diff = newt - old;
   Serial.println( diff, DEC ); 
   }
}

void loop() {
// do nothing  
}
