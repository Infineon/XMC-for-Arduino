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
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between
// to avoid issues with other defined macros e.g. XMC1400
#define XMC_BOARD           XMC 1400 Kit for Arduino

/* On board LED is ON when digital output is 0, LOW, FALSE, OFF */
#define XMC_LED_ON 0

// Following were defines now evaluated by compilation as const variables
// After definitions of associated mapping arrays
extern const uint8_t NUM_DIGITAL;
extern const uint8_t GND;
extern const uint8_t NUM_PWM4;
extern const uint8_t NUM_PWM;
extern const uint8_t NUM_INTERRUPT;
extern const uint8_t NUM_ANALOG_INPUTS;
#define NUM_LEDS 3
#define NUM_SERIAL 1
#define NUM_TONE_PINS 4
#define NUM_TASKS_VARIANT 8
#define NUM_SPI 1
#define NUM_I2C 1

// Indicate unit has RTC/Alarm
#define HAS_RTC 1

// Indicate variant has a GPIO pin used for Reset pin
#define HAS_GPIO_RESET 1

// Defines will be either set by ArduinoIDE in the menu or manually
#ifdef SERIAL_HOSTPC
    // Comment out following line to use Serial on pins (board)
    #define SERIAL_DEBUG 1
#elif SERIAL_ONBOARD
// No SERIAL_DEBUG will be defined, kept here for clarity
#else
    // Define the SERIAL_DEBUG as default setting
    #define SERIAL_DEBUG 1
#endif

#define PWM4_TIMER_PERIOD (2041U) // Generate 490Hz @fCCU=1MHz

#define PCLK 96000000u // PCLK can go to this max value

#define PIN_SPI_SS 10
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
// duplicate defines for AD_AUX_n
#define A6 6
#define A7 7
#define A8 8
#define A9 9

#define AD_AUX_1 6 // AD_AUX
#define AD_AUX_2 7 // AD_AUX
#define AD_AUX_3 8 // AD_AUX
#define AD_AUX_4 9 // AD_AUX

#define AUX_1 25 // AUX

#define LED1 13
#define LED2 2
#define LED3 26
#define LED_BUILTIN LED1

#define EXT_INTR_0 3
#define EXT_INTR_1 25

#define digitalPinToInterrupt(p) ((p) == 3 ? 0 : ((p) == 25 ? 1 : NOT_AN_INTERRUPT))

/* Mapping interrupt handlers. Notice that XMC1400 can have interrupt handlers working in 3 modes,
   the defines below assumes the mode A. For details refer to assembly file and reference manual.
*/
#define USIC0_0_IRQHandler IRQ9_Handler // UART
#define USIC0_0_IRQn IRQ9_IRQn

#define CCU40_0_IRQHandler IRQ21_Handler // interrupt 1
#define CCU40_0_IRQn IRQ21_IRQn

#define CCU40_1_IRQHandler IRQ22_Handler // interrupt 0
#define CCU40_1_IRQn IRQ22_IRQn

#define USIC0_4_IRQHandler IRQ13_Handler // I2C
#define USIC0_4_IRQn IRQ13_IRQn

#define USIC0_5_IRQHandler IRQ14_Handler // I2C
#define USIC0_5_IRQn IRQ14_IRQn

#define SCU_1_IRQHandler IRQ1_Handler // RTC
#define SCU_1_IRQn IRQ1_IRQn

#define ERU0_0_IRQHandler IRQ3_Handler // RESET
#define ERU0_0_IRQn IRQ3_IRQn

