// std includes

// test includes
#include "Test_common_includes.h"

// project includes

// defines
#define TRACE_OUTPUT

// variables

// Method invoked by Unity before a test suite is run
void CAN_suiteSetUp() {}

// Method invoked by Unity after a test suite is run
void CAN_suiteTearDown() {}

// variables used in the tests below that have to be accessed in the setup and tear down methods
extern CANXMC CAN;

// test includes that may require dut

// define test group name
TEST_GROUP(CAN);
TEST_GROUP(CAN_internal);

// Setup method called before every individual test defined for this test group
static TEST_SETUP(CAN_internal) {}

// Tear down method called before every individual test defined for this test group
static TEST_TEAR_DOWN(CAN_internal) {}

// Functionality not - yet - supported
TEST_IFX(CAN_internal, checkUnsupportedFunctionality) {
    TEST_ASSERT_FALSE(CAN.observe());
    // TEST_ASSERT_TRUE(CAN.packetRtr() ); Remote frame not tested
}

TEST_IFX(CAN_internal, checkSupportedFunctionality) {
    /*TODO: How to test this?
    TEST_ASSERT_TRUE(CAN.begin() );
    // TEST_ASSERT_TRUE(CAN.end() );
    // TEST_ASSERT_TRUE(CAN.endPacket() ); // need to configure
    // TEST_ASSERT_TRUE(CAN.parsePacket() ); // return value
    // TEST_ASSERT_TRUE(CAN.onReceive(0) ); // void
    TEST_ASSERT_TRUE(CAN.filter(0x12, 0x7FF) );
    TEST_ASSERT_TRUE(CAN.filterExtended(0x12345678, 0x1FFFFFFF) );

    TEST_ASSERT_TRUE(CAN.loopback() );

    // TEST_ASSERT_TRUE(CAN.setIdentifier(0x123) ); // need to be deleted in the future
    TEST_ASSERT_TRUE(CAN.beginPacket(0x12, 8, false) );
    TEST_ASSERT_TRUE(CAN.beginExtendedPacket(0xFFF, 8, false) );

    TEST_ASSERT_TRUE(CAN.available() );
    TEST_ASSERT_TRUE(CAN.read() );
    TEST_ASSERT_TRUE(CAN.peek() );
    // TEST_ASSERT_TRUE(CAN.flush() ); // void
    TEST_ASSERT_TRUE(CAN.write(0x12) );
    TEST_ASSERT_TRUE(CAN.write((uint8_t*)0x12, 1) );

    TEST_ASSERT_TRUE(CAN.sleep() );

    // TEST_ASSERT_TRUE(CAN.onInterrupt() ); // void
    // TEST_ASSERT_TRUE(CAN.packetDlc() );
    // TEST_ASSERT_TRUE(CAN.packetExtended() );
    // TEST_ASSERT_TRUE(CAN.packetId() );
    */
}

// Test case for CAN_msg_tx initialization
void test_CAN_msg_tx_initialization(void) {
    // Get the Tx message object
    XMC_CAN_MO_t *txMessage = CAN.getTxMessage();

    // Verify that the Tx message object is correctly initialized
    TEST_ASSERT_NOT_NULL(txMessage);
    TEST_ASSERT_EQUAL_UINT32(XMC_CAN_FRAME_TYPE_STANDARD_11BITS,
                             txMessage->can_id_mode); // Standard 11-bit identifier
    TEST_ASSERT_EQUAL_UINT32(XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1, txMessage->can_priority);
    TEST_ASSERT_EQUAL_UINT32(0x1FFFFFFFU, txMessage->can_id_mask);
    TEST_ASSERT_EQUAL_UINT32(0U, txMessage->can_ide_mask); // send both standard and extended frames
    TEST_ASSERT_EQUAL_UINT32(XMC_CAN_MO_TYPE_TRANSMSGOBJ, txMessage->can_mo_type);
}

// Test case for CAN_msg_rx initialization
void test_CAN_msg_rx_initialization(void) {
    // Get the Rx message object
    XMC_CAN_MO_t *rxMessage = CAN.getRxMessage();

    // Verify that the Rx message object is correctly initialized
    TEST_ASSERT_NOT_NULL(rxMessage);
    TEST_ASSERT_EQUAL_UINT32(XMC_CAN_FRAME_TYPE_STANDARD_11BITS,
                             rxMessage->can_id_mode); // Standard 11-bit identifier
    TEST_ASSERT_EQUAL_UINT32(XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1, rxMessage->can_priority);
    TEST_ASSERT_EQUAL_UINT32(0x000, rxMessage->can_id_mask);
    TEST_ASSERT_EQUAL_UINT32(0U,
                             rxMessage->can_ide_mask); // receive both standard and extended frames
    TEST_ASSERT_EQUAL_UINT32(XMC_CAN_MO_TYPE_RECMSGOBJ, rxMessage->can_mo_type);
}

// Test case for CAN begin function with different baud rates
void test_CAN_initialization_with_baudrate_125k(void) {
    int result = CAN.begin(125000);
    TEST_ASSERT_EQUAL(1, result);
}

void test_CAN_initialization_with_baudrate_250k(void) {
    int result = CAN.begin(250000);
    TEST_ASSERT_EQUAL(1, result);
}

void test_CAN_initialization_with_baudrate_500k(void) {
    int result = CAN.begin(500000);
    TEST_ASSERT_EQUAL(1, result);
}

void test_CAN_initialization_with_baudrate_1M(void) {
    int result = CAN.begin(1000000);
    TEST_ASSERT_EQUAL(1, result);
}

void test_CAN_beginPacket(void) {
    int result = CAN.beginPacket(0x123); // Assuming 0x123 is the identifier
    TEST_ASSERT_EQUAL(1, result);
}

void test_CAN_write(void) {
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    size_t result = CAN.write(data, sizeof(data));
    TEST_ASSERT_EQUAL(sizeof(data), result);
}

void test_CAN_endPacket(void) {
    int result = CAN.endPacket();
    TEST_ASSERT_EQUAL(1, result);
}

// Bundle all tests to be executed for this test group
static TEST_GROUP_RUNNER(CAN_internal) {
    RUN_TEST_CASE(CAN_internal, checkUnsupportedFunctionality);
    RUN_TEST_CASE(CAN_internal, checkSupportedFunctionality);
    RUN_TEST(test_CAN_msg_tx_initialization);
    RUN_TEST(test_CAN_msg_rx_initialization);
    RUN_TEST(test_CAN_initialization_with_baudrate_125k);
    RUN_TEST(test_CAN_initialization_with_baudrate_250k);
    RUN_TEST(test_CAN_initialization_with_baudrate_1M);
    RUN_TEST(test_CAN_initialization_with_baudrate_500k);
    RUN_TEST(test_CAN_beginPacket);
    RUN_TEST(test_CAN_write);
    RUN_TEST(test_CAN_endPacket);
}

// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(CAN) {
    CAN_suiteSetUp();

    RUN_TEST_GROUP(CAN_internal);

    CAN_suiteTearDown();
}
