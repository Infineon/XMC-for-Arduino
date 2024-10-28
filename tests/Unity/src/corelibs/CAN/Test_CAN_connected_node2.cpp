// std includes

// test includes
#include "Test_common_includes.h"

// project includes


// defines
#define TRACE_OUTPUT
#define CAN_ID_1 0x123
#define CAN_ID_2 0x321

// variables

const static uint8_t node1Increment = 10;
const static uint8_t node2Increment = 1;
const static uint8_t canDataLengthMax = 8;

static uint8_t canDataLength = canDataLengthMax;
static uint8_t node2Data[canDataLengthMax] = {0};
static uint8_t receivedData[canDataLengthMax] = {0};

volatile bool newDataReceivedNode2 = false;


// test feature includes requiring the above defined variables

extern CANXMC CAN;

void receiveEventNode2(int packetSize) 
{
        uint8_t count = 0;
        while (CAN.available()) {
            receivedData[count++] = CAN.read();
        }
        newDataReceivedNode2 = true;
        canDataLength = packetSize;
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

// define test group name
TEST_GROUP(CAN_connected_node2);
TEST_GROUP(CAN_connected_node2Internal);

void processReceivedMessagesNode2() 
{
    if (newDataReceivedNode2) {
        // Process the received data
        for (uint8_t i = 0; i < canDataLength; ++i) {
            node2Data[i] = receivedData[i] + node2Increment;
        }

        // Send processed data back to Node1
        TEST_ASSERT_TRUE(CAN.beginPacket(CAN_ID_2));
        for (uint8_t i = 0; i < canDataLength; ++i) {
            TEST_ASSERT_EQUAL(1, CAN.write(node2Data[i]));
        }
        TEST_ASSERT_EQUAL(1, CAN.endPacket());

        // Clear flag
        newDataReceivedNode2 = false;

#ifdef TRACE_OUTPUT
        printArray("\nReceived Data", receivedData, canDataLength);
        printArray("Sent Data", node2Data, canDataLength);
#endif
    }
}
// Setup method called by Unity before every individual test defined for this test group.
static TEST_SETUP(CAN_connected_node2Internal)
{
}


// Tear down method called by Unity after every individual test defined for this test group.
static TEST_TEAR_DOWN(CAN_connected_node2Internal)
{
}

TEST_IFX(CAN_connected_node2Internal, checkPingPong) 
{
  processReceivedMessagesNode2();
}


static TEST_GROUP_RUNNER(CAN_connected_node2Internal)
{
    RUN_TEST_CASE(CAN_connected_node2Internal, checkPingPong);

}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(CAN_connected_node2)
{
    CAN_connected_node2_suiteSetup();

    RUN_TEST_GROUP(CAN_connected_node2Internal);
 
    CAN_connected_node2_suiteTearDown();
}


