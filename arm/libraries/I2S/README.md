# The I2S library for XMC

The IIS protocol is a synchronous serial communication protocol mainly for audio and infotainment applications. This library allows the microcontroller to work as 
the master device and read audio input from another device such as a microphone.

## Wiring
The library has been tested with the XMC4700 Relax Kit/XMC1100 XMC2G0/XMC1100 Boot Kit. interfacing an Adafruit I2S MEMS Microphone Breakout. 

* For the XMC4700 relax board, following ports should be connected:
  - LRCL -- 3.10
  - DOUT -- 3.7
  - SCLK -- 3.9
  - GND  -- GND
  - 3.3V -- 3.3V

*  For the XMC1100 boards the connection should be the following:
    - LRCL -- 0.9
    - DOUT -- 0.6
    - SCLK -- 0.8
    -  GND  -- GND (VSS)
    - 3.3V -- 3.3V (VDD)

SCL (for channel selection) on the breakout can be left unconnected if only one microphone is used. When 2 microphones are connected, the SCL ports on the microphones should be
pulled low/high respectively for transmission on left/right channels.

## Implementation
This library uses interrupts to read data from a microphone. The microcontroller generates a WA (word address, or WS for word select) which is output to LRCL port of the microphone.
This signal controls the timing of data transmission. On the rising edge of the WA signal the right channel transmits and on the falling edge the left channel transmits. 

By default mono channel is used:
```
XMCI2SClass(bool isMono = true, uint8_t bitsPerSample = 16);
```

To use stereo channels you should modify the source code and change `isMono` to `false`, then interrupts are generated on both falling and rising edges. In this case, using `I2S.peek()` wouldn't make much sense since the reading is not synced with the interrupts. Instead, `I2S.read()` should be used which writes the samples from the left and write channels one after another in the buffer you passed into the function.

For simplicity 16-bit samples are reconstructed from twice reading of FIFO buffer. Some microphones, such as the Infineon Mic Shield2Go has an accuracy of 20 bits per sample. However to represent it 32-bit integers would be necessary. This has not been implemented in the current library, and you need to modify the source code if you need to have higher accuracy than 16-bit.

## Usage
Caution: use the default settings if modifying parameters cause the microphone to stop working.

### Choosing the sampling rate
Please refer to the data sheets of your microphone for the rate of the sampling rate. 

If you are using XMC1000 family boards, the default sampling rate is 12 kHz when you call `I2S.begin();`
Also make sure you use a lower baud rate when you are using XMC1000 boards, since both `Serial` and `I2S` use USCI interrupts, and the older boards seem not able to handle a large number of interrupts.

However, if you are using an XMC4000 board such as a XMC4700 relax kit, you shouldn't have to worry about these issues.

### Data delay
Sometimes it also makes sense to adjust the data delay, which is the delay between a changing WA/LRCL edge and the start of a sample. However, if the delay is too long the highest bits might be lost.

## Additional Information
See also our [Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki/Core-Libraries) and doxygen-generated [documentation page](https://github.com/Infineon/InfineonDoxyGenerator).