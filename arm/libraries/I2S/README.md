# The I2S library for XMC

The IIS protocol is a synchronous serial communication protocol mainly for audio and infotainment applications. This library allows the microcontroller to work as 
the master device and read audio input from another device such as a microphone.

Be aware that only reading is possible for the time being - no I2S output is supported.

## Wiring
The library has been tested with the XMC4700 Relax Kit, XMC1100 XMC 2Go, and XMC1100 Boot Kit in combination with the IM69D130 Microphone Shield2Go.

* For the XMC4700 Relax Kit, following ports/pins should be connected:
  - BCLK -- P3.10
  - DATA -- P3.7
  - CLK -- P3.9
  - GND  -- GND
  - 3.3V -- 3.3V

`Ensure that level shifting is in place as the microphone board has 3.3 V logic level.`

*  For the XMC1100 2Go board the ports/pin connection should be the following:
    - BCLK -- P0.9
    - DATA -- P0.6
    - CLK -- P0.8
    - GND  -- GND (VSS)
    - 3.3V -- 3.3V (VDD)

`No level shifting needed as the XMC 2Go board runs at 3.3 V.`

*  For the XMC1100 Boot Kit board the ports/pins connection should be as follows:
    - BCLK -- P0.9
    - DATA -- P1.0
    - CLK -- P0.7
    - GND  -- GND (VSS)
    - 3.3V -- 3.3V (VDD)

`Ensure that level shifting is in place as the microphone board has 3.3 V logic level, XMC1100 Boot Kit has 5 V by default.`

This configuration is defined in `utility\xmc_i2s_conf.h`.

If we take the pin out of XMC for Arduino, the respective pins for SPI are redefined.
Therefore, SPI cannot be used anymore in combination with I2S - please keep this in mind. On the other hand, using `SPI.begin()` and `I2S.begin()` will reactivate the original setting and switching between both interfaces is possible on the fly.

Overall, the following SPI - I2S pin matching is in place:

* SPI:MISO -- I2S:DATA (INPUT)
* SPI:SCK -- I2S:CLK
* SPI:SS -- I2S:BCLK

## Implementation
This library uses interrupts to read data from a microphone or, more general, an I2S source. Internally, the microcontroller uses an FIFO to receive the data and once the FIFO is full, the microcontroller generates an interrupt. During the interrupt, the FIFO is emptied and the values are assigned to the single microphone(s), depending on whether  based on the sampling information.

Please see the example `sampleValues` how to read raw values from from the IM69D130 microphone. 

To use stereo channels, you should need to activate both microphones as shown in the example `sampleValues` by calling the respective `  I2S.enableMicrophoneLow()` or `  I2S.enableMicrophoneHigh()` functions. Please note that the buffer will contain values from both microphones one after another and they need to be separated manually.
In this case, using `I2S.peek()` wouldn't make much sense since the reading has no indication about the currently sampled value. However, by assigning a custom callback function via `I2S.onReceive()` which stores information about the channel once could easily get additional information which is shown in the example `sampleValuesWithCallback`.

For simplicity 16-bit samples are reconstructed from twice reading of FIFO buffer. Some microphones, such as the Infineon Mic Shield2Go has an accuracy of 20 bits per sample. However to represent it 32-bit integers would be necessary. This has not been implemented in the current library, and you need to modify the source code if you need to have higher accuracy than 16-bit.

## Usage
Caution: be careful with the settings for the I2S library as wrong settings could lead to not getting any output at all.
Therefore, please ensure that you know the parameters of your system and crosscheck with working solutions, i.e. it would not be an good idea to change too many parameters of the system once. As an example, if you migrate your code to XMC and use a different microphone as the ones which have been tested, it is likely that the cause of something not working cannot be traced down easily.

### Choosing the sampling rate
Please refer to the data sheet of your specific microphone for the sampling rate. Especially, take care that you select a sampling rate within the suitable range as otherwise the

If you are using XMC1000 family boards, the recommended sampling rate is 12 kHz as higher values might interfere with the microcontroller speed.
Since both `Serial` and `I2S` use USIC interrupts, there could be a problem with processing remaining code as the processor could get locked out via interrupts.

However, if you are using an XMC4000 board such as a XMC4700 Relax Kit, you shouldn't have to worry about these issues in particular.

### Data delay
Sometimes, it also makes sense to adjust the data delay, which is the delay between a changing WA/LRCL edge and the start of a sample depending on the microphone of your choice. Please be aware that there are different `I2S.begin()` functions which allow to set the parameters very precisely. Have a look in the I2S.h file for more information.

## Additional Information
See also our [Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki/Core-Libraries) and doxygen-generated [documentation page](https://github.com/Infineon/InfineonDoxyGenerator).

## Authors
Manuel Hollfelder 
Yuxi Sun