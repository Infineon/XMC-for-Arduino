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
#include <XMC1400.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD XMC 1400 XMC2GO

/* On board LED is ON when digital output is 1, HIGH, TRUE, ON */
#define XMC_LED_ON 1

// Following were defines now evaluated by compilation as const variables
// After definitions of associated mapping arrays
extern const uint8_t NUM_DIGITAL;
extern const uint8_t GND;
extern const uint8_t NUM_PWM4;
extern const uint8_t NUM_PWM;
extern const uint8_t NUM_INTERRUPT;
extern const uint8_t NUM_ANALOG_INPUTS;
#define NUM_LEDS 2
#define NUM_SERIAL 1
#define NUM_TONE_PINS 4 // PWM Pins
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

// Generate 490Hz @fCCU=1MHz
#define PWM4_TIMER_PERIOD (2041U)

// PCLK = 2 * MCLK
#define PCLK 96000000u

// Define SPI pin
#define PIN_SPI_SS 3
#define PIN_SPI_MOSI 1
#define PIN_SPI_MISO 0
#define PIN_SPI_SCK 2

// Define analog pin
#define A0 0
#define A1 1
#define A2 2
#define A3 3

// XMC_I2S defines
/*U0C1*/
/*DX0C(Input) -> P0.0*/
/*SCLKOUT(ALT6) -> P0.3*/
/*WA(ALT6) -> P0.4*/

// XMC_I2S instance
#define MASTER_CHANNEL XMC_I2S1_CH1
#define MASTER_MRST PORT0, 0
#define INPUT_SOURCE USIC1_C1_DX0_P0_0
#define MASTER_SCLK PORT0, 3
#define MASTER_WACLK PORT0, 4

// Define LED & builtin-led
#define LED1 14
#define LED2 15
#define LED_BUILTIN LED1

/* Mapping interrupt handlers. Notice that XMC1400 can have interrupt handlers working in 3 modes,
   the defines below assumes the mode A. For details refer to assembly file and reference manual.
*/
#define USIC0_0_IRQHandler IRQ9_Handler // UART
#define USIC0_0_IRQn IRQ9_IRQn

#define CCU40_0_IRQHandler IRQ21_Handler // interrupt 0
#define CCU40_0_IRQn IRQ21_IRQn

#define CCU40_1_IRQHandler IRQ22_Handler // interrupt x, placeholder
#define CCU40_1_IRQn IRQ22_IRQn

#define USIC0_4_IRQHandler IRQ13_Handler // I2C
#define USIC0_4_IRQn IRQ13_IRQn

#define USIC0_5_IRQHandler IRQ14_Handler // I2C
#define USIC0_5_IRQn IRQ14_IRQn

/* I2S interrupt source B */
#define USIC1_2_IRQHandler IRQ11_Handler // I2S
#define USIC1_2_IRQn IRQ11_IRQn

#define SCU_1_IRQHandler IRQ1_Handler // RTC
#define SCU_1_IRQn IRQ1_IRQn

#define ERU0_0_IRQHandler IRQ3_Handler // RESET
#define ERU0_0_IRQn IRQ3_IRQn

/* CAN interrupt source B */
#define CAN0_3_IRQHandler IRQ7_Handler // CAN
#define CAN0_3_IRQn IRQ7_IRQn

#define digitalPinToInterrupt(p) (((p) == 9) ? 0 : NOT_AN_INTERRUPT)

#ifdef ARDUINO_MAIN
// Mapping of digital pins and comments
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */ {XMC_GPIO_PORT0, 0},   // SPI-MISO P0.0
    /* 1  */ {XMC_GPIO_PORT0, 1},   // SPI-MOSI / PWM40-1 output P0.1
    /* 2  */ {XMC_GPIO_PORT0, 3},   // SPI-SCK  / PWM40-3 output P0.3
    /* 3  */ {XMC_GPIO_PORT0, 4},   // SPI-SS  / PWM40-1 output P0.4
    /* 4  */ {XMC_GPIO_PORT0, 14},  // GPIO P0.14
    /* 5  */ {XMC_GPIO_PORT0, 15},  // GPIO P0.15
    /* 6  */ {XMC_GPIO_PORT2, 0},   // TX P2.0
    /* 7  */ {XMC_GPIO_PORT2, 6},   // RX P2.6 (INPUT ONLY)
    /* 8  */ {XMC_GPIO_PORT0, 5},   // PWM40-0 output P0.5
    /* 9  */ {XMC_GPIO_PORT1, 4},   // External interrupt 0 P1.4
    /* 10  */ {XMC_GPIO_PORT2, 11}, // I2C Clock SCL / A3 ADC P2.11
    /* 11  */ {XMC_GPIO_PORT2, 10}, // I2C Data / A2 ADC P2.10
    /* 12  */ {XMC_GPIO_PORT2, 9},  // A1 / ADC Input P2.9 (INPUT ONLY)
    /* 13  */ {XMC_GPIO_PORT2, 8},  // A0 / ADC Input P2.8 (INPUT ONLY)
    /* 14  */ {XMC_GPIO_PORT0, 7},  // LED 1 output P0.7
    /* 15  */ {XMC_GPIO_PORT0, 6},  // LED 2 output P0.6
    /* 16  */ {XMC_GPIO_PORT2, 1},  // DEBUG_TX P2.1
    /* 17  */ {XMC_GPIO_PORT2, 2},  // DEBUG_RX P2.2 (INPUT ONLY)

    /* 18  */ {XMC_GPIO_PORT1, 0}, // CAN_TX P1.0 (connected with CAN Transceiver)
    /* 19  */ {XMC_GPIO_PORT1, 1}  // CAN_RX P1.1 (connected with CAN Transceiver)
};
const uint8_t GND = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
const uint8_t NUM_DIGITAL = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));

