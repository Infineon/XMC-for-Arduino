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

static uint8_t globalQuantity = 8U;

static uint8_t masterData[globalQuantityMax] = {0};

static TwoWire *master = nullptr;

// test feature includes requiring the above defined variables
#include "Test_IIC_pingPong2BoardsMaster_connected.hpp"

// Method invoked before a test suite is run.
static void IIC_pingPong2BoardsMaster_connected_suiteSetup() {
    master = &Wire;

    master->begin();
}

// Method invoked after a test suite is run.
static void IIC_pingPong2BoardsMaster_connected_suiteTearDown() { master->end(); }
