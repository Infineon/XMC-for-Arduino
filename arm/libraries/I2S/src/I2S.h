/**
 *  @page The I2S library for XMC
 *  @section introduction Introduction
 * 	The IIS protocol is a synchronous serial communication protocol mainly for audio and infotainment applications. This library allows the microcontroller to work as 
 *  the master device and read audio input from another device such as a microphone.
 *
 *	@section Wiring
 *  The library has been tested with the XMC4700 Relax Kit/XMC1100 XMC2G0/XMC1100 Boot Kit. interfacing an Adafruit I2S MEMS Microphone Breakout. 
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
 *  SCL (for channel selection) on the breakout can be left unconnected if only one microphone is used. When 2 microphones are connected, the SCL ports on the microphones should be
 *  pulled low/high respectively for transmission on left/right channels.
 *
 *	@subsection Implementation
 *  This library uses interrupts to read data from a microphone. The microcontroller generates a WA (word address, or WS for word select) which is output to LRCL port of the microphone.
 *  This signal controls the timing of data transmission. On the rising edge of the WA signal the right channel transmits and on the falling edge the left channel transmits. Therefore interrupts
 *  are enabled for both falling and rising edge, which starts the reading of sensor data from the FIFO buffer. 
 * 
 */

#ifndef I2S_h
#define I2S_h

#include <Arduino.h>
#include <SignalInput.h>
#include "utility/xmc_i2s_conf.h"

#if (UC_FAMILY == XMC4)
#include <DMA.h>
#endif

class XMCI2SClass : public SignalInput
{
private:
  XMC_I2S_CH_CONFIG_t channel_config;
  uint16_t _i2sOffset;
  bool _isMono;
  bool _downScalingFlag = false;
  bool _downScalingEnabled = false;
  int32_t _lastVal;
  uint8_t _bitsPerSample;
  int16_t retval;
  int16_t _i2sBuffer[BUFFER_SIZE];
  
#if (UC_FAMILY == XMC4)
  DMA dma_module;
  static bool _dmaInProgress;
  interrupt_cb_t customCallback;
#endif

public:
  /**
	 * @brief Constructor of the I2S class.
	 * @param isMono if mono channel is enabled and is set to true by default. If you are using the Adafruit microphone breakout, this corresponds to an unconnected SEL.
	 */
  XMCI2SClass(bool isMono = true, uint8_t bitsPerSample = 16);

  /**
	 * @brief Starts I2S communication with default configuration. 
	 */
  void begin();

  /**
	 * @brief Starts I2S communication. 
   * @param samplingRate samples per seconds
   * @param dataBits length of one data frame. Ranges from 1 to 16 (size of the FIFO buffer)
   * @param frameLength number of bits between 2 changing edges
   * @param dataDelay the number of clock cycles after which a transmission of one samples is started 
	 */
  void begin(uint32_t samplingRate, uint8_t frameLength = 32, uint8_t dataDelay = 1, uint8_t dataBits = 16);

  /**
	 * @brief Ends I2S communication with default configuration. 
	 */
  void end();

  /**
	 * @brief Returns the latest received sample. 
	 */
  int peek();

  /**
	 * @brief Copies samples into an int array.
   * @param readBuffer the user-defined buffer of integers.  
   * @param readSize number of samples that should be copied into the buffer. Must be smaller than the buffer's length
	 */
  void read(int16_t *readBuffer, uint16_t readSize);

  /**
   * @brief Enables master clock output signal with a fixed phase relation to the shift clock to support oversampling for audio components.
   * */
  void enableMasterClock();

  /**
	 * @brief Returns the number of samples in buffer available for read.
	 */
  uint16_t available();

  /**
	 * @brief Read in one sample on rising/falling edge of WA signal.
	 */
  void onSampleReceived();

  /**
   * @brief Reduces the sampling frequency by half; this function can be used to sample at below the lowest frequency of the microphone.
   */
  void downScaleByTwo();
  
#if (UC_FAMILY == XMC4)
  /**
   * @brief Configures the interrupt generated when the buffer for audio samples is full.
   * 
   * @param callback the callback where data processing happens.
   */
  void configureInterrupt(interrupt_cb_t callback);

  /**
   * @brief Wrapper function for custom callback. Toggles the _inDmaInProgress flag.
   * 
   */
  static void dmaCallback();
#endif
};
extern XMCI2SClass I2S;
#endif /* I2S_h */
