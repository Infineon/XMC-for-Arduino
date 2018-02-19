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
*/
#include <XMC4800.h>
#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************


//****************************************************************************
// @Defines
//****************************************************************************

#define NUM_DIGITAL_PINS 18
#define NUM_ANALOG_INPUTS 6
#define NUM_PWM 6
#define NUM_LEDS 2
#define NUM_INTERRUPT 2
#define NUM_SERIAL 2

// Board has two serial ports pre-assigned to debug and on-board

#define PWM4_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz

#define PCLK 144000000u

#define PIN_RX   	  (0)
#define PIN_TX  	  (1)
#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

#define PIN_SPI_SS_SD    (28)
#define PIN_SPI_MOSI_SD  (29)
#define PIN_SPI_MISO_SD  (30)
#define PIN_SPI_SCK_SD   (31)

#define PIN_AREF            (14)
#define PIN_WIRE_SDA        (15)
#define PIN_WIRE_SCL        (16)

static const uint8_t RX   = 0;
static const uint8_t TX   = 1;

static const uint8_t SS   = 10;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 12;
static const uint8_t SCK  = 13;

static const uint8_t SDA = 14;
static const uint8_t SCL = 15;

#define A0   16
#define A1   17
#define A2   18
#define A3   19
#define A4   20
#define A5   21

#define LED_BUILTIN		13	// Standard Arduino LED 
#define LED1	24	// Additional LED1
#define LED2	25 	// Additional LED2
#define BUTTON1	26	// Additional BUTTON1
#define BUTTON2	27 	// Additional BUTTON2
#define GND		50	// GND


#define digitalPinToPCICR(p)        (((p) >= 0 && (p) <= 21) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p)     (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)        (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p)     (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))
#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))
#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 14 : -1)
#define isanalogPin(p)        		(((p == A0) || (p == A1) || (p == A2) || (p == A3) || (p == A4) || (p == A5)) ? 1 : 0)
#define analogPinToADCNum(p)		((p == A0) ? (0) :  (p == A1) ? (1) : (p == A2) ? (2) : (p == A3) ? (3) : (p == A4) ? (4) : (p == A5) ? (5) : -1)
#define digitalPinHasPWM4(p)        ((p) == 3) ||  ((p) == 10) || ((p) == 11)
#define digitalPinHasPWM8(p)		((p) == 5) || ((p) == 6) ||  ((p) == 9)
#define digitalPinToPWM4Num(p)      (((p) == 3) ? (0) : ((p) == 10) ? (1) : ((p) == 11) ? (2) : -1 )
#define digitalPinToPWM8Num(p)      (((p) == 5) ? (0) : ((p) == 6) ? (1) : ((p) == 9) ? (2) : -1 )

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)

const XMC_PORT_PIN_t mapping_port_pin[] = {
	/* 0  */ 	{XMC_GPIO_PORT2, 15}, // PIN_RX								
	/* 1  */ 	{XMC_GPIO_PORT2 ,14}, // PIN_TX			  					
	/* 2  */ 	{XMC_GPIO_PORT1 ,0},  // GPIO / External INT 0								
	/* 3  */ 	{XMC_GPIO_PORT1 ,1},  // PWM output / External INT 1					
	/* 4  */ 	{XMC_GPIO_PORT1 ,8},  // GPIO							
	/* 5  */ 	{XMC_GPIO_PORT2 ,12}, // PWM output 							
	/* 6  */ 	{XMC_GPIO_PORT2 ,11}, // PWM output							
	/* 7  */ 	{XMC_GPIO_PORT1 ,9},  // GPIO								
	/* 8  */ 	{XMC_GPIO_PORT1 ,10}, // GPIO								 
	/* 9  */ 	{XMC_GPIO_PORT1 ,11}, // PWM output							
	/* 10  */ 	{XMC_GPIO_PORT3 ,10}, // SPI-SS	/ PWM output		// TODO: SPI_SS_1				
	/* 11  */ 	{XMC_GPIO_PORT3 ,8},  // SPI-MOSI / PWM output						
	/* 12  */ 	{XMC_GPIO_PORT3 ,7},  // SPI-MISO							
	/* 13  */ 	{XMC_GPIO_PORT3 ,9},  // SPI-SCK 	
	/* 14  */ 	{XMC_GPIO_PORT2 ,3},  // AREF TODO:
	/* 15  */ 	{XMC_GPIO_PORT3 ,15}, // I2C Data / Address SDA	
	/* 16  */ 	{XMC_GPIO_PORT0 ,13}, // I2C Clock SCL			
	/* 17  */ 	{XMC_GPIO_PORT14 ,0}, // A0 / ADC Input 		
	/* 18  */ 	{XMC_GPIO_PORT14 ,1}, // A1 / ADC Input 		
	/* 19  */ 	{XMC_GPIO_PORT14 ,2}, // A2 / ADC Input			
	/* 20  */ 	{XMC_GPIO_PORT14 ,3}, // A3 / ADC Input			
	/* 21  */ 	{XMC_GPIO_PORT14 ,4}, // A4 / ADC Input			
	/* 22  */ 	{XMC_GPIO_PORT14 ,5}, // A5 / ADC Input			
	/* 23  */ 	{XMC_GPIO_PORT3 ,10}, // SPI_SS_2			
	/* 24  */ 	{XMC_GPIO_PORT5 ,9},  // Additional LED1			
	/* 25  */ 	{XMC_GPIO_PORT5 ,8},  // Additional LED2								
	/* 26  */ 	{XMC_GPIO_PORT15 ,13}, // Additional BUTTON1			
	/* 27  */ 	{XMC_GPIO_PORT15 ,12}, // Additional BUTTON2		
	/* 28  */ 	{XMC_GPIO_PORT4 ,1},  // SPI_SS_3 (SD CARD)			
	/* 29  */ 	{XMC_GPIO_PORT3 ,5},  // SPI-MOSI (SD CARD)					
	/* 30  */ 	{XMC_GPIO_PORT4 ,0},  // SPI-MISO (SD CARD)							
	/* 31  */ 	{XMC_GPIO_PORT3 ,6},  // SPI-SCK  (SD CARD)					
	/* 32  */ 	{XMC_GPIO_PORT1 ,6},  // 							
	/* 33  */ 	{XMC_GPIO_PORT1 ,7},  // 					
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
	/* 0  */ 	{CCU40, CCU40_CC43, 3, 0, CCU40_IN3_P1_0}, 
	/* 1  */ 	{CCU40, CCU40_CC42, 2, 1, CCU40_IN2_P1_1}, 
};

