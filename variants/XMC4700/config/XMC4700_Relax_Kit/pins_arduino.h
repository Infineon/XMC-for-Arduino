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
#define XMC_BOARD           XMC 4700 Relax Kit
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define XMC_LED_ON          0

#define NUM_ANALOG_INPUTS   22
#define NUM_PWM             23
#define NUM_LEDS            2
#define NUM_INTERRUPT       2
#define NUM_SERIAL          2
#define NUM_TONE_PINS       16
#define NUM_TASKS_VARIANT   32

// Indicate unit has RTC/Alarm
#define HAS_RTC             1

// Board has two serial ports pre-assigned to debug and on-board

#define PWM4_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz
#define PWM8_TIMER_PERIOD (0x11EF)  // Generate 490Hz @fCCU=144MHz

#define PCLK 144000000u 
 
#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

extern uint8_t SS; 
extern uint8_t MOSI;
extern uint8_t MISO;
extern uint8_t SCK;

#define PIN_SPI_SS_SD    28
#define PIN_SPI_MOSI_SD  29
#define PIN_SPI_MISO_SD  30
#define PIN_SPI_SCK_SD   31

static const uint8_t SS_SD   = PIN_SPI_SS_SD;
static const uint8_t MOSI_SD = PIN_SPI_MOSI_SD;
static const uint8_t MISO_SD = PIN_SPI_MISO_SD;
static const uint8_t SCK_SD  = PIN_SPI_SCK_SD;

#define A0   0
#define A1   1
#define A2   2
#define A3   3
#define A4   4
#define A5   5
//Additional ADC ports starting here
#define A6	 6		// ADC G2CH6 on P15.6
#define A7	 7		// ADC G2CH5 on P15.5
#define A8	 8		// ADC G2CH3 on P15.3
#define A9	 9		// ADC G1CH7 on P14.15
#define A10	 10		// ADC G1CH5 on P14.13
#define A11	 11		// ADC G0CH7 on P14.7
#define A12	 12		// ADC G3CH7 on P15.15
#define A13	 13		// ADC G1CH1 on P14.9
#define A14	 14		// ADC G1CH0 on P14.8
#define A15	 15		// ADC G3CH6 on P15.14
#define A16	 16		// ADC G0CH6 on P14.6
#define A17	 17		// ADC G1CH4 on P14.12
#define A18	 18		// ADC G1CH6 on P14.14
#define A19	 19		// ADC G2CH2 on P15.2
#define A20	 20		// ADC G2CH4 on P15.4
#define A21	 21		// ADC G2CH7 on P15.7
// ADC G3CH0 on P15.8	not available
// ADC G3CH1 on P15.9	not available
// ADC G3CH4 on P15.12	button
// ADC G3CH5 on P15.13	button


#define LED_BUILTIN 24  //Standard Arduino LED: Used LED1
#define LED1        24  // Additional LED1
#define LED2        25  // Additional LED2
#define BUTTON1     26  // Additional BUTTON1
#define BUTTON2     27  // Additional BUTTON2
#define GND         50  // GND

#define digitalPinToInterrupt(p)    ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN
/* Mapping of Arduino Pins to PWM4 channels as pin and PWM4 channel
   last entry 255 for both parts.
   Putting both parts in array means if a PWM4 channel gets reassigned for
   another function later a gap in channel numbers will not mess things up */
const uint8_t mapping_pin_PWM4[][ 2 ] = {
                                        { 3, 0 },
                                        { 10, 1 },
                                        { 11, 2 },
                                        { 95, 3 },
                                        { 72, 4 },
                                        { 96, 5 },
                                        { 63, 6 },
                                        { 36, 7 },
                                        { 78, 8 },
                                        { 90, 9 },
                                        { 91, 10 },
                                        { 255, 255 } };
