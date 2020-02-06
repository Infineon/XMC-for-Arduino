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

#include <xmc_config.h>

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][ 2 ] = {
                                        { 8, 0 },
                                        { 1, 1 },
                                        { 2, 2 },
                                        { 3, 3 },
                                        { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT0 , 6},   // SPI-MISO                         P0.6
    /* 1  */    {XMC_GPIO_PORT0 , 7},   // SPI-MOSI / PWM40-1 output        P0.7
    /* 2  */    {XMC_GPIO_PORT0 , 8},   // SPI-SCK / PWM40-2 output         P0.8
    /* 3  */    {XMC_GPIO_PORT0 , 9},   // SPI-SS  / PWM40-3 output         P0.9
    /* 4  */    {XMC_GPIO_PORT0 , 14},  // GPIO                             P0.14
    /* 5  */    {XMC_GPIO_PORT0 , 15},  // GPIO                             P0.15
    /* 6  */    {XMC_GPIO_PORT2 , 0},   // TX                               P2.0
    /* 7  */    {XMC_GPIO_PORT2 , 6},   // RX                               P2.6 (INPUT ONLY)
    /* 8  */    {XMC_GPIO_PORT0 , 5},   // PWM40-0 output                   P0.5
    /* 9  */    {XMC_GPIO_PORT0 , 0},   // External interrupt 0             P0.0
    /* 10  */   {XMC_GPIO_PORT2 , 11},  // I2C Clock SCL / A3 ADC           P2.11
    /* 11  */   {XMC_GPIO_PORT2 , 10},  // I2C Data / Address SDA / A2 ADC  P2.10
    /* 12  */   {XMC_GPIO_PORT2 , 9},   // A1 / ADC Input                   P2.9 (INPUT ONLY)
    /* 13  */   {XMC_GPIO_PORT2 , 7},   // A0 / ADC Input                   P2.7 (INPUT ONLY)
    /* 14  */   {XMC_GPIO_PORT1 , 1},   // LED 1 output    (BUILTIN)        P1.1
    /* 15  */   {XMC_GPIO_PORT1 , 0},   // LED 2 output                     P1.0
    /* 16  */   {XMC_GPIO_PORT2 , 1},   // DEBUG_TX                         P2.1
    /* 17  */   {XMC_GPIO_PORT2 , 2}    // DEBUG_RX                         P2.2 (INPUT ONLY)
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_P0_0}
};

XMC_PWM4_t mapping_pwm4[] =
{
    {CCU40, CCU40_CC40, 0, mapping_port_pin[8], P0_5_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled  8    P0.5
    {CCU40, CCU40_CC41, 1, mapping_port_pin[1], P0_7_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},  // PWM disabled  1    P0.7
    {CCU40, CCU40_CC42, 2, mapping_port_pin[2], P0_8_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED},   // PWM disabled  2    P0.8
    {CCU40, CCU40_CC43, 3, mapping_port_pin[3], P0_9_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}   // PWM disabled  3    P0.9
};

XMC_ADC_t mapping_adc[] =
{
    {VADC, 1, DISABLED},
    {VADC, 2, DISABLED},
    {VADC, 3, DISABLED},
    {VADC, 4, DISABLED}
};

/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

/* First UART channel pins are swapped between debug and  normal use */
XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART0_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
#ifdef SERIAL_DEBUG
                            .pin  = (uint8_t)2
#else
                            .pin  = (uint8_t)6
#endif
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
#ifdef SERIAL_DEBUG
                            .pin  = (uint8_t)1
#else
                            .pin  = (uint8_t)0
#endif
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
#ifdef SERIAL_DEBUG
  .input_source_dx3     = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_2,
#else
  .input_source_dx3     = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_6,
#endif
  .irq_num              = USIC0_0_IRQn,
  .irq_service_request  = 0
  };

HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );

#endif

#endif
