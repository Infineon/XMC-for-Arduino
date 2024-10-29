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
#include <XMC4400.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define XMC_BOARD XMC 4400 Platform 2GO

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
#define NUM_LEDS 2
#define NUM_BUTTONS 2
#define NUM_SERIAL 1
#define NUM_TONE_PINS 16
#define NUM_TASKS_VARIANT 32
#define NUM_SPI 1
#define NUM_I2C 1

// Indicate unit has RTC/Alarm
#define HAS_RTC 1

// Generate 490Hz @fCCU=144MHz
#define PWM4_TIMER_PERIOD (0x11EF)
// Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)

#define PCLK 64000000u

#define PIN_SPI_SS 10
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13

extern uint8_t SS;
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
// Additional ADC ports starting here
#define A6 6
#define A7 7
#define A8 8
#define A9 9
#define A10 10
#define A11 11
#define A12 12
#define A13 13
#define A14 14
#define A15 15
#define A16 16
#define A17 17

#define LED1 65
#define LED2 62
#define LED_BUILTIN LED1

#define BUTTON1 68
#define BUTTON2 57

#define digitalPinToInterrupt(p) ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
// Mapping of digital pins and comments
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */ {XMC_GPIO_PORT2, 15}, // RX                                     P2.15 X1-4
    /* 1  */ {XMC_GPIO_PORT2, 14}, // TX                                     P2.14 X1-3
    /* 2  */ {XMC_GPIO_PORT1, 0},  // GPIO / External INT 0                  P1.0 X1-11
    /* 3  */ {XMC_GPIO_PORT3, 6},  // PWM42-0 / PWM0 / External INT 1        P3.6 X2-6
    /* 4  */ {XMC_GPIO_PORT1, 6},  // GPIO / IO_0                            P1.6 X1-7
    /* 5  */ {XMC_GPIO_PORT3, 3},  // PWM42-3 output / PWM1                  P3.3 X2-5
    /* 6  */ {XMC_GPIO_PORT3, 4},  // PWM42-2 output / PWM2                  P3.4 X2-8
    /* 7  */ {XMC_GPIO_PORT1, 14}, // GPIO / IO_1                            P1.14 X1-21
    /* 8  */ {XMC_GPIO_PORT4, 1},  // GPIO / IO_2                            P4.1 X1-6
    /* 9  */ {XMC_GPIO_PORT0, 11}, // PWM80-31 output / PWM3                 P0.11 X2-7
    /* 10 */ {XMC_GPIO_PORT0, 2},  // SPI-SS / PWM80-01 / PWM4               P0.2 X2-16
    /* 11 */ {XMC_GPIO_PORT1, 9},  // SPI-MOSI                               P1.9 X1-10
    /* 12 */ {XMC_GPIO_PORT0, 0},  // SPI-MISO                               P0.0 X2-18
    /* 13 */ {XMC_GPIO_PORT1, 8},  // SPI-SCK / GPIO                         P1.8 X1-9
    /* 14 */ {XMC_GPIO_PORT2, 5},  // I2C Data / Address SDA / A4 / PWM41-0  P2.5  (Hardwired to A4)
                                   // X1-34
    /* 15 */ {XMC_GPIO_PORT3, 0},  // I2C Clock SCL  / A5 - ADC Input        P3.0  (Hardwired to A5)
                                   // X2-19
    /* 16 */ {XMC_GPIO_PORT14, 0}, // A0 / ADC Input                         P14.0 (INPUT ONLY)
    /* 17 */ {XMC_GPIO_PORT14, 1}, // A1 / ADC Input                         P14.1 (INPUT ONLY)
    /* 18 */ {XMC_GPIO_PORT14, 2}, // A2 / ADC Input                         P14.2 (INPUT ONLY)
    /* 19 */ {XMC_GPIO_PORT14, 3}, // A3 / ADC Input                         P14.3 (INPUT ONLY)
                                   // X2-31
    /* 20 */ {XMC_GPIO_PORT14, 4}, // A4 / ADC Input / SDA / GPIO            P14.4 (Hardwired to
                                   // SDA)       X2-24
    /* 21 */ {XMC_GPIO_PORT14, 5}, // A5 / ADC Input / SCL                   P14.5 (Hardwired to
                                   // SCL)       X2-30
    /* 22 */ {XMC_GPIO_PORT1, 15}, // USB Debug RX                           P1.15 X1-22
    /* 23 */ {XMC_GPIO_PORT0, 5},  // USB Debug TX                           P0.5 X2-9

    // Additional pins for port X1 starting here
    /* 24 */ {XMC_GPIO_PORT2, 10}, // GPIO / ETH_LED                         P2.10 X1-37
    /* 25 */ {XMC_GPIO_PORT2, 8},  // GPIO / ETH_TXDO / PWM80-32             P2.8 X1-35
    /* 26 */ {XMC_GPIO_PORT2, 4},  // GPIO / ETH_RXER / PWM41-1              P2.4 X1-33
    /* 27 */ {XMC_GPIO_PORT2, 3},  // ETH_RXD1 / PWM41-2                     P2.3 X1-32
    /* 28 */ {XMC_GPIO_PORT2, 2},  // GPIO / ETH_RXDO / PWM41-3              P2.2 X1-31
    /* 29 */ {XMC_GPIO_PORT2, 0},  // GPIO / ETH_MDIO / PWM81-21             P2.0 X1-29
    /* 30 */ {XMC_GPIO_PORT2, 6},  // PWM80-13 / GPIO4_2GO_2                 P2.6 X1-27
    /* 31 */ {XMC_GPIO_PORT5, 2},  // GPIO / RST                             P5.2 X1-25
    /* 32 */ {XMC_GPIO_PORT5, 0},  // GPIO1_2GO_1                            P5.0 X1-23
    /* 33 */ {XMC_GPIO_PORT1, 12}, // GPIO / CAN_TX                          P1.12 X1-19
    /* 34 */ {XMC_GPIO_PORT1, 10}, // GPIO / GPIO2_2GO_1                     P1.10 X1-17
    /* 35 */ {XMC_GPIO_PORT1, 4},  // GPIO / QSPI_IO1                        P1.4 X1-15
    /* 36 */ {XMC_GPIO_PORT1, 2},  // GPIO / QSPI_IO3                        P1.2 X1-13
    /* 37 */ {XMC_GPIO_PORT4, 0},  // GPIO / GPIO2_2GO_2                     P4.0 X1-5
    /* 38 */ {XMC_GPIO_PORT1, 7}, // GPIO / SPI_CS_2GO_2                    P1.7 (Chip Select - Slot
                                  // 2)    X1-8
    /* 39 */ {XMC_GPIO_PORT1, 1}, // GPIO1_2GO_2                            P1.1 X1-12
    /* 40 */ {XMC_GPIO_PORT1, 3}, // GPIO / QSPI_IO3                        P1.3 X1-14
    /* 41 */ {XMC_GPIO_PORT1, 5}, // GPIO / QSPI_IO0                        P1.5 X1-16
    /* 42 */ {XMC_GPIO_PORT1, 11}, // GPIO / QSPI_CS                         P1.11 X1-18
    /* 43 */ {XMC_GPIO_PORT1, 13}, // GPIO / CAN_RX                          P1.13 X1-20
    /* 44 */ {XMC_GPIO_PORT5, 1},  // GPIO / ETH_INT                         P5.1 X1-24
    /* 45 */ {XMC_GPIO_PORT5, 7},  // PWM81-02                               P5.7 X1-26
    /* 46 */ {XMC_GPIO_PORT2, 7},  // PWM80-03 / ETH_MDC                     P2.7 X1-28
    /* 47 */ {XMC_GPIO_PORT2, 1},  // SWV   ""DEBUG Do NOT Use **            P2.1 X1-30
    /* 48 */ {XMC_GPIO_PORT2, 9},  // PWM80-22 / ETH_TXD1                    P2.9 X1-36
    /* 49 */ {XMC_GPIO_PORT15, 8}, // A16 / ETH_CLK                          P15.8 X1-38

    // Additional pins for port X2 starting here
    /* 50 */ {XMC_GPIO_PORT14, 8}, // A14 / DAC 0 Output                    P14.8 X2-33
    /* 51 */ {XMC_GPIO_PORT15, 2}, // A12 - ADC Input                       P15.2 (INPUT ONLY) X2-32
    /* 52 */ {XMC_GPIO_PORT14, 15}, // A11 - ADC Input                       P14.15 (INPUT ONLY)
                                    // X2-29
    /* 53 */ {XMC_GPIO_PORT15, 9},  // A17 - ADC Input / ETH_CRS             P15.9 X2-27
    /* 54 */ {XMC_GPIO_PORT14, 6}, // A6 / AN1_2GO_1 - ADC Input            P14.6 (INPUT ONLY) X2-25
    /* 55 */ {XMC_GPIO_PORT14, 12}, // A8 / AN1_2GO_2 - ADC Input            P14.12 (INPUT ONLY)
                                    // X2-23
    /* 56 */ {XMC_GPIO_PORT14, 14}, // A10 / ADC Input                       P14.14 (INPUT ONLY)
                                    // X2-21
    /* 57 */ {XMC_GPIO_PORT3, 2},   // BUTTON2                               P3.2 X2-17
    /* 58 */ {XMC_GPIO_PORT0, 10},  // INT / GPIO3_2GO_1                     P0.10 X2-15
    /* 59 */ {XMC_GPIO_PORT0, 1},   // INT                                   P0.1 X2-13
    /* 60 */ {XMC_GPIO_PORT0, 3},   // INT / GPIO3_2GO_2                     P0.3 X2-11
    /* 61 */ {XMC_GPIO_PORT3, 5},  // CS_2GO_1                              P3.5 (Chip Select - Slot
                                   // 1)    X2-3
    /* 62 */ {XMC_GPIO_PORT0, 7},  // LED2                                  P0.7 X2-1
    /* 63 */ {XMC_GPIO_PORT0, 8},  // QSPI_CLK                              P0.8 X2-4
    /* 64 */ {XMC_GPIO_PORT0, 12}, // CS_MB                                 P0.12 (Chip Select -
                                   // MikroBUS) X2-10
    /* 65 */ {XMC_GPIO_PORT0, 6},  // LED1                                  P0.6 X2-12
    /* 66 */ {XMC_GPIO_PORT0, 4},  // ETH_TXEN                              P0.4 X2-14
    /* 67 */ {XMC_GPIO_PORT0, 9},  // GPIO4_2GO_1 / PWM80-12 / PWM          P0.9 X2-20
    /* 68 */ {XMC_GPIO_PORT3, 1},  // BUTTON1                               P3.1 X2-22
    /* 69 */ {XMC_GPIO_PORT14, 13}, // A9 / AN2_2GO_2 - ADC Input            P14.13 (INPUT ONLY)
                                    // X2-26
    /* 70 */ {XMC_GPIO_PORT14, 7}, // A7 / AN2_2GO_1 - ADC Input            P14.7 (INPUT ONLY) X2-28
    /* 71 */ {XMC_GPIO_PORT15, 3}, // A13 - ADC Input                       P15.3 (INPUT ONLY) X2-34
    /* 72 */ {XMC_GPIO_PORT14, 9}  // A15 / DAC 1 Output                    P14.9 X2-36
};
const uint8_t GND = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
const uint8_t NUM_DIGITAL = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
;

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0 */ {CCU40, CCU40_CC43, 3, 0, CCU40_IN3_P1_0},
    /* 1 */ {CCU42, CCU42_CC40, 0, 1, CCU42_IN0_P3_6}};
const uint8_t NUM_INTERRUPT = (sizeof(mapping_interrupt) / sizeof(XMC_PIN_INTERRUPT_t));

/* Mapping of Arduino Pins to PWM4 channels as pin and index in PWM4 channel
   mapping array XMC_PWM4_t mapping_pwm4[]
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][2] = {{3, 0},  // PWM0
                                       {5, 1},  // PWM1
                                       {6, 2},  // PWM2
                                       {14, 3}, // PWM
                                       {26, 4}, // PWM
                                       {27, 5}, // PWM
                                       {28, 6}, // PWM
                                       {255, 255}};

/* Configurations of PWM channels for CCU4 type */
XMC_PWM4_t mapping_pwm4[] = {
    {CCU42, CCU42_CC40, 0, mapping_port_pin[3], P3_6_AF_CCU42_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  3  P3.6
    {CCU42, CCU42_CC43, 3, mapping_port_pin[5], P3_3_AF_CCU42_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  5  P3.3
    {CCU42, CCU42_CC42, 2, mapping_port_pin[6], P3_4_AF_CCU42_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  6  P3.4
    {CCU41, CCU41_CC40, 0, mapping_port_pin[14], P2_5_AF_CCU41_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  14   P2.5
    {CCU41, CCU41_CC41, 1, mapping_port_pin[26], P2_4_AF_CCU41_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  26   P2.4
    {CCU41, CCU41_CC42, 2, mapping_port_pin[27], P2_3_AF_CCU41_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  27   P2.3
    {CCU41, CCU41_CC43, 3, mapping_port_pin[28], P2_2_AF_CCU41_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  28   P2.2
};
const uint8_t NUM_PWM4 = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));

/* Mapping in same manner as PWM4 for PWM8 channels */
const uint8_t mapping_pin_PWM8[][2] = {{9, 0},  // PWM3
                                       {10, 1}, // PWM4
                                       {25, 2}, // PWM
                                       {29, 3}, // PWM
                                       {30, 4}, // PWM
                                       {45, 5}, // PWM
                                       {46, 6}, // PWM
                                       {48, 7}, // PWM
                                       {67, 8}, // PWM
                                       {255, 255}};

/* Configurations of PWM channels for CCU8 type */
XMC_PWM8_t mapping_pwm8[] = {
    {CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9],
     P0_11_AF_CCU80_OUT31, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  9  P0.11
    {CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[10],
     P0_2_AF_CCU80_OUT01, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  10 P0.2
    // additional pwm outputs starting here
    {CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[25],
     P2_8_AF_CCU80_OUT32, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  25 P2.8
    {CCU81, CCU81_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[29],
     P2_0_AF_CCU81_OUT21, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  29 P2.0
    {CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[30],
     P2_6_AF_CCU80_OUT13, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  30 P2.6
    {CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[45],
     P5_7_AF_CCU81_OUT02, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  45 P5.7
    {CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[46],
     P2_7_AF_CCU80_OUT03, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  46 P2.7
    {CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[48],
     P2_9_AF_CCU80_OUT22, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  48 P2.9
    {CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[67],
     P0_9_AF_CCU80_OUT12, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED} // PWM disabled  67 P0.9
};

const uint8_t NUM_PWM8 = (sizeof(mapping_pwm8) / sizeof(XMC_PWM8_t));
const uint8_t NUM_PWM =
    (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t)) + (sizeof(mapping_pwm8) / sizeof(XMC_PWM8_t));

    /* Analog Pin mappings and configurations */
    #ifdef DAC
const uint8_t mapping_pin_DAC[][2] = {{50, 0}, {72, 1}, {255, 255}};

/* Analog Pin mappings and configurations */
XMC_ARD_DAC_t mapping_dac[] = {{XMC_DAC0, 1, 12}, {XMC_DAC0, 0, 12}};
const uint8_t NUM_ANALOG_OUTPUTS = (sizeof(mapping_dac) / sizeof(XMC_ARD_DAC_t));
    #endif

// Result reg numbers are now equal to channel numbers
XMC_ADC_t mapping_adc[] = {
    {VADC, 0, VADC_G0, 0, 0, DISABLED}, {VADC, 1, VADC_G0, 0, 1, DISABLED},
    {VADC, 2, VADC_G1, 1, 2, DISABLED}, {VADC, 3, VADC_G1, 1, 3, DISABLED},
    {VADC, 0, VADC_G2, 2, 0, DISABLED}, {VADC, 1, VADC_G2, 2, 1, DISABLED},
    {VADC, 6, VADC_G2, 2, 6, DISABLED}, {VADC, 5, VADC_G2, 2, 5, DISABLED},
    {VADC, 3, VADC_G2, 2, 3, DISABLED}, {VADC, 7, VADC_G1, 1, 7, DISABLED},
    {VADC, 5, VADC_G1, 1, 5, DISABLED}, {VADC, 7, VADC_G0, 0, 7, DISABLED},
    {VADC, 7, VADC_G3, 3, 7, DISABLED}, {VADC, 1, VADC_G1, 1, 1, DISABLED},
    {VADC, 0, VADC_G1, 1, 0, DISABLED}, {VADC, 6, VADC_G3, 3, 6, DISABLED},
    {VADC, 6, VADC_G0, 0, 6, DISABLED}, {VADC, 4, VADC_G1, 1, 4, DISABLED},
};
const uint8_t NUM_ANALOG_INPUTS = (sizeof(mapping_adc) / sizeof(XMC_ADC_t));

/*
 * UART objects
 *
 * See many XMC1x00 pins_arduino.h for proper way to handle HOSTPC
 * NUM_SERIAL defines number of PHYSICAL ports NOT configurations
 */
RingBuffer rx_buffer_0;
RingBuffer tx_buffer_0;

XMC_UART_t XMC_UART_0 = {
    .channel = XMC_UART1_CH0,
    .rx =
        {
    #ifdef SERIAL_HOSTPC
            .port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)5
    #elif SERIAL_ONBOARD
            .port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)15
    #endif
        },
    .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE},
    .tx =
        {
    #ifdef SERIAL_HOSTPC
            .port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)15
    #elif SERIAL_ONBOARD
            .port = (XMC_GPIO_PORT_t *)PORT2_BASE, .pin = (uint8_t)14
    #endif
        },
    .tx_config =
        {
    #ifdef SERIAL_HOSTPC
            .mode = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
    #elif SERIAL_ONBOARD
            .mode = (XMC_GPIO_MODE_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
    #endif
            .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
            .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE},
    #ifdef SERIAL_HOSTPC
    .input_source_dx0 = (XMC_USIC_INPUT_t)USIC1_C0_DX0_P0_5,
    #elif SERIAL_ONBOARD
    .input_source_dx0 = (XMC_USIC_INPUT_t)USIC1_C0_DX0_P2_15,
    #endif
    .input_source_dx1 = XMC_INPUT_INVALID,
    .input_source_dx2 = XMC_INPUT_INVALID,
    .input_source_dx3 = XMC_INPUT_INVALID,
    .irq_num = USIC1_0_IRQn,
    .irq_service_request = 0};

// Single Hardware Serial object for both UART interfaces
HardwareSerial Serial(&XMC_UART_0, &rx_buffer_0, &tx_buffer_0);

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
                       .slave_receive_irq_num = (IRQn_Type)91,
                       .slave_receive_irq_service_request = 1,
                       .protocol_irq_num = (IRQn_Type)92,
                       .protocol_irq_service_request = 2};

    // XMC CAN instance
    #ifdef CAN_xmc
XMC_ARD_CAN_t XMC_CAN_0 = {.can_node = CAN_NODE1,
                           .can_node_num = XMC_NODE_NUM_1,
                           .can_clock = XMC_CAN_CANCLKSRC_FPERI,
                           .can_frequency = (uint32_t)144000000,
                           .rx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)13},
                           .rx_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE},
                           .tx = {.port = (XMC_GPIO_PORT_t *)PORT1_BASE, .pin = (uint8_t)12},
                           .tx_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2},
                           .node_input = CAN_NODE1_RXD_P1_13,
                           .irq_num = CAN0_7_IRQn,
                           .irq_service_request = 7u};
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

void USIC1_0_IRQHandler() { Serial.IrqHandler(); }

    #ifdef __cplusplus
}
    #endif
#endif /* ARDUINO_MAIN*/

#ifdef __cplusplus
extern HardwareSerial Serial;
#endif /* cplusplus */

#endif
