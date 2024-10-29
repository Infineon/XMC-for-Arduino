// std includes

// test includes
#include "Test_common_includes.h"

// project includes

static void IIC_pingPong2BoardsSlave_connected_suiteSetup(void);
static void IIC_pingPong2BoardsSlave_connected_suiteTearDown(void);

// variables used in the tests below that have to be accessed in the setup and tear down methods

// test includes that may require dut

// define test group name
TEST_GROUP(IIC_pingPong2BoardsSlave_connected);
TEST_GROUP(IIC_pingPong2BoardsSlave_connectedInternal);

// Setup method called by Unity before every individual test defined for this test group.
static TEST_SETUP(IIC_pingPong2BoardsSlave_connectedInternal) {}

// Tear down method called by Unity after every individual test defined for this test group.
static TEST_TEAR_DOWN(IIC_pingPong2BoardsSlave_connectedInternal) {}

TEST_IFX(IIC_pingPong2BoardsSlave_connectedInternal, checkPingPong) {
#ifdef TRACE_OUTPUT

    printArray("\nslaveData", slaveData, globalQuantity);
    printArray("howManyCopy", howManyCopy, globalQuantity);
    printArray("availCopy", availCopy, globalQuantity);
    printArray("peekCopy", peekCopy, globalQuantity);
    Serial.flush();

    Serial.print("bytesWrittenCopy : ");
    Serial.println(bytesWrittenCopy);
    Serial.flush();

#endif

    for (uint8_t i = 0; i < globalQuantity; ++i) {
        TEST_ASSERT_EQUAL_UINT8(globalQuantity, howManyCopy[i]);
        TEST_ASSERT_EQUAL_UINT8(availCopy[i], globalQuantity - i);

        peekCopy[i] += slaveIncrement;
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY(slaveData, peekCopy, globalQuantity);

    TEST_ASSERT_EQUAL_UINT8(globalQuantity, bytesWrittenCopy);
}

static TEST_GROUP_RUNNER(IIC_pingPong2BoardsSlave_connectedInternal) {
    RUN_TEST_CASE(IIC_pingPong2BoardsSlave_connectedInternal, checkPingPong);
}

// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(IIC_pingPong2BoardsSlave_connected) {
    IIC_pingPong2BoardsSlave_connected_suiteSetup();

    RUN_TEST_GROUP(IIC_pingPong2BoardsSlave_connectedInternal);

    IIC_pingPong2BoardsSlave_connected_suiteTearDown();
}
