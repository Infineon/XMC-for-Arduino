#pragma once
//****************************************************************************
// @External Prototypes
//****************************************************************************

#include "Arduino.h"
//****************************************************************************
// @Project Includes
//****************************************************************************
#include "api/HardwareSerial.h"
#include "api/RingBuffer.h"

//****************************************************************************
// @Typedefs
//****************************************************************************
// Define config for Serial.begin(baud, config);
#undef SERIAL_5N1
#undef SERIAL_6N1
#undef SERIAL_7N1
#undef SERIAL_8N1
#undef SERIAL_5N2
#undef SERIAL_6N2
#undef SERIAL_7N2
#undef SERIAL_8N2
#undef SERIAL_5E1
#undef SERIAL_6E1
#undef SERIAL_7E1
#undef SERIAL_8E1
#undef SERIAL_5E2
#undef SERIAL_6E2
#undef SERIAL_7E2
#undef SERIAL_8E2
#undef SERIAL_5O1
#undef SERIAL_6O1
#undef SERIAL_7O1
#undef SERIAL_8O1
#undef SERIAL_5O2
#undef SERIAL_6O2
#undef SERIAL_7O2
#undef SERIAL_8O2

typedef enum XMC_UART_MODE {
    SERIAL_5N1 = 0x15 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_6N1 = 0x16 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_7N1 = 0x17 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_8N1 = 0x18 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_5N2 = 0x25 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_6N2 = 0x26 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_7N2 = 0x27 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_8N2 = 0x28 | XMC_USIC_CH_PARITY_MODE_NONE,
    SERIAL_5E1 = 0x15 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_6E1 = 0x16 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_7E1 = 0x17 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_8E1 = 0x18 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_5E2 = 0x25 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_6E2 = 0x26 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_7E2 = 0x27 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_8E2 = 0x28 | XMC_USIC_CH_PARITY_MODE_EVEN,
    SERIAL_5O1 = 0x15 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_6O1 = 0x16 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_7O1 = 0x17 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_8O1 = 0x18 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_5O2 = 0x25 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_6O2 = 0x26 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_7O2 = 0x27 | XMC_USIC_CH_PARITY_MODE_ODD,
    SERIAL_8O2 = 0x28 | XMC_USIC_CH_PARITY_MODE_ODD
} XMC_UART_MODE_t;

//****************************************************************************
// @Class Definitionsw
//****************************************************************************
class Uart : public HardwareSerial {
public:
    XMC_UART_t *_XMC_UART_config;
    Uart(XMC_UART_t *xmc_uart_config);
    void begin(unsigned long);
    void begin(unsigned long baudrate, uint16_t config) override;
    void begin(unsigned long, XMC_UART_MODE_t config);
    void end();
    int available(void);
    int availableForWrite(void);
    int peek(void);
    int read(void);
    void flush(void);

    size_t write(const uint8_t);
    size_t write(const uint8_t *buffer, size_t size);
    using Print::write; // pull in write(str) and write(buf, size) from Print

    operator bool();

    void setInterruptPriority(uint32_t priority);
    uint32_t getInterruptPriority();

    void IrqHandler(void);

private:
    static constexpr size_t BUF_LENGTH = 512;
    RingBufferN<BUF_LENGTH> _rx_buffer;
    bool serial_ready = false;
};

extern Uart Serial;
extern Uart Serial1;
