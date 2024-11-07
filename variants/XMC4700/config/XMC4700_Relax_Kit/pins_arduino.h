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
#include <XMC4700.h>

//****************************************************************************
// @Defines
//****************************************************************************
// XMC_BOARD for stringifying into serial or other text outputs/logs
// Note the actual name XMC and number MUST have a character between
// to avoid issues with other defined macros e.g. XMC1100
#define XMC_BOARD XMC 4700 Relax Kit

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
#define NUM_SERIAL 2
#define NUM_TONE_PINS 16
#define NUM_TASKS_VARIANT 32
#define NUM_SPI 3
#define NUM_I2C 2

// to use SPI_for_xmc_SD if desired by user
#define XMC_SPI_for_xmc_SD XMC_SPI_1

// Indicate unit has RTC/Alarm
#define HAS_RTC 1

// Board has two serial ports pre-assigned to debug and on-board

// Generate 490Hz @fCCU=144MHz
#define PWM4_TIMER_PERIOD (0x11EF)
// Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)

#define PCLK 144000000u

#define PIN_SPI_SS 10
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13

extern uint8_t SS;
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define PIN_SPI_SS_SD 26
#define PIN_SPI_MOSI_SD 27
#define PIN_SPI_MISO_SD 28
#define PIN_SPI_SCK_SD 29

static const uint8_t SS_SD = PIN_SPI_SS_SD;
static const uint8_t MOSI_SD = PIN_SPI_MOSI_SD;
static const uint8_t MISO_SD = PIN_SPI_MISO_SD;
static const uint8_t SCK_SD = PIN_SPI_SCK_SD;

// XMC_I2S defines
/*U2C0*/
/*DX0C -> P3.7*/
/*SCLKOUT(ALT1) -> P3.9*/
/*WA(ALT1) -> P3.10*/
#define MASTER_CHANNEL XMC_I2S2_CH0
// master transmit slave receive
#define MASTER_MTSR PORT3, 8
// master receive slave transmit
#define MASTER_MRST PORT3, 7
#define INPUT_SOURCE USIC2_C0_DX0_P3_7
#define MASTER_SCLK PORT3, 9
#define MASTER_WACLK PORT3, 10

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
#define A18 18
#define A19 19
#define A20 20
#define A21 21
// ADC G3CH0 on P15.8   not available
// ADC G3CH1 on P15.9   not available
// ADC G3CH4 on P15.12  button
// ADC G3CH5 on P15.13  button

#define LED1 22
#define LED2 23
#define LED_BUILTIN LED1

#define BUTTON1 24
#define BUTTON2 25

