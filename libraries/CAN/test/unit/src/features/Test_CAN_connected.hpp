// std includes

// test includes
#include "Test_includes.hpp"

// project includes


void CAN_connected_suiteSetup(void);
void CAN_connected_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods
static CANXMC dut = CAN;


// test includes that may require dut


// define test group name
TEST_GROUP(CAN_connected);
TEST_GROUP(CAN_connectedInternal);


// Setup method called by Unity before every individual test defined for this test group.
static TEST_SETUP(CAN_connectedInternal)
{
}


// Tear down method called by Unity after every individual test defined for this test group.
static TEST_TEAR_DOWN(CAN_connectedInternal)
{
}


// Define tests for unsupported functionality. These should return false to indicate this.
TEST_IFX(CAN_connectedInternal, checkUnsupportedFunctionality)
{
}


// Define tests for supported common functionality. These should return true to indicate this.
TEST_IFX(CAN_connectedInternal, checkSupportedFunctionality)
{
    // TEST_ASSERT_TRUE( dut.method_connected() );
}


TEST_IFX(CAN_connectedInternal, checkWhatever)
{
    // Useful macros, but many more available - check cheat sheet.
    // TEST_ASSERT_TRUE(  );
    // TEST_ASSERT_FLOAT_WITHIN(  );
    // TEST_ASSERT_EQUAL_INT16(  );
    // TEST_ASSERT_EQUAL_FLOAT(  );
    // TEST_ASSERT_EQUAL_STRING( "ERROR : Unknown sensorType !", <some other string> );
}


static TEST_GROUP_RUNNER(CAN_connectedInternal)
{
    RUN_TEST_CASE(CAN_connectedInternal, checkUnsupportedFunctionality);
    RUN_TEST_CASE(CAN_connectedInternal, checkSupportedFunctionality);

    RUN_TEST_CASE(CAN_connectedInternal, checkWhatever);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(CAN_connected)
{
    CAN_connected_suiteSetup();

    RUN_TEST_GROUP(CAN_connectedInternal);
 
    CAN_connected_suiteTearDown();
}
