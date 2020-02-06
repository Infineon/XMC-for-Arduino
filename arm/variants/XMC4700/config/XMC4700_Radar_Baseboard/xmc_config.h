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
#define XMC_BOARD           DEMO Radar BB XMC4700
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define XMC_LED_ON          0
// Pins that are allocated or free to be used as Analog input
#define NUM_ANALOG_INPUTS   6 
#define NUM_PWM             6
#define NUM_LEDS            0
#define NUM_INTERRUPT       2
#define NUM_SERIAL          1
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

#define PIN_SPI_SS_SD    26
#define PIN_SPI_MOSI_SD  27
#define PIN_SPI_MISO_SD  28
#define PIN_SPI_SCK_SD   29

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

#define LED_RED     22  // LED Red channel
#define LED_GREEN   23  // LED Green channel
#define LED_BLUE    24  // LED Blue channel
#define BUTTON1     25  // Additional BUTTON1
#define GND         39  // GND

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 32 ? 1 : NOT_AN_INTERRUPT))

#endif
