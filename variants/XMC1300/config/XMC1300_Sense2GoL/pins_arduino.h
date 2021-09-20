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

#define NUM_ANALOG_INPUTS   2
#define NUM_PWM             2
#define NUM_LEDS            3
#define NUM_INTERRUPT       0
#define NUM_SERIAL          1
// Following could be 4 unless add/delete task has issues
#define NUM_TONE_PINS       0
#define NUM_TASKS_VARIANT   8

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

#define PWM4_TIMER_PERIOD (2041U)  // Generate 490Hz @fCCU=1MHz

#define PCLK 64000000u

extern uint8_t SS;
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define A0   0
#define A1   1

// These 2 lines should be defined in higher level or examples
#define CH_I    A0
#define CH_Q    A1
// Actual on board signal is TX_ON
#define BGT_ON  2

#define LED_BUILTIN 3   // Standard Arduino LED
#define LED1    3       // Extended LEDs P0.5 D5
#define LED2    5       // Extended LEDs P0.7 D4
#define LED3    7       // Extended LEDs P0.9 D3
#define GND     16      // GND

// Disable interrupts
//#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))
#define digitalPinToInterrupt(p)    NOT_AN_INTERRUPT

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
   const uint8_t mapping_pin_PWM4[][ 2 ] = {
            { 0, 6 },
            { 0, 8 },
            { 255, 255 } };

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */    { XMC_GPIO_PORT2, 6 },  // PIN_RX                 P2.6
    /* 1  */    { XMC_GPIO_PORT2 ,0 },  // PIN_TX                 P2.0
    /* 2  */    { XMC_GPIO_PORT0 ,0 },  // TX_ON                  P0.0
    /* 3  */    { XMC_GPIO_PORT0 ,5 },  // LED output  D5         P0.5
    /* 4  */    { XMC_GPIO_PORT0 ,6 },  // PWM1                   P0.6
    /* 5  */    { XMC_GPIO_PORT0 ,7 },  // LED output  D4         P0.7
    /* 6  */    { XMC_GPIO_PORT0 ,8 },  // PWM 2                  P0.8
    /* 7  */    { XMC_GPIO_PORT0 ,9 },  // LED output  D2         P0.9
    /* 8  */    { XMC_GPIO_PORT0 ,14 }, // GPIO   - SWDIO         P0.14
    /* 9  */    { XMC_GPIO_PORT0 ,15 }, // GPIO   - SWDCLK        P0.15
    /* 10  */   { XMC_GPIO_PORT2 ,8 },  // NOT CONNECTED          P2.8 (also P2.7)
    /* 11  */   { XMC_GPIO_PORT2 ,9 },  // A0 / ADC Input         P2.9 (INPUT ONLY)
    /* 12  */   { XMC_GPIO_PORT2 ,10 }, // NOT CONNECTED          P2.10
    /* 13  */   { XMC_GPIO_PORT2 ,11 }  // A1 / ADC Input         P2.11
    };

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
//    /* 0  */    { CCU40, CCU40_CC40, 0, 0, CCU40_IN0_U0C0_DX2INS },
//    /* 1  */    { CCU40, CCU40_CC40, 0, 1, CCU40_IN0_P0_0 }
    };

XMC_PWM4_t mapping_pwm4[] = {
    { CCU40, CCU40_CC40, 0, mapping_port_pin[ 4 ], P0_6_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED },  // PWM disabled 3   P0.6
    { CCU40, CCU40_CC42, 2, mapping_port_pin[ 6 ], P0_8_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED }   // PWM disabled 9   P0.8
    };

XMC_ADC_t mapping_adc[] = {
    { VADC, 2, VADC_G0, 2, 2, DISABLED },  // A0 - CH_I
    { VADC, 4, VADC_G0, 4, 4, DISABLED }   // A1 - CH_Q
    };

/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART0_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t *)PORT2_BASE,
                            .pin  = (uint8_t)6
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t *)PORT2_BASE,
                            .pin  = (uint8_t)0
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
                            .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_6,
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
