#ifndef TwoWire_h
#define TwoWire_h

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <Arduino.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define BUFFER_LENGTH 32

#define WIRE_COMMUNICATION_TIMEOUT 5000u

//****************************************************************************
// @Class Definitions
//****************************************************************************
class TwoWire : public Stream {
private:
    XMC_I2C_t *XMC_I2C_config;

    bool isMaster;
    bool inRepStart;
    uint8_t transmitting;
    uint16_t timeout;

    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    uint8_t slaveAddress;
    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferIndex;
    uint8_t txBufferLength;

    uint8_t pre_rxBuffer[BUFFER_LENGTH];
    uint8_t pre_rxBufferCount;

    void (*user_onRequest)(void);
    void (*user_onReceive)(int);
    void OnRequestService(void);
    void OnReceiveService(uint8_t *, uint8_t);

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
    uint8_t requestFrom(uint8_t, size_t);
    uint8_t requestFrom(uint8_t, size_t, bool);
    uint8_t requestFrom(uint8_t, size_t, uint32_t, uint8_t, bool);
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));
    void ReceiveHandler(void);
    void ProtocolHandler(void);

    using Print::write;
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
