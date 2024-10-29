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
#include <XMC1100.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD XMC 1100 Boot Kit

/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define XMC_LED_ON 0

// Following were defines now evaluated by compilation as const variables
// After definitions of associated mapping arrays
extern const uint8_t NUM_DIGITAL;
extern const uint8_t GND;
extern const uint8_t NUM_PWM4;
extern const uint8_t NUM_PWM;
extern const uint8_t NUM_INTERRUPT;
extern const uint8_t NUM_ANALOG_INPUTS;
#define NUM_LEDS 7
#define NUM_SERIAL 1
#define NUM_TONE_PINS 4
#define NUM_TASKS_VARIANT 8
#define NUM_SPI 1
#define NUM_I2C 1

// Indicate unit has RTC/Alarm for simpler RTC control
#define HAS_RTC

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

// Generate 490Hz @fCCU=1MHz
#define PWM4_TIMER_PERIOD (2041U)

#define PCLK 64000000u

#define PIN_SPI_SS 10
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13

extern uint8_t SS;
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

// XMC_I2S defines
/*U0C1*/
/*DX0C(Input) -> P0.6*/
/*SCLKOUT(ALT6) -> P0.8*/
/*WA(ALT6) -> P0.9*/
#define MASTER_CHANNEL XMC_I2S0_CH1
#define MASTER_MRST PORT0, 6
#define INPUT_SOURCE USIC0_C1_DX0_P0_6
#define MASTER_SCLK PORT0, 8
#define MASTER_WACLK PORT0, 9

// Uncomment this to use the second I2S interface,
// uses some of the same pins as SPI!
// /*U0C0*/
// /*DX0C(Input) -> P1.0*/
// /*SCLKOUT(ALT6) -> P0.7*/
// /*WA(ALT6) -> P0.9*/
// #define MASTER_CHANNEL  XMC_I2S0_CH0
// #define MASTER_MRST     PORT0, 11
// #define INPUT_SOURCE    USIC0_C0_DX0_P1_0
// #define MASTER_SCLK     PORT0, 7
// #define MASTER_WACLK    PORT0, 9

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

// AD_AUX Connector
#define AD_AUX_1 23
#define AD_AUX_2 24
// AUX Connector
#define AUX_1 25
#define AUX_2 26
#define AUX_3 27
#define AUX_4 28
#define AUX_5 29

#define LED_BUILTIN 13
#define LED1 25
#define LED2 26
#define LED3 0
#define LED4 1
#define LED5 2
#define LED6 30

#define digitalPinToInterrupt(p) ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
// Mapping of digital pins and comments
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */ {XMC_GPIO_PORT1, 2},   // RX / LED 3 output                  P1.2
    /* 1  */ {XMC_GPIO_PORT1, 3},   // TX / LED 4 output                  P1.3
    /* 2  */ {XMC_GPIO_PORT1, 4},   // External int 0 / LED 5 output      P1.4
    /* 3  */ {XMC_GPIO_PORT0, 0},   // External int 1 / PWM40-0 output    P0.0
    /* 4  */ {XMC_GPIO_PORT0, 1},   // PWM40-1 output                     P0.1
    /* 5  */ {XMC_GPIO_PORT0, 2},   // GPIO                               P0.2
    /* 6  */ {XMC_GPIO_PORT0, 3},   // PWM40-3 output                     P0.3
    /* 7  */ {XMC_GPIO_PORT0, 4},   // GPIO                               P0.4
    /* 8  */ {XMC_GPIO_PORT0, 12},  // GPIO                               P0.12
    /* 9  */ {XMC_GPIO_PORT0, 8},   // PWM40-2 output                     P0.8
    /* 10  */ {XMC_GPIO_PORT0, 9},  // SPI-SS / PWM40-3 output            P0.9
    /* 11  */ {XMC_GPIO_PORT1, 1},  // SPI-MOSI / PWM40-1 output          P1.1
    /* 12  */ {XMC_GPIO_PORT1, 0},  // SPI-MISO                           P1.0
    /* 13  */ {XMC_GPIO_PORT0, 7},  // SPI-SCK / LED BUILTIN output       P0.7
    /* 14  */ {XMC_GPIO_PORT2, 3},  // AREF ** DO NOT USE as GPIO or REF ** P2.3
    /* 15  */ {XMC_GPIO_PORT2, 1},  // I2C Data / Address SDA / A7  ADC   P2.1
    /* 16  */ {XMC_GPIO_PORT2, 0},  // I2C Clock SCL / A6  ADC            P2.0
    /* 17  */ {XMC_GPIO_PORT2, 6},  // A0 / ADC Input                     P2.6 (INPUT ONLY)
    /* 18  */ {XMC_GPIO_PORT2, 8},  // A1 / ADC Input                     P2.8 (INPUT ONLY)
    /* 19  */ {XMC_GPIO_PORT2, 9},  // A2 / ADC Input                     P2.9 (INPUT ONLY)
    /* 20  */ {XMC_GPIO_PORT2, 10}, // A3 / ADC Input                     P2.10
    /* 21  */ {XMC_GPIO_PORT2, 11}, // A4 / ADC Input                     P2.11
    /* 22  */ {XMC_GPIO_PORT2, 2},  // A5 / ADC Input                     P2.2 (INPUT ONLY)
    /* 23  */ {XMC_GPIO_PORT2, 5},  // AD_AUX                             P2.5 (INPUT ONLY)
    /* 24  */ {XMC_GPIO_PORT2, 7},  // AD_AUX                             P2.7 (INPUT ONLY)
    /* 25  */ {XMC_GPIO_PORT0, 5},  // AUX / GPIO / LED 1 output          P0.5
    /* 26  */ {XMC_GPIO_PORT0, 6},  // AUX / GPIO / LED 2 output          P0.6
    /* 27  */ {XMC_GPIO_PORT0, 10}, // AUX / GPIO                         P0.10
    /* 28  */ {XMC_GPIO_PORT0, 11}, // AUX / GPIO                         P0.11
    /* 29  */ {XMC_GPIO_PORT0, 13}, // AUX / GPIO                         P0.13
    /* 30  */ {XMC_GPIO_PORT1, 5}   // LED 6 output                       P1.5
};
const uint8_t GND = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
const uint8_t NUM_DIGITAL = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
;

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0  */ {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_U0C0_DX2INS},
    /* 1  */ {CCU40, CCU40_CC40, 0, 1, CCU40_IN0_P0_0}};
