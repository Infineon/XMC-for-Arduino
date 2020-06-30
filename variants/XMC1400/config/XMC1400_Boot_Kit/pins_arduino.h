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
#ifndef PINS_ARDUINO_H_
#define PINS_ARDUINO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <XMC1400.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define XMC_BOARD           XMC 1400 Boot Kit

/* On board LED is ON when digital output is 0, LOW, FALSE, OFF */
#define  XMC_LED_ON         0 

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

#define PCLK 96000000u 
 
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


const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT1, 2}, // RX                                 P1.2
    /* 1  */    {XMC_GPIO_PORT1, 3}, // TX                                 P1.3
    /* 2  */    {XMC_GPIO_PORT0 , 0}, // External int 0                     P0.0
    /* 3  */    {XMC_GPIO_PORT0 , 1}, // External int 1 / PWM40-1 output    P0.1
    /* 4  */    {XMC_GPIO_PORT0 , 6}, // PWM40-0 output                     P0.6
    /* 5  */    {XMC_GPIO_PORT0 , 2}, // GPIO                               P0.2
    /* 6  */    {XMC_GPIO_PORT1 , 7}, // PWM40-1 output                     P1.7
    /* 7  */    {XMC_GPIO_PORT0 , 4}, // GPIO                               P0.4
    /* 8  */    {XMC_GPIO_PORT0 , 13}, // GPIO                              P0.13
    /* 9  */    {XMC_GPIO_PORT1 , 8}, // PWM80-2 output                     P1.8
    /* 10  */   {XMC_GPIO_PORT0 , 9}, // SPI-SS                             P0.9
    /* 11  */   {XMC_GPIO_PORT1 , 1}, // SPI-MOSI                           P1.1
    /* 12  */   {XMC_GPIO_PORT1 , 0}, // SPI-MISO                           P1.0
    /* 13  */   {XMC_GPIO_PORT0 , 7}, // SPI-SCK                            P0.7   
    /* 14  */   {XMC_GPIO_PORT2 , 3}, // AREF                               P2.3 (INPUT ONLY)
    /* 15  */   {XMC_GPIO_PORT2 , 1}, // I2C Data / Address SDA             P2.1
    /* 16  */   {XMC_GPIO_PORT2 , 0}, // I2C Clock SCL                      P2.0
    /* 17  */   {XMC_GPIO_PORT2 , 6}, // A0 / ADC Input                     P2.6 (INPUT ONLY)
    /* 18  */   {XMC_GPIO_PORT2 , 8}, // A1 / ADC Input                     P2.8 (INPUT ONLY)
    /* 19  */   {XMC_GPIO_PORT2 , 9}, // A2 / ADC Input                     P2.9 (INPUT ONLY)
    /* 20  */   {XMC_GPIO_PORT2 , 10}, // A3 / ADC Input                    P2.10
    /* 21  */   {XMC_GPIO_PORT2 , 11}, // A4 / ADC Input                    P2.11
    /* 22  */   {XMC_GPIO_PORT2 , 2}, // A5 / ADC Input                     P2.2 (INPUT ONLY)
    /* 23  */   {XMC_GPIO_PORT2 , 4}, // RESET input ( DO NOT USE as GPIO ) P2.4 (INPUT ONLY)
    /* 24 */    {XMC_GPIO_PORT4 , 0}, // LED
    /* 25 */    {XMC_GPIO_PORT4 , 1}, // LED
    /* 26 */    {XMC_GPIO_PORT4 , 2}, // LED
    /* 27 */    {XMC_GPIO_PORT4 , 3}, // LED
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_P0_0},
    /* 1  */    {CCU40, CCU40_CC41, 1, 1, CCU40_IN1_P0_1}
};

XMC_PWM4_t mapping_pwm4[] =
{
    {CCU40, CCU40_CC41, 1, mapping_port_pin[3], P0_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled  4   
    {CCU40, CCU40_CC40, 0, mapping_port_pin[4], P0_6_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled  4   
    {CCU40, CCU40_CC43, 3, mapping_port_pin[6], P1_7_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled  6  
    {CCU40, CCU40_CC40, 0, mapping_port_pin[9], P1_8_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled  6  
};

XMC_ADC_t mapping_adc[] =
{
    {VADC, 0, DISABLED},
    {VADC, 1, DISABLED},
    {VADC, 2, DISABLED},
    {VADC, 3, DISABLED},
    {VADC, 4, DISABLED},
    {VADC, 7, DISABLED}
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
                            .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
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
