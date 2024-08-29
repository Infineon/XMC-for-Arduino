// std includes

// test includes
#include "Test_includes.hpp"

// project includes


void CAN_suiteSetUp(void);
void CAN_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods
static CANXMC dut = CAN;


// test includes that may require dut


// define test group name
TEST_GROUP(CAN);
TEST_GROUP(CAN_internal);


// Setup method called before every individual test defined for this test group
static TEST_SETUP(CAN_internal)
{
}


// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(CAN_internal)
{
}


// Functionality not - yet - supported
TEST_IFX(CAN_internal, checkUnsupportedFunctionality)
{
    TEST_ASSERT_FALSE(CAN.observe() );
}


TEST_IFX(CAN_internal, checkSupportedFunctionality)
{
    TEST_ASSERT_TRUE(CAN.begin() );
}


TEST_IFX(CAN_internal, checkWhatever)
{
}


// Bundle all tests to be executed for this test group
static TEST_GROUP_RUNNER(CAN_internal)
{
    RUN_TEST_CASE(CAN_internal, checkUnsupportedFunctionality);
    RUN_TEST_CASE(CAN_internal, checkSupportedFunctionality);

    RUN_TEST_CASE(CAN_internal, checkWhatever);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(CAN)
{
    CAN_suiteSetUp();

    RUN_TEST_GROUP(CAN_internal);

    CAN_suiteTearDown();
}
