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

  Copyright (c) 2018 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
*/

#ifndef _WIRING_DIGITAL_
#define _WIRING_DIGITAL_

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// @External Prototypes
//****************************************************************************

/*
* \brief Configures the specified pin to behave either as an input or an output. See the description of digital pins for details.
*
* \param pin The number of the pin whose mode you wish to set
* \param mode Either INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
*/
void pinMode(uint8_t pin, uint8_t mode);

/*
* \brief Reads the value from a specified digital pin, either HIGH or LOW.
*
* \param pin The number of the digital pin you want to read (int)
*
* \return HIGH or LOW
*/
extern uint8_t digitalRead(uint8_t pin);

/*
* \brief Write a HIGH or a LOW value to a digital pin.
*
* If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the
* corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
*
* If the pin is configured as an INPUT, writing a HIGH value with digitalWrite() will enable an internal
* 20K pullup resistor (see the tutorial on digital pins). Writing LOW will disable the pullup. The pullup
* resistor is enough to light an LED dimly, so if LEDs appear to work, but very dimly, this is a likely
* cause. The remedy is to set the pin to an output with the pinMode() function.
*
* \note Digital pin PIN_LED is harder to use as a digital input than the other digital pins because it has an LED
* and resistor attached to it that's soldered to the board on most boards. If you enable its internal 20k pull-up
* resistor, it will hang at around 1.7 V instead of the expected 5V because the onboard LED and series resistor
* pull the voltage level down, meaning it always returns LOW. If you must use pin PIN_LED as a digital input, use an
* external pull down resistor.
*
* \param pin the pin number
* \param value HIGH or LOW
*/
extern void digitalWrite(uint8_t pin, uint8_t value);

/*
* \brief Toggles output signal of a digital pin.
*
* \param pin The number of the pin who you want to toggle
*/
extern void digitalToggle(uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_DIGITAL_ */