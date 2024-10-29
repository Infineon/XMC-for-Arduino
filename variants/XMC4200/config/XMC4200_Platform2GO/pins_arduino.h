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
#define XMC_BOARD XMC 4200 Platform 2GO

/* On board LED is ON when digital output is 1, HIGH, TRUE, ON */
#define XMC_LED_ON 1

// Following were defines now evaluated by compilation as const variables
// After definitions of associated mapping arrays
extern const uint8_t NUM_DIGITAL;
extern const uint8_t GND;
extern const uint8_t NUM_PWM4;
extern const uint8_t NUM_PWM8;
extern const uint8_t NUM_PWM;
extern const uint8_t NUM_INTERRUPT;
extern const uint8_t NUM_ANALOG_INPUTS;
#ifdef DAC
extern const uint8_t NUM_ANALOG_OUTPUTS;
#endif
#define NUM_LEDS 1
#define NUM_BUTTONS 1
#define NUM_SERIAL 1
#define NUM_TONE_PINS 7
#define NUM_TASKS_VARIANT 12
#define NUM_SPI 1
#define NUM_I2C 1

// Indicate unit has RTC/Alarm
#define HAS_RTC 1

// Generate 490Hz @fCCU=80MHz
#define PWM4_TIMER_PERIOD (0x09F7)
// Generate 490Hz @fCCU=80MHz
#define PWM8_TIMER_PERIOD (0x09F7)

#define PCLK 80000000u

#define PIN_SPI_SS 10
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13

extern uint8_t SS;
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define A0 0 // ADC G0CH0 P14.0
#define A1 1 // ADC G0CH6 P14.6
#define A2 2 // ADC G0CH7 P14.7
#define A3 3 // ADC G1CH0 P14.8
#define A4 4 // ADC G0CH4 P14.4
#define A5 5 // ADC G0CH5 P14.5
// Additional ADC ports starting here
#define A6 6 // ADC G1CH6 on P14.14
#define A7 7 // ADC G1CH1 on P14.9

#define LED1 36          // Additional LED1
#define LED_BUILTIN LED1 // Standard Arduino LED: Uses LED1
#define LED2 \
    LED1 // Dummy LED define macro; added to comply with LED Library examples in CI/CD workflow
#define BUTTON1 27 // Additional BUTTON1

