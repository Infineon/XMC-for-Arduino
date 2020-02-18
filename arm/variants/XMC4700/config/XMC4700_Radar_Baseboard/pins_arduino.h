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
  
  Copyright (c) 2019 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
*/
#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

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
#define NUM_LEDS            3
#define NUM_INTERRUPT       2
#define NUM_SERIAL          1
#define NUM_TONE_PINS       16
#define NUM_TASKS_VARIANT   32

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

// Board has two serial ports pre-assigned to debug and on-board

#define PWM4_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz

#define PCLK 144000000u 
 
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
const uint8_t mapping_pin_PWM8[][ 2 ] = {
                                        { 37, 0 },
                                        { 38, 1 },
                                        { 255, 255 } };

const uint8_t mapping_pin_DAC[][2] = {
										{ 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT3, 14},   // RX                           P3.14 (also DEBUG_RX)
    /* 1  */    {XMC_GPIO_PORT3, 15},   // TX                           P3.15 (also DEBUG_TX)
    /* 2  */    {XMC_GPIO_PORT0, 4},    // GPIO / External INT 2        P0.4
	/* 3  */    {XMC_GPIO_PORT4, 6},    // PWM43-0 output / Ext INT 1   P4.6
    /* 4  */    {XMC_GPIO_PORT2, 7},    // GPIO                         P2.7
    /* 5  */    {XMC_GPIO_PORT7, 6},    // PWM42-2 output               P7.6
    /* 6  */    {XMC_GPIO_PORT3, 10},   // PWM41-0 output               P3.10
    /* 7  */    {XMC_GPIO_PORT3, 3},    // GPIO / PWM8 input0           P3.3
    /* 8  */    {XMC_GPIO_PORT9, 6},    // GPIO / SPI_CS_2              P9.6
    /* 9  */    {XMC_GPIO_PORT1, 1},    // PWM40-2 output               P1.1
    /* 10 */    {XMC_GPIO_PORT9, 2},    // SPI-CS0                      P9.2
    /* 11  */   {XMC_GPIO_PORT9, 3},    // SPI_MOSI                     P9.3
    /* 12  */   {XMC_GPIO_PORT9, 4},    // SPI-MISO                     P9.4
    /* 13  */   {XMC_GPIO_PORT9, 1},    // SPI-SCK                      P9.1
    /* 14  */   {XMC_GPIO_PORT2, 14},   // I2C Data / Address SDA       P2.14
    /* 15  */   {XMC_GPIO_PORT5, 8},    // I2C Clock SCL                P5.8
    /* 16  */   {XMC_GPIO_PORT14, 1},   // A0 / ADC Input               P14.1 (INPUT ONLY)
    /* 17  */   {XMC_GPIO_PORT14, 2},   // A1 / ADC Input               P14.2 (INPUT ONLY)
    /* 18  */   {XMC_GPIO_PORT14, 4},   // A2 / ADC Input               P14.4 (INPUT ONLY)
    /* 19  */   {XMC_GPIO_PORT15, 8},   // A3 / ADC Input               P15.8 (INPUT ONLY)
    /* 20  */   {XMC_GPIO_PORT14, 5},   // A4 / ADC Input               P14.5 (INPUT ONLY)
    /* 21  */   {XMC_GPIO_PORT15, 2},   // A5 / ADC Input               P15.2 (INPUT ONLY)
    /* 22  */   {XMC_GPIO_PORT1, 15},   // PWM81-0 output (LED_RED)     P1.15
    /* 23  */   {XMC_GPIO_PORT1, 14},   // PWM81-1 output (LED_GREEN)   P1.14
    /* 24  */   {XMC_GPIO_PORT1, 13},   // PWM81-2 output (LED_BLUE)    P1.13
    /* 25  */   {XMC_GPIO_PORT8, 8},    // Additional BUTTON1           P8.8 (INPUT ONLY)
    /* 26  */   {XMC_GPIO_PORT4, 1},    // SPI_SS_3 (SD CARD)           P4.1
    /* 27  */   {XMC_GPIO_PORT3, 5},    // SPI-MOSI (SD CARD)           P3.5
    /* 28  */   {XMC_GPIO_PORT4, 0},    // SPI-MISO (SD CARD)           P4.0
    /* 29 */    {XMC_GPIO_PORT3, 6},    // SPI-SCK  (SD CARD)           P3.6
    /* 30  */   {XMC_GPIO_PORT1, 6},    // SD DATA 1                    P1.6
    /* 31  */   {XMC_GPIO_PORT1, 7},    // SD DATA 2                    P1.7

	/* 32 */    {XMC_GPIO_PORT0, 3},    //  External INT 1 (Alt Pin 3)  P0.3
    /* 33 */    {XMC_GPIO_PORT0, 6},    //  PWM8 input2 (Alt Pin 5)     P0.6
    /* 34 */    {XMC_GPIO_PORT5, 0},    //  PWM8 input1 (Alt Pin 6)     P5.0
    /* 35 */    {XMC_GPIO_PORT9, 7},    //  SPI-CS3 (Alt Pin 7)         P9.7
    /* 36 */    {XMC_GPIO_PORT9, 5},    //  SPI-CS1 (Alt Pin 9)         P9.5
    /* 37 */    {XMC_GPIO_PORT6, 0},    //  PWM81-3 output (Alt Pin 10) P6.0
    /* 38 */    {XMC_GPIO_PORT0, 10},   //  PWM80-0 output (Alt Pin 11) P0.10

};

