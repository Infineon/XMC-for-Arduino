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

// test defines
const uint8_t TEST_DIGITALIO_OUTPUT = 7; // IO0
const uint8_t TEST_DIGITALIO_INPUT = 8;  // IO1

#endif // TEST_CONFIG_H