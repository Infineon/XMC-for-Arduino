// std includes

// test includes
#include "Test_includes.hpp"

// project includes


// variables used in the tests below that have to be accessed in the setup and tear down methods
static ifx::CAN dut;


// test includes that may require dut


// define test group name
TEST_GROUP(CAN);
TEST_GROUP(CAN_internal);


// Method invoked by Unity before a test suite is run
void CAN_suiteSetUp() {
}


// Method invoked by Unity after a test suite is run 
void CAN_suiteTearDown() {
}


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
    TEST_ASSERT_FALSE( dut.method_unsupported() );
}


TEST_IFX(CAN_internal, checkSupportedFunctionality)
{
    TEST_ASSERT_TRUE( dut.method_1() );
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
