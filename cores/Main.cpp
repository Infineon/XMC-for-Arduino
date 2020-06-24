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
void dummy_sbrk_caller()
{
  _sbrk(0);
} 

int main(void)
{
/*
 *  Initialization Time first to get closer to startup time accuracy
 */
wiring_time_init();
wiring_analog_init();
// Initialize the reset pin for the XMC1100 Boot Kit series
#ifdef XMC1100_Boot_Kit
  reset_init();
#endif

// Arduino's main() function just calls setup() and loop()....
setup();
while (1)
    {
    loop();
    serialEventRun();
    }
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
