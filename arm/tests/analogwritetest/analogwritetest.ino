/* Test analogwrite functions for any board */
// Print defines values as strings macros
#define str(x)  Serial.print( #x )
#define str1(x) str(x)

void setup() {
#if XMC_BOARD == XMC2GO
analogWrite( 8, 32 );      // PWM4
#endif
#if XMC_BOARD == Boot_Kit
#if ARDUINO == 1100
// XMC1100 Boot Kit
analogWrite( 3, 32 );       // all PWM4
analogWrite( 4, 64 );
analogWrite( 6, 96 );
analogWrite( 9, 128 );
#else
// XMC1300 Boot Kit
analogWrite( 31, 32 );      // PWM4
analogWrite( 26, 64 );
analogWrite( 32, 96 );      // PWM8
analogWrite( 33, 128 );
#endif
#endif
#if XMC_BOARD == Relax_Kit
analogWrite( 3, 32 );       // PWM4
analogWrite( 5, 64 );       // PWM8 rest
analogWrite( 6, 96 );
analogWrite( 9, 128 );
#endif
delay( 100 );
Serial.begin( 115200, SERIAL_8N1 );
Serial.println(  "PC Services analogWrite Test" );
Serial.print(  "Configured for XMC" );
str1( ARDUINO );
Serial.write( ' ' );
str1( XMC_BOARD );
}

void loop() {
}
