/* Example of how to access XMC defines and use for debug
 *  
 *  Updated 8-Feb-2020 Paul Carpenter
 */
// Linker symbols to get flash/RAM usage
#if( UC_FAMILY == XMC1 )
extern char VeneerStart, VeneerEnd, eROData;
#endif
extern char __ram_code_start, __ram_code_end, __bss_end, __bss_start;
extern char Heap_Bank1_Start, Heap_Bank1_End;
extern char sText, __initial_sp, __stack_start, __data_start, __data_end;

#define str(x)  Serial.println( #x )
#define str1(x) str(x)
#define str2(x) Serial.print( #x )

uint32_t temp, code_size;

void setup( )
{
delay( 60 );
Serial.begin( 115200, SERIAL_8N1 );
Serial.println( "PC Services - XMC-for-Arduino useful defines example" );
#ifdef XMC_BOARD_NAME
Serial.read();
str2( XMC_BOARD_NAME );
Serial.write( '\t' );
str1( XMC_BOARD_NAME );
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
temp = &__initial_sp - &__stack_start;
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
}


void loop( )
{
}
