// std includes

// test includes
#include "Test_includes.hpp"

// project includes


void CAN_connected_node1_suiteSetup(void);
void CAN_connected_node1_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods


// test includes that may require dut


// define test group name
TEST_GROUP(CAN_connected_node1);
TEST_GROUP(CAN_connected_node1Internal);


// Setup method called by Unity before every individual test defined for this test group.
static TEST_SETUP(CAN_connected_node1Internal)
{
}

// Tear down method called by Unity after every individual test defined for this test group.
static TEST_TEAR_DOWN(CAN_connected_node1Internal)
{
}

void testSendReceive() 
{

    CAN.beginPacket(CAN_ID_1);
    for (uint8_t i = 0; i < globalQuantity; ++i) {
        CAN.write(node1Data[i]);
    }
    CAN.endPacket();
#ifdef TRACE_OUTPUT
        printArray("Sent Data", node1Data, globalQuantity);
#endif
    while (!newDataReceivedNode1) {
    }

    if (newDataReceivedNode1) {
        for (uint8_t i = 0; i < globalQuantity; ++i) {
            UNITY_TEST_ASSERT_EQUAL_UINT8(node1Data[i] + node1Increment, receivedData[i], __LINE__, "Data mismatch");
        }
        newDataReceivedNode1 = false;

#ifdef TRACE_OUTPUT
        printArray("Sent Data", node1Data, globalQuantity);
        printArray("Received Data", receivedData, globalQuantity);
#endif
    }
}


TEST_IFX(CAN_connected_node1Internal, checkPingPong) 
{
    testSendReceive();
}


static TEST_GROUP_RUNNER(CAN_connected_node1Internal) 
{
    RUN_TEST_CASE(CAN_connected_node1Internal, checkPingPong);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(CAN_connected_node1)
{
    CAN_connected_node1_suiteSetup();

    RUN_TEST_GROUP(CAN_connected_node1Internal);
 
    CAN_connected_node1_suiteTearDown();
}
