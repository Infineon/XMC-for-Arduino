/* Test analogwrite functions for any board

    If used prints signon message to serial port at 115200 baud
    Including board run on

    Uses available PWM Pin outputs and outputs 'tones' of

        32 Hz
        64 Hz
        96 Hz
        128 Hz

    First one only all boards, remainder on all supported boards with 4 PWM outputs
*/
// Print defines values as strings macros
#define str(x)  Serial.print( #x )
#define str1(x) str(x)


void setup() {
#if defined ( XMC1100_XMC2GO )
analogWrite( 8, 32 );       // all PWM4
analogWrite( 1, 64 );
analogWrite( 2, 96 );
analogWrite( 3, 128 );
#endif
#if defined ( XMC1100_H_BRIDGE2GO )
analogWrite( 8, 32 );       // PWM4
#endif
#if defined ( XMC1100_Boot_Kit ) || defined ( XMC1400_Boot_Kit ) || defined ( XMC1300_Sense2GoL )
// XMC1100 Boot Kit or XMC1400 Boot Kit  or XMC1300 Sense2GoL
analogWrite( 3, 32 );       // all PWM4
analogWrite( 4, 64 );
analogWrite( 6, 96 );
analogWrite( 9, 128 );
#endif
#if defined ( XMC1300_Boot_Kit )
// XMC1300 Boot Kit
analogWrite( 31, 32 );      // PWM4
analogWrite( 26, 64 );
analogWrite( 32, 96 );      // PWM8
analogWrite( 33, 128 );
#endif
#if defined ( XMC4700_Relax_Kit ) || defined( XMC4700_Radar_Baseboard )
analogWrite( 3, 32 );       // PWM4
analogWrite( 5, 64 );       // PWM8 rest relax kit only
analogWrite( 6, 96 );
analogWrite( 9, 128 );
#endif
delay( 100 );
Serial.begin( 115200, SERIAL_8N1 );
Serial.println(  "PC Services analogWrite Test" );
Serial.print(  "Configured for XMC" );
str1( ARDUINO );
Serial.print( "\tBoard Name: " );
str1( XMC_BOARD );
}

void loop() {
}
