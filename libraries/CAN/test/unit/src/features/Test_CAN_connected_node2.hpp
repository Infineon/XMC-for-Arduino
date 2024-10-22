// std includes

// test includes
#include "Test_includes.hpp"

// project includes


void CAN_connected_node2_suiteSetup(void);
void CAN_connected_node2_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods


// test includes that may require dut


// define test group name
TEST_GROUP(CAN_connected_node2);
TEST_GROUP(CAN_connected_node2Internal);

void processReceivedMessagesNode2() 
{
    if (newDataReceivedNode2) {
        // Process the received data
        canDataLength = CAN.packetDlc();
        for (uint8_t i = 0; i < canDataLength; ++i) {
            node2Data[i] = receivedData[i] + node2Increment;
        }

        // Send processed data back to Node1
        CAN.beginPacket(CAN_ID_2);
        for (uint8_t i = 0; i < canDataLength; ++i) {
            CAN.write(node2Data[i]);
        }
        CAN.endPacket();

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