XMC_PWM4_t mapping_pwm4[] ={
	{CCU40, CCU40_CC42, 2, mapping_port_pin[3] , P1_1_AF_CCU40_OUT2, 	DISABLED},   	// PWM disabled		3					P1.1
	{CCU41, CCU41_CC40, 0, mapping_port_pin[10], P3_10_AF_CCU41_OUT0, 	DISABLED},  	// PWM disabled		10					P3.10
	{CCU41, CCU41_CC42, 2, mapping_port_pin[11], P3_8_AF_CCU41_OUT2, 	DISABLED},   	// PWM disabled		11					P3.8
};

XMC_PWM8_t mapping_pwm8[] ={
	{CCU81, CCU81_CC83, 3,	XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[5], P2_12_AF_CCU81_OUT33, 	DISABLED},  	// PWM disabled 		5				P2.12
	{CCU80, CCU80_CC82, 2,	XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[6], P2_11_AF_CCU80_OUT22, 	DISABLED},  	// PWM disabled 		6				P2.11
	{CCU81, CCU81_CC81, 1,	XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9], P1_11_AF_CCU81_OUT11, 	DISABLED},  	// PWM disabled 		9				P1.11
};

XMC_ADC_t mapping_adc[] ={
	{VADC, 0, VADC_G0, 0, 4	, DISABLED},
	{VADC, 1, VADC_G0, 0, 15, DISABLED},
	{VADC, 2, VADC_G1, 1, 15, DISABLED},
	{VADC, 3, VADC_G1, 1, 3	, DISABLED},
	{VADC, 0, VADC_G2, 2, 1	, DISABLED},
	{VADC, 1, VADC_G2, 2, 0	, DISABLED},
};

/*
 * UART objects
 */
RingBuffer rx_buffer_debug;
RingBuffer tx_buffer_debug;
RingBuffer rx_buffer_on_board;
RingBuffer tx_buffer_on_board;

XMC_UART_t XMC_UART_debug =
{
  .channel 				= XMC_UART0_CH0,
  .rx 					= {	.port = (XMC_GPIO_PORT_t *)PORT1_BASE,
							.pin  = (uint8_t)4
							},
  .rx_config			= { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
							.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
							.output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
							},
  .tx 					= {	.port = (XMC_GPIO_PORT_t *)PORT1_BASE,
							.pin  = (uint8_t)5
						  },
  .tx_config			= { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
							.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
							.output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
						  },
  .input_source 		= (XMC_USIC_CH_INPUT_t)USIC0_C0_DX0_P1_4,
  .irq_num				= USIC0_0_IRQn,	
  .irq_service_request	= 0
};	

XMC_UART_t XMC_UART_1 =
{
  .channel 				= XMC_UART1_CH0,
  .rx 					= {	.port = (XMC_GPIO_PORT_t *)PORT2_BASE,
							.pin  = (uint8_t)15
							},
  .rx_config			= { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
							.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
							.output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
							},
  .tx 					= {	.port = (XMC_GPIO_PORT_t *)PORT2_BASE,
							.pin  = (uint8_t)14
							},
  .tx_config			= { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
							.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
							.output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
							},
  .input_source 		= (XMC_USIC_CH_INPUT_t)USIC1_C0_DX0_P2_15,
  .irq_num				= USIC1_0_IRQn,	
  .irq_service_request	= 0
};	

// Debug port
HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );
// On-board port
HardwareSerial Serial1( &XMC_UART_1, &rx_buffer_1, &tx_buffer_1 );

#endif

#endif