/* Configurations of Interrupt */
const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0  */ {CCU40, CCU40_CC40, 0, 0, CCU40_IN0_U0C0_DX2INS}};
const uint8_t NUM_INTERRUPT = (sizeof(mapping_interrupt) / sizeof(XMC_PIN_INTERRUPT_t));

/* Mapping of Arduino Pins to PWM4 channels as pin and index in PWM4 channel
   mapping array XMC_PWM4_t mapping_pwm4[]
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][2] = {{1, 0}, {2, 1}, {3, 2}, {8, 3}, {9, 4}, {255, 255}};

/* Configurations of PWM channels for CCU4 type */
XMC_PWM4_t mapping_pwm4[] = {
    {CCU40, CCU40_CC41, 1, mapping_port_pin[1], P0_1_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  1    P0.1
    {CCU40, CCU40_CC43, 3, mapping_port_pin[2], P0_3_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  2    P0.3
    {CCU40, CCU40_CC41, 1, mapping_port_pin[3], P0_4_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  3    P0.4
    {CCU40, CCU40_CC40, 0, mapping_port_pin[8], P0_5_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  8    P0.5
    {CCU41, CCU41_CC40, 0, mapping_port_pin[9], P1_4_AF_CCU41_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED} // PWM disabled  9    P1.4
};
const uint8_t NUM_PWM = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));
const uint8_t NUM_PWM4 = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));

/* Analog Pin mappings and configurations */
// XMC_ADC_t mapping_adc[] =
//     {
//     { VADC, 1, DISABLED },   //A0 P2.8
//     { VADC, 2, DISABLED },  //A1 P2.9
//     { VADC, 3, DISABLED },   //A2 P2.10
//     { VADC, 4, DISABLED },  //A3 P2.11
//     };

XMC_ADC_t mapping_adc[] = {
    {VADC, 1, VADC_G0, 0, 1, DISABLED}, // A0 P2.8
    {VADC, 2, VADC_G0, 0, 2, DISABLED}, // A1 P2.9
    {VADC, 3, VADC_G0, 0, 3, DISABLED}, // A2 P2.10
    {VADC, 4, VADC_G0, 0, 4, DISABLED}, // A3 P2.11
};

const uint8_t NUM_ANALOG_INPUTS = (sizeof(mapping_adc) / sizeof(XMC_ADC_t));

/*
 * UART objects
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

/* First UART channel pins are swapped between debug and normal use */
XMC_UART_t XMC_UART_0 = {.channel = XMC_UART0_CH0,
                         .rx = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, // RX P2.6
    #ifdef SERIAL_DEBUG
                                .pin = (uint8_t)2
    #else
                                .pin = (uint8_t)6
    #endif
                         },
                         .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                                       .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                         },
                         .tx = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, // TX P2.0
    #ifdef SERIAL_DEBUG
                                .pin = (uint8_t)1
    #else
                                .pin = (uint8_t)0
    #endif
                         },
                         .tx_config = {.mode = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
                                       .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                         },
                         .input_source_dx0 = (XMC_USIC_INPUT_t)USIC0_C0_DX0_DX3INS,
                         .input_source_dx1 = XMC_INPUT_INVALID,
                         .input_source_dx2 = XMC_INPUT_INVALID,
    #ifdef SERIAL_DEBUG
                         .input_source_dx3 = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_2,
    #else
                         .input_source_dx3 = (XMC_USIC_INPUT_t)USIC0_C0_DX3_P2_6,
    #endif
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

XMC_I2C_t XMC_I2C_0 = {.channel = XMC_I2C0_CH1,
                       .channel_config = {.baudrate = (uint32_t)(100000U), .address = 0U},
                       .sda = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)10},
                       .sda_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
                                      .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                       },
                       .scl = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)11},
                       .scl_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
                                      .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                       },
                       .input_source_dx0 = XMC_INPUT_F,
                       .input_source_dx1 = XMC_INPUT_E,
                       .slave_receive_irq_num = (IRQn_Type)USIC0_4_IRQn,
                       .slave_receive_irq_service_request = 4,
                       .protocol_irq_num = (IRQn_Type)USIC0_5_IRQn,
                       .protocol_irq_service_request = 5};

XMC_I2S_t i2s_config = {.input_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                                         .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                         .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                        },
                        .sclk_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT8,
                                        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                        },
                        .wa_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT8,
                                      .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH

                        },
                        .protocol_irq_num = (IRQn_Type)USIC1_2_IRQn,
                        .protocol_irq_service_request = 2,
                        .protocol_irq_source = XMC_SCU_IRQCTRL_USIC1_SR2_IRQ11};

    // XMC CAN instance
    #ifdef CAN_xmc
XMC_ARD_CAN_t XMC_CAN_0 = {.can_node = CAN_NODE0,
                           .can_node_num = XMC_NODE_NUM_0,
                           .can_clock = XMC_CAN_CANCLKSRC_MCLK,
                           .can_frequency = (uint32_t)48000000,
                           .rx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)1},
                           .rx_config =
                               {
                                   .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                               },
                           .tx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)0},
                           .tx_config =
                               {
                                   .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT9,
                               },
                           .node_input = CAN_NODE0_RXD_P1_1,
                           .irq_num = CAN0_3_IRQn,
                           .irq_service_request = 3,
                           .irq_source = XMC_SCU_IRQCTRL_CAN0_SR3_IRQ7};
    #endif

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