#define INTERRUPT_USE_ERU
const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {XMC_ERU0, XMC_ERU_ETL_INPUT_A0, XMC_ERU_ETL_INPUT_B3, 2, 3, 0},
    /* 1  */    {XMC_ERU1, XMC_ERU_ETL_INPUT_A0, XMC_ERU_ETL_INPUT_B0, 3, 0, 1},
};

XMC_PWM4_t mapping_pwm4[] =
{
	{CCU43, CCU43_CC40, 0, mapping_port_pin[3], P4_6_AF_CCU43_OUT0,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   3  P4.6
	{CCU42, CCU42_CC42, 2, mapping_port_pin[5], P7_6_AF_CCU42_OUT2,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   5   P7.6
    {CCU41, CCU41_CC40, 0, mapping_port_pin[6], P3_10_AF_CCU41_OUT0,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   6  P3.10
    {CCU40, CCU40_CC42, 2, mapping_port_pin[9], P1_1_AF_CCU40_OUT2,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   9  P1.1
};

XMC_PWM8_t mapping_pwm8[] =
{
    {CCU81, CCU81_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[37],  P6_0_AF_CCU81_OUT31, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  38  P6.0
    {CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[38],  P0_10_AF_CCU80_OUT02, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  39  P0.10
};

XMC_ARD_DAC_t mapping_dac[] =
{

};

XMC_ADC_t mapping_adc[] =
{
	//Result reg numbers are now equal to channel numbers
	{VADC, 1, VADC_G0, 0, 1, DISABLED},
    {VADC, 2, VADC_G1, 1, 2, DISABLED},
    {VADC, 0, VADC_G2, 2, 0, DISABLED},
    {VADC, 0, VADC_G3, 3, 4, DISABLED},
    {VADC, 5, VADC_G0, 0, 5, DISABLED},
    {VADC, 2, VADC_G2, 2, 2, DISABLED},
};


/*
 * UART objects
 *
 * Serial 0 is Debug port
 * Serial 1  is on-board port
 */
#define SERIAL_USE_U1C1
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

XMC_UART_t XMC_UART_0 =
{
  .channel              = XMC_UART1_CH1,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
                            .pin  = (uint8_t)14
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
                            .pin  = (uint8_t)15
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC1_C1_DX0_P3_14,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC0_0_IRQn,
  .irq_service_request  = 0
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


void USIC0_0_IRQHandler( )
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

#endif  /* PINS_ARDUINO_H_ */
