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
#include <XMC1300.h>
//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between 
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD           XMC 1300 Sense2GoL
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define  XMC_LED_ON         0

#define NUM_ANALOG_INPUTS 	2
#define NUM_PWM 			4
#define NUM_LEDS 			3
#define NUM_INTERRUPT 		2
#define NUM_SERIAL 			1
// Following could be 4 unless add/delete task has issues
#define NUM_TONE_PINS       0
#define NUM_TASKS_VARIANT   8

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

#define PWM4_TIMER_PERIOD (2041U)  // Generate 490Hz @fCCU=1MHz

#define PCLK 64000000u 
 
#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

extern uint8_t SS; 
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define PIN_AREF      14

#define A0   0
#define A1   1

// These 2 lines should be defined in higher level or examples
#define CH_I A0
#define CH_Q A1
// These 2 lines should also be defined at higher level
// TX_ON defined but only used in .h file to set BGT24LTR11_TX_ON_PIN that is NEVER used
//#define TX_ON 3
#define BGT_ON 27

#define PIN_SPI_SS_2	23

#define AD_AUX_1	24	// AD_AUX
#define AD_AUX_2	25	// AD_AUX
#define AUX_1	26	// AUX
#define AUX_2	27	// AUX
#define AUX_3	28	// AUX
#define AUX_4	29	// AUX
#define AUX_5	30	// AUX

#define LED_BUILTIN 10 // Standard Arduino LED
#define LED1	10  // Extended LEDs P0.7
#define LED2	13	// Extended LEDs P0.9
#define LED3	26	// Extended LEDs P0.5
#define GND		32	// GND

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#endif
