/*
  pins_arduino.h - Pin definition functions for Arduino
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
  
  Copyright (c) 2018 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
*/

#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

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

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
   const uint8_t mapping_pin_PWM4[][ 2 ] = {
            { 3, 0 },
            { 4, 1 },
            { 6, 2 },
            { 9, 3 },
            { 255, 255 } };

	const uint8_t mapping_pin_PWM8[][ 2 ] = { { 255, 255 } };


// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)

// These mappings look more like XMC1100 Boot Kit mappings
// Has 6 Analog inputs defined but apparently NUM_ANALOG_INPUTS is 2

const XMC_PORT_PIN_t mapping_port_pin[] = {
	/* 0  */ 	{XMC_GPIO_PORT1, 2},  // PIN_RX / LED output	 			P1.2
	/* 1  */ 	{XMC_GPIO_PORT1 ,3},  // PIN_TX / LED output	  			P1.3
	/* 2  */ 	{XMC_GPIO_PORT1 ,4},  // External interrupt/ LED output		P1.4
	/* 3  */ 	{XMC_GPIO_PORT0 ,0},  // External interrupt/ PWM output  	P0.0
	/* 4  */ 	{XMC_GPIO_PORT0 ,1},  // PWM output 						P0.1
	/* 5  */ 	{XMC_GPIO_PORT0 ,2},  // GPIO								P0.2
	/* 6  */ 	{XMC_GPIO_PORT0 ,3},  // PWM output							P0.3
	/* 7  */ 	{XMC_GPIO_PORT0 ,4},  // GPIO								P0.4
	/* 8  */ 	{XMC_GPIO_PORT0 ,12}, // GPIO								P0.12 
	/* 9  */ 	{XMC_GPIO_PORT0 ,8},  // PWM output							P0.8
	/* 10  */ 	{XMC_GPIO_PORT0 ,9},  // SPI-SS								P0.9
	/* 11  */ 	{XMC_GPIO_PORT1 ,1},  // SPI-MOSI							P1.1
	/* 12  */ 	{XMC_GPIO_PORT1 ,0},  // SPI-MISO							P1.0
	/* 13  */ 	{XMC_GPIO_PORT0 ,7},  // SPI-SCK / LED output				P0.7
	/* 14  */ 	{XMC_GPIO_PORT2 ,3},  // AREF								P2.3 (INPUT ONLY)
	/* 15  */ 	{XMC_GPIO_PORT2 ,1},  // I2C Data / Address SDA				P2.1
	/* 16  */ 	{XMC_GPIO_PORT2 ,0},  // I2C Clock SCL						P2.0
	/* 17  */ 	{XMC_GPIO_PORT2 ,6},  // A0 / ADC Input 					P2.6 (INPUT ONLY)
	/* 18  */ 	{XMC_GPIO_PORT2 ,8},  // A1 / ADC Input 					P2.8 (INPUT ONLY)
	/* 19  */ 	{XMC_GPIO_PORT2 ,9},  // A2 / ADC Input						P2.9 (INPUT ONLY)
	/* 20  */ 	{XMC_GPIO_PORT2 ,10}, // A3 / ADC Input						P2.10
	/* 21  */ 	{XMC_GPIO_PORT2 ,11}, // A4 / ADC Input						P2.11
	/* 22  */ 	{XMC_GPIO_PORT2 ,2},  // A5 / ADC Input						P2.2 (INPUT ONLY)
	/* 23  */ 	{XMC_GPIO_PORT2 ,4},  // SPI_SS_2							P2.4 (INPUT ONLY)
	/* 24  */ 	{XMC_GPIO_PORT2 ,5},  // AD_AUX 	                    	P2.5 (INPUT ONLY)
	/* 25  */ 	{XMC_GPIO_PORT2 ,7},  // AD_AUX 	                    	P2.7 (INPUT ONLY)
	/* 26  */ 	{XMC_GPIO_PORT0 ,5},  // AUX / GPIO / LED output			P0.5
	/* 27  */ 	{XMC_GPIO_PORT0 ,6},  // AUX / GPIO / LED output 			P0.6
	/* 28  */ 	{XMC_GPIO_PORT0 ,10}, // AUX / GPIO							P0.10
	/* 29  */ 	{XMC_GPIO_PORT0 ,11}, // AUX / GPIO							P0.11
	/* 30  */ 	{XMC_GPIO_PORT0 ,13}, // AUX / GPIO							P0.13
	/* 31  */ 	{XMC_GPIO_PORT1 ,5}   // LED output							P1.5
    };

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
	/* 0  */ 	{CCU40, CCU40_CC40, 0, 0, CCU40_IN0_U0C0_DX2INS}, 
	/* 1  */ 	{CCU40, CCU40_CC40, 0, 1, CCU40_IN0_P0_0} 
    };

XMC_PWM4_t mapping_pwm4[] = {
	{CCU40, CCU40_CC40, 0, mapping_port_pin[3], P0_0_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled	3	P0.0
	{CCU40, CCU40_CC41, 1, mapping_port_pin[4], P0_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled	4	P0.1
	{CCU40, CCU40_CC43, 3, mapping_port_pin[6], P0_3_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled	6	P0.3
	{CCU40, CCU40_CC42, 2, mapping_port_pin[9], P0_8_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}   // PWM disabled	9	P0.8
    };

XMC_PWM8_t mapping_pwm8[1];

XMC_ADC_t mapping_adc[] = {
	{VADC, 2, VADC_G0, 0, 10, DISABLED},			// CH_I
	{VADC, 4, VADC_G0, 0, 11, DISABLED}				// CH_Q
    };
 
/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

XMC_UART_t XMC_UART_0 =
{
  .channel 				= XMC_UART0_CH0,
  .rx 					= {	.port = (XMC_GPIO_PORT_t *)PORT2_BASE,
							.pin  = (uint8_t)6
							},
  .rx_config			= { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
							.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
							.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
							},
  .tx 					= {	.port = (XMC_GPIO_PORT_t *)PORT2_BASE,
							.pin  = (uint8_t)0
							},
  .tx_config			= { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
							.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
							.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
							},
  .input_source_dx0		= (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
  .input_source_dx1		= XMC_INPUT_INVALID,
  .input_source_dx2		= XMC_INPUT_INVALID,
  .input_source_dx3		= (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_6,
  .irq_num				= USIC0_0_IRQn,	
  .irq_service_request	= 0
};	

HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );
#endif

#endif
