// std includes

// test includes
#include "Test_includes.hpp"

// project includes


// defines
#define TRACE_OUTPUT
#define CAN_ID_1 0x123
#define CAN_ID_2 0x321

// variables
static uint8_t node2Data[8];
static uint8_t node2Increment = 1;
static uint8_t globalQuantity = 8;

volatile bool newDataReceivedNode2 = false;
static uint8_t receivedData[8];

// test feature includes requiring the above defined variables
#include "Test_CAN_connected_node2.hpp"
extern CANXMC CAN;

void receiveEventNode2(int packetSize) 
{
        uint8_t count = 0;
        while (CAN.available() && count < 8) {
            receivedData[count++] = CAN.read();
        }
        newDataReceivedNode2 = true;
}

// Method invoked before a test suite is run.
void CAN_connected_node2_suiteSetup() 
{
    CAN.begin();
    CAN.filter(CAN_ID_1, 0x7FF); // Set filter to receive messages with CAN_ID_1
    CAN.onReceive(receiveEventNode2);
}


// Method invoked after a test suite is run.
void CAN_connected_node2_suiteTearDown() 
{
    CAN.end();
}

