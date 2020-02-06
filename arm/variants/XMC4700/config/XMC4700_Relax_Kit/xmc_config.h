/*
  xmc_config.h - Variant specific definitions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  
  Copyright (c) 2020 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
*/
#ifndef XMC_CONFIG_H_
#define XMC_CONFIG_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <XMC4700.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between 
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD           XMC 4700 Relax Kit
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define  XMC_LED_ON         0

#define NUM_ANALOG_INPUTS   22
#define NUM_PWM             23
#define NUM_LEDS            2
#define NUM_INTERRUPT       2
#define NUM_SERIAL          2
#define NUM_TONE_PINS       16
#define NUM_TASKS_VARIANT   32

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

// Board has two serial ports pre-assigned to debug and on-board

#define PWM4_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz

#define PCLK 64000000u 
 
#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

extern uint8_t SS; 
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define PIN_SPI_SS_SD    28
#define PIN_SPI_MOSI_SD  29
#define PIN_SPI_MISO_SD  30
#define PIN_SPI_SCK_SD   31

static const uint8_t SS_SD   = PIN_SPI_SS_SD;
static const uint8_t MOSI_SD = PIN_SPI_MOSI_SD;
static const uint8_t MISO_SD = PIN_SPI_MISO_SD;
static const uint8_t SCK_SD  = PIN_SPI_SCK_SD;

#define A0   0
#define A1   1
#define A2   2
#define A3   3
#define A4   4
#define A5   5
//Additional ADC ports starting here
#define A6	 6		// ADC G2CH6 on P15.6
#define A7	 7		// ADC G2CH5 on P15.5
#define A8	 8		// ADC G2CH3 on P15.3
#define A9	 9		// ADC G1CH7 on P14.15
#define A10	 10		// ADC G1CH5 on P14.13
#define A11	 11		// ADC G0CH7 on P14.7
#define A12	 12		// ADC G3CH7 on P15.15
#define A13	 13		// ADC G1CH1 on P14.9
#define A14	 14		// ADC G1CH0 on P14.8
#define A15	 15		// ADC G3CH6 on P15.14
#define A16	 16		// ADC G0CH6 on P14.6
#define A17	 17		// ADC G1CH4 on P14.12
#define A18	 18		// ADC G1CH6 on P14.14
#define A19	 19		// ADC G2CH2 on P15.2
#define A20	 20		// ADC G2CH4 on P15.4
#define A21	 21		// ADC G2CH7 on P15.7
// ADC G3CH0 on P15.8	not available
// ADC G3CH1 on P15.9	not available
// ADC G3CH4 on P15.12	button
// ADC G3CH5 on P15.13	button


#define LED_BUILTIN 24  //Standard Arduino LED: Used LED1
#define LED1        24  // Additional LED1
#define LED2        25  // Additional LED2
#define BUTTON1     26  // Additional BUTTON1
#define BUTTON2     27  // Additional BUTTON2
#define GND         50  // GND

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#endif
