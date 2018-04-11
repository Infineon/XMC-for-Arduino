/*
 * TwoWire.h - TWI/I2C library for Arduino & Wiring
 * Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * This library has been modified for the XMC microcontroller series.
*/

#ifndef TwoWire_h
#define TwoWire_h

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <Arduino.h>
#include "utility/xmc_i2c_conf.h"

//****************************************************************************
// @Defines
//****************************************************************************
#define BUFFER_LENGTH 32
// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1

#define WIRE_COMMUNICATION_TIMEOUT 5000u

//****************************************************************************
// @Class Definitions
//****************************************************************************
class TwoWire : public Stream
{
private:
    XMC_I2C_t* XMC_I2C_config;

    bool isMaster;
    bool inRepStart;
    uint8_t transmitting;
    uint16_t timeout;

    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    uint8_t slaveAddress;
    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferIndex;
    uint8_t txBufferLength;

    uint8_t pre_rxBuffer[BUFFER_LENGTH];
    uint8_t pre_rxBufferCount;
	
    void (*user_onRequest)(void);
    void (*user_onReceive)(int);
    void OnRequestService(void);
    void OnReceiveService(uint8_t*, uint8_t);
public:
	bool volatile hasError;
	TwoWire(XMC_I2C_t *conf);
    void begin();
    void begin(uint8_t);
    void begin(int);
    void end();
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t*, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive( void (*)(int) );
    void onRequest( void (*)(void) );
    void ReceiveHandler(void);
    void ProtocolHandler(void);

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
    using Print::write;
};

extern TwoWire Wire;
#if (NUM_I2C > 1)
	extern TwoWire Wire1;
#	if (NUM_I2C > 2)
		extern TwoWire Wire2;
#		if (NUM_I2C > 3)
			extern TwoWire Wire3;
#			if (NUM_I2C > 4)
				extern TwoWire Wire4;
#			endif
#		endif
#	endif
#endif

#endif /* TwoWire_h */