const uint8_t NUM_INTERRUPT = (sizeof(mapping_interrupt) / sizeof(XMC_PIN_INTERRUPT_t));

/* Mapping of Arduino Pins to PWM4 channels as pin and index in PWM4 channel
   mapping array XMC_PWM4_t mapping_pwm4[]
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][2] = {{3, 0},  {4, 1},  {6, 2},  {9, 3},
                                       {10, 4}, {11, 5}, {20, 6}, {255, 255}};

/* Configurations of PWM channels for CCU4 type */
XMC_PWM4_t mapping_pwm4[] = {
    {CCU40, CCU40_CC40, 0, mapping_port_pin[3], P0_0_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  3   P0.0
    {CCU40, CCU40_CC41, 1, mapping_port_pin[4], P0_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  4   P0.1
    {CCU40, CCU40_CC43, 3, mapping_port_pin[6], P0_3_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  6   P0.3
    {CCU40, CCU40_CC42, 2, mapping_port_pin[9], P0_8_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  9   P0.8
    {CCU40, CCU40_CC43, 3, mapping_port_pin[10], P0_9_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled 10   P0.9
    {CCU40, CCU40_CC41, 1, mapping_port_pin[11], P1_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled 11   P1.1
    {CCU40, CCU40_CC42, 2, mapping_port_pin[20], P2_10_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED} // PWM disabled 20   P2.10
};
const uint8_t NUM_PWM = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));
const uint8_t NUM_PWM4 = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));

/* Analog Pin mappings and configurations */
XMC_ADC_t mapping_adc[] = {{VADC, 0, DISABLED}, {VADC, 1, DISABLED}, {VADC, 2, DISABLED},
                           {VADC, 3, DISABLED}, {VADC, 4, DISABLED}, {VADC, 7, DISABLED},
                           {VADC, 5, DISABLED}, {VADC, 6, DISABLED}};
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
    .channel = XMC_SPI0_CH0,
    .channel_config = {.baudrate = 15984375U,
                       .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
                       .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
                       .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE},
    .mosi = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)1},
    .mosi_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
                    .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                    .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

    },
    .miso = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)0},
    .miso_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                    .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD},
    .input_source = XMC_INPUT_C,
    .sclkout = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)7},
    .sclkout_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
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

// XMC_I2S instance
XMC_I2S_t i2s_config = {.input_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                                         .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                         .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                        },
                        .sclk_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
                                        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                        },
                        .wa_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
                                      .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                        },
                        .protocol_irq_num = (IRQn_Type)USIC0_2_IRQn,
                        .protocol_irq_service_request = 2};

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