const uint8_t mapping_pin_PWM8[][ 2 ] = {
                                        { 5, 0 },
                                        { 6, 1 },
                                        { 9, 2 },
                                        { 53, 3 },
                                        { 39, 4 },
                                        { 64, 5 },
                                        { 38, 6 },
                                        { 68, 7 },
                                        { 79, 8 },
                                        { 83, 9 },
                                        { 82, 10 },
                                        { 81, 11 },
                                        { 255, 255 } };
const uint8_t mapping_pin_DAC[][ 2 ] = {
                                        { 50, 0 },
                                        { 55, 1 },
                                        { 255, 255 } };

const XMC_PORT_PIN_t mapping_port_pin[] =
{
    /* 0  */    {XMC_GPIO_PORT2, 15},  // RX                           P2.15
    /* 1  */    {XMC_GPIO_PORT2, 14},  // TX                           P2.14
    /* 2  */    {XMC_GPIO_PORT1, 0},   // GPIO / External INT 0        P1.0
    /* 3  */    {XMC_GPIO_PORT1, 1},   // PWM40-2 / External INT 1     P1.1
    /* 4  */    {XMC_GPIO_PORT1, 8},   // GPIO                         P1.8
    /* 5  */    {XMC_GPIO_PORT2, 12},  // PWM81-3 output               P2.12
    /* 6  */    {XMC_GPIO_PORT2, 11},  // PWM80-2 output               P2.11
    /* 7  */    {XMC_GPIO_PORT1, 9},   // GPIO                         P1.9
    /* 8  */    {XMC_GPIO_PORT1, 10},  // GPIO                         P1.10
    /* 9  */    {XMC_GPIO_PORT1, 11},  // PWM81-1 output               P1.11
    /* 10  */   {XMC_GPIO_PORT3, 10},  // SPI-SS / PWM41-0 output      P3.10
    /* 11  */   {XMC_GPIO_PORT3, 8},   // SPI-MOSI / PWM41-2 output    P3.8
    /* 12  */   {XMC_GPIO_PORT3, 7},   // SPI-MISO                     P3.7
    /* 13  */   {XMC_GPIO_PORT3, 9},   // SPI-SCK                      P3.9
    /* 14  */   {XMC_GPIO_PORT2, 3},   // AREF TODO:                   P2.3
    /* 15  */   {XMC_GPIO_PORT3, 15},  // I2C Data / Address SDA / A4  P3.15 (Hardwired to A4)
    /* 16  */   {XMC_GPIO_PORT0, 13},  // I2C Clock SCL / A5           P0.13 (Hardwired to A5)
    /* 17  */   {XMC_GPIO_PORT14, 0},  // A0 / ADC Input               P14.0 (INPUT ONLY)
    /* 18  */   {XMC_GPIO_PORT14, 1},  // A1 / ADC Input               P14.1 (INPUT ONLY)
    /* 19  */   {XMC_GPIO_PORT14, 2},  // A2 / ADC Input               P14.2 (INPUT ONLY)
    /* 20  */   {XMC_GPIO_PORT14, 3},  // A3 / ADC Input               P14.3 (INPUT ONLY)
    /* 21  */   {XMC_GPIO_PORT14, 4},  // A4 / ADC Input / SDA         P14.4 (Hardwired to SDA)
    /* 22  */   {XMC_GPIO_PORT14, 5},  // A5 / ADC Input / SCL         P14.5 (Hardwired to SCL)
    /* 23  */   {XMC_GPIO_PORT3, 12},  // SPI_SS_2                     P3.12
    /* 24  */   {XMC_GPIO_PORT5, 9},   // Additional LED1              P5.9
    /* 25  */   {XMC_GPIO_PORT5, 8},   // Additional LED2              P5.8
    /* 26  */   {XMC_GPIO_PORT15, 13}, // Additional BUTTON1           P15.13 (INPUT ONLY)
    /* 27  */   {XMC_GPIO_PORT15, 12}, // Additional BUTTON2           P15.12 (INPUT ONLY)
    /* 28  */   {XMC_GPIO_PORT4, 1},   // SPI_SS_3 (SD CARD)           P4.1
    /* 29  */   {XMC_GPIO_PORT3, 5},   // SPI-MOSI (SD CARD)           P3.5
    /* 30  */   {XMC_GPIO_PORT4, 0},   // SPI-MISO (SD CARD)           P4.0
    /* 31  */   {XMC_GPIO_PORT3, 6},   // SPI-SCK  (SD CARD)           P3.6
    /* 32  */   {XMC_GPIO_PORT1, 6},   //                              P1.6
    /* 33  */   {XMC_GPIO_PORT1, 7},   //                              P1.7
    /* 34  */   {XMC_GPIO_PORT1, 4},   // USB Debug RX                 P1.4
    /* 35  */   {XMC_GPIO_PORT1, 5},   // USB Debug TX                 P1.5

	//Additional pins for port X1 starting here
	/* 36  */   {XMC_GPIO_PORT3, 4},   // PWM42-2                      P3.4
	/* 37  */   {XMC_GPIO_PORT0, 5},   // I2C_1 SDA  // SPI_4 MOSI     P0.5
	/* 38  */   {XMC_GPIO_PORT0, 3},   // PWM80-2                      P0.3
	/* 39  */   {XMC_GPIO_PORT0, 1},   // PWM80-1                      P0.1
	/* 40  */   {XMC_GPIO_PORT0, 10},  //                              P0.10
	/* 41  */   {XMC_GPIO_PORT3, 2},   //                              P3.2
	/* 42  */   {XMC_GPIO_PORT3, 1},   //                              P3.1
	/* 43  */   {XMC_GPIO_PORT15, 6},  // A6 / ADC Input               P15.6 (INPUT ONLY)
	/* 44  */   {XMC_GPIO_PORT15, 5},  // A7 / ADC Input               P15.5 (INPUT ONLY)
	/* 45  */   {XMC_GPIO_PORT15, 3},  // A8 / ADC Input               P15.3 (INPUT ONLY)
	/* 46  */   {XMC_GPIO_PORT14, 15}, // A9 / ADC Input               P14.15 (INPUT ONLY)
	/* 47  */   {XMC_GPIO_PORT14, 13}, // A10 / ADC Input              P14.13 (INPUT ONLY)
	/* 48  */   {XMC_GPIO_PORT14, 7},  // A11 / ADC Input              P14.7 (INPUT ONLY)
	/* 49  */   {XMC_GPIO_PORT15, 15}, // A12 / ADC Input              P15.15 (INPUT ONLY)
	/* 50  */   {XMC_GPIO_PORT14, 9},  // DAC0 // A13 / ADC Input      P14.9 (INPUT ONLY)
	/* 51  */   {XMC_GPIO_PORT2, 13},  //                              P2.13
	/* 52  */   {XMC_GPIO_PORT5, 10},  //                              P5.10
	/* 53  */   {XMC_GPIO_PORT5, 11},  // PWM80-0                      P5.11
	/* 54  */   {XMC_GPIO_PORT1, 14},  //                              P1.14
	/* 55  */   {XMC_GPIO_PORT14, 8},  // DAC1 // A14 / ADC Input      P14.8 (INPUT ONLY)
	/* 56  */   {XMC_GPIO_PORT15, 14}, // A15 / ADC Input              P15.14 (INPUT ONLY)
	/* 57  */   {XMC_GPIO_PORT14, 6},  // A16 / ADC Input              P14.6 (INPUT ONLY)
	/* 58  */   {XMC_GPIO_PORT14, 12}, // A17 / ADC Input              P14.12 (INPUT ONLY)
	/* 59  */   {XMC_GPIO_PORT14, 14}, // A18 / ADC Input              P14.14 (INPUT ONLY)
	/* 60  */   {XMC_GPIO_PORT15, 2},  // A19 / ADC Input              P15.2 (INPUT ONLY)
	/* 61  */   {XMC_GPIO_PORT15, 4},  // A20 / ADC Input              P15.4 (INPUT ONLY)
	/* 62  */   {XMC_GPIO_PORT15, 7},  // A21 / ADC Input              P15.7 (INPUT ONLY)
	/* 63  */   {XMC_GPIO_PORT3, 0},  // PWM42-0                       P3.0
	/* 64  */   {XMC_GPIO_PORT0, 9},  // PWM80-1                       P0.9
	/* 65  */   {XMC_GPIO_PORT0, 0},  //                               P0.0
	/* 66  */   {XMC_GPIO_PORT0, 2},  //                               P0.2
	/* 67  */   {XMC_GPIO_PORT0, 4},  // SPI_4 MISO                    P0.4
	/* 68  */   {XMC_GPIO_PORT0, 6},  // PWM80-3                       P0.6
	/* 69  */   {XMC_GPIO_PORT0, 11}, // I2C_1 SCL // SPI_4 SCLK       P0.11

	//Additional pins for port X2 starting here
	/* 70  */   {XMC_GPIO_PORT3, 13}, // SPI_2 SCLK                    P3.13
	/* 71  */   {XMC_GPIO_PORT3, 11}, // SPI_2 MOSI                    P3.11
	/* 72  */   {XMC_GPIO_PORT0, 14}, // PWM40-1                       P0.14
	/* 73  */   {XMC_GPIO_PORT3, 14}, //                               P3.14
	/* 74  */   {XMC_GPIO_PORT0, 7},  //                               P0.7
	/* 75  */   {XMC_GPIO_PORT1, 2},  //                               P1.2
	/* 76  */   {XMC_GPIO_PORT6, 1},  //                               P6.1
	/* 77  */   {XMC_GPIO_PORT5, 3},  //                               P5.3
	/* 78  */   {XMC_GPIO_PORT6, 5},  // PWM43-0                       P6.5
	/* 79  */   {XMC_GPIO_PORT1, 15}, // PWM81-0                       P1.15
	/* 80  */   {XMC_GPIO_PORT5, 1},  // SPI_3 MOSI                    P5.1
	/* 81  */   {XMC_GPIO_PORT5, 3},  // PWM81-2                       P5.3
	/* 82  */   {XMC_GPIO_PORT5, 5},  // PWM81-1                       P5.5
	/* 83  */   {XMC_GPIO_PORT5, 7},  // PWM81-0                       P5.7
	/* 84  */   {XMC_GPIO_PORT2, 6},  //                               P2.6
	/* 85  */   {XMC_GPIO_PORT5, 6},  //                               P5.6
	/* 86  */   {XMC_GPIO_PORT5, 4},  //                               P5.4
	/* 87  */   {XMC_GPIO_PORT5, 2},  //                               P5.2
	/* 88  */   {XMC_GPIO_PORT5, 0},  // SPI_3 MISO                    P5.0
	/* 89  */   {XMC_GPIO_PORT6, 6},  //                               P6.6
	/* 90  */   {XMC_GPIO_PORT6, 4},  // PWM43-1                       P6.4
	/* 91  */   {XMC_GPIO_PORT6, 2},  // PWM43-3                       P6.2
	/* 92  */   {XMC_GPIO_PORT6, 0},  //                               P6.0
	/* 93  */   {XMC_GPIO_PORT0, 8},  // SPI_3 SCLK                    P0.8
	/* 94  */   {XMC_GPIO_PORT3, 3},  //                               P3.3
	/* 95  */   {XMC_GPIO_PORT0, 15}, // PWM40-0                       P0.15
	/* 96  */   {XMC_GPIO_PORT0, 12}, // PWM40-3                       P0.12
	/* 97  */   {XMC_GPIO_PORT3, 12}  // SPI_2 MISO                    P3.12
};

