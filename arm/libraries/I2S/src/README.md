# The I2S library for XMC

## introduction Introduction

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
This signal controls the timing of data transmission. On the rising edge of the WA signal the right channel transmits and on the falling edge the left channel transmits. Therefore interrupts
 are enabled for both falling and rising edge, which starts the reading of sensor data from the FIFO buffer. 

