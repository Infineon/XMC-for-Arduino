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
#include <XMC1100.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between 
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD           XMC 1100 H-BRIDGE2GO
/* On board LED is ON when digital output is 1, HIGH, TRUE, ON */
#define  XMC_LED_ON         1

#define NUM_ANALOG_INPUTS   2
#define NUM_PWM             2
#define NUM_LEDS            2
#define NUM_INTERRUPT       1
#define NUM_SERIAL          1
#define NUM_TONE_PINS       2
#define NUM_TASKS_VARIANT   8

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

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

#define PWM4_TIMER_PERIOD (2041U)  // Generate 490Hz @fCCU=64MHz

#define PCLK 64000000u 
 
#define PIN_SPI_SS    3
#define PIN_SPI_MOSI  1
#define PIN_SPI_MISO  0
#define PIN_SPI_SCK   2

extern uint8_t SS; 
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define A0   0
#define A1   1

#define LED_BUILTIN 14	//Standard Arduino LED: Used LED1
#define LED1    14  	// Extended LEDs
#define LED2    15  	// Extended LEDs
#define GND     32  	// GND

// H-BRIDGE2Go specific Pins
#define SO 		PIN_SPI_MISO
#define SI 		PIN_SPI_MOSI
//#define SCK 	PIN_SPI_SCK

// Following for DOCUMENTATION only
//#define CSN 	PIN_SPI_SS
//#define DIR		6
//#define DIS		10
//#define PWM 	11

#define digitalPinToInterrupt(p)    (((p) == 9) ? 0 : NOT_AN_INTERRUPT)

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
   const uint8_t mapping_pin_PWM4[][ 2 ] = {
    { 8, 0 },
    { 11, 1},
    { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT0, 6},    // SPI-MISO	                        P0.6
    /* 1  */    {XMC_GPIO_PORT0 , 7},   // SPI-MOSI / I2C Data              P0.7
    /* 2  */    {XMC_GPIO_PORT0 , 8},   // SPI-SCK / I2C Clock             	P0.8
    /* 3  */    {XMC_GPIO_PORT0 , 9},   // SPI-SS                           P0.9
    /* 4  */    {XMC_GPIO_PORT0 , 14},  // TX                               P0.14
    /* 5  */    {XMC_GPIO_PORT0 , 15},  // RX                  	            P0.15
    /* 6  */    {XMC_GPIO_PORT2 , 0},   // DIR	(Fixed on PCB)              P2.0
    /* 7  */    {XMC_GPIO_PORT2 , 6},   // GPIO		                        P2.6 (INPUT ONLY)
    /* 8  */    {XMC_GPIO_PORT0 , 5},   // PWM0 output                      P0.5
    /* 9  */    {XMC_GPIO_PORT0 , 0},   // External interrupt               P0.0
    /* 10  */   {XMC_GPIO_PORT2 , 11},  // DIS  (Fixed on PCB)              P2.11
    /* 11  */   {XMC_GPIO_PORT2 , 10},  // PWM / PWM1 output (Fixed on PCB) P2.10
    /* 12  */   {XMC_GPIO_PORT2 , 9},   // A1 / ADC Input                   P2.9 (INPUT ONLY)
    /* 13  */   {XMC_GPIO_PORT2 , 7},   // A0 / ADC Input                   P2.7 (INPUT ONLY)
    /* 14  */   {XMC_GPIO_PORT1 , 1},   // LED1 output                      P1.1
    /* 15  */   {XMC_GPIO_PORT1 , 0},   // LED2 output                      P1.0
    /* 16  */   {XMC_GPIO_PORT2 , 1},   // DEBUG_TX                         P2.1
    /* 17  */   {XMC_GPIO_PORT2 , 2}    // DEBUG_RX                         P2.2 (INPUT ONLY)
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_P0_0}
};

XMC_PWM4_t mapping_pwm4[] =
{
    {CCU40, CCU40_CC40, 0, mapping_port_pin[8],  P0_0_AF_CCU40_OUT0,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  8    P0.5
    {CCU40, CCU40_CC42, 2, mapping_port_pin[11], P2_10_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}  // PWM disabled  10   P2.11
};

XMC_ADC_t mapping_adc[] =
{
    {VADC, 1, DISABLED},
    {VADC, 2, DISABLED}
};

/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART0_CH0,
  .rx                   = {
#ifdef SERIAL_DEBUG
                            .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
                            .pin  = (uint8_t)2
#else
                            .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)15
#endif
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
  .tx                   = {
#ifdef SERIAL_DEBUG
                            .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
                            .pin  = (uint8_t)1
#else
                            .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
                            .pin  = (uint8_t)14
#endif
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
#ifdef SERIAL_DEBUG
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
#else
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_P0_15,
#endif
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
#ifdef SERIAL_DEBUG
  .input_source_dx3     = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_2,
#else
  .input_source_dx3     = XMC_INPUT_INVALID,
#endif
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
