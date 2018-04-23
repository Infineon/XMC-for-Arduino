/* MODIFIED Free Stack example for ANY board

    Sends details to first serial port at 115,200 baud.

    Note free stack displayed is a SIGNED value so if a negative value
    appears it is a stack over run. That is too many items on the stack
    and has gone beyond its allocated area.

  Programme Flow and results
    Sets up serial port
    wait
    Send example name and initial Stack settings
    Calculate and send free stack at this point
    Call a function and show stack free at this point
    Return show stack free now
    Call a second function that calls the first function to show stack
    Return show stack free now

    Loop doing nothing

  New example  Paul Carpenter, PC Services, April 2018
 */
// The actual calculation to get amount of free Stack
#define freeStackRAM    (int32_t)( __get_MSP( ) - (int32_t)&__stack_start )

// Variables
extern char __stack_start, __stack_end;

int dummy;

/****  FUNCTIONS USED ******/
/****** Display current current stack free space *****/
void dispfree( int32_t free )
{
Serial.println( free );
delay( 1000 );
}


// Function that does nothing. just some parameters & local variables,
// so that the difference in stack will be more obvious
void doNothing( int value )
{
int j = 0;

j = value * 2;

for( int i = 0; i < value; i++ )
     j += i + 1;

Serial.print("Free stack in doNothing function is: \t");
dispfree( freeStackRAM );
}


// second do nothing to also call first
void SecondNothing( int value )
{
int j = 0;

j = value + 1;
for( int i = 0; i < value; i += 2 )
     j += i + 3;

Serial.println("In first of two levels of functions");
doNothing( value / 4);
}


// Actual Main Code here
void setup()
{
Serial.begin( 115200 );

delay(100);
Serial.println( "XMC - Free Stack example  (V2.0)\n" );
// Show inital stack settings
Serial.print( "Stack starts at\t" );
Serial.println( (uint32_t)&__stack_start, HEX );
Serial.print( "Stack size is\t" );
Serial.println( (uint32_t)(&__stack_end - &__stack_start ) );

// Start showing stack changes
Serial.print("Free stack in function loop is:\t");
dispfree( freeStackRAM );

// Check the stack value after calling another function
doNothing( 200 );

// Check the stack after going back to loop
Serial.print("Free stack after going back to loop is:\t");
dispfree(  freeStackRAM  );

dummy = 1000;
// Check the stack value after calling two levels of functions
SecondNothing( dummy );

// Check the stack after going back to loop
Serial.print("Free stack after going back to loop is:\t");
dispfree(  freeStackRAM );
}


void loop()
{
  // do absolutely nothing
}


