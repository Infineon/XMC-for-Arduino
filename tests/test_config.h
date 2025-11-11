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
#include <SPI.h>

#if defined(ARDUINO_ARCH_XMC)

    #define SPI_TRANSFER_DELAY_US 2000
    // Test Pin Definitions
    #define TEST_PIN_SPI_SSEL 10 // IO_0
    #define TEST_PIN_ONEWIRE 7

    #if defined(KIT_XMC47_RELAX)
        #define TEST_PIN_DIGITAL_IO_OUTPUT 3  // IO_4
        #define TEST_PIN_DIGITAL_IO_INPUT 2   // IO_3
        #define TEST_PIN_PULSE 5              // IO_2
        #define TEST_PIN_SYNC_IO 4            // IO_1
        #define PWM_FREQUENCY_HZ 490          // PWM Frequency in Hz
        #define TEST_PIN_ANALOG_IO_VREF A2    // Pin connected to Vdd
        #define TEST_PIN_ANALOG_IO_DIVIDER A1 // Pin connected to voltage divider
        #define TEST_PIN_ANALOG_IO_GND A0     // Pin connected to Ground
        #define TEST_ADC_MAX_VALUE 1023
        #define TEST_ADC_RESOLUTION 10 // ADC resolution

        #define TEST_PIN_ANALOG_IO_DAC 53
        #define TEST_PIN_ANALOG_IO_DAC_INPUT A3
static const float test_pwm_frequencies[] = {1, 50, 5000, 50000};
    #elif defined(KIT_XMC1400_ARDUINO)
        #define TEST_PIN_DIGITAL_IO_OUTPUT 4
        #define TEST_PIN_DIGITAL_IO_INPUT 25
        #define TEST_PIN_PULSE 6
        #define TEST_PIN_SYNC_IO 5 // IO_1

        #define PWM_FREQUENCY_HZ 490          // PWM Frequency in Hz
        #define TEST_PIN_ANALOG_IO_VREF A2    // Pin connected to Vdd
        #define TEST_PIN_ANALOG_IO_DIVIDER A1 // Pin connected to voltage divider
        #define TEST_PIN_ANALOG_IO_GND A0     // Pin connected to Ground
        #define TEST_ADC_MAX_VALUE 1023
        #define TEST_ADC_RESOLUTION 10 // ADC resolution
static const float test_pwm_frequencies[] = {1, 50, 5000, 20000};
    #elif defined(KIT_XMC11_BOOT_001)
        #define TEST_PIN_DIGITAL_IO_OUTPUT 3  // IO_4
        #define TEST_PIN_DIGITAL_IO_INPUT 2   // IO_3
        #define TEST_PIN_PULSE 6              // IO_2
        #define TEST_PIN_SYNC_IO 4            // IO_1
        #define PWM_FREQUENCY_HZ 490          // PWM Frequency in Hz
        #define TEST_PIN_ANALOG_IO_VREF A2    // Pin connected to Vdd
        #define TEST_PIN_ANALOG_IO_DIVIDER A1 // Pin connected to voltage divider
        #define TEST_PIN_ANALOG_IO_GND A0     // Pin connected to Ground
        #define TEST_ADC_MAX_VALUE 1023
        #define TEST_ADC_RESOLUTION 10 // ADC resolution
    #elif defined(KIT_XMC14_2GO)
        #define PWM_FREQUENCY_HZ 490          // PWM Frequency in Hz
        #define TEST_PIN_ANALOG_IO_VREF A0    // Pin connected to Vdd
        #define TEST_PIN_ANALOG_IO_DIVIDER A1 // Pin connected to voltage divider
        #define TEST_ADC_MAX_VALUE 1023
        #define TEST_ADC_RESOLUTION 10 // ADC resolution
    #endif
extern XMCSPIClass SPI;
#endif // ARDUINO_ARCH_XMC

// TODO: Need definition of PSOC6 for spi slave test. It should be managed more effectively.
#if defined(ARDUINO_ARCH_PSOC6)
static const float test_pwm_frequencies[] = {1, 50, 5000, 50000};

    // Test Pin Definitions
    #define TEST_PIN_SYNC_IO 4  // IO_1
    #define TEST_PIN_SPI_SSEL 3 // IO_0

// Forward declarations for SPI instances
extern SPIClassPSOC SPI1;
#endif // ARDUINO_ARCH_PSOC6

#endif // TEST_CONFIG_H
