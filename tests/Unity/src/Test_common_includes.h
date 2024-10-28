#ifndef TEST_COMMON_INCLUDES_H
#define TEST_COMMON_INCLUDES_H


// std includes
#include <stdbool.h>


// project c includes


// test includes

// Unity c includes
#include "unity.h"
#include "unity_fixture.h"

// IFX Unity addons
#include "unity_ifx.h"

// Arduino includes
#include <Arduino.h>
#if defined(TEST_CAN) || defined(TEST_CAN_CONNECTED_NODE1) || defined(TEST_CAN_CONNECTED_NODE2) 
#include <CAN.h>
#endif

#if defined (TEST_IIC_PINGPONG_CONNECTED) || defined(TEST_IIC_PINGPONG_2BOARDS_MASTER_CONNECTED) || defined(TEST_IIC_PINGPONG_2BOARDS_SLAVE_CONNECTED)
#include <Wire.h>
#endif



// project cpp includes
#include "Utilities.hpp"

#endif // TEST_COMMON_INCLUDES_H
