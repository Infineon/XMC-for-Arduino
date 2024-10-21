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

static bool node1Send(const void *data, const uint8_t size, bool isChar = false) {
    CAN.beginPacket(node1_id);

    TEST_ASSERT_EQUAL_UINT8(size, CAN.write(static_cast<const uint8_t*>(data), size));
    CAN.endPacket();
    // TEST_ASSERT_EQUAL_UINT8(0U, CAN.endPacket());
    return true;
}

// Define tests for supported common functionality. These should return true to indicate this.
TEST_IFX(CAN_connected_node1Internal, node1Sending)
{
    TEST_ASSERT_TRUE(node1Send(node1data, 5));
}


static TEST_GROUP_RUNNER(CAN_connected_node1Internal)
{
    RUN_TEST_CASE(CAN_connected_node1Internal, node1Sending);

}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(CAN_connected_node1)
{
    CAN_connected_node1_suiteSetup();

    RUN_TEST_GROUP(CAN_connected_node1Internal);
 
    CAN_connected_node1_suiteTearDown();
}
