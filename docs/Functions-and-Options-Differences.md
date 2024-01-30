# Extra modes (if patches applied)
This section covers the differences between standard Arduino and XMC-for-Arduino

## GPIO
Extra pinMode types added that most engineers want
~~~
    INPUT_PULLDOWN
    OUTPUT_OPENDRAIN
~~~

# Extra functions (than standard Arduino AVR)
## GPIO
Does what the function names says but must have been configured as output
~~~
    digitalToggle( pin )
~~~
# Arduino Function Differences

## Input Mode Pins
On standard Arduino boards, GPIO is by default either a function like Serial or in INPUT mode.

On XMC boards the inputs are UNDEFINED, you **MUST** specify every pin to be in INPUT Mode that needs Inputs.

## Wire/I2C Differences
The method in Wire class for 'begin' is not the same as AVR Arduino, and has different modes for Master and Slave

In AVR Arduino setting an I2C Master or Slave
~~~
   Wire.begin(8); // join i2c bus (address optional for master)
~~~
XMC-for-Arduino setting for I2C Master **ONLY**
~~~
    Wire.begin(); // join i2c bus (address blank for master)
~~~
Currently the address is NOT optional for XMC as this currently assumes this must be Slave mode configuration and sets the I2C configuration differently.

## Tone
Number of Tone pins is determined by pins_arduino.h define NUM_TONE_PINS. This allows for use in other modules and for variations between boards as >100MHz boards can obviously handle more tone pins.

The default for XMC1xxx is 4 with a change XMC4xxxx should be 16

Tone has frequency range of
	maximum = 500 Hz
	minimum = 1 Hz

This is due to the fact that the tone frequency is software derived from the Systick handler, Systick has a time period of 1 ms. At maximum each handler event for Systick toggles a GPIO pin, so at minimum period of 1 ms the output is toggled, so TWO events produce one square wave cycle, therefore the maximum output frequency is 500Hz.

The minimum is due to the fact that tone function only accepts an unsigned integer (32 bit) for the frequency, so the minimum usable frequency is 1.

Standard Arduino boards use hardware timers (the few that are available) to generate tones and at least one timer can interfere with other functions.

However this does mean you can have more tone pins, just much lower frequency range.
