#include <Arduino.h>

// Linker symbols to get falsh/RAM usage
#if( UC_FAMILY == XMC1 )
extern char VeneerStart, VeneerEnd, eROData;
#endif
extern char __ram_code_start, __ram_code_end, __bss_end, __bss_start;
extern char Heap_Bank1_Start, Heap_Bank1_End;
extern char sText, __initial_sp, __data_start, __data_end;

#define str(x)  Serial.println( #x )
#define str1(x) str(x)
#define str2(x) Serial.print( #x )

uint32_t temp, code_size;

void setup()
{
delay( 2000 );
Serial.begin( 115200, SERIAL_8N1 );
Serial.println( "PC Services - XMC-for-Arduino useful defines example" );
Serial.print( "Built on: " );
Serial.print( __DATE__ );
Serial.print( "  " );
Serial.println( __TIME__ );

#ifdef XMC_BOARD
str2( XMC_BOARD );
Serial.write( '\t' );
str1( XMC_BOARD );
#endif
Serial.print( "Family\t\t" );
str1( UC_FAMILY );
Serial.print( "Series\t\t" );
str1( UC_SERIES );
Serial.print( "Device\t\t" );
str1( UC_DEVICE );
Serial.print( "Package\t\t" );
str1( UC_PACKAGE );
Serial.print( "Flash (kB)\t" );
Serial.println( UC_FLASH );
#if defined ARDUINO_ARM_XMC
str2( ARDUINO_ARM_XMC );
Serial.write( '\t' );
str1( ARDUINO_ARM_XMC );
#endif
#if defined ARDUINO_ARCH_CORTEX-M4
str2( ARDUINO_ARM_XMC );
Serial.write( '\t' );
str1( ARDUINO_ARM_XMC );
#endif
#if defined UC_RAM
str2( UC_RAM );
Serial.print( "\t\t" );
str1( UC_RAM );
str2( UC_ALL_RAM );
Serial.write( '\t' );
str1( UC_ALL_RAM );
#endif
str2( F_CPU );
Serial.print( "\t\t" );
str1( F_CPU );
str2( ARDUINO );
Serial.print( "\t\t" );
str1( ARDUINO );
str2( ARDUINO_ARCH_ARM );
Serial.write( ' ' );
str1( ARDUINO_ARCH_ARM );

Serial.print( "Library Version\t" );
Serial.print( XMC_LIB_MAJOR_VERSION );
Serial.print( '.' );
Serial.print( XMC_LIB_MINOR_VERSION );
Serial.write( '.' );
Serial.println( XMC_LIB_PATCH_VERSION );

Serial.println( "\nMemory usage-" );
Serial.print( "Code Size:\t" );
#if( UC_FAMILY == XMC1 )
code_size = &eROData - &sText;
#else
code_size = &__data_end - &sText;
#endif
Serial.println( code_size );

#if( UC_FAMILY == XMC1 )
Serial.print( "Veneer:\t\t" );
temp = &VeneerEnd - &VeneerStart;
code_size += temp;
Serial.println( temp );
#endif
Serial.print( "Stack\t\t" );
temp = &__initial_sp ;
Serial.println( temp );
Serial.print( "Data\t\t" );
temp =  &__data_end - &__data_start;
code_size += temp;
Serial.println( temp );
Serial.print( "Ram Code\t" );
temp =  &__ram_code_end - &__ram_code_start;
code_size += temp;
Serial.println( temp );
Serial.print( "bss\t\t" );
temp =  &__bss_end - &__bss_start;
Serial.println( temp );
Serial.print( "Heap or unused\t" );
temp =  &Heap_Bank1_End - &Heap_Bank1_Start;
Serial.println( temp );

Serial.print( "\nTotal Flash\t" );
Serial.println( code_size );

Serial.print( "Ram less Stack\t" );
temp = &Heap_Bank1_Start - &__data_start;
Serial.println( temp );

Serial.print( "\nCapabilities\nDigital Pins\t" );
Serial.println( NUM_DIGITAL );
Serial.print( "PWM4\t\t" );
Serial.println( NUM_PWM4 );
#ifdef CCU8V2
Serial.print( "PWM8\t\t" );
Serial.println( NUM_PWM8 );
#endif
Serial.print( "PWM\t\t" );
Serial.println( NUM_PWM );
Serial.print( "Ints\t\t" );
Serial.println( NUM_INTERRUPT );
Serial.print( "ADC\t\t" );
Serial.println( NUM_ANALOG_INPUTS );
#ifdef DAC
Serial.print( "DAC\t\t" );
Serial.println( NUM_ANALOG_OUTPUTS );
#endif
#ifdef CAN
Serial.print( "CAN enabled" );
#endif
str2( NUM_LEDS );
Serial.write( '\t' );
str1( NUM_LEDS );
#ifdef BUTTON1
str2( NUM_BUTTONS );
Serial.write( '\t' );
str1( NUM_BUTTONS );
#endif
str2( NUM_SERIAL );
Serial.write( '\t' );
str1( NUM_SERIAL );
}


void loop()
{
}
