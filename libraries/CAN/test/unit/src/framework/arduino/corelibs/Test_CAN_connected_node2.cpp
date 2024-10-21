// std includes

// test includes
#include "Test_includes.hpp"

// project includes


// defines
#define TRACE_OUTPUT

// variables
const static int node1_id = 0x01;
const static uint8_t node1Increment    = 1U;
static char node1data[5] = {'h', 'e', 'l', 'l', 'o'};

const static int node2_id = 0x02;
const static uint8_t node2Increment    = 2U;
static char node2data[5] = {'w', 'o', 'r', 'l', 'd'};

// test feature includes requiring the above defined variables
#include "Test_CAN_connected_node2.hpp"


static void ReceiveEvent(int packetSize) {
    while (CAN.available()) {
    Serial.print((char)CAN.read());
    }
    Serial.println();
}

// Method invoked before a test suite is run.
void CAN_connected_node2_suiteSetup() {
    extern CANXMC CAN;
    CAN.begin();
    CAN.onReceive(ReceiveEvent);
}


// Method invoked after a test suite is run.
void CAN_connected_node2_suiteTearDown() {
    CAN.end();
}

