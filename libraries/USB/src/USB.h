/*
  USB.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/**
 * @brief USB 
 * @bug clearBuffer() function cannot be called in a task on its own. Something else must also (not clear what) must also be called in the task
 */

#ifndef USB_h
#define USB_h

#include "Arduino.h"
#include "util/VirtualSerial.h"
#define USB_RX_BUFFER_SIZE SERIAL_BUFFER_SIZE
// a larger buffer is suitable for storing processed sensor data, e.g. fft results
#define USB_TX_BUFFER_SIZE SERIAL_BUFFER_SIZE

#define FLOAT_BYTES 4


union {
	float float_val;
	char byte_array[FLOAT_BYTES];
} float_to_bytes;


class USBClass
{

  private:
	const XMC_SCU_CLOCK_CONFIG_t clock_configuration;
	uint32_t baudrate;
	void init(uint32_t baudrate);
	void setupClock();

	RingBuffer *_rx_buffer;
	RingBuffer *_tx_buffer;

  public:
	USBClass();
	USBClass(const XMC_SCU_CLOCK_CONFIG_t _clk_config);
	void begin(void); // begins with  baud rate 9600
	void begin(uint32_t _baudrate);
	void end(void);

	void writeToBuffer(const uint8_t uc_data);
	void writeToBuffer(const char uc_data);
	void writeToBuffer(const float val, uint8_t delimiter = ',');
	void clearTxBuffer();
	void write(const char *const String);					  // send string
	void write(const uint8_t *Buffer, const uint16_t Length); //sent buffer
	void write(const uint8_t Data);							  // send byte

	bool available();
	int read();

	void flush();

	// TODO:  transfer file; manage break sent;

	void IrqHandler(void);
};
extern USBClass USB;
#endif
