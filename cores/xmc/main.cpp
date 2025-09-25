/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//****************************************************************************
// @Defines
//****************************************************************************
#define ARDUINO_MAIN

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"

// work around to use new operator
extern "C" void *_sbrk(int incr);
void dummy_sbrk_caller() __attribute__((__used__));

void dummy_sbrk_caller() { _sbrk(0); }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));

void initVariant() {}

int main(void) {
    /*
     *  Initialization Time first to get closer to startup time accuracy
     */
    wiring_time_init();

// Initialize the reset pin for the KIT_XMC11_BOOT_001 series and KIT_XMC1400_ARDUINO as they are
// based on Arduino Uno form-factor. Hence a dedicated reset pin is required.
#ifdef HAS_GPIO_RESET
    reset_init();
#endif

    // Arduino's main() function just calls setup() and loop()....
    setup();
    while (1) {
        loop();
        ::serialEventRun();
    }
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