#define digitalPinToInterrupt(p) ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
// Mapping of digital pins and comments
const XMC_PORT_PIN_t mapping_port_pin[] = {
    /* 0  */ {XMC_GPIO_PORT2, 15},   // RX                           P2.15
    /* 1  */ {XMC_GPIO_PORT2, 14},   // TX                           P2.14
    /* 2  */ {XMC_GPIO_PORT1, 0},    // GPIO / External INT 0        P1.0
    /* 3  */ {XMC_GPIO_PORT1, 1},    // PWM40-2(PWM0) / External INT 1  P1.1
    /* 4  */ {XMC_GPIO_PORT1, 8},    // GPIO                         P1.8
    /* 5  */ {XMC_GPIO_PORT2, 12},   // PWM81-3 output / PWM1        P2.12
    /* 6  */ {XMC_GPIO_PORT2, 11},   // PWM80-2 output / PWM2        P2.11
    /* 7  */ {XMC_GPIO_PORT1, 9},    // GPIO                         P1.9
    /* 8  */ {XMC_GPIO_PORT1, 10},   // GPIO                         P1.10
    /* 9  */ {XMC_GPIO_PORT1, 11},   // PWM81-1 output / PWM3        P1.11
    /* 10  */ {XMC_GPIO_PORT3, 10},  // SPI-SS / PWM41-0 / PWM4      P3.10
    /* 11  */ {XMC_GPIO_PORT3, 8},   // SPI-MOSI / PWM41-2 / PWM5    P3.8
    /* 12  */ {XMC_GPIO_PORT3, 7},   // SPI-MISO                     P3.7
    /* 13  */ {XMC_GPIO_PORT3, 9},   // SPI-SCK                      P3.9
    /* 14  */ {XMC_GPIO_PORT3, 15},  // I2C Data / Address SDA / A4  P3.15 (Hardwired to A4)
    /* 15  */ {XMC_GPIO_PORT0, 13},  // I2C Clock SCL / A5           P0.13 (Hardwired to A5)
    /* 16  */ {XMC_GPIO_PORT14, 0},  // A0 / ADC Input               P14.0 (INPUT ONLY)
    /* 17  */ {XMC_GPIO_PORT14, 1},  // A1 / ADC Input               P14.1 (INPUT ONLY)
    /* 18  */ {XMC_GPIO_PORT14, 2},  // A2 / ADC Input               P14.2 (INPUT ONLY)
    /* 19  */ {XMC_GPIO_PORT14, 3},  // A3 / ADC Input               P14.3 (INPUT ONLY)
    /* 20  */ {XMC_GPIO_PORT14, 4},  // A4 / ADC Input / SDA         P14.4 (Hardwired to SDA)
    /* 21  */ {XMC_GPIO_PORT14, 5},  // A5 / ADC Input / SCL         P14.5 (Hardwired to SCL)
    /* 22  */ {XMC_GPIO_PORT5, 9},   // Additional LED1              P5.9
    /* 23  */ {XMC_GPIO_PORT5, 8},   // Additional LED2              P5.8
    /* 24  */ {XMC_GPIO_PORT15, 13}, // Additional BUTTON1           P15.13 (INPUT ONLY)
    /* 25  */ {XMC_GPIO_PORT15, 12}, // Additional BUTTON2           P15.12 (INPUT ONLY)
    /* 26  */ {XMC_GPIO_PORT4, 1},   // SPI_SS_3 (SD CARD)           P4.1
    /* 27  */ {XMC_GPIO_PORT3, 5},   // SPI-MOSI (SD CARD)           P3.5
    /* 28  */ {XMC_GPIO_PORT4, 0},   // SPI-MISO (SD CARD)           P4.0
    /* 29  */ {XMC_GPIO_PORT3, 6},   // SPI-SCK  (SD CARD)           P3.6
    /* 30  */ {XMC_GPIO_PORT1, 6},   //                              P1.6
    /* 31  */ {XMC_GPIO_PORT1, 7},   //                              P1.7
    /* 32  */ {XMC_GPIO_PORT1, 4},   // USB Debug RX                 P1.4
    /* 33  */ {XMC_GPIO_PORT1, 5},   // USB Debug TX                 P1.5

    // Additional pins for port X1 starting here
    /* 34  */ {XMC_GPIO_PORT3, 4},   // PWM42-2 / PWM12              P3.4     X1-1
    /* 35  */ {XMC_GPIO_PORT0, 5},   // I2C_1 SDA  / SPI_4 MOSI      P0.5     X1-3
    /* 36  */ {XMC_GPIO_PORT0, 3},   // PWM80-2 / PWM10              P0.3     X1-5
    /* 37  */ {XMC_GPIO_PORT0, 1},   // PWM80-1 / PWM9               P0.1     X1-7
    /* 38  */ {XMC_GPIO_PORT0, 10},  //                              P0.10    X1-9
    /* 39  */ {XMC_GPIO_PORT3, 2},   //                              P3.2     X1-11
    /* 40  */ {XMC_GPIO_PORT3, 1},   //                              P3.1     X1-13
    /* 41  */ {XMC_GPIO_PORT15, 6},  // A6 / ADC Input               P15.6    X1-15
    /* 42  */ {XMC_GPIO_PORT15, 5},  // A7 / ADC Input               P15.5    X1-17
    /* 43  */ {XMC_GPIO_PORT15, 3},  // A8 / ADC Input               P15.3    X1-19
    /* 44  */ {XMC_GPIO_PORT14, 15}, // A9 / ADC Input               P14.15   X1-21
    /* 45  */ {XMC_GPIO_PORT14, 13}, // A10 / ADC Input              P14.13   X1-23
    /* 46  */ {XMC_GPIO_PORT14, 7},  // A11 / ADC Input              P14.7    X1-25
    /* 47  */ {XMC_GPIO_PORT15, 15}, // A12 / ADC Input              P15.15   X1-27
    /* 48  */ {XMC_GPIO_PORT14, 9},  // DAC0 / A13 / ADC Input       P14.9    X1-29
    /* 49  */ {XMC_GPIO_PORT2, 13},  //                              P2.13    X1-31
    /* 50  */ {XMC_GPIO_PORT5, 10},  //                              P5.10    X1-33
    /* 51  */ {XMC_GPIO_PORT5, 11},  // PWM80-0 / PWM6               P5.11    X1-34
    /* 52  */ {XMC_GPIO_PORT1, 14},  //                              P1.14    X1-32
    /* 53  */ {XMC_GPIO_PORT14, 8},  // DAC1 / A14 / ADC Input       P14.8    X1-30
    /* 54  */ {XMC_GPIO_PORT15, 14}, // A15 / ADC Input              P15.14   X1-28
    /* 55  */ {XMC_GPIO_PORT14, 6},  // A16 / ADC Input              P14.6    X1-26
    /* 56  */ {XMC_GPIO_PORT14, 12}, // A17 / ADC Input              P14.12   X1-24
    /* 57  */ {XMC_GPIO_PORT14, 14}, // A18 / ADC Input              P14.14   X1-22
    /* 58  */ {XMC_GPIO_PORT15, 2},  // A19 / ADC Input              P15.2    X1-20
    /* 59 */ {XMC_GPIO_PORT15, 4},   // A20 / ADC Input              P15.4    X1-18
    /* 60  */ {XMC_GPIO_PORT15, 7},  // A21 / ADC Input              P15.7    X1-16
    /* 61  */ {XMC_GPIO_PORT3, 0},   // PWM42-0 / PWM7               P3.0     X1-14
    /* 62  */ {XMC_GPIO_PORT0, 9},   // PWM80-1 / PWM8               P0.9     X1-12
    /* 63  */ {XMC_GPIO_PORT0, 0},   //                              P0.0     X1-10
    /* 64  */ {XMC_GPIO_PORT0, 2},   //                              P0.2     X1-8
    /* 65  */ {XMC_GPIO_PORT0, 4},   // SPI_4 MISO                   P0.4     X1-6
    /* 66  */ {XMC_GPIO_PORT0, 6},   // PWM80-3 / PWM11              P0.6     X1-4
    /* 67  */ {XMC_GPIO_PORT0, 11},  // I2C_1 SCL / SPI_4 SCLK       P0.11    X1-2

    // Additional pins for port X2 starting here
    /* 68  */ {XMC_GPIO_PORT3, 13}, // SPI_2 SCLK                   P3.13    X2-1
    /* 69  */ {XMC_GPIO_PORT3, 11}, // SPI_2 MOSI                   P3.11    X2-3
    /* 70  */ {XMC_GPIO_PORT0, 14}, // PWM40-1 / PWM21              P0.14    X2-5
    /* 71  */ {XMC_GPIO_PORT3, 14}, //                              P3.14    X2-7
    /* 72  */ {XMC_GPIO_PORT0, 7},  //                              P0.7     X2-9
    /* 73  */ {XMC_GPIO_PORT1, 2},  //                              P1.2     X2-11
    /* 74  */ {XMC_GPIO_PORT6, 1},  //                              P6.1     X2-13
    /* 75  */ {XMC_GPIO_PORT6, 3},  //                              P6.3     X2-15
    /* 76  */ {XMC_GPIO_PORT6, 5},  // PWM43-0 / PWM17              P6.5     X2-17
    /* 77  */ {XMC_GPIO_PORT1, 15}, // PWM81-0 / PWM16              P1.15    X2-19
    /* 78  */ {XMC_GPIO_PORT5, 1},  // SPI_3 MOSI                   P5.1     X2-21
    /* 79 */ {XMC_GPIO_PORT5, 3},   // PWM81-2 / PWM15              P5.3     X2-23
    /* 80  */ {XMC_GPIO_PORT5, 5},  // PWM81-1 / PWM14              P5.5     X2-25
    /* 81  */ {XMC_GPIO_PORT5, 7},  // PWM81-0 / PWM13              P5.7     X2-27
    /* 82  */ {XMC_GPIO_PORT2, 6},  //                              P2.6     X2-28
    /* 83  */ {XMC_GPIO_PORT5, 6},  //                              P5.6     X2-26
    /* 84  */ {XMC_GPIO_PORT5, 4},  //                              P5.4     X2-24
    /* 85  */ {XMC_GPIO_PORT5, 2},  //                              P5.2     X2-22
    /* 86  */ {XMC_GPIO_PORT5, 0},  // SPI_3 MISO                   P5.0     X2-20
    /* 87  */ {XMC_GPIO_PORT6, 6},  //                              P6.6     X2-18
    /* 88  */ {XMC_GPIO_PORT6, 4},  // PWM43-1 / PWM18              P6.4     X2-16
    /* 89  */ {XMC_GPIO_PORT6, 2},  // PWM43-3 / PWM19              P6.2     X2-14
    /* 90  */ {XMC_GPIO_PORT6, 0},  //                              P6.0     X2-12
    /* 91  */ {XMC_GPIO_PORT0, 8},  // SPI_3 SCLK                   P0.8     X2-10
    /* 92  */ {XMC_GPIO_PORT3, 3},  //                              P3.3     X2-8
    /* 93  */ {XMC_GPIO_PORT0, 15}, // PWM40-0 / PWM20              P0.15    X2-6
    /* 94  */ {XMC_GPIO_PORT0, 12}, // PWM40-3 / PWM22              P0.12    X2-4
    /* 95  */ {XMC_GPIO_PORT3, 12}, // ECAT0.P1_LINK_ACT            P3.12    X2-2

    /* 96  */ {XMC_GPIO_PORT1, 12}, // CAN_TX
    /* 97  */ {XMC_GPIO_PORT1, 13}  // CAN_RX
};
const uint8_t GND = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
const uint8_t NUM_DIGITAL = (sizeof(mapping_port_pin) / sizeof(XMC_PORT_PIN_t));
;

