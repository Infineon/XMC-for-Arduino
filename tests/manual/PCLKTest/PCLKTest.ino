/* PCLK temp variation observations

Sets PWM Output to 10 kHz 50% PWM to measure accuracy
Reads out Die temp every 10 seconds

If both LED1 and LED2 are permanently ON then an invalid pin for PWM has been
attempted to be attached to a invalid pin

Wiring
    Default PWM pin are 3

    Some Board variant PWM Pins
    XMC1100 Boot Kit    3, 4, 6, 9
    XMC1100 XMC2Go      8, 3, 2, 1
    XMC1300 Boot Kit    31, 26, 32, 33
    XMC4700 Relax       3, 10, 11, 95, 72, 96, 63, 36, 78, 90, 91,
                        5,  6, 9, 53, 39, 64, 38, 68, 79, 83, 82, 81
 */
#include <LED.h>
#include <DeviceControlXMC.h>

// For library macro printing
#define str(x)  Serial.println( #x )
#define str1(x) str(x)

// Adjust the following defines to match your setup
// Pins for Servos and pot
//#define PWM_A_PIN 3
// XMC1300 Boot Kit pins
#define PWM_A_PIN 31

#define RESOLUTION          16
#define REFRESH_FREQUENCY   10000
#define DUTY_50             32767

LED Led;                    /* Create an LED object */
XMCClass devCtrl;

int32_t temperature;


void setup( )
{
Led.Add( LED1 );            // Configure the LEDs
Led.Add( LED2 );
Led.Off( LED1 );            // Set default state of LEDs
Led.Off( LED2 );
Serial.begin( 115200 );
delay( 100 );
Serial.println( "XMC PCLK Temp test" );
Serial.print( "Running on " );
str1( XMC_BOARD );
// dummy read to ensure first value which may be erroneous is ignored
temperature = devCtrl.getTemperature();

// Setup the PWM pins 
analogWriteResolution( RESOLUTION );
if( setAnalogWriteFrequency( PWM_A_PIN, REFRESH_FREQUENCY ) < 0  )
  {                 // Invalid pin trap for non-PWM pin
  Led.On( LED1 );
  Led.On( LED2 );
  while( 1 );       // Stick in error loop
  }
analogWrite( PWM_A_PIN, DUTY_50 );             // Duty for mid (1500) = 4915
}


void loop( )
{
/* If UC_FAMILY = XMC4 you can also calibrate temperature for finer measurements */
temperature = devCtrl.getTemperature();

Serial.print( "Die Temp:\t" );
Serial.println( temperature );
delay( 10000 );
}
