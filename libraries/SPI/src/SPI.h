/*
 * SPI Master library.
 * Copyright (c) 2015 Arduino LLC
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
 * Copyright (c) 2018 Infineon Technologies AG
 * This library has been modified for the XMC microcontroller series.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <Arduino.h>

//****************************************************************************
// @Defines
//****************************************************************************
// Define USE_SW_SPI to use the software SPI(not verified)
//#define USE_SW_SPI

// Define USE_XMC_RELAX_KIT_SD allows to use the SD Lib to communicate with a SD Card over
// the on-board SD Card Slot
//#define USE_XMC_RELAX_KIT_SD

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

#define SPI_IMODE_NONE 0x00

#define MSBFIRST 0x00
#define LSBFIRST 0x01

#define ARDUINO_SPI_CLOCK 16000000U

#define SPI_CLOCK_DIV2   2
#define SPI_CLOCK_DIV4   4
#define SPI_CLOCK_DIV8   8
#define SPI_CLOCK_DIV16  16
#define SPI_CLOCK_DIV32  32
#define SPI_CLOCK_DIV64  64
#define SPI_CLOCK_DIV128 128


#if !defined(USE_SW_SPI)
#include "utility/xmc_spi_conf.h"
#else
#include "utility/SW_SPI.h"
#endif

//#define pin_cs 	10
//
//#if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
//#define pin_cs  3

//#elif defined(XMC4400_Platform2GO)
///#define pin_cs_slot_1  95
//#define pin_cs_slot_2  96

//#endif

//****************************************************************************
// @Class Definitions
//****************************************************************************
class SPISettings
{
public:
    SPISettings(uint32_t cF, uint8_t bO, uint8_t dM)
    {
        clockFreq   = cF;
        bitOrder    = bO;
        dataMode    = dM;
    }

    SPISettings()
    {
        clockFreq   = 4000000;
        bitOrder    = MSBFIRST;
        dataMode    = SPI_MODE0;
    }

    uint32_t clockFreq;
    uint8_t bitOrder;
    uint8_t dataMode;
};

class SPIClass
{
public:

// Constructors for HW SPI
#if !defined(USE_SW_SPI)
    SPIClass()
    {
        // default SPI
        XMC_SPI_config = &XMC_SPI_default;
    }

    SPIClass(XMC_SPI_t* conf)
    {
        XMC_SPI_config = conf;
    }

// Constructors for SW SPI
#else
    SPIClass()
    {
        // default SPI
        spi_settings = SPISettings();

        mosi_pin = MOSI;
        miso_pin = MISO;
        clk_pin = SCK;
    }

    SPIClass(SPISettings settings)
    {
        spi_settings = settings;

        mosi_pin = MOSI;
        miso_pin = MISO;
        clk_pin = SCK;
    }


    SPIClass(SPISettings settings, uint8_t mosi, uint8_t miso, uint8_t sck)
    {
        spi_settings = settings;

        mosi_pin = mosi;
        miso_pin = miso;
        clk_pin = sck;
    }
#endif

    uint8_t transfer(uint8_t data);
    inline uint16_t transfer16(uint16_t data);
    inline void transfer(uint8_t* buf, uint8_t count);

    // Transaction Functions
    // Function not used here
    //void usingInterrupt(int interruptNumber);
    void beginTransaction(SPISettings settings);
    void endTransaction(void);

    // SPI Configuration methods
    void attachInterrupt();
    void detachInterrupt();

    static void usingInterrupt(uint8_t interruptNumber){};
    static void notUsingInterrupt(uint8_t interruptNumber){};

    void begin();
    void end();

    void setBitOrder(uint8_t order);
    void setDataMode(uint8_t mode);
    void setClockDivider(uint8_t div);

private:
    void init();
// Config for HW SPI
#if !defined(USE_SW_SPI)

    XMC_SPI_t* XMC_SPI_config;

// Config for SW SPI
#else
    uint8_t mosi_pin;
    uint8_t miso_pin;
    uint8_t clk_pin;

    SPISettings spi_settings;
#endif

    bool initialized;
    uint8_t interruptMode;
    char interruptSave;
    uint32_t interruptMask;
};

extern SPIClass SPI;
#if (NUM_SPI > 1)
	extern SPIClass SPI1;
#	if (NUM_SPI > 2)
		extern SPIClass SPI2;
#		if (NUM_SPI > 3)
			extern SPIClass SPI3;
#			if (NUM_SPI > 4)
				extern SPIClass SPI4;
#			endif
#		endif
#	endif
#endif

void SPIClass::transfer(uint8_t *buf, uint8_t count)
{
    uint8_t buf_in[count];
    for (uint8_t i = 0; i < count; i++)
    {
        buf_in[i] = transfer(buf[i]);
    }
    buf = buf_in;
}

uint16_t SPIClass::transfer16(uint16_t data)
{
    uint8_t data_out_msb = (uint8_t)((data >> 8) & 0xFF);
    uint8_t data_out_lsb = (uint8_t)(data & 0xFF);

    uint8_t data_in_msb = transfer(data_out_msb);
    uint8_t data_in_lsb = transfer(data_out_lsb);

    return (uint16_t)(((uint16_t)data_in_msb << 8) | (data_in_lsb));
}

#endif /* _SPI_H_INCLUDED */
