/**
 * @file test_config.h
 * @brief Configuration file for board-specific test pin definitions.
 *
 * This header file contains the definitions of the pins used for testing
 * purposes on the specific board. These pins are configured as output and
 * input pins for various test scenarios.
 *
 */
#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include <stdint.h>

// Test Pin Definitions
#define TEST_PIN_DIGITAL_IO_OUTPUT 3 // IO_4
#define TEST_PIN_DIGITAL_IO_INPUT 2  // IO_3
#define TEST_PIN_SYNC_IO 4           // IO_1
#define TEST_PIN_PULSE                  5       // IO_2


#define PWM_FREQUENCY_HZ 490          // PWM Frequency in Hz
#define TEST_PIN_ANALOG_IO_VREF A2    // Pin connected to Vdd
#define TEST_PIN_ANALOG_IO_DIVIDER A1 // Pin connected to voltage divider
#define TEST_PIN_ANALOG_IO_GND A0     // Pin connected to Ground
#define ADC_RESOLUTION 1023           // ADC resolution

#define TEST_PIN_ANALOG_IO_DAC 53
#define TEST_PIN_ANALOG_IO_DAC_INPUT A3

#endif // TEST_CONFIG_H