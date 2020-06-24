/**
 * I2S.h - Library for Arduino to interface with I2S devices.
 * 
 * Have a look at the application note/datasheet for more information.
 * Currently, only reading via I2S is supported - no output can be generated.
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/**
 *  @page The I2S library for XMC
 *  @section introduction Introduction
 * 	The IIS protocol is a synchronous serial communication protocol mainly for audio and infotainment applications. This library allows the microcontroller to work as 
 *  the master device and read audio input from another device such as a microphone.
 *
 *	@section Wiring
 *  The library has been tested with the XMC4700 Relax Kit/XMC1100 XMC2G0/XMC1100 Boot Kit. interfacing an Infineon IM69D130 Microphone Shield2Go. 
 *  For the XMC4700 relax board, following ports should be connected:
 *  LRCL -- 3.10
 *  DOUT -- 3.7
 *  SCLK -- 3.9
 *  GND  -- GND
 *  3.3V -- 3.3V
 *  
 *  For the XMC1100 boards the connection should be the following:
 *  LRCL -- 0.9
 *  DOUT -- 0.6
 *  SCLK -- 0.8
 *  GND  -- GND (VSS)
 *  3.3V -- 3.3V (VDD)
 * 
 *  SCL (for channel selection) on the breakout can be left unconnected if only one microphone is used. 
 *  When 2 microphones are connected, the SCL ports on the microphones should be
 *  pulled low/high respectively for transmission on left/right channels.
 * 
 *
 *	@subsection Implementation
 *  This library uses interrupts to read data from a microphone. The microcontroller generates a WA (word address, or WS for word select) which is output to LRCL port of the microphone.
 *  This signal controls the timing of data transmission. On the rising edge of the WA signal the right channel transmits and on the falling edge the left channel transmits.
 * 
 */
#ifndef I2S_h
#define I2S_h

#if defined(XMC4700_Relax_Kit) || defined(XMC1100_XMC2GO) || defined(XMC1100_Boot_Kit)
#include "utility/xmc_i2s_conf.h"

typedef enum {
  I2S_PHILIPS_MODE,
  I2S_RIGHT_JUSTIFIED_MODE,
  I2S_LEFT_JUSTIFIED_MODE
} I2SMode_t;

typedef enum {
  NO_MICROPHONE,
  MICROPHONE_LOW,
  MICROPHONE_HIGH,
  MICROPHONE_LOW_HIGH = 4
} I2SMicrophones_t;

class I2SClass
{
private:
  XMC_I2S_CH_CONFIG_t _channel_config;
  uint8_t _systemWordLength;
  uint8_t _bitsPerSample;

  // State variables
  bool _initialized = false;
  uint8_t _microphoneSelection;
  uint8_t _shiftFirst = 0;
  uint32_t _firstShiftMask = 0;
  uint8_t _shiftSecond = 0;
  uint32_t _secondShiftMask = 0;

  // Sample generation related variables
  int32_t _lastValue;    
  uint32_t _bitMask1;
  uint32_t _lastValueBuffer;
  I2SMicrophones_t _sampleInformation;

  // Callback functions
  void (*_onReceiveEvent)(void);

  // Ring buffer related private variables
  volatile int32_t *_i2sBuffer;
  volatile uint16_t _posHead = 0;
  volatile uint16_t _posTail = 0;
  uint16_t _bufferSize;
  bool _overflow = false;

  /**
	 * @brief Inserts a value into the buffer
	 * @param Signed 32 Bit integer of the value which shall be inserted into the buffer
   * @return Returns the amount inserted into the buffer - 1 on success and 0 on failure
	 */
  uint8_t _storeValue(int32_t value);

  /**
	 * @brief Starts I2S communication with full settings 
   * @return Returns an XMC_I2S_CH_STATUS_t with the result of the settings
	 */
  XMC_I2S_CH_STATUS_t _init();

public:
  /**
	 * @brief Register an additional callback function which is executed before return statement of I2S ISR
   * @param _onReceiveEvent Pointer to a function returning void and accepting no argument
	 */
  void onReceive(void(*func)(void));

  /**
	 * @brief ISR handling the data transfer
	 */
  void _onSampleReceived();

  /**
	 * @brief Constructor of the I2S class.
	 */
  I2SClass();

  /**
	 * @brief Starts I2S communication compatible to standard I2S library for Arduino 
   * @param mode I2S mode as defined in I2SMode_t (I2S_PHILIPS_MODE, I2S_RIGHT_JUSTIFIED_MODE, I2S_LEFT_JUSTIFIED_MODE) compatible to standard I2S library for Arduino
   * @param samplingRate samples per seconds for the microphone(s)
   * @param bitsPerSample the number os bits in a data word
   * @return Returns an XMC_I2S_CH_STATUS_t with the result of the settings
	 */
  XMC_I2S_CH_STATUS_t begin(I2SMode_t mode, uint32_t samplingRate, uint8_t bitsPerSample);

  /**
	 * @brief Starts I2S communication with basic settings 
   * @param samplingRate samples per seconds for the microphone(s)
   * @param clocksPerWord the clocksPerWord rate of the underlying microphone
   * @param bitsPerSample the number of bits in a data word
   * @return Returns an XMC_I2S_CH_STATUS_t with the result of the settings
	 */
  XMC_I2S_CH_STATUS_t begin(uint32_t samplingRate, uint8_t clocksPerWord, uint8_t bitsPerSample);

  /**
	 * @brief Starts I2S communication with advanced settings 
   * @param baudrate the baudrate of the microphone sampling
   * @param dataBits length of one data frame. Ranges from 1 to 16 (size of the FIFO buffer)
   * @param frameLengthInBits length of frame which should be sampled in one cycle - the overall length is set the same
   * @param dataDelay the number of clock cycles after which a transmission of one sample is started
   * @param bitsPerSample the number of bits in one sample, i.e. the sample accuracy like 20 Bits
   * @return Returns an XMC_I2S_CH_STATUS_t with the result of the settings
	 */
  XMC_I2S_CH_STATUS_t begin(uint32_t baudrate, uint8_t frameLengthInBitsInBits, uint8_t dataDelay, uint8_t dataBits, uint8_t bitsPerSample);

  /**
	 * @brief Starts I2S communication with full settings 
   * @param baudrate the baudrate of the microphone sampling
   * @param dataBits length of one data frame. Ranges from 1 to 16 (size of the FIFO buffer)
   * @param frameLengthInBits length of frame which should be sampled in one cycle
   * @param systemWordLength length of the overall frame between word select changes
   * @param dataDelay the number of clock cycles after which a transmission of one sample is started
   * @param bitsPerSample the number of bits in one sample, i.e. the sample accuracy like 20 Bits
   * @return Returns an XMC_I2S_CH_STATUS_t with the result of the settings
	 */
  XMC_I2S_CH_STATUS_t begin(uint32_t baudrate, uint8_t systemWordLength, uint8_t frameLengthInBits, uint8_t dataBits, uint8_t bitsPerSample, uint8_t dataDelay);

  /**
	 * @brief Ends I2S communication with default configuration 
   * @return Returns an XMC_I2S_CH_STATUS_t with the result of the settings
	 */
  XMC_I2S_CH_STATUS_t end();

  /**
	 * @brief Enables microphone sampling when word select low
   * @return Returns 0 when no microphones are sampled, 1 when microphone is sampled at word select low, 2 when microphone is sampled at word select high, 4 when microphones are sampled at both levels	 */
  uint8_t enableMicrophoneLow();

  /**
	 * @brief Enables microphone sampling when word select low
   * @return Returns 0 when no microphones are sampled, 1 when microphone is sampled at word select low, 2 when microphone is sampled at word select high, 4 when microphones are sampled at both levels
	 */
  uint8_t enableMicrophoneHigh();

  /**
	 * @brief Disable all microphones
   * @return Returns 0 to indicate that no microphones are sampled anymore
	 */
  uint8_t disableMicrophones();

  /**
	 * @brief Get the current microphone selection 
   * @return Returns 0 when no microphones are sampled, 1 when microphone is sampled at word select low, 2 when microphone is sampled at word select high, 4 when microphones are sampled at both levels
	 */
  uint8_t getMicrophones();

  /**
	 * @brief Copies samples into an int32_t array
   * @param readBuffer the user-defined buffer of integers  
   * @param readSize number of samples that should be copied into the buffer. Must be smaller than the buffer's length
   * @return Returns the values copied into readBuffer
	 */
  uint16_t read(int32_t *readBuffer, uint16_t readSize);

  /**
   * @brief Enables master clock output signal with a fixed phase relation to the shift clock to support oversampling for audio components.
   * */
  void enableMasterClock();

  /**
   * @brief Returns the available values for reading from the buffer
   * @return The number of values which can be read from the buffer
   */
  uint16_t available();

  /**
   * @brief Returns the last value inserted into the buffer
   * @return The last value which has been read from the microphone and inserted into the buffer
   */
  int32_t peek();

  /**
   * @brief Reads one value from the buffer and returns it
   * @return Returns a value on success or 0 in case of a failure - check available() whether values can be returned
   */
  int32_t read();

  /**
   * @brief Empties the receive buffer by reading all values
   * @return Returns 1 on failure, e.g values are faster inserted as read out, and 0 on success
   */
  uint8_t flush();

  /**
   * @brief Returns whether an overflow would have happened or not. Overflow will be cleared once new data is successfully inserted.
   * @return Overflow if last value could not be inserted into the ring buffer
   */
  bool getOverflow();

  /**
   * @brief Returns the information about the last sampled value. This information will be updated before the custom ISR runs, i.e. information is available to separate sampled values from peek()
   * @return I2SMicrophones_t which indicates the sampled value - only NO_MICROPHONE, MICROPHONE_LOW, and MICROPHONE_HIGH will be returned
   */
  I2SMicrophones_t getSampleInformation();
};

extern I2SClass I2S;

#else
#error "Only XMC4700 Relax Kit, XMC1100 XMC2Go or XMC1100 Boot Kit is supported for I2S"
#endif

#endif /* I2S_h */
