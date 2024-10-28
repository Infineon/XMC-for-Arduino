// std includes

// test includes
#include "Test_common_includes.h"

// project includes


static void IIC_pingPong2BoardsMaster_connected_suiteSetup(void);
static void IIC_pingPong2BoardsMaster_connected_suiteTearDown(void);


// variables used in the tests below that have to be accessed in the setup and tear down methods


// test includes that may require dut


// define test group name
TEST_GROUP(IIC_pingPong2BoardsMaster_connected);
TEST_GROUP(IIC_pingPong2BoardsMaster_connectedInternal);


// Setup method called by Unity before every individual test defined for this test group.
static TEST_SETUP(IIC_pingPong2BoardsMaster_connectedInternal)
{ 
    for(uint8_t count = 0; count < globalQuantity; ++count) {
        masterData[count] = 0;
    }
}


// Tear down method called by Unity after every individual test defined for this test group.
static TEST_TEAR_DOWN(IIC_pingPong2BoardsMaster_connectedInternal)
{
}


static bool masterSend(const uint8_t *data, const uint8_t quantity) {
    master->beginTransmission(slaveAddress);

    TEST_ASSERT_EQUAL_UINT8( quantity, master->write(data, quantity) );
    TEST_ASSERT_EQUAL_UINT8( 0U, master->endTransmission() ); // TODO: Fails from time to time !

    return true;
}


static bool masterReceive(uint8_t *data, uint8_t &quantity) {
    uint8_t count       = 0;
    uint8_t locQuantity = quantity;

    TEST_ASSERT_EQUAL_UINT8( quantity, master->requestFrom(slaveAddress, quantity) );
    TEST_ASSERT_EQUAL_UINT8( quantity, master->available() );

    while( master->available() > 0 ) {
        uint8_t peekValue = master->peek();
        data[count]       = master->read();
   
       TEST_ASSERT_EQUAL_UINT8( peekValue, data[count] );

        ++count;
    }

    TEST_ASSERT_EQUAL_UINT8( quantity, count );

    quantity = count;

    return quantity == locQuantity;
}


static void IIC_pingPong(uint8_t quantity, uint8_t iterations) {
    globalQuantity = quantity;

    uint8_t masterDataCopy[quantity];

    for(uint8_t loop = 0; loop < iterations; ++loop) {
        TEST_ASSERT_TRUE( masterSend(masterData, quantity) );

#ifdef TRACE_OUTPUT

        printArray("\nMaster send", masterData, quantity);

#endif

        for(uint8_t i = 0; i < quantity; ++i) {
            masterDataCopy[i] = masterData[i] + slaveIncrement;
        }

        TEST_ASSERT_TRUE( masterReceive(masterData, quantity) );

#ifdef TRACE_OUTPUT

            printArray("\nMaster received", masterData, quantity);

#endif

        TEST_ASSERT_EQUAL_UINT8_ARRAY(masterDataCopy, masterData, quantity);
        
        for(uint8_t i = 0; i < quantity; ++i) {
            masterData[i] += masterIncrement;
        }
    }

}


TEST_IFX(IIC_pingPong2BoardsMaster_connectedInternal, checkPingPong)
{
    // TODO: Loop over different amounts of data, clock frequencies and other parameters ! 
    // Must set variable globalQuantity identically in slave and master ! This can be done by communicating
    // that value from master to slave, thereby allowing for a more dynamic behaviour. 
    // IIC_pingPong(1, 15);
    // IIC_pingPong(2, 15);
    IIC_pingPong(8, 15);
}


static TEST_GROUP_RUNNER(IIC_pingPong2BoardsMaster_connectedInternal)
{
    RUN_TEST_CASE(IIC_pingPong2BoardsMaster_connectedInternal, checkPingPong);
}


// Bundle all tests to be executed for this test group
TEST_GROUP_RUNNER(IIC_pingPong2BoardsMaster_connected)
{
    IIC_pingPong2BoardsMaster_connected_suiteSetup();

    RUN_TEST_GROUP(IIC_pingPong2BoardsMaster_connectedInternal);
 
    IIC_pingPong2BoardsMaster_connected_suiteTearDown();
}
