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
#include <XMC4200.h>
//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between 
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD           XMC 4200 Distance2Go
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define XMC_LED_ON          0

#define NUM_ANALOG_INPUTS   8
#define NUM_PWM             4
#define NUM_LEDS            1
#define NUM_INTERRUPT       2
#define NUM_SERIAL          1
#define NUM_TONE_PINS       0
#define NUM_TASKS_VARIANT   16

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

#define PWM4_TIMER_PERIOD (2041U) // Generate 490Hz @fCCU=80MHz

#define PCLK 80000000u

#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

extern uint8_t SS;
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define A0  0   //ADC G0CH0 P14.0
#define A1  1   //ADC G0CH3 P14.3
#define A2  2   //ADC G0CH4 P14.4
#define A3  3   //ADC G0CH5 P14.5
#define A4  4   //ADC G0CH6 P14.6
#define A5  5   //ADC G0CH7 P14.7
#define A6  6   //ADC G1CH0 P14.8
#define A7  7   //ADC G1CH1 P14.9

#define LED_BUILTIN 34  //Standard Arduino LED: Used LED1
#define LED1        34  //Additional LED1 P2.0
#define GND         14  //GND

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
	const uint8_t mapping_pin_PWM4[][ 2 ] = {
            { 3, 0 },
            { 5, 1 },
            { 6, 2 },
            { 9, 3 },
            { 255, 255 } };

	const uint8_t mapping_pin_PWM8[][ 2 ] = { { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] = {
	/* 0    pin 1  */    {XMC_GPIO_PORT0, 1},   // UART TX
	/* 1    pin 2  */    {XMC_GPIO_PORT0, 0},   // UART RX
	/* 2    pin 11 */    {XMC_GPIO_PORT14, 7},  // A5 - ADC G0CH7
	/* 3    pin 12 */    {XMC_GPIO_PORT14, 6},  // A4 - ADC G0CH6
	/* 4    pin 13 */    {XMC_GPIO_PORT14, 5},  // A3 - ADC G0CH5
	/* 5    pin 14 */    {XMC_GPIO_PORT14, 4},  // A2 - ADC G0CH4, IFI high gain
	/* 6    pin 15 */    {XMC_GPIO_PORT14, 3},  // A1 - ADC G0CH3, IFQ high gain
	/* 7    pin 16 */    {XMC_GPIO_PORT14, 0},  // A0 - ADC G0CH0, IFI low gain
	/* 8    pin 19  */   {XMC_GPIO_PORT14, 9},  // A7 - ADC G1CH1, IFQ low gain
	/* 9    pin 20  */   {XMC_GPIO_PORT14, 8},  // A6 - ADC G1CH0,
	/* 10   pin 21  */   {XMC_GPIO_PORT2, 5},
	/* 11   pin 22  */   {XMC_GPIO_PORT2, 4},
	/* 12   pin 23  */   {XMC_GPIO_PORT2, 3},
	/* 13   pin 24  */   {XMC_GPIO_PORT2, 2},
	/* 14   pin 25  */   {XMC_GPIO_PORT2, 1},   // PLL - MUXOUT
	/* 15   pin 26  */   {XMC_GPIO_PORT2, 0},   // LED31 (red LED)
	/* 16   pin 35  */   {XMC_GPIO_PORT1, 5},
	/* 17   pin 36  */   {XMC_GPIO_PORT1, 4},
	/* 18   pin 37  */   {XMC_GPIO_PORT1, 3},   // PLL - TRIG 2
	/* 19   pin 38  */   {XMC_GPIO_PORT1, 2},   // PLL - TRIG 1
	/* 20   pin 39  */   {XMC_GPIO_PORT1, 1},   // PLL - MOD
	/* 21   pin 40  */   {XMC_GPIO_PORT1, 0},
	/* 22   pin 42  */   {XMC_GPIO_PORT0, 8},
	/* 23   pin 43  */   {XMC_GPIO_PORT0, 7},
	/* 24   pin 44  */   {XMC_GPIO_PORT0, 6},   // PLL - CE
	/* 25   pin 45  */   {XMC_GPIO_PORT0, 5},
	/* 26   pin 46  */   {XMC_GPIO_PORT0, 4},
	/* 27   pin 47  */   {XMC_GPIO_PORT0, 3},
	/* 28   pin 48  */   {XMC_GPIO_PORT0, 2}
	};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0  */    {CCU41, CCU41_CC40, 0, 0, CCU41_IN0_P2_5},
    /* 1  */    {CCU41, CCU41_CC41, 1, 1, CCU41_IN1_P2_4}
	};


