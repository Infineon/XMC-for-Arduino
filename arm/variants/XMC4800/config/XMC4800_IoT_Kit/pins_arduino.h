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
#include <XMC4800.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between 
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD           XMC 4800 IoT Kit
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define  XMC_LED_ON         0

#define NUM_ANALOG_INPUTS   6
#define NUM_PWM             7
#define NUM_LEDS            2
#define NUM_INTERRUPT       2
#define NUM_SERIAL          3
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

#define A0   0
#define A1   1
#define A2   2
#define A3   3
#define A4   4
#define A5   5
/* //Additional ADC ports starting here
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
#define A21	 21		// ADC G2CH7 on P15.7 */
// ADC G3CH0 on P15.8	not available
// ADC G3CH1 on P15.9	not available
// ADC G3CH4 on P15.12	button
// ADC G3CH5 on P15.13	button


#define LED_BUILTIN 24  //Standard Arduino LED: Used LED1
#define LED1        23  // Additional LED1
/* #define LED2        25  // Additional LED2 */
#define BUTTON1     25  // Additional BUTTON1
/* #define BUTTON2     27  // Additional BUTTON2*/
#define GND         50  // GND 

#define digitalPinToInterrupt(p)    ((p) == 8 ? 0 : ((p) == 11 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][ 2 ] = {
                                        { 8, 0 },
                                        { 11, 1 },
                                        { 255, 255 } };
const uint8_t mapping_pin_PWM8[][ 2 ] = {
	                                    { 3, 0 },
                                        { 5, 1 },
                                        { 6, 2 },
                                        { 9, 3 },
                                        { 10, 4 },
                                        { 33, 5 },
                                        { 255, 255 } };
const uint8_t mapping_pin_DAC[][ 2 ] = {
                                        { 22, 0 },
                                        { 34, 1 },
                                        { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT0, 0},    // RX                           P0.0
    /* 1  */    {XMC_GPIO_PORT0 , 1},   // TX                           P0.1
    /* 2  */    {XMC_GPIO_PORT0 , 7},   // GPIO                         P0.7
    /* 3  */    {XMC_GPIO_PORT0 , 9},   // PWM80-1                      P0.9
    /* 4  */    {XMC_GPIO_PORT5 , 0},   // GPIO                         P5.0
    /* 5  */    {XMC_GPIO_PORT2 , 7},   // PWM80-0 output               P2.7
    /* 6  */    {XMC_GPIO_PORT2 , 9},   // PWM80-2 output               P2.9
    /* 7  */    {XMC_GPIO_PORT15 , 9},  // GPIO                         P15.9
    /* 8  */    {XMC_GPIO_PORT3 , 6},   // GPIO   /PWM42-0 output       P3.6  /External INT 0
    /* 9  */    {XMC_GPIO_PORT0 , 6},   // PWM80-3 output               P0.6 / External INT 1
    /* 10  */   {XMC_GPIO_PORT1 , 14},  // SPI-SS / PWM81-1 output      P1.14
    /* 11  */   {XMC_GPIO_PORT2 , 5},   // SPI-MOSI / PWM41-0 output    P2.5   // MikroBus_MOSI / External INT 1
    /* 12  */   {XMC_GPIO_PORT2 , 2},   // SPI-MISO / MikroBus_MISO     P2.2
    /* 13  */   {XMC_GPIO_PORT2 , 4},   // SPI-SCK /MikroBus_SCK        P2.4
    /* 14  */   {XMC_GPIO_PORT2 , 3},   // AREF TODO:                   P2.3
    /* 15  */   {XMC_GPIO_PORT1 , 5},   // I2C Data / Address SDA       P1.5
    /* 16  */   {XMC_GPIO_PORT0 , 8},   // I2C Clock SCL                P0.8
    /* 17  */   {XMC_GPIO_PORT14 , 0},  // A0 / ADC Input               P14.0 (INPUT ONLY)
    /* 18  */   {XMC_GPIO_PORT14 , 1},  // A1 / ADC Input               P14.1 (INPUT ONLY)
    /* 19  */   {XMC_GPIO_PORT14 , 2},  // A2 / ADC Input               P14.2 (INPUT ONLY)
    /* 20  */   {XMC_GPIO_PORT14 , 4},  // A3 / ADC Input               P14.4 (INPUT ONLY)
    /* 21  */   {XMC_GPIO_PORT14 , 5},  // A4 / ADC Input               P14.5 (INPUT ONLY)
    /* 22  */   {XMC_GPIO_PORT14 , 9},  // A5 / ADC Input /DAC0         P14.9 (INPUT ONLY)	
    /* 23  */   {XMC_GPIO_PORT4 , 1},   // Additional LED1              P4.1
    /* 24  */   {XMC_GPIO_PORT4 , 0},   // Additional LED2              P4.0
    /* 25  */   {XMC_GPIO_PORT3 , 4},   // Additional BUTTON1           P3.4 (INPUT ONLY)
    /* 26  */   {XMC_GPIO_PORT0 , 4},   // USB Debug RX                 P0.4
    /* 27  */   {XMC_GPIO_PORT0 , 5},   // USB Debug TX                 P0.5

	//Additional pins to control MIKROBUS starting here
	/* 28  */   {XMC_GPIO_PORT1 , 5},   // MikroBus_SDA                 P1.5
	/* 29  */   {XMC_GPIO_PORT0 , 8},   // MikroBus_SCL                 P0.8
	/* 30  */   {XMC_GPIO_PORT2 , 14},  // MikroBus_TX                  P2.14
	/* 31  */   {XMC_GPIO_PORT2 , 15},  // MikroBus_RX                  P2.15
	/* 32  */   {XMC_GPIO_PORT3 , 5},   // MikroBus_INT                 P3.5
	/* 33  */   {XMC_GPIO_PORT2 , 8},   // MikroBus_PWM / PWM80-3       P2.8
	/* 34  */   {XMC_GPIO_PORT14 ,8},   // MikroBus_AN  /DAC1           P14.8
	/* 35  */   {XMC_GPIO_PORT2 , 3},   // MikroBus_SPI_CS              P2.3 (INPUT ONLY)


	//Additional pins for CAN Transreceiver IFX1051LE starting here
	/* 36  */   {XMC_GPIO_PORT2 , 0},  // CAN_TXD                       P2.0
	/* 37  */   {XMC_GPIO_PORT14 , 3} // CAN_RXD                       P14.3
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
  /*  0 */    {CCU42, CCU42_CC40, 0, 0, CCU42_IN0_P3_6},
  /*  1 */    {CCU41, CCU42_CC40, 0, 1, CCU41_IN0_P2_5}
 };

