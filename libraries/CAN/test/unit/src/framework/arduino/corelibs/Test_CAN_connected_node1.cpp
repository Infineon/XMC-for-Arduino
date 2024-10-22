// std includes

// test includes
#include "Test_includes.hpp"

// project includes


// defines
#define TRACE_OUTPUT
#define CAN_ID_1 0x123
#define CAN_ID_2 0x321

// variables
static uint8_t node1Data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
static uint8_t node1Increment = 1;
static uint8_t globalQuantity = 8;

volatile bool newDataReceivedNode1 = false;
static uint8_t receivedData[8];

// test feature includes requiring the above defined variables
#include "Test_CAN_connected_node1.hpp"
extern CANXMC CAN;

void receiveEventNode1(int packetSize) {
        uint8_t count = 0;
        while (CAN.available() && count < 8) {
            receivedData[count++] = CAN.read();
        }
        newDataReceivedNode1 = true;
}
// Method invoked before a test suite is run.
void CAN_connected_node1_suiteSetup() {
    CAN.begin();
    CAN.filter(CAN_ID_2, 0x7FF); // Set filter to receive messages with CAN_ID_2
    CAN.onReceive(receiveEventNode1);
}


// Method invoked after a test suite is run.
void CAN_connected_node1_suiteTearDown() {
    CAN.end();
}
