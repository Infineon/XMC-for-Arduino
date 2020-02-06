/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public<
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

#include <xmc_config.h>

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][ 2 ] = {
                                        { 31, 0 },
                                        { 26, 1 },
                                        { 255, 255 } };

const uint8_t mapping_pin_PWM8[][ 2 ] = {
                                        { 32, 0 },
                                        { 33, 1 },
                                        { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
	/* 0  */ 	{ XMC_GPIO_PORT2, 4 },  // A0 / ADC Input 					P2.4    (INPUT ONLY)
	/* 1  */ 	{ XMC_GPIO_PORT2, 5 },  // A1 / ADC Input 					P2.5    (INPUT ONLY)
	/* 2  */ 	{ XMC_GPIO_PORT2, 6 },  // A2 / ADC Input					P2.6    (INPUT ONLY)
	/* 3  */ 	{ XMC_GPIO_PORT2, 7 },  // A3 / ADC Input					P2.7    (INPUT ONLY)
	/* 4  */ 	{ XMC_GPIO_PORT2, 8 },  // A4 / ADC Input					P2.8    (INPUT ONLY)
	/* 5  */ 	{ XMC_GPIO_PORT2, 9 },  // A5 / ADC Input					P2.9    (INPUT ONLY)
	/* 6  */ 	{ XMC_GPIO_PORT2, 10 }, // GPIO / A6 ADC Input				P2.10
	/* 7  */ 	{ XMC_GPIO_PORT2, 11 }, // GPIO / A7 ADC Input				P2.11
	/* 8  */ 	{ XMC_GPIO_PORT2, 2 },  // GPIO / A9 ADC Input				P2.2    (INPUT ONLY)
	/* 9  */ 	{ XMC_GPIO_PORT2, 3 },  // GPIO / A8 ADC Input				P2.3    (INPUT ONLY)
	/* 10  */ 	{ XMC_GPIO_PORT2, 0 },  // I2C Clock SCL / A11 ADC Input	P2.0
	/* 11  */ 	{ XMC_GPIO_PORT2, 1 },  // I2C Data  SDA / A10 ADC Input    P2.1
	/* 12  */ 	{ XMC_GPIO_PORT0, 14 }, // GPIO								P0.14
	/* 13  */ 	{ XMC_GPIO_PORT0, 15 }, // GPIO								P0.15
	/* 14  */ 	{ XMC_GPIO_PORT0, 12 }, // External interrupt	0			P0.12
	/* 15  */ 	{ XMC_GPIO_PORT0, 13 }, // External interrupt	1			P0.13
	/* 16  */ 	{ XMC_GPIO_PORT0, 10 }, // GPIO								P0.10
	/* 17  */ 	{ XMC_GPIO_PORT0, 11 }, // GPIO								P0.11
	/* 18  */ 	{ XMC_GPIO_PORT1, 5 },  // GPIO								P1.5
	/* 19  */ 	{ XMC_GPIO_PORT1, 4 },  // GPIO								P1.4
	/* 20  */ 	{ XMC_GPIO_PORT1, 3 },  // TX 	    			  			P1.3
	/* 21  */ 	{ XMC_GPIO_PORT1, 2 },  // RX     	 						P1.2
	/* 22  */ 	{ XMC_GPIO_PORT1, 1 },  // SPI-MOSI							P1.1
	/* 23  */ 	{ XMC_GPIO_PORT1, 0 },  // SPI-MIS0							P1.0
	/* 24  */ 	{ XMC_GPIO_PORT0, 0 },  // LED output	(BUILTIN)   LED1	P0.0
	/* 25  */ 	{ XMC_GPIO_PORT0, 1 },  // LED output	            LED2	P0.1
	/* 26  */ 	{ XMC_GPIO_PORT0, 2 },  // PWM (PWM4 slice 1)				P0.2
	/* 27  */ 	{ XMC_GPIO_PORT0, 8 },  // LED output	    	    LED5	P0.8
	/* 28  */ 	{ XMC_GPIO_PORT0, 9 },  // LED output		        LED6	P0.9
	/* 29  */ 	{ XMC_GPIO_PORT0, 6 },  // SPI-SS / LED output      LED3   	P0.6
	/* 30  */ 	{ XMC_GPIO_PORT0, 7 },  // SPI-SCK / LED output     LED4	P0.7
	/* 31  */ 	{ XMC_GPIO_PORT0, 4 },  // PWM (PWM4 slice 0)				P0.4
	/* 32  */ 	{ XMC_GPIO_PORT0, 5 },  // PWM (PWM8 slice 0)				P0.5
	/* 33  */ 	{ XMC_GPIO_PORT0, 3 }   // PWM (PWM8 slice 1)			    P0.3
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    { CCU40, CCU40_CC40, 0, 0, CCU40_IN0_P0_12 },
    /* 1  */    { CCU40, CCU40_CC40, 0, 1, CCU40_IN0_U0C0_DX2INS }
};

XMC_PWM4_t mapping_pwm4[] =
{
    { CCU40, CCU40_CC41, 1, mapping_port_pin[ 31 ], P0_4_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED }, // PWM disabled  31  P0.4
    { CCU40, CCU40_CC42, 2, mapping_port_pin[ 26 ], P0_2_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED }  // PWM disabled  26  P0.2
};

XMC_PWM8_t mapping_pwm8[] =
{
    { CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[ 32 ], P0_5_AF_CCU80_OUT12, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED },  // PWM disabled  32   P0.5
    { CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[ 33 ], P0_3_AF_CCU80_OUT03, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED }   // PWM disabled  33   P0.3
};

XMC_ADC_t mapping_adc[] =
{
    { VADC, 6, VADC_G1, 1, 4, DISABLED },
    { VADC, 7, VADC_G1, 1, 11, DISABLED },
    { VADC, 0, VADC_G0, 0, 9, DISABLED },
    { VADC, 1, VADC_G1, 1, 12, DISABLED },
    { VADC, 1, VADC_G0, 0, 10, DISABLED },
    { VADC, 2, VADC_G0, 0, 7, DISABLED },
    // Additional channels added here
    { VADC, 3, VADC_G0, 0, 5, DISABLED },
    { VADC, 4, VADC_G0, 0, 1, DISABLED },
    { VADC, 5, VADC_G1, 1, 2, DISABLED },
    { VADC, 7, VADC_G0, 0, 3, DISABLED },
    { VADC, 6, VADC_G0, 0, 6, DISABLED },
    { VADC, 5, VADC_G0, 0, 8, DISABLED }
};

/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

/* First UART channel pins are swapped between debug and  normal use */
XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART0_CH1,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
#ifdef SERIAL_DEBUG
                            .pin  = (uint8_t)3
#else
                            .pin  = (uint8_t)2
#endif
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
#ifdef SERIAL_DEBUG
                            .pin  = (uint8_t)2
#else
                            .pin  = (uint8_t)3
#endif
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
                            .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
#ifdef SERIAL_DEBUG
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C1_DX0_P1_3,
#else
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_P1_2,
#endif
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC0_0_IRQn,
  .irq_service_request  = 0
  };

HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );

#endif

#endif