const XMC_PIN_INTERRUPT_t mapping_interrupt[] =
{
    /* 0  */    {CCU40, CCU40_CC43, 3, 0, CCU40_IN3_P1_0},
    /* 1  */    {CCU40, CCU40_CC42, 2, 1, CCU40_IN2_P1_1}
};

XMC_PWM4_t mapping_pwm4[] =
{
    {CCU40, CCU40_CC42, 2, mapping_port_pin[3], P1_1_AF_CCU40_OUT2,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   3   P1.1
    {CCU41, CCU41_CC40, 0, mapping_port_pin[10], P3_10_AF_CCU41_OUT0,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   10  P3.10
    {CCU41, CCU41_CC42, 2, mapping_port_pin[11], P3_8_AF_CCU41_OUT2,  XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled   11  P3.8
	//additional pwm outputs starting here
	{CCU40, CCU40_CC40, 0, mapping_port_pin[95], P0_15_AF_CCU40_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  95  P0.15
	{CCU40, CCU40_CC41, 1, mapping_port_pin[72], P0_14_AF_CCU40_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  72  P0.14
	{CCU40, CCU40_CC43, 3, mapping_port_pin[96], P0_12_AF_CCU40_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  96  P0.12
	{CCU42, CCU42_CC40, 0, mapping_port_pin[63], P3_0_AF_CCU42_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  63  P3.0
	{CCU42, CCU42_CC42, 2, mapping_port_pin[36], P3_4_AF_CCU42_OUT2, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  36  P3.4
	{CCU43, CCU43_CC40, 0, mapping_port_pin[78], P6_5_AF_CCU43_OUT0, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  78  P6.5
	{CCU43, CCU43_CC41, 1, mapping_port_pin[90], P6_4_AF_CCU43_OUT1, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}, // PWM disabled  90  P6.4
	{CCU43, CCU43_CC43, 3, mapping_port_pin[91], P6_2_AF_CCU43_OUT3, XMC_CCU4_SLICE_PRESCALER_64, PWM4_TIMER_PERIOD, DISABLED}  // PWM disabled  91  P6.2
};

XMC_PWM8_t mapping_pwm8[] =
{
    {CCU81, CCU81_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[5],  P2_12_AF_CCU81_OUT33, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  5  P2.12
    {CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[6],  P2_11_AF_CCU80_OUT22, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  6  P2.11
    {CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[9],  P1_11_AF_CCU81_OUT11, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  9  P1.11
	//additional pwm outputs starting here
	{CCU80, CCU80_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[53], P5_11_AF_CCU80_OUT00, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  53 P5.11
	{CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[39], P0_1_AF_CCU80_OUT11,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  39 P0.1
	{CCU80, CCU80_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[64], P0_9_AF_CCU80_OUT12,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  64 P0.9
	{CCU80, CCU80_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[38], P0_3_AF_CCU80_OUT20,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  38 P0.3
	{CCU80, CCU80_CC83, 3, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[68], P0_6_AF_CCU80_OUT30,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  68 P0.6
	{CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, mapping_port_pin[79], P1_15_AF_CCU81_OUT00, XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  79 P1.15
	{CCU81, CCU81_CC80, 0, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[83], P5_7_AF_CCU81_OUT02,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  83 P5.7
	{CCU81, CCU81_CC81, 1, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[82], P5_5_AF_CCU81_OUT12,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}, // PWM disabled  82 P5.5
	{CCU81, CCU81_CC82, 2, XMC_CCU8_SLICE_COMPARE_CHANNEL_2, mapping_port_pin[81], P5_3_AF_CCU81_OUT22,  XMC_CCU8_SLICE_PRESCALER_64, PWM8_TIMER_PERIOD, DISABLED}  // PWM disabled  81 P5.3
};

XMC_ARD_DAC_t mapping_dac[] =
{
	{XMC_DAC0, 1, 12},
	{XMC_DAC0, 0, 12}
};

XMC_ADC_t mapping_adc[] =
{
	//Result reg numbers are now equal to channel numbers
	{VADC, 0, VADC_G0, 0, 0, DISABLED},
    {VADC, 1, VADC_G0, 0, 1, DISABLED},
    {VADC, 2, VADC_G1, 1, 2, DISABLED},
    {VADC, 3, VADC_G1, 1, 3, DISABLED},
    {VADC, 0, VADC_G2, 2, 0, DISABLED},
    {VADC, 1, VADC_G2, 2, 1, DISABLED},
	//Additional ADC channels starting here
	{VADC, 6, VADC_G2, 2, 6, DISABLED},
	{VADC, 5, VADC_G2, 2, 5, DISABLED},
	{VADC, 3, VADC_G2, 2, 3, DISABLED},
	{VADC, 7, VADC_G1, 1, 7, DISABLED},
	{VADC, 5, VADC_G1, 1, 5, DISABLED},
	{VADC, 7, VADC_G0, 0, 7, DISABLED},
	{VADC, 7, VADC_G3, 3, 7, DISABLED},
	{VADC, 1, VADC_G1, 1, 1, DISABLED},
	{VADC, 0, VADC_G1, 1, 0, DISABLED},
	{VADC, 6, VADC_G3, 3, 6, DISABLED},
	{VADC, 6, VADC_G0, 0, 6, DISABLED},
	{VADC, 4, VADC_G1, 1, 4, DISABLED},
	{VADC, 6, VADC_G1, 1, 6, DISABLED},
	{VADC, 2, VADC_G2, 2, 2, DISABLED},
	{VADC, 4, VADC_G2, 2, 4, DISABLED},
	{VADC, 7, VADC_G2, 2, 7, DISABLED}
};


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

XMC_UART_t XMC_UART_0 =
  {
  .channel              = XMC_UART0_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
                            .pin  = (uint8_t)4
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
                            .pin  = (uint8_t)5
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC0_C0_DX0_P1_4,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC0_0_IRQn,
  .irq_service_request  = 0
  };

XMC_UART_t XMC_UART_1 =
  {
  .channel              = XMC_UART1_CH0,
  .rx                   = { .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
                            .pin  = (uint8_t)15
                          },
  .rx_config            = { .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .tx                   = { .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
                            .pin  = (uint8_t)14
                          },
  .tx_config            = { .mode = (XMC_GPIO_MODE_t) XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
                            .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
                            .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
                          },
  .input_source_dx0     = (XMC_USIC_INPUT_t)USIC1_C0_DX0_P2_15,
  .input_source_dx1     = XMC_INPUT_INVALID,
  .input_source_dx2     = XMC_INPUT_INVALID,
  .input_source_dx3     = XMC_INPUT_INVALID,
  .irq_num              = USIC1_0_IRQn,
  .irq_service_request  = 0
   };

// Debug port
HardwareSerial Serial( &XMC_UART_0, &rx_buffer_0, &tx_buffer_0 );
// On-board port
HardwareSerial Serial1( &XMC_UART_1, &rx_buffer_1, &tx_buffer_1 );

// Serial Interrupt and event handling
#ifdef __cplusplus
extern "C" {
#endif
void serialEventRun( );
void serialEvent( ) __attribute__((weak));
void serialEvent1( ) __attribute__((weak));


void serialEventRun( )
{
if( serialEvent )
  {
  if( Serial.available( ) )
    serialEvent( );
  }
if( serialEvent1 )
  {
  if( Serial1.available( ) )
    serialEvent1( );
  }
}


void USIC0_0_IRQHandler( )
{
Serial.IrqHandler( );
}


void USIC1_0_IRQHandler( )
{
Serial1.IrqHandler( );
}
#ifdef __cplusplus
}
#endif
#endif  /* ARDUINO_MAIN */

#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
#endif  /* cplusplus */

#endif  /* PINS_ARDUINO_H_ */