#ifdef ARDUINO_MAIN
// index is Arduino pin count
//  Mapping of digital pins and comments
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */ {XMC_GPIO_PORT1, 2},   // RX                                        P1.2
    /* 1  */ {XMC_GPIO_PORT1, 3},   // TX                                        P1.3
    /* 2  */ {XMC_GPIO_PORT0, 5},   // GPIO / LED2 output                       P0.5
    /* 3  */ {XMC_GPIO_PORT1, 1},   // External int 0 / PWM40-1 output          P1.1
    /* 4  */ {XMC_GPIO_PORT1, 0},   // PWM40-0 output                           P1.0
    /* 5  */ {XMC_GPIO_PORT0, 2},   // GPIO                                     P0.2
    /* 6  */ {XMC_GPIO_PORT0, 6},   // PWM41-0 output                           P0.6
    /* 7  */ {XMC_GPIO_PORT0, 13},  // GPIO                                    P0.13
    /* 8  */ {XMC_GPIO_PORT0, 12},  // GPIO                                    P0.12
    /* 9  */ {XMC_GPIO_PORT0, 7},   // PWM40-1 output                           P0.7
    /* 10  */ {XMC_GPIO_PORT0, 4},  // SPI-SS / PWM40-1                         P0.4
    /* 11  */ {XMC_GPIO_PORT0, 1},  // SPI-MOSI / PWM40-1                       P0.1
    /* 12  */ {XMC_GPIO_PORT0, 0},  // SPI-MISO                                 P0.0
    /* 13  */ {XMC_GPIO_PORT0, 3},  // SPI-SCK                                  P0.3
    /* 14  */ {XMC_GPIO_PORT2, 3},  // AREF * DO NOT USE as GPIO or REF **      P2.3 (INPUT ONLY)
    /* 15  */ {XMC_GPIO_PORT2, 6},  // A0 / ADC Input                           P2.6 (INPUT ONLY)
    /* 16  */ {XMC_GPIO_PORT2, 8},  // A1 / ADC Input                           P2.8 (INPUT ONLY)
    /* 17  */ {XMC_GPIO_PORT2, 9},  // A2 / ADC Input                           P2.9 (INPUT ONLY)
    /* 18  */ {XMC_GPIO_PORT2, 10}, // A3 / ADC Input                          P2.10
    /* 19  */ {XMC_GPIO_PORT2, 1},  // A4  / I2C Data / Address SDA             P2.1
    /* 20  */ {XMC_GPIO_PORT2, 0},  // A5  / I2C Clock SCL                      P2.0
    /* 21  */ {XMC_GPIO_PORT2, 11}, // GPIO / AD_AUX_1 Additional Pin          P2.11
    /* 22 */ {XMC_GPIO_PORT2, 7},   // GPIO / AD_AUX_2 Additional Pin           P2.7
    /* 23 */ {XMC_GPIO_PORT2, 5},   // GPIO / AD_AUX_3 Additional Pin           P2.5
    /* 24 */ {XMC_GPIO_PORT2, 2},   // GPIO / AD_AUX_4 Additional Pin           P2.2
    /* 25 */ {XMC_GPIO_PORT1, 4},   // External int 1                           P1.4
    /* 26 */ {XMC_GPIO_PORT1, 5}    // LED3 output                               P1.5
};

const uint8_t GND = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
const uint8_t NUM_DIGITAL = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
;

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0  */ {CCU40, CCU40_CC41, 1, 1, CCU40_IN1_U0C1_DX2INS},
    /* 1  */ {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_U0C0_DX2INS}};
const uint8_t NUM_INTERRUPT = (sizeof(mapping_interrupt) / sizeof(XMC_PIN_INTERRUPT_t));

