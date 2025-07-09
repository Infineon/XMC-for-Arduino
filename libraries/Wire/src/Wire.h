#ifndef TwoWire_h
#define TwoWire_h

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <Arduino.h>
#include "api/RingBuffer.h"
#include "api/HardwareI2C.h"
//****************************************************************************
// @Defines
//****************************************************************************

#define WIRE_COMMUNICATION_TIMEOUT 5000u
#define BUFFER_LENGTH 128

//****************************************************************************
// @Class Definitions
//****************************************************************************
class TwoWire : public arduino::HardwareI2C {
public:
    bool volatile hasError;
    TwoWire(XMC_I2C_t *conf);
    void begin();
    void begin(uint8_t);
    void end();
    void setClock(uint32_t);
    void beginTransmission(uint8_t);
    uint8_t endTransmission(void);
    uint8_t endTransmission(bool);
    size_t  requestFrom(uint8_t, size_t);
    size_t  requestFrom(uint8_t, size_t, bool);
    size_t  requestFrom(uint8_t, size_t, uint32_t, uint8_t, bool);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
     int available(void);
     int read(void);
     int peek(void);
     void flush(void);
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));
    void ReceiveHandler(void);
    void ProtocolHandler(void);

    using Print::write;
private:
    XMC_I2C_t *XMC_I2C_config;

    bool isMaster;
    bool inRepStart;
    uint8_t transmitting;
    uint16_t timeout;
    arduino::RingBufferN < BUFFER_LENGTH > rx_ringBuffer;
    arduino::RingBufferN < BUFFER_LENGTH > tx_ringBuffer;
    arduino::RingBufferN < BUFFER_LENGTH > pre_rx_ringBuffer;
    uint8_t temp_rx_buff[BUFFER_LENGTH] = {0};
    uint8_t temp_tx_buff[BUFFER_LENGTH] = {0};
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    uint8_t slaveAddress;
    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferIndex;
    uint8_t txBufferLength;

    // uint8_t pre_rxBuffer[BUFFER_LENGTH];
    // uint8_t pre_rxBufferCount;

    void (*user_onRequest)(void);
    void (*user_onReceive)(int);
    void OnRequestService(void);
    void OnReceiveService(void);
};

extern TwoWire Wire;
#if (NUM_I2C > 1)
extern TwoWire Wire1;
    #if (NUM_I2C > 2)
extern TwoWire Wire2;
        #if (NUM_I2C > 3)
extern TwoWire Wire3;
            #if (NUM_I2C > 4)
extern TwoWire Wire4;
            #endif
        #endif
    #endif
#endif

#endif /* TwoWire_h */