#define digitalPinToInterrupt(p) ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
// Mapping of digital pins and comments
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */ {XMC_GPIO_PORT2, 15}, // RX                                     P2.15 X1-4
    /* 1  */ {XMC_GPIO_PORT2, 14}, // TX                                     P2.14 X1-3
    /* 2  */ {XMC_GPIO_PORT1, 0},  // GPIO / External INT 0                  P1.0 X1-11
    /* 3  */ {XMC_GPIO_PORT2, 2},  // PWM41-3 / PWM0 / External INT 1        P2.2 X1-31
    /* 4  */ {XMC_GPIO_PORT2, 9},  // IO_0                                   P2.9 X1-36
    /* 5  */ {XMC_GPIO_PORT2, 3},  // PWM41-2 output / PWM1                  P2.3 X1-32
    /* 6  */ {XMC_GPIO_PORT2, 4},  // PWM41-1 output / PWM2                  P2.4 X1-33
    /* 7  */ {XMC_GPIO_PORT2, 8},  // IO_1                                   P2.8 X1-35

    /* 8  */ {XMC_GPIO_PORT2, 6},  // IO_2                                   P2.6 X1-27
    /* 9  */ {XMC_GPIO_PORT0, 11}, // PWM80-31 output / PWM3                 P0.11 X2-7
    /* 10 */ {XMC_GPIO_PORT1, 7},  // SPI-CS                                 P1.7 X1-8
    /* 11 */ {XMC_GPIO_PORT1, 9},  // SPI-MOSI                               P1.9 X1-10
    /* 12 */ {XMC_GPIO_PORT0, 0},  // SPI-MISO                               P0.0 X2-18
    /* 13 */ {XMC_GPIO_PORT1, 8},  // SPI-SCK                                P1.8 X1-9
    /* 14 */ {XMC_GPIO_PORT2, 5},  // I2C Data / Address SDA / A4            P2.5  (Hardwired to A4)
                                   // X1-34
    /* 15 */ {XMC_GPIO_PORT3, 0},  // I2C Clock SCL  / A5                    P3.0  (Hardwired to A5)
                                   // X2-19
    /* 16  */ {XMC_GPIO_PORT14, 0}, // A0 / ADC Input                         P14.0 (INPUT ONLY)
                                    // X2-34
    /* 17  */ {XMC_GPIO_PORT14, 6}, // A1 / ADC Input                         P14.6 (INPUT ONLY)
                                    // X2-25
    /* 18  */ {XMC_GPIO_PORT14, 7}, // A2 / ADC Input                         P14.7 (INPUT ONLY)
                                    // X2-28
    /* 19  */ {XMC_GPIO_PORT14, 8}, // A3 / ADC Input / AN_MikroBus / DAC0    P14.8 X2-33
    /* 20  */ {XMC_GPIO_PORT14, 4}, // A4 / ADC Input / SDA / AN1_2GO_1       P14.4 (Hardwired to
                                    // SDA)            X2-24
    /* 21  */ {XMC_GPIO_PORT14, 5}, // A5 / ADC Input / SCL / AN2_2GO_2       P14.5 (Hardwired to
                                    // SCL)            X2-30

    // Additional pins for port X1 starting here
    /* 22  */ {XMC_GPIO_PORT1, 1},  // PWM_MikroBus / PWM40-2                 P1.1 X1-12
    /* 23  */ {XMC_GPIO_PORT1, 2},  // PWM / PWM40-1 / GPIO4_S2GO_1           P1.2 X1-13
    /* 24  */ {XMC_GPIO_PORT1, 3},  // PWM / PWM40-0 / GPIO4_2GO_2            P1.3 X1-14
    /* 25  */ {XMC_GPIO_PORT1, 4},  // PC_TXD                                 P1.4 X1-15
    /* 26  */ {XMC_GPIO_PORT1, 5},  // PC_RXD                                 P1.5 X1-16
    /* 27  */ {XMC_GPIO_PORT1, 15}, // BUTTON1                                P1.15 X1-22
    /* 28  */ {XMC_GPIO_PORT2, 7},  // RST_MikroBus                           P2.7 X1-28
    /* 29  */ {XMC_GPIO_PORT2, 0},  // CAN_TX                                 P2.0 X1-29
    /* 30  */ {XMC_GPIO_PORT2, 1},  // GPIO1_2GO_2                            P2.1 X1-30

    // Additional pins for port X2 starting here
    /* 31  */ {XMC_GPIO_PORT0, 7},   // SPI-CS_MikroBus                        P0.7 X2-1
    /* 32  */ {XMC_GPIO_PORT0, 8},   // RST / GPIO2_2GO_1                      P0.8 X2-4
    /* 33  */ {XMC_GPIO_PORT0, 5},   // INT / GPIO3_2GO_1                      P0.5 X2-9
    /* 34  */ {XMC_GPIO_PORT0, 3},   // INT / GPIO3_2GO_2                      P0.3 X2-11
    /* 35  */ {XMC_GPIO_PORT0, 6},   // RST / GPIO2_2GO_2                      P0.6 X2-12
    /* 36  */ {XMC_GPIO_PORT0, 1},   // LED1                                   P0.1 X2-13
    /* 37  */ {XMC_GPIO_PORT0, 4},   // GPIO1_S2GO_1                           P0.4 X2-14
    /* 38  */ {XMC_GPIO_PORT0, 10},  // INT_MikroBus                           P0.10 X2-15
    /* 39  */ {XMC_GPIO_PORT0, 2},   // SPI-CS_2GO_1                           P0.2 X2-16
    /* 40  */ {XMC_GPIO_PORT0, 9},   // SPI-CS_2GO_2                           P0.9 X2-20
    /* 41  */ {XMC_GPIO_PORT14, 14}, // AN2_2GO_1 / A6 / ADC Input             P14.14 (INPUT ONLY)
                                     // X2-21
    /* 42  */ {XMC_GPIO_PORT14, 3},  // CAN_RX                                 P14.3 X2-32
    /* 43  */ {XMC_GPIO_PORT14, 9},  // AN1_2GO_2 / A7 / ADC Input / DAC1      P14.9 X2-36
};

const uint8_t GND = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
const uint8_t NUM_DIGITAL = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
;

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0  */ {XMC_ERU0, XMC_ERU_ETL_INPUT_A0, XMC_ERU_ETL_INPUT_B0, 3, 3, 0},
    /* 1  */ {XMC_ERU0, XMC_ERU_ETL_INPUT_A0, XMC_ERU_ETL_INPUT_B2, 1, 0, 1}};
const uint8_t NUM_INTERRUPT = (sizeof(mapping_interrupt) / sizeof(XMC_PIN_INTERRUPT_t));

/* Mapping of Arduino Pins to PWM4 channels as pin and index in PWM4 channel
   mapping array XMC_PWM4_t mapping_pwm4[]
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][2] = {{3, 0},  // PWM0
                                       {5, 1},  // PWM1
                                       {6, 2},  // PWM2
                                       {22, 3}, // PWM
                                       {23, 4}, // PWM
                                       {24, 5}, // PWM
                                       {255, 255}};

/* Configurations of PWM channels for CCU4 type */
XMC_PWM4_t mapping_pwm4[] = {
    {CCU41, CCU41_CC43, 3, mapping_port_pin[3], P2_2_AF_CCU41_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  3  P2.2
    {CCU41, CCU41_CC42, 2, mapping_port_pin[5], P2_3_AF_CCU41_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  5  P2.3
    {CCU41, CCU41_CC41, 1, mapping_port_pin[6], P2_4_AF_CCU41_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  6  P2.4
    // additional pwm outputs starting here
    {CCU40, CCU40_CC42, 2, mapping_port_pin[22], P1_1_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  22   P1.1
    {CCU40, CCU40_CC41, 1, mapping_port_pin[23], P1_2_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  23   P1.2
    {CCU40, CCU40_CC40, 0, mapping_port_pin[24], P1_3_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED} // PWM disabled  24   P1.3
};
const uint8_t NUM_PWM4 = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));

/* Mapping in same manner as PWM4 for PWM8 channels */
const uint8_t mapping_pin_PWM8[][2] = {{9, 0}, // PWM3
                                       {255, 255}};

/* Configurations of PWM channels for CCU8 type */
XMC_PWM8_t mapping_pwm8[] = {
    {CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9],
     P0_11_AF_CCU80_OUT31, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED} // PWM disabled  9  P0.11
};
const uint8_t NUM_PWM8 = (sizeof(mapping_pwm8) / sizeof(XMC_PWM8_t));
const uint8_t NUM_PWM =
    (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t)) + (sizeof(mapping_pwm8) / sizeof(XMC_PWM8_t));

    /* Analog Pin mappings and configurations */
    #ifdef DAC
const uint8_t mapping_pin_DAC[][2] = {{19, 0}, {43, 1}, {255, 255}};

/* Analog Pin mappings and configurations */
XMC_ARD_DAC_t mapping_dac[] = {{XMC_DAC0, 0, 12}, {XMC_DAC0, 1, 12}};
const uint8_t NUM_ANALOG_OUTPUTS = (sizeof(mapping_dac) / sizeof(XMC_ARD_DAC_t));
    #endif

XMC_ADC_t mapping_adc[] = {
    // Result reg numbers are now equal to channel numbers
    {VADC, 0, VADC_G0, 0, 0, DISABLED}, // A0
    {VADC, 6, VADC_G0, 0, 1, DISABLED}, // A1
    {VADC, 7, VADC_G0, 0, 2, DISABLED}, // A2
    {VADC, 0, VADC_G1, 1, 0, DISABLED}, // A3
    {VADC, 4, VADC_G0, 0, 3, DISABLED}, // A4
    {VADC, 5, VADC_G0, 0, 4, DISABLED}, // A5
    // Additional ADC channels starting here
    {VADC, 6, VADC_G1, 1, 1, DISABLED}, // A6
    {VADC, 1, VADC_G1, 1, 2, DISABLED}, // A7
};
const uint8_t NUM_ANALOG_INPUTS = (sizeof(mapping_adc) / sizeof(XMC_ADC_t));

/*
 * UART objects
 *
 */

// Since both the UART interfaces are present on different USIC instances,
// both can be enabled independently.

// Serial is PC-DEBUG interface
// Serial1  is ONBOARD interface

RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

RingBuffer rx_buffer_1;
RingBuffer tx_buffer_1;

XMC_UART_t XMC_UART_0 = {
    .channel = XMC_UART0_CH0,
    .rx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)4},
    .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE},
    .tx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)5},
    .tx_config = {.mode = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE},
    .input_source_dx0 = (XMC_USIC_INPUT_t)USIC0_C0_DX0_P1_4,
    .input_source_dx1 = XMC_INPUT_INVALID,
    .input_source_dx2 = XMC_INPUT_INVALID,
    .input_source_dx3 = XMC_INPUT_INVALID,
    .irq_num = USIC0_0_IRQn,
    .irq_service_request = 0};

