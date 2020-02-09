/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef HardwareSerial_h
#define HardwareSerial_h

//****************************************************************************
// @External Prototypes
//****************************************************************************
#ifdef __cplusplus

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "RingBuffer.h"
#include "Stream.h"

//****************************************************************************
// @Typedefs
//****************************************************************************
typedef enum XMC_UART_MODE
{
    SERIAL_5N1 = 0x15 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_6N1 = 0x16 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_7N1 = 0x17 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_8N1 = 0x18 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_5N2 = 0x25 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_6N2 = 0x26 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_7N2 = 0x27 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_8N2 = 0x28 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_5E1 = 0x15 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_6E1 = 0x16 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_7E1 = 0x17 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_8E1 = 0x18 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_5E2 = 0x25 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_6E2 = 0x26 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_7E2 = 0x27 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_8E2 = 0x28 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_5O1 = 0x15 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_6O1 = 0x16 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_7O1 = 0x17 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_8O1 = 0x18 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_5O2 = 0x25 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_6O2 = 0x26 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_7O2 = 0x27 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_8O2 = 0x28 | XMC_USIC_CH_PARITY_MODE_ODD
} XMC_UART_MODE_t;

//****************************************************************************
// @Class Definitions
//****************************************************************************
class HardwareSerial: public Stream
{
public:
    XMC_UART_t* _XMC_UART_config;
	
    HardwareSerial(XMC_UART_t* xmc_uart_config, RingBuffer* rx_buffer, RingBuffer* tx_buffer);
	
    void begin( uint32_t speed);
    void begin( uint32_t speed, XMC_UART_MODE_t config);
    void end(void);
    int available(void);
    int availableForWrite(void);
    int peek(void);
    void flush(void);
    int read(void);

    //virtual size_t readBytes(char *buffer, size_t length) ; // read chars from stream into buffer
    //virtual size_t readBytes(uint8_t *buffer, size_t length) ;

    size_t write(const uint8_t);
    //virtual size_t write(const uint8_t *buffer, size_t size) ;
    inline size_t write(unsigned long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(unsigned int n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(int n)
    {
        return write((uint8_t)n);
    }

    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool()
    {
        return true;
    }

    void setInterruptPriority(uint32_t priority);
    uint32_t getInterruptPriority();

    void IrqHandler(void);

private:
    RingBuffer* _rx_buffer;
    RingBuffer* _tx_buffer;
};
#endif  /* cplusplus */

#endif /* HardwareSerial_h */
