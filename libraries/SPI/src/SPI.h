/*
 * SPI Master library for XMC microcontrollers.
 * Inherits from Arduino's HardwareSPI.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>
#include <api/HardwareSPI.h> // Base HardwareSPI class provided by Arduino core for XMC

// SPI modes
#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

// Bit order definitions
#define MSBFIRST 0x00
#define LSBFIRST 0x01

// SPI Clock Dividers
#define ARDUINO_SPI_CLOCK 16000000U
#define SPI_CLOCK_DIV2 2
#define SPI_CLOCK_DIV4 4
#define SPI_CLOCK_DIV8 8
#define SPI_CLOCK_DIV16 16
#define SPI_CLOCK_DIV32 32
#define SPI_CLOCK_DIV64 64
#define SPI_CLOCK_DIV128 128

// Custom SPI implementation class
class XMC_SPIClass : public arduino::HardwareSPI {
public:
    // Constructor
    XMC_SPIClass(XMC_SPI_t *spiConfig);

    // Explicit empty destructor
    ~XMC_SPIClass();

    // Implement required methods from HardwareSPI
    void begin() override;
    void end() override;
    uint8_t transfer(uint8_t data) override;
    uint16_t transfer16(uint16_t data) override;
    void transfer(void *buf, size_t count) override;

    // Interrupt-related methods
    void attachInterrupt() override;
    void detachInterrupt() override;

    // Transaction-related methods
    void usingInterrupt(int interruptNumber) override;
    void notUsingInterrupt(int interruptNumber) override;
    void beginTransaction(arduino::SPISettings settings) override;
    void endTransaction() override;

private:
    void init(); // Internal initialization logic

    XMC_SPI_t *XMC_SPI_Config; // XMC-specific SPI configuration
    bool initialized;
};

// Declare the global SPI object
extern XMC_SPIClass SPI;

#endif /* _SPI_H_INCLUDED */
