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
#include <XMC1400.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define XMC_BOARD           XMC1400 Boot Kit
#define NUM_ANALOG_INPUTS   6
#define NUM_PWM             4
#define NUM_LEDS            4
#define NUM_INTERRUPT       2
#define NUM_SERIAL          1
#define NUM_TONE_PINS       4
#define NUM_TASKS_VARIANT   8

// Defines will be either set by ArduinoIDE in the menu or manually
#ifdef SERIAL_HOSTPC
// Comment out following line to use Serial on pins (board)
#define SERIAL_DEBUG    1
#elif SERIAL_ONBOARD
// No SERIAL_DEBUG will be defined, kept here for clarity
#else
// Define the SERIAL_DEBUG as default setting
#define SERIAL_DEBUG    1
#endif

#define PWM4_TIMER_PERIOD (2041U)  // Generate 490Hz @fCCU=1MHz

#define PCLK 48000000u 
 
#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

#define A0   0
#define A1   1
#define A2   2
#define A3   3
#define A4   4
#define A5   5

#define LED_BUILTIN LED1  
#define LED1        24  
#define LED2        25  
#define LED3        26   
#define LED4        27   

#define EXT_INTR_0  2
#define EXT_INTR_1  3

#define GND 30  // non-existing
#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

/* Mapping interrupt handlers. Notice that XMC1400 can have interrupt handlers working in 3 modes, the defines below assues the mode A.
   For details refer to assembly file and reference manual.
*/
// #define USIC0_0_IRQHandler IRQ9_Handler // UART
#define USIC0_0_IRQn IRQ9_IRQn

#define CCU40_0_IRQHandler IRQ21_Handler // interrupt 0 
#define CCU40_0_IRQn IRQ21_IRQn 

#define CCU40_1_IRQHandler IRQ22_Handler // interrupt 1 
#define CCU40_1_IRQn IRQ22_IRQn

#define USIC0_4_IRQHandler IRQ13_Handler // I2C
#define USIC0_4_IRQn IRQ13_IRQn 

#define USIC0_5_IRQHandler IRQ14_Handler // I2C
#define USIC0_5_IRQn IRQ14_IRQn 

#endif
