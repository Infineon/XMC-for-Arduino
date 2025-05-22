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
#define TEST_DIGITALIO_OUTPUT 2 // IO_4
#define TEST_DIGITALIO_INPUT 3  // IO_3
#define TEST_PIN_SYNC_IO 4      // IO_1
#endif                          // TEST_CONFIG_H