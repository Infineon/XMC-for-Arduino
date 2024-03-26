// test includes
#include "Test_includes.hpp"


/***
     * Uses flags / defines to determine which groups of tests should be added to this test such that multiple tests can be executed in a single run.
     * Use the '--build-property option of the 'arduino_compile' target to add the flags by defining the respective targets in the makefile.
     * makefile : --build-property "compiler.cpp.extra_flags=\"-D<TEST_SPECIFIER>=1\"" build
*/
void RunAllTests(void)
{

// CAN
#ifdef TEST_CAN

    RUN_TEST_GROUP(CAN);

#endif


// CAN with connections
#ifdef TEST_CAN_CONNECTED

    RUN_TEST_GROUP(CAN_connected);

#endif


// // CAN
// #ifdef TEST_MASTER_BAUDRATE

//     RUN_TEST_GROUP(MASTER_BAUDRATE);

// #endif


// // CAN with connections
// #ifdef TEST_SLAVE_BAUDRATE

//     RUN_TEST_GROUP(SLAVE_BAUDRATE);

// #endif

}


//
void setup() {
    Serial.begin(115200);

    Serial.print("setup done.\n");
}


//
void loop() {
    Serial.println("\n");

    const int   argc       = 2;
    const char *argv[argc] = { "", "-v" };

    (void) UnityMain(argc, argv, RunAllTests);
    delay(3000);
}