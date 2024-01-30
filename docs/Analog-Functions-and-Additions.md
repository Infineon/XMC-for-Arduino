## wiring_analog after V1.2.1
Analog functions like analogRead and 
analogWrite etc. have changed after V1.2.1 to have extra safety measures to ensure invalid settings cannot be done and report errors.

Additionally extra getter functions have been added so other libraries can access the resolution of read and write functions as number of bits and current maximum value possible.

## Extra functions
These functions return the analogue resolution as number of bits
* uint8_t getAnalogReadBits( ) - range 8 to 12
* uint8_t getAnalogWriteBits( ) - range 8 to 16

These functions return the analogue resolution as its maximum value
* uint16_t getAnalogReadMaximum( ) - range 255 to 4095
* uint16_t getAnalogWriteMaximum( ) - range 255 to 65535

This function enables the analog amplifiers at the ADC inputs with adjustible gain (for XMC1000 series)
* uint32_t analogRead_variableGain( uint8_t channel, uint8_t gain_value ) \
    The gain factor values can be found [here.](#analog-amplifiers-at-the-adc-inputs-with-adjustible-gain)

## Default Values
Read resolution default is 10 bits (0 to 1023)

Write resolution default is 8 bits (0 to 255)
## Error and Return Codes by Function
Where possible functions do **NOT** action invalid parameters passed in.

Functions return error codes or valid values so be sure which error code you are looking for as some functions can return 0 as a valid value (e.g. analogRead) so an out of range value is returned instead.
<table align=centre border=0>
 <tr>
  <td><b>Function</b></td>
  <td><b>Valid Return</b></td>
  <td><b>Errors</b></td>
 </tr>
 <tr>
  <td>analogReadResolution</td>
  <td>8 to 12<br>as passed in</td>
  <td>255</td>
 </tr>
 <tr>
  <td>getAnalogReadBits</td>
  <td>8 to 12</td>
  <td> none</td>
 </tr>
 <tr>
  <td>getanalogReadMaximum</td>
  <td>255 to 4095</td>
  <td>none</td>
 </tr>
 <tr>
  <td>analogWriteResolution</td>
  <td>8 to 16<br>as passed in</td>
  <td>255</td>
 </tr>
 <tr>
  <td>getAnalogWriteBits</td>
  <td>8 to 16</td>
  <td> none</td>
 </tr>
 <tr>
  <td>getanalogWriteMaximum</td>
  <td>255 to 65535</td>
  <td>none</td>
 </tr>
 <tr>
  <td>analogRead</td>
  <td>0 to Maximum for Resolution </td>
  <td>0xFFFFFFFF usually invalid channel</td>
 </tr>
 <tr>
  <td>analogWrite</td>
  <td>0 success </td>
  <td>-1 = invalid value<br>
      -2 = wrong pin</td>
 </tr>
 <tr>
  <td>setAnalogWriteFrequency</td>
  <td>0 success </td>
  <td>-1 = invalid frequency<br>
      -2 = wrong pin</td>
 </tr>
 <tr>
  <td>analogReference</td>
  <td>none</td>
  <td>NULL function see below</td>
 </tr>
</table>
This should enable checks in software for valid operation and debugging problem code.

## AREF Analogue Reference
On all boards the Analogue Reference is set to use the internal power supply (however noisy), so the AREF pin is an **OUTPUT** of the AREF in use. Do **NOT** connect any external voltage source to this pin, or use shields that change this voltage.

**CAUTION** any shorts on this pin especially to 0V (GND) will bring down the supply of the chip.

The pin voltage is the current supply voltage to AREF for analogue conversions.

This pin **CANNOT** be reassigned as GPIO (pinMode has no effect).

### analogReference( )
This function has NO operation and will not match any call on parameters passed in with other libraries or examples that use this call.

Any shields and examples that try to change this, will **NOT** function the same on these boards.

## Analog amplifiers at the ADC inputs with adjustible gain
Each analog input channel can be configured to be amplified by an adjustable gain factor, for XMC1000 series. To configure the gain, the `gain value` is to be selected in the `analogRead_variableGain()` function which translates to a `gain factor` as per the following table:

<table align=centre border=0>
 <tr>
  <td><b>Gain value</b></td>
  <td><b>Gain factor</b></td>
 </tr>
 <tr>
 <td>0</td>
 <td>1</td>
 </tr>
 <tr>
 <td>1</td>
 <td>3</td>
 </tr>
 <tr>
 <td>2</td>
 <td>6</td>
 </tr>
 <tr>
 <td>3</td>
 <td>12</td>
 </tr>
 </table>

 For more information, please refer to the application note [here.](https://www.infineon.com/dgdl/Infineon-VADC-XMC1200_XMC1300-AP32304-AN-v01_10-EN.pdf?fileId=5546d4624e765da5014ed981f63136d6)

[Home](https://github.com/Infineon/XMC-for-Arduino/wiki)