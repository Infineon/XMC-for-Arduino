/*
 * SPI Master library implementation for XMC microcontrollers.
 */

#include "SPI.h"

// Constructor
XMC_SPIClass::XMC_SPIClass(XMC_SPI_t *spiConfig)
    : XMC_SPI_Config(spiConfig),
      initialized(false) {}

// Explicit empty destructor
XMC_SPIClass::~XMC_SPIClass() {
    // Explicitly empty - no dynamic memory used
}

// Arduino SPI API Methods
void XMC_SPIClass::begin() {
    if (initialized)
        return;

    init();
}

void XMC_SPIClass::end() {
    if (!initialized)
        return;

    // Stop SPI hardware if in SPI mode
    if ((XMC_SPI_Config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI) {
        XMC_SPI_CH_Stop(XMC_SPI_Config->channel);
    }

    initialized = false;
}

uint8_t XMC_SPIClass::transfer(uint8_t data) {
    // Send data via SPI
    XMC_SPI_CH_Transmit(XMC_SPI_Config->channel, data, XMC_SPI_CH_MODE_STANDARD);

    // Wait for data transmission to complete
    while (!(XMC_SPI_CH_GetStatusFlag(XMC_SPI_Config->channel) &
             XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION))
        ;
    XMC_SPI_CH_ClearStatusFlag(XMC_SPI_Config->channel,
                               XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

    // Wait for data reception
    while (XMC_USIC_CH_GetReceiveBufferStatus(XMC_SPI_Config->channel) == 0)
        ;
    return XMC_SPI_CH_GetReceivedData(XMC_SPI_Config->channel);
}

uint16_t XMC_SPIClass::transfer16(uint16_t data) {
    uint8_t msb = transfer((data >> 8) & 0xFF);
    uint8_t lsb = transfer(data & 0xFF);
    return (msb << 8) | lsb;
}

void XMC_SPIClass::transfer(void *buf, size_t count) {
    uint8_t *buffer = (uint8_t *)buf;
    for (size_t i = 0; i < count; i++) {
        buffer[i] = transfer(buffer[i]);
    }
}

void XMC_SPIClass::attachInterrupt() {
    // No implementation for attachInterrupt in XMC
}

void XMC_SPIClass::detachInterrupt() {
    // No implementation for detachInterrupt in XMC
}

void XMC_SPIClass::usingInterrupt(int interruptNumber) {
    // No implementation for usingInterrupt in XMC
}

void XMC_SPIClass::notUsingInterrupt(int interruptNumber) {
    // No implementation for notUsingInterrupt in XMC
}

void XMC_SPIClass::beginTransaction(arduino::SPISettings settings) {
    // Configure SPI settings
    if ((XMC_SPI_Config->channel->CCR & USIC_CH_CCR_MODE_Msk) != XMC_USIC_CH_OPERATING_MODE_SPI) {
        begin();
    }

    XMC_SPI_CH_SetBaudrate(XMC_SPI_Config->channel, settings.getClockFreq());
}

void XMC_SPIClass::endTransaction() {
    // Placeholder for endTransaction logic
}

// Internal initialization logic
void XMC_SPIClass::init() {
    if (initialized)
        return;

    // Initialize hardware SPI
    XMC_SPI_CH_Init(XMC_SPI_Config->channel, &(XMC_SPI_Config->channel_config));
    XMC_SPI_CH_SetInputSource(XMC_SPI_Config->channel, XMC_SPI_CH_INPUT_DIN0,
                              (uint8_t)XMC_SPI_Config->input_source);
    XMC_SPI_CH_Start(XMC_SPI_Config->channel);

    initialized = true;
}

// Instantiate the global SPI object statically
XMC_SPIClass SPI(&XMC_SPI_default);

// Provide dummy operator delete implementation for embedded environments
void operator delete(void *ptr) {
    // Do nothing - memory is not allocated dynamically
}
