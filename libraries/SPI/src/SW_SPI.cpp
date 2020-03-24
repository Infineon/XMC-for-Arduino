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

#include "SPI.h"
#if defined(USE_SW_SPI)

#define SPI_MODE_PASSIVE_HIGH   ((spi_settings.dataMode == SPI_MODE2) || (spi_settings.dataMode == SPI_MODE3))
#define SPI_MODE_DELAY_ENABLED  ((spi_settings.dataMode == SPI_MODE0) || (spi_settings.dataMode == SPI_MODE2))

SPIClass SPI;

uint8_t SS   = PIN_SPI_SS   ;
uint8_t MOSI = PIN_SPI_MOSI ;
uint8_t MISO = PIN_SPI_MISO ;
uint8_t SCK  = PIN_SPI_SCK  ;

SPISettings DEFAULT_SPI_SETTINGS;

void SPIClass::begin()
{
  init();
  
  setBitOrder(DEFAULT_SPI_SETTINGS.bitOrder);
  
  setDataMode(DEFAULT_SPI_SETTINGS.dataMode);
  
  setClockDivider(ARDUINO_SPI_CLOCK/DEFAULT_SPI_SETTINGS.clockFreq);
  
  pinMode(mosi_pin, OUTPUT);
  pinMode(miso_pin, INPUT);
  pinMode(clk_pin, OUTPUT);
}

void SPIClass::init()
{
  if (initialized)
    return;

  interruptMode = SPI_IMODE_NONE;
  interruptSave = 0;
  interruptMask = 0;
  initialized = true;
}

void SPIClass::end()
{
  initialized = false;
}

void SPIClass::usingInterrupt(int interruptNumber)
{
  // not used
}

void SPIClass::beginTransaction(SPISettings settings)
{
  setBitOrder(settings.bitOrder);
  setDataMode(settings.dataMode);
  setClockDivider(ARDUINO_SPI_CLOCK/settings.clockFreq);

  // TODO: Do sth with SS? 
}

void SPIClass::endTransaction(void)
{
	// TODO: inTransactionFlag and interrupt not use
}

void SPIClass::setBitOrder(uint8_t order)
{
    spi_settings.bitOrder = order;
}

void SPIClass::setDataMode(uint8_t mode)
{
    spi_settings.dataMode = mode;
      
    if(SPI_MODE_PASSIVE_HIGH)
    {
        digitalWrite(clk_pin, HIGH);
    }
    else 
    {
        digitalWrite(clk_pin, LOW);
    }
}

void SPIClass::setClockDivider(uint8_t div)
{ 
    spi_settings.clockFreq = ARDUINO_SPI_CLOCK / div;
}

uint8_t SPIClass::transfer(uint8_t data_out)
{
  uint8_t data_in = 0;
  bool delay = 0;
  uint32_t div = ARDUINO_SPI_CLOCK / spi_settings.clockFreq;
  if(SPI_MODE_DELAY_ENABLED)
  {
    delay = 1;
  }

  digitalWrite(SS, HIGH);
  switch(div)
  {
    case SPI_CLOCK_DIV2:                                 
      data_in = SW_SPI_transfer_clock_div_2(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);
      break;                                             
                                                         
    case SPI_CLOCK_DIV4:                                 
      data_in = SW_SPI_transfer_clock_div_4(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);
      break;                                             
                                                         
    case SPI_CLOCK_DIV8:                                      
      data_in = SW_SPI_transfer_clock_div_8(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);                          
      break;                                             
                                                         
    case SPI_CLOCK_DIV16:                                    
      //data_in = SW_SPI_transfer_clock_div_16(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);                            
      //break;                                             
                                                         
    case SPI_CLOCK_DIV32:                                    
      //data_in = SW_SPI_transfer_clock_div_32(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);                            
      //break;                                             
                                                         
    case SPI_CLOCK_DIV64:                                   
      //data_in = SW_SPI_transfer_clock_div_64(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);                             
      //break;                                             
                                                         
    case SPI_CLOCK_DIV128:                                  
      //data_in = SW_SPI_transfer_clock_div_128(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);                            
      //break;
  
    default:
      data_in = SW_SPI_transfer_clock_div_2(mosi_pin, miso_pin, clk_pin, data_out, delay, spi_settings.dataMode);
      break;
  }
  digitalWrite(SS, LOW);
  
  return data_in;
}

void SPIClass::attachInterrupt() {
  // Should be enableInterrupt()
}

void SPIClass::detachInterrupt() {
  // Should be disableInterrupt()
}

#endif
