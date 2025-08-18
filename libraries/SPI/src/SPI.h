#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "api/HardwareSPI.h"
#include "xmc_spi.h"
#include <Arduino.h>

//****************************************************************************
// @Defines
//****************************************************************************
// Define USE_SW_SPI to use the software SPI(not verified)
// #define USE_SW_SPI

// Define USE_XMC_RELAX_KIT_SD allows to use the SD Lib to communicate with a SD Card over
// the on-board SD Card Slot. This feature is only available on XMC4700 RelaxKits.
#if defined(XMC4700_Relax_Kit)
    #define USE_XMC_RELAX_KIT_SD
#endif

#define SPI_IMODE_NONE 0x00

#define ARDUINO_SPI_CLOCK 16000000U

#define SPI_CLOCK_DIV2 2
#define SPI_CLOCK_DIV4 4
#define SPI_CLOCK_DIV8 8
#define SPI_CLOCK_DIV16 16
#define SPI_CLOCK_DIV32 32
#define SPI_CLOCK_DIV64 64
#define SPI_CLOCK_DIV128 128

#if defined(USE_SW_SPI)
    #include "SW_SPI.h"
#endif

class XMCSPIClass : public arduino::HardwareSPI {
public:
// Constructors for HW SPI
#if !defined(USE_SW_SPI)
    XMCSPIClass()
        : XMCSPIClass(&XMC_SPI_default) {}

    XMCSPIClass(XMC_SPI_t *conf);
    ~XMCSPIClass();
// Constructors for SW SPI
#else
    SPIClass() {
        // default SPI
        spi_settings = SPISettings();

        mosi_pin = MOSI;
        miso_pin = MISO;
        clk_pin = SCK;
    }

    SPIClass(SPISettings settings) {
        spi_settings = settings;

        mosi_pin = MOSI;
        miso_pin = MISO;
        clk_pin = SCK;
    }

    SPIClass(SPISettings settings, uint8_t mosi, uint8_t miso, uint8_t sck) {
        spi_settings = settings;

        mosi_pin = mosi;
        miso_pin = miso;
        clk_pin = sck;
    }
#endif

    virtual byte transfer(uint8_t data);
    virtual uint16_t transfer16(uint16_t data);
    virtual void transfer(void *buf, size_t count);

    // Transaction Functions
    // Function not used here
    // void usingInterrupt(int interruptNumber);
    virtual void beginTransaction(SPISettings settings);
    virtual void endTransaction(void);

    // SPI Configuration methods
    virtual void attachInterrupt();
    virtual void detachInterrupt();

    virtual void usingInterrupt(int interruptNumber);
    virtual void notUsingInterrupt(int interruptNumber);

    virtual void begin();
    virtual void end();

    void setBitOrder(BitOrder order);
    void setDataMode(uint8_t mode);
    void setClockDivider(uint8_t div);

private:
    void init();
// Config for HW SPI
#if !defined(USE_SW_SPI)

    XMC_SPI_t *XMC_SPI_config;
    arduino::SPISettings const DEFAULT_SPI_SETTINGS =
        arduino::SPISettings(ARDUINO_SPI_CLOCK, MSBFIRST, SPI_MODE0);

    arduino::SPISettings _settings = arduino::SPISettings();
// Config for SW SPI
#else
    uint8_t mosi_pin;
    uint8_t miso_pin;
    uint8_t clk_pin;

    SPISettings spi_settings;
#endif

    bool initialized;
    uint8_t interruptMode;
    char interruptSave;
    uint32_t interruptMask;
};

extern XMCSPIClass SPI;
#if (NUM_SPI > 1)
extern XMCSPIClass SPI1;
    #if (NUM_SPI > 2)
extern XMCSPIClass SPI2;
        #if (NUM_SPI > 3)
extern XMCSPIClass SPI3;
            #if (NUM_SPI > 4)
extern XMCSPIClass SPI4;
            #endif
        #endif
    #endif
#endif

#endif /* _SPI_H_INCLUDED */