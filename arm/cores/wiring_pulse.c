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
// @Project Includes
//****************************************************************************
#include "Arduino.h"

//****************************************************************************
// @Local Functions
//****************************************************************************

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * This function relies on delayMicroseconds(1). As other instructions are also
 * called within the while loops, its result might be higher than the
 * actual pulse length
 */
uint32_t pulseIn( uint32_t pin, uint32_t state, uint32_t timeout )
{
    uint32_t pulse_state = state ? HIGH : LOW;
    uint32_t width = 0;

    pinMode(pin, INPUT);

    while (timeout && (digitalRead(pin) != pulse_state))
    {
        delayMicroseconds(1);
        timeout--;
    }

    while (timeout && (digitalRead(pin) == pulse_state))
    {
        delayMicroseconds(1);
        width++;
        timeout--;
    }

    return width;
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************