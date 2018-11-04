/*
  Simple example to check heap memory during run time for XMC devices
  Demonstrates the ability to check on free heap memory.

  Amended April 2018 Paul Carpenter, PC Services
  Needs first serial port to display results at 115,200 baud

  Add sign on header and total heap at compile time
  Add details for malloc and free after new() and delete[]() of array done
  Simplify code
  Make board agnostic

  At best gives largest free chunk available depending on any other
  malloc/free usage in your application.
 */
#include <DeviceControlXMC.h>

XMCClass devCtrl;

char *pointer;        // Points to allocated memory
size_t  freeMemory;  // Used to store the value of unused memory;


// Gets amount of free heap and sends to serial port as decimal number
void dispFree( )
{
  freeMemory = devCtrl.freeHeapRAM( );
  Serial.println( freeMemory );
}


void setup( )
{
  Serial.begin( 115200 );
  delay( 100 );
  Serial.println( "Heap free memory example  (V2.0)" );
  Serial.print( "Total heap at Compile time\t" );
  Serial.println( (uint32_t)( total_heap_s ) );
  // Check the total free memory
  Serial.print( "Free memory before allocation:\t" );
  dispFree( );

  // Allocate some memory and check the changes
  pointer = (char*)malloc( 100 );
  if( pointer != NULL )  // check if we had enough space to allocate that memory
    Serial.println( "Allocated 100 bytes" );
  else
    Serial.println( "Failed to allocate memory" );
  Serial.print( "Free memory after allocation:\t" );
  dispFree( );

  // Free the allocated memory and check the memory now
  free( pointer );
  Serial.println( "Freed 100 bytes" );
  Serial.print( "Free memory after freeing:\t" );
  dispFree( );

  // use new and delete on array of 100 x 32 bit ints
  pointer = (char *)new( int[ 100 ] );
  if( pointer != NULL )  // check if we had enough space to allocate that memory
    Serial.println( "new() array of integers " );
  else
    Serial.println( "Failed to allocate memory" );
  Serial.print( "Free memory after new():\t" );
  dispFree( );

  // Free the allocated memory and check the memory now
  delete[]( pointer );
  Serial.println( "Delete array" );
  Serial.print( "Free memory after delete:\t" );
  dispFree( );
}


void loop( )
{
// do absolutely nothing
}