/* Mapping of Arduino Pins to PWM4 channels as pin and index in PWM4 channel
   mapping array XMC_PWM4_t mapping_pwm4[]
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][2] = {{3, 0},  {4, 1},  {6, 2},    {9, 3},
                                       {10, 4}, {11, 5}, {255, 255}};

/* Configurations of PWM channels for CCU4 type */
XMC_PWM4_t mapping_pwm4[] = {
    {CCU40, CCU40_CC41, 1, mapping_port_pin[3], P1_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  4
    {CCU40, CCU40_CC40, 0, mapping_port_pin[4], P1_0_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  4
    {CCU41, CCU41_CC40, 0, mapping_port_pin[6], P0_6_AF_CCU41_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  4
    {CCU40, CCU40_CC41, 1, mapping_port_pin[9], P0_7_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  4
    {CCU40, CCU40_CC41, 1, mapping_port_pin[10], P0_4_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  4
    {CCU40, CCU40_CC41, 1, mapping_port_pin[11], P0_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED} // PWM disabled  4
};

const uint8_t NUM_PWM4 = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));
const uint8_t NUM_PWM = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));

/* Analog Pin mappings and configurations */
// ADC grouping for XMC 1400 series.
XMC_ADC_t mapping_adc[] = {
    {VADC, 0, VADC_G0, 0, 4, DISABLED},  // A0
    {VADC, 1, VADC_G0, 0, 11, DISABLED}, // A1
    {VADC, 2, VADC_G0, 0, 9, DISABLED},  // A2
    {VADC, 3, VADC_G0, 0, 12, DISABLED}, // A3
    {VADC, 6, VADC_G0, 0, 7, DISABLED},  // A4
    {VADC, 5, VADC_G0, 0, 10, DISABLED}, // A5
    // Additional channels added here
    {VADC, 4, VADC_G0, 0, 5, DISABLED}, // AUX 21
    {VADC, 1, VADC_G1, 1, 1, DISABLED}, // AUX 22
    {VADC, 7, VADC_G1, 1, 2, DISABLED}, // AUX 23
    {VADC, 7, VADC_G0, 0, 3, DISABLED}  // AUX 24
};

const uint8_t NUM_ANALOG_INPUTS = (sizeof(mapping_adc) / sizeof(XMC_ADC_t));

/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

/* First UART channel pins are swapped between debug and  normal use */
XMC_UART_t XMC_UART_0 = {.channel = XMC_UART0_CH1,
                         .rx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE,
    #ifdef SERIAL_DEBUG
                                .pin = (uint8_t)3
    #else
                                .pin = (uint8_t)2
    #endif
                         },
                         .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                                       .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                         .tx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE,
    #ifdef SERIAL_DEBUG
                                .pin = (uint8_t)2
    #else
                                .pin = (uint8_t)3
    #endif
                         },
                         .tx_config = {.mode = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
                                       .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    #ifdef SERIAL_DEBUG
                         .input_source_dx0 = (XMC_USIC_INPUT_t)USIC0_C1_DX0_P1_3,
    #else
                         .input_source_dx0 = (XMC_USIC_INPUT_t)USIC0_C1_DX0_P1_2,
    #endif
                         .input_source_dx1 = XMC_INPUT_INVALID,
                         .input_source_dx2 = XMC_INPUT_INVALID,
                         .input_source_dx3 = XMC_INPUT_INVALID,
                         .irq_num = USIC0_0_IRQn,
                         .irq_service_request = 0};

HardwareSerial Serial(&XMC_UART_0, &rx_buffer_0, &tx_buffer_0);

// SPI instance
XMC_SPI_t XMC_SPI_0 = {
    .channel = XMC_SPI1_CH1,
    .channel_config = {.baudrate = 15984375U,
                       .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
                       .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
                       .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE},
    .mosi = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)1},
    .mosi_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT9,
                    .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                    .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

    },
    .miso = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)0},
    .miso_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                    .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD},
    .input_source = XMC_INPUT_A,
    .sclkout = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)3},
    .sclkout_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT8,
                       .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

    }};

// I2C instance
XMC_I2C_t XMC_I2C_0 = {.channel = XMC_I2C0_CH0,
                       .channel_config = {.baudrate = (uint32_t)(100000U), .address = 0U},
                       .sda = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)1},
                       .sda_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
                                      .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                       },
                       .scl = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)0},
                       .scl_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
                                      .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                       },
                       .input_source_dx0 = XMC_INPUT_F,
                       .input_source_dx1 = XMC_INPUT_E,
                       .slave_receive_irq_num = (IRQn_Type)USIC0_4_IRQn,
                       .slave_receive_irq_service_request = 4,
                       .protocol_irq_num = (IRQn_Type)USIC0_5_IRQn,
                       .protocol_irq_service_request = 5};

    // Serial Interrupt and event handling
    #ifdef __cplusplus
extern "C" {
    #endif
void serialEventRun();
void serialEvent() __attribute__((weak));

void serialEventRun() {
    if (serialEvent) {
        if (Serial.available())
            serialEvent();
    }
}

void USIC0_0_IRQHandler() { Serial.IrqHandler(); }
    #ifdef __cplusplus
}
    #endif
#endif /* ARDUINO_MAIN */

#ifdef __cplusplus
extern HardwareSerial Serial;
#endif /* cplusplus */

#endif // PINS_ARDUINO_H_
