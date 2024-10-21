// std includes

// test includes
#include "Test_includes.hpp"

// project includes


// defines
#define TRACE_OUTPUT


// variables
static uint8_t node1Data[8];
static uint8_t node1Increment = 1;
static uint8_t node2Increment = 10;
static uint8_t globalQuantity = 8;


// test feature includes requiring the above defined variables
#include "Test_CAN_connected_node1.hpp"


// Method invoked before a test suite is run.
void CAN_connected_node1_suiteSetup() {
    extern CANXMC CAN;
    CAN.begin();
}


// Method invoked after a test suite is run.
void CAN_connected_node1_suiteTearDown() {
    CAN.end();
}