XMC_UART_t XMC_UART_1 = {
    .channel = XMC_UART1_CH0,
    .rx = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)15},
    .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE},
    .tx = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)14},
    .tx_config = {.mode = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE},
    .input_source_dx0 = (XMC_USIC_INPUT_t)USIC1_C0_DX0_P2_15,
    .input_source_dx1 = XMC_INPUT_INVALID,
    .input_source_dx2 = XMC_INPUT_INVALID,
    .input_source_dx3 = XMC_INPUT_INVALID,
    .irq_num = USIC1_0_IRQn,
    .irq_service_request = 0};

// Object instantiated of the HardwareSerial class for UART PC (debug) interface
HardwareSerial Serial(&XMC_UART_0, &rx_buffer_0, &tx_buffer_0);
// Object instantiated of the HardwareSerial class for UART ONBOARD interface
HardwareSerial Serial1(&XMC_UART_1, &rx_buffer_1, &tx_buffer_1);

// SPI instance
XMC_SPI_t XMC_SPI_0 = {
    .channel = XMC_SPI1_CH1,
    .channel_config = {.baudrate = 20003906U,
                       .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
                       .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
                       .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE},
    .mosi = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)9},
    .mosi_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
                    .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
    .miso = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)0},
    .miso_config =
        {
            .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        },
    .input_source = XMC_INPUT_D,
    .sclkout = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)8},
    .sclkout_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                       .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
};

// I2C instance
XMC_I2C_t XMC_I2C_0 = {.channel = XMC_I2C0_CH1,
                       .channel_config = {.baudrate = (uint32_t)(100000U), .address = 0U},
                       .sda = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)5},
                       .sda_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                       .scl = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)0},
                       .scl_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                       .input_source_dx0 = XMC_INPUT_B,
                       .input_source_dx1 = XMC_INPUT_B,
                       .slave_receive_irq_num = (IRQn_Type)84,
                       .slave_receive_irq_service_request = 1,
                       .protocol_irq_num = (IRQn_Type)85,
                       .protocol_irq_service_request = 2};

    // XMC CAN instance
    #ifdef CAN_xmc
XMC_ARD_CAN_t XMC_CAN_0 = {.can_node = CAN_NODE0,
                           .can_node_num = XMC_NODE_NUM_0,
                           .can_clock = XMC_CAN_CANCLKSRC_FPERI,
                           .can_frequency = (uint32_t)144000000,
                           .rx = {.port = (XMC_GPIO_PORT_t *)PORT14_BASE, .pin = (uint8_t)3},
                           .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE},
                           .tx = {.port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)0},
                           .tx_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1},
                           .node_input = CAN_NODE0_RXD_P14_3,
                           .irq_num = CAN0_7_IRQn,
                           .irq_service_request = 7u};
    #endif

    // Serial Interrupt and event handling
    #ifdef __cplusplus
extern "C" {
    #endif
void serialEventRun();
void serialEvent() __attribute__((weak));
void serialEvent1() __attribute__((weak));

void serialEventRun() {
    if (serialEvent) {
        if (Serial.available())
            serialEvent();
    }
    if (serialEvent1) {
        if (Serial1.available())
            serialEvent1();
    }
}

// IRQ Handler of Serial Onboard (USIC1)
void USIC1_0_IRQHandler() { Serial1.IrqHandler(); }

// IRQ Handler of Serial to PC USB (USIC0)
void USIC0_0_IRQHandler() { Serial.IrqHandler(); }

    #ifdef __cplusplus
}
    #endif
#endif /* ARDUINO_MAIN*/

#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
#endif /* cplusplus */
#endif