XMC_PWM4_t mapping_pwm4[] = {
	{CCU40, CCU40_CC40, 0, mapping_port_pin[18] , P1_3_AF_CCU40_OUT0 ,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   P1.3
	{CCU40, CCU40_CC41, 1, mapping_port_pin[19] , P1_2_AF_CCU40_OUT1 ,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   P1.2
	{CCU40, CCU40_CC42, 2, mapping_port_pin[20] , P1_1_AF_CCU40_OUT2 ,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   P1.1
	{CCU40, CCU40_CC43, 3, mapping_port_pin[21] , P1_0_AF_CCU40_OUT3 ,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}  // PWM disabled   P1.0
	};


XMC_PWM8_t mapping_pwm8[1];

XMC_ADC_t mapping_adc[] = {
	{VADC, 0, VADC_G0, 0, 0, DISABLED}, // A0 ADC G0CH0 P14.0
	{VADC, 3, VADC_G0, 0, 3, DISABLED}, // A1 ADC G0CH3 P14.3
	{VADC, 4, VADC_G0, 0, 4, DISABLED}, // A2 ADC G0CH4 P14.4
	{VADC, 5, VADC_G0, 0, 5, DISABLED}, // A3 ADC G0CH5 P14.5
	{VADC, 6, VADC_G0, 0, 6, DISABLED}, // A4 ADC G0CH6 P14.6
	{VADC, 7, VADC_G0, 0, 7, DISABLED}, // A5 ADC G0CH7 P14.7
	{VADC, 0, VADC_G1, 1, 0, DISABLED}, // A6 ADC G1CH0 P14.8
	{VADC, 1, VADC_G1, 1, 1, DISABLED}  // A7 ADC G1CH1 P14.9
	};
 
/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

XMC_UART_t XMC_UART_0 =
{
  .channel             = XMC_UART0_CH0,
  .rx                  = { .port = (XMC_GPIO_PORT_t *)PORT0_BASE,
                           .pin  = (uint8_t)0
                           },
  .rx_config           = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                           .output_level      = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                           .output_strength   = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                           },
  .tx                  = { .port = (XMC_GPIO_PORT_t *)PORT0_BASE,
                           .pin  = (uint8_t)1
                           },
  .tx_config           = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                           .output_level      = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                           .output_strength   = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                           },
  .input_source_dx0    = (XMC_USIC_INPUT_t)USIC1_C1_DX0_P0_0,
  .input_source_dx1    = XMC_INPUT_INVALID,
  .input_source_dx2    = XMC_INPUT_INVALID,
  .input_source_dx3    = XMC_INPUT_INVALID,
  .irq_num             = USIC1_1_IRQn,
  .irq_service_request = 0
};	

HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );

// Serial Interrupt and event handling
#ifdef __cplusplus
extern "C" {
#endif
void serialEventRun( );
void serialEvent( ) __attribute__((weak));


void serialEventRun( )
{
if( serialEvent )
  {
  if( Serial.available( ) )
    serialEvent( );
  }
}


void USIC1_1_IRQHandler( )
{
Serial.IrqHandler( );
}
#ifdef __cplusplus
}
#endif
#endif  /* ARDUINO_MAIN */

#ifdef __cplusplus
extern HardwareSerial Serial;
#endif  /* cplusplus */

#endif // PINS_ARDUINO_H_
