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
// Pins that are allocated or free to be used as Analog input
#define NUM_ANALOG_INPUTS   6
#define NUM_PWM             6
#define NUM_LEDS            3
#define NUM_INTERRUPT       2
#define NUM_SERIAL          1
#define NUM_TONE_PINS       8
#define NUM_TASKS_VARIANT   16

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

// Board has two serial ports pre-assigned to debug and on-board

#define PWM4_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz

#define PCLK 80000000u 
 
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

// These 2 lines should be defined in higher level or examples
#define CH_I A0
#define CH_Q A1
// These 2 lines should also be defined at higher level
// TX_ON defined but only used in .h file to set BGT24LTR11_TX_ON_PIN that is NEVER used
//#define TX_ON 3
#define BGT_ON 27

#define LED_RED     26  // LED Red channel
#define GND         7   // GND

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 32 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT0, 0},    // RX                           P0.0 (also DEBUG_RX)
    /* 1  */    {XMC_GPIO_PORT0, 1},    // TX                           P0.1 (also DEBUG_TX)
    /* 2  */    {XMC_GPIO_PORT0, 4},    // GPIO / External INT 2        P0.4
	  /* 3  */    //{XMC_GPIO_PORT4, 6},    // PWM43-0 output / Ext INT 1   P4.6
    /* 4  */    {XMC_GPIO_PORT2, 7},    // GPIO                         P2.7
    /* 5  */    {XMC_GPIO_PORT2, 2},    // PWM42-2 output               P2.2
    /* 6  */    //{XMC_GPIO_PORT3, 10},   // PWM41-0 output               P3.10
    /* 7  */    {XMC_GPIO_PORT3, 3},    // GPIO / PWM8 input0           P3.3
    /* 8  */    //{XMC_GPIO_PORT9, 6},    // GPIO / SPI_CS_2              P9.6
    /* 9  */    {XMC_GPIO_PORT1, 1},    // PWM40-2 output               P1.1
    /* 10 */    //{XMC_GPIO_PORT9, 2},    // SPI-CS0                      P9.2
    /* 11  */   //{XMC_GPIO_PORT9, 3},    // SPI_MOSI                     P9.3
    /* 12  */   //{XMC_GPIO_PORT9, 4},    // SPI-MISO                     P9.4
    /* 13  */   //{XMC_GPIO_PORT9, 1},    // SPI-SCK                      P9.1
    /* 14  */   //{XMC_GPIO_PORT2, 14},   // I2C Data / Address SDA       P2.14
    /* 15  */   //{XMC_GPIO_PORT5, 8},    // I2C Clock SCL                P5.8
    /* 16  */   {XMC_GPIO_PORT14, 4},   // A0 / ADC Input               P14.4 
    /* 17  */   {XMC_GPIO_PORT14, 3},   // A1 / ADC Input               P14.3 
    /* 18  */   {XMC_GPIO_PORT14, 0},   // A2 / ADC Input               P14.0 
    /* 19  */   {XMC_GPIO_PORT14, 5},   // A3 / ADC Input               P14.5 
    /* 20  */   {XMC_GPIO_PORT14, 6},   // A4 / ADC Input               P14.6 
    /* 21  */   {XMC_GPIO_PORT14, 9},   // A5 / ADC Input               P14.9
    /* 22  */   {XMC_GPIO_PORT2, 0},    // PWM81-0 output (LED_RED)     P2.0
    /* 23  */   //{XMC_GPIO_PORT1, 14},   // PWM81-1 output (LED_GREEN)   P1.14
    /* 24  */   //{XMC_GPIO_PORT1, 13},   // PWM81-2 output (LED_BLUE)    P1.13
    /* 25  */   //{XMC_GPIO_PORT8, 8},    // Additional BUTTON1           P8.8 (INPUT ONLY)
    /* 26  */   //{XMC_GPIO_PORT4, 1},    // SPI_SS_3 (SD CARD)           P4.1
    /* 27  */   //{XMC_GPIO_PORT3, 5},    // SPI-MOSI (SD CARD)           P3.5
    /* 28  */   //{XMC_GPIO_PORT4, 0},    // SPI-MISO (SD CARD)           P4.0
    /* 29 */    //{XMC_GPIO_PORT3, 6},    // SPI-SCK  (SD CARD)           P3.6
    /* 30  */   //{XMC_GPIO_PORT1, 6},    // SD DATA 1                    P1.6
    /* 31  */   //{XMC_GPIO_PORT1, 7},    // SD DATA 2                    P1.7

	  /* 32 */    {XMC_GPIO_PORT0, 4},    //  External INT 1 (Alt Pin 3)  P0.4
    /* 33 */    {XMC_GPIO_PORT0, 6},    //  PWM8 input2 (Alt Pin 5)     P0.6
    /* 34 */    //{XMC_GPIO_PORT5, 0},    //  PWM8 input1 (Alt Pin 6)     P5.0
    /* 35 */    //{XMC_GPIO_PORT9, 7},    //  SPI-CS3 (Alt Pin 7)         P9.7
    /* 36 */    //{XMC_GPIO_PORT9, 5},    //  SPI-CS1 (Alt Pin 9)         P9.5
    /* 37 */    {XMC_GPIO_PORT2, 2},    //  PWM81-3 output (Alt Pin 10) P2.2
    /* 38 */    //{XMC_GPIO_PORT0, 10},   //  PWM80-0 output (Alt Pin 11) P0.10

};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
	/* 0  */ 	//{CCU40, CCU40_CC40, 0, 0, CCU40_IN0_U0C0_DX2INS}, 
	/* 1  */ 	//{CCU40, CCU40_CC40, 0, 1, CCU40_IN0_P0_0} 
    };

XMC_ADC_t mapping_adc[] = {
	{VADC, 14, VADC_G0, 0, 3, DISABLED},			// CH_I
	{VADC, 15, VADC_G0, 0, 4, DISABLED}				// CH_Q
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

#endif // PINS_ARDUINO_H_