const XMC_PIN_INTERRUPT_t mapping_interrupt[] = {
    /* 0 */ {CCU40, CCU40_CC43, 3, 0, CCU40_IN3_P1_0},
    /* 1 */ {CCU40, CCU40_CC42, 2, 1, CCU40_IN2_P1_1}};
const uint8_t NUM_INTERRUPT = (sizeof(mapping_interrupt) / sizeof(XMC_PIN_INTERRUPT_t));

/* Mapping of Arduino Pins to PWM4 channels as pin and index in PWM4 channel
   mapping array XMC_PWM4_t mapping_pwm4[]
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][2] = {{3, 0},   // PWM0
                                       {10, 1},  // PWM4
                                       {11, 2},  // PWM5
                                       {93, 3},  // PWM20
                                       {70, 4},  // PWM21
                                       {94, 5},  // PWM22
                                       {61, 6},  // PWM7
                                       {34, 7},  // PWM12
                                       {76, 8},  // PWM17
                                       {88, 9},  // PWM18
                                       {89, 10}, // PWM19
                                       {255, 255}};

/* Configurations of PWM channels for CCU4 type */
XMC_PWM4_t mapping_pwm4[] = {
    {CCU40, CCU40_CC42, 2, mapping_port_pin[3], P1_1_AF_CCU40_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  3   P1.1
    {CCU41, CCU41_CC40, 0, mapping_port_pin[10], P3_10_AF_CCU41_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  10  P3.10
    {CCU41, CCU41_CC42, 2, mapping_port_pin[11], P3_8_AF_CCU41_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  11  P3.8
    {CCU40, CCU40_CC40, 0, mapping_port_pin[93], P0_15_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  93  P0.15
    {CCU40, CCU40_CC41, 1, mapping_port_pin[70], P0_14_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  70  P0.14
    {CCU40, CCU40_CC43, 3, mapping_port_pin[94], P0_12_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  94  P0.12
    {CCU42, CCU42_CC40, 0, mapping_port_pin[61], P3_0_AF_CCU42_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  61  P3.0
    {CCU42, CCU42_CC42, 2, mapping_port_pin[34], P3_4_AF_CCU42_OUT2, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  34  P3.4
    {CCU43, CCU43_CC40, 0, mapping_port_pin[76], P6_5_AF_CCU43_OUT0, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  76  P6.5
    {CCU43, CCU43_CC41, 1, mapping_port_pin[88], P6_4_AF_CCU43_OUT1, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  88  P6.4
    {CCU43, CCU43_CC43, 3, mapping_port_pin[89], P6_2_AF_CCU43_OUT3, XMC_CCU4_SLICE_PRESCALER_64,
     PWM4_TIMER_PERIOD, DISABLED} // PWM disabled  89  P6.2
};
const uint8_t NUM_PWM4 = (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t));

/* Mapping in same manner as PWM4 for PWM8 channels */
const uint8_t mapping_pin_PWM8[][2] = {{5, 0},   // PWM1
                                       {6, 1},   // PWM2
                                       {9, 2},   // PWM3
                                       {51, 3},  // PWM6
                                       {37, 4},  // PWM9
                                       {62, 5},  // PWM8
                                       {36, 6},  // PWM10
                                       {66, 7},  // PWM11
                                       {77, 8},  // PWM16
                                       {81, 9},  // PWM13
                                       {80, 10}, // PWM14
                                       {79, 11}, // PWM15
                                       {255, 255}};

/* Configurations of PWM channels for CCU8 type */
XMC_PWM8_t mapping_pwm8[] = {
    {CCU81, CCU81_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[5],
     P2_12_AF_CCU81_OUT33, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  5  P2.12
    {CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[6],
     P2_11_AF_CCU80_OUT22, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  6  P2.11
    {CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9],
     P1_11_AF_CCU81_OUT11, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  9  P1.11
    {CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[51],
     P5_11_AF_CCU80_OUT00, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  51 P5.11
    {CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[37],
     P0_1_AF_CCU80_OUT11, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  37 P0.1
    {CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[62],
     P0_9_AF_CCU80_OUT12, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  62 P0.9
    {CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[36],
     P0_3_AF_CCU80_OUT20, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  36 P0.3
    {CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[66],
     P0_6_AF_CCU80_OUT30, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  66 P0.6
    {CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[77],
     P1_15_AF_CCU81_OUT00, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  77 P1.15
    {CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[81],
     P5_7_AF_CCU81_OUT02, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  81 P5.7
    {CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[80],
     P5_5_AF_CCU81_OUT12, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED}, // PWM disabled  80 P5.5
    {CCU81, CCU81_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[79],
     P5_3_AF_CCU81_OUT22, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD,
     DISABLED} // PWM disabled  79 P5.3
};
const uint8_t NUM_PWM8 = (sizeof(mapping_pwm8) / sizeof(XMC_PWM8_t));
const uint8_t NUM_PWM =
    (sizeof(mapping_pwm4) / sizeof(XMC_PWM4_t)) + (sizeof(mapping_pwm8) / sizeof(XMC_PWM8_t));

    /* Analog Pin mappings and configurations */
    #ifdef DAC
const uint8_t mapping_pin_DAC[][2] = {{48, 0}, {53, 1}, {255, 255}};
XMC_ARD_DAC_t mapping_dac[] = {{XMC_DAC0, 1, 12}, {XMC_DAC0, 0, 12}};
const uint8_t NUM_ANALOG_OUTPUTS = (sizeof(mapping_dac) / sizeof(XMC_ARD_DAC_t));
    #endif

// Result reg numbers are now equal to channel numbers
XMC_ADC_t mapping_adc[] = {{VADC, 0, VADC_G0, 0, 0, DISABLED}, {VADC, 1, VADC_G0, 0, 1, DISABLED},
                           {VADC, 2, VADC_G1, 1, 2, DISABLED}, {VADC, 3, VADC_G1, 1, 3, DISABLED},
                           {VADC, 0, VADC_G2, 2, 0, DISABLED}, {VADC, 1, VADC_G2, 2, 1, DISABLED},
                           {VADC, 6, VADC_G2, 2, 6, DISABLED}, {VADC, 5, VADC_G2, 2, 5, DISABLED},
                           {VADC, 3, VADC_G2, 2, 3, DISABLED}, {VADC, 7, VADC_G1, 1, 7, DISABLED},
                           {VADC, 5, VADC_G1, 1, 5, DISABLED}, {VADC, 7, VADC_G0, 0, 7, DISABLED},
                           {VADC, 7, VADC_G3, 3, 7, DISABLED}, {VADC, 1, VADC_G1, 1, 1, DISABLED},
                           {VADC, 0, VADC_G1, 1, 0, DISABLED}, {VADC, 6, VADC_G3, 3, 6, DISABLED},
                           {VADC, 6, VADC_G0, 0, 6, DISABLED}, {VADC, 4, VADC_G1, 1, 4, DISABLED},
                           {VADC, 6, VADC_G1, 1, 6, DISABLED}, {VADC, 2, VADC_G2, 2, 2, DISABLED},
                           {VADC, 4, VADC_G2, 2, 4, DISABLED}, {VADC, 7, VADC_G2, 2, 7, DISABLED}};
const uint8_t NUM_ANALOG_INPUTS = (sizeof(mapping_adc) / sizeof(XMC_ADC_t));

/*
 * UART objects
 *
 * Serial 0 is Debug port
 * Serial 1  is on-board port
 */
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

// Debug port
HardwareSerial Serial(&XMC_UART_0, &rx_buffer_0, &tx_buffer_0);
// On-board port
HardwareSerial Serial1(&XMC_UART_1, &rx_buffer_1, &tx_buffer_1);

// Three SPI instances possible
XMC_SPI_t XMC_SPI_0 = {
    .channel = XMC_SPI2_CH0,
    .channel_config = {.baudrate = 20003906U,
                       .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
                       .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
                       .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE},
    .mosi = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)8},
    .mosi_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
                    .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
    .miso = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)7},
    .miso_config =
        {
            .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        },
    .input_source = XMC_INPUT_C,
    .sclkout = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)9},
    .sclkout_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                       .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
};

XMC_SPI_t XMC_SPI_1 = {
    .channel = XMC_SPI0_CH1,
    .channel_config = {.baudrate = 20003906U,
                       .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
                       .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
                       .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE},
    .mosi = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)5},
    .mosi_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
                    .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
    .miso = {.port = (XMC_GPIO_PORT_t *)PORT4_BASE, .pin = (uint8_t)0},
    .miso_config =
        {
            .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        },
    .input_source = XMC_INPUT_E,
    .sclkout = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)6},
    .sclkout_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                       .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
};

XMC_SPI_t XMC_SPI_2 = {
    .channel = XMC_SPI2_CH1,
    .channel_config = {.baudrate = 20003906U,
                       .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
                       .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
                       .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE},
    .mosi = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)11},
    .mosi_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
                    .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
    .miso = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)12},
    .miso_config =
        {
            .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        },
    .input_source = XMC_INPUT_D,
    .sclkout = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)13},
    .sclkout_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
                       .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                       .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM},
};

// Only two serial objects are possible: Serial and Serial1 so anymore serial interfaces has to
// overwrite/reuse the existing serial objects
//  Will overwrite Serial
// XMC_SPI_t XMC_SPI_3 =
//{
//     .channel          = XMC_SPI0_CH0,
//     .channel_config   = {
//         .baudrate = 20003906U,
//         .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
//         .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
//         .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
//     },
//     .mosi             = {
//         .port = (XMC_GPIO_PORT_t*)PORT5_BASE,
//         .pin  = (uint8_t)1
//     },
//     .mosi_config      = {
//         .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
//         .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//         .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//     },
//     .miso             = {
//         .port = (XMC_GPIO_PORT_t*)PORT5_BASE,
//         .pin  = (uint8_t)0
//     },
//     .miso_config      = {
//         .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
//     },
//     .input_source     = XMC_INPUT_D,
//     .sclkout = {
//         .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//         .pin  = (uint8_t)8
//     },
//     .sclkout_config   = {
//         .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
//         .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//         .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//     },
// };

// Will overwrite Serial1
// XMC_SPI_t XMC_SPI_4 =
//{
//    .channel          = XMC_SPI1_CH0,
//    .channel_config   = {
//        .baudrate = 20003906U,
//        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
//        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
//        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
//    },
//    .mosi             = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)5
//    },
//    .mosi_config      = {
//        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
//        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//    },
//    .miso             = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)4
//    },
//    .miso_config      = {
//        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
//    },
//    .input_source     = XMC_INPUT_A,
//    .sclkout = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)11
//    },
//    .sclkout_config   = {
//        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
//        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//    },
//};

// Two I2C instances possible
XMC_I2C_t XMC_I2C_0 = {.channel = XMC_I2C1_CH1,
                       .channel_config = {.baudrate = (uint32_t)(100000U), .address = 0U},
                       .sda = {.port = (XMC_GPIO_PORT_t *)PORT3_BASE, .pin = (uint8_t)15},
                       .sda_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                       .scl = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)13},
                       .scl_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                       .input_source_dx0 = XMC_INPUT_A,
                       .input_source_dx1 = XMC_INPUT_B,
                       .slave_receive_irq_num = (IRQn_Type)91,
                       .slave_receive_irq_service_request = 1,
                       .protocol_irq_num = (IRQn_Type)92,
                       .protocol_irq_service_request = 2};
XMC_I2C_t XMC_I2C_1 = {.channel = XMC_I2C1_CH0,
                       .channel_config = {.baudrate = (uint32_t)(100000U), .address = 0U},
                       .sda = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)5},
                       .sda_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                       .scl = {.port = (XMC_GPIO_PORT_t *)PORT0_BASE, .pin = (uint8_t)11},
                       .scl_config = {.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                       .input_source_dx0 = XMC_INPUT_B,
                       .input_source_dx1 = XMC_INPUT_A,
                       .slave_receive_irq_num = (IRQn_Type)93,
                       .slave_receive_irq_service_request = 3,
                       .protocol_irq_num = (IRQn_Type)94,
                       .protocol_irq_service_request = 4};

// XMC_I2S instance
XMC_I2S_t i2s_config = {.input_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                                         .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                        .sclk_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
                                        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                        .wa_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
                                      .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
                        .protocol_irq_num = (IRQn_Type)USIC2_2_IRQn,
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

void USIC0_0_IRQHandler() { Serial.IrqHandler(); }

void USIC1_0_IRQHandler() { Serial1.IrqHandler(); }
    #ifdef __cplusplus
}
    #endif
#endif /* ARDUINO_MAIN */

#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
#endif /* cplusplus */

#endif /* PINS_ARDUINO_H_ */
