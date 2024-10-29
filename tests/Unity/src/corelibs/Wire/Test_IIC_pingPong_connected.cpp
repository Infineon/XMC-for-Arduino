// std includes

// test includes
#include "Test_common_includes.h"

// project includes

// defines
#define TRACE_OUTPUT

// variables
const static uint8_t slaveAddress = 8U;
const static uint8_t slaveIncrement = 10U;
const static uint8_t masterIncrement = 1U;

const static uint8_t globalQuantityMax = 20U;

// TODO: Maximum value to request by master is 2, otherwise XMC_I2C_CH_MasterStart in line 253 of
// Wire.cpp hangs !
static uint8_t globalQuantity = 1U;

// static uint8_t slaveData[globalQuantityMax]  = { 0 };
static uint8_t masterData[globalQuantityMax] = {0};

volatile static uint8_t slaveData[globalQuantityMax] = {0};

volatile static uint8_t howManyCopy[globalQuantityMax] = {0};
volatile static uint8_t availCopy[globalQuantityMax] = {0};
volatile static uint8_t peekCopy[globalQuantityMax] = {0};

static TwoWire *master = nullptr;
static TwoWire *slave = nullptr;

// test feature includes requiring the above defined variables
#include "Test_IIC_pingPong_connected.hpp"

static void slaveReceiveEventIIC(int howMany) {
    uint8_t count = 0;

    while (slave->available() > 0) {
        howManyCopy[count] = howMany;
        availCopy[count] = slave->available();
        peekCopy[count] = slave->peek();
        slaveData[count] = slave->read();
        ++count;
    }
}

static void slaveRequestEventIIC() {
    uint8_t count = 0;

    while (count < globalQuantity) {
        slaveData[count] += slaveIncrement;
        ++count;
    }

    (void)slave->write((const uint8_t *)slaveData, globalQuantity);
}

// Method invoked before a test suite is run.
static void IIC_pingPong_connected_suiteSetup() {
    master = &Wire;
    master->begin();

    slave = &Wire1;
    slave->begin(slaveAddress);
    slave->onReceive(slaveReceiveEventIIC);
    slave->onRequest(slaveRequestEventIIC);
}

// Method invoked after a test suite is run.
static void IIC_pingPong_connected_suiteTearDown() {
    master->end();
    slave->end();
}
