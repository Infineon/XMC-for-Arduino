/**
 * @file test_config.h
 * @brief Configuration file for board-specific test pin definitions.
 *
 * This header file contains the definitions of the pins used for testing
 * purposes on the specific board.
 */
#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include <stdint.h>

// Digital I/O test pins
const uint8_t TEST_DIGITALIO_OUTPUT = 4; // IO0
const uint8_t TEST_DIGITALIO_INPUT = 2;  // IO1

// Analog I/O test pins
#define TEST_PIN_ANALOG_IO_VREF A0    // Pin connected to VREF
#define TEST_PIN_ANALOG_IO_DIVIDER A1 // Pin connected to voltage divider
#define TEST_PIN_ANALOG_IO_GND A2     // Pin connected to GND
#define TEST_PIN_ANALOG_IO_DAC 53     // DAC output pin, siehe pins_arduino.h, entspricht A3 (P14.8)
#define TEST_PIN_ANALOG_IO_DAC_INPUT A3

#define ADC_RESOLUTION 1023 // 10-bit ADC resolution

#endif // TEST_CONFIG_H