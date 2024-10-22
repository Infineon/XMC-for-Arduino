// std includes

// test includes
#include "Test_includes.hpp"

// project includes


// defines
#define TRACE_OUTPUT
#define CAN_ID_1 0x123
#define CAN_ID_2 0x321

// variables


const static uint8_t node1Increment = 10;
const static uint8_t node2Increment = 1;
const static uint8_t canDataLengthMax = 8;

static uint8_t node1Data[canDataLengthMax];
static uint8_t receivedData[canDataLengthMax];
static uint8_t canDataLength = canDataLengthMax;

volatile bool newDataReceivedNode1 = false;


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
