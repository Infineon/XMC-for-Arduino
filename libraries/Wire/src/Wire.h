#ifndef TwoWire_h
#define TwoWire_h

#include <Arduino.h>
#include "api/RingBuffer.h"
#include "api/HardwareI2C.h"

#define WIRE_COMMUNICATION_TIMEOUT 5000u
#define BUFFER_LENGTH 256
#define WIRE_HAS_END 1
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
    
    uint8_t slaveAddress;
    uint8_t txAddress;
    
    void (*user_onRequest)(void);
    void (*user_onReceive)(int);
    void OnRequestService(void);
    void OnReceiveService(uint8_t numBytes);
    void resetBus();
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