XMC_PWM4_t mapping_pwm4[] =
{
    {CCU42, CCU42_CC40, 0, mapping_port_pin[8] , P3_6_AF_CCU42_OUT0 ,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   8   P3.6
    {CCU41, CCU41_CC40, 0, mapping_port_pin[11], P2_5_AF_CCU41_OUT0,   XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}  // PWM disabled   11  P2.5
};

XMC_PWM8_t mapping_pwm8[] =
{
    {CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[3],  P0_9_AF_CCU80_OUT12,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  3  P0.9
    {CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[5],  P2_7_AF_CCU80_OUT03,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  5  P2.7
    {CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[6],  P2_9_AF_CCU80_OUT22,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  6  P2.9
	//additional pwm outputs starting here
	{CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9],  P0_6_AF_CCU80_OUT30,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  9  P0.6
	{CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[10], P1_14_AF_CCU81_OUT10, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  10 P1.14
	{CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[33], P2_8_AF_CCU80_OUT32,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}  // PWM disabled  33 P2.8
};

XMC_ARD_DAC_t mapping_dac[] =
{
	{XMC_DAC0, 1, 12},
	{XMC_DAC0, 0, 12}
};

XMC_ADC_t mapping_adc[] =
{
	//Result reg numbers are now equal to channel numbers
	{VADC, 0, VADC_G0, 0, 0, DISABLED},
    {VADC, 1, VADC_G0, 0, 1, DISABLED},
    {VADC, 2, VADC_G1, 1, 2, DISABLED},
    {VADC, 0, VADC_G2, 2, 0, DISABLED},
    {VADC, 1, VADC_G2, 2, 1, DISABLED},
    {VADC, 1, VADC_G1, 1, 1, DISABLED},
};


/*
 * UART objects
 *
 * Serial 0 is Debug port
 * Serial 1  is on-board port
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;
RingBuffer rx_buffer_1;
RingBuffer tx_buffer_1;
RingBuffer rx_buffer_2;
RingBuffer tx_buffer_2;

XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART1_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)4
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)5
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC1_C0_DX0_P0_4,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC1_0_IRQn,
  .irq_service_request  = 0
  };

XMC_UART_t XMC_UART_1 =
  {
  .channel              = XMC_UART1_CH1,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)0
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)1
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC1_C1_DX0_P0_0,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC1_1_IRQn,
  .irq_service_request  = 0
   };
   
 XMC_UART_t XMC_UART_2 =
  {
  .channel              = XMC_UART1_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
                            .pin  = (uint8_t)15
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
                            .pin  = (uint8_t)14
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC1_C0_DX0_P2_15,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC1_0_IRQn,
  .irq_service_request  = 0
   };  
   

// Debug port
HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );
// On-board port
HardwareSerial Serial1( &XMC_UART_1, &rx_buffer_1, &tx_buffer_1 );
//On-board connection with MikroBus ESP8266
HardwareSerial Serial2 ( &XMC_UART_2 , &rx_buffer_2, & tx_buffer_2); // Dont use the On board Debug Connecion along with the Debug Serial Line. They are both using USIC1_CH0

#endif

#endif
