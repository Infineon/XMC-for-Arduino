/**
 * LED.cpp - Library for Arduino to control the RTC (Real Time Clock) of the XMC microcontroller series.
 *
 * On board LEDs on the XMC boards do not always operate the same way
 * This library encapsulates LED functions for on board LEDs to work the same
 * way on ALL boards
 *
 * Copyright (c) 2018 Infineon Technologies AG
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/*!	\file LED.cpp
 *	\brief This file has to be included in projects that use Infineon's XMC on board LEDs
 */
#include <Arduino.h>
#include "LED.h"

//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

//****************************************************************************
// @Local Functions
//****************************************************************************

//****************************************************************************
// @Public Methods
//****************************************************************************

// Nothing to initialise
void LED::begin( )
{
}

// Nothing to release
void LED::end( )
{
}


/* Configure pin for output for specified pin */
void LED::Add( int pin )
{
pinMode( pin, OUTPUT );
}


/* Set LED On for specified pin */
void LED::On( int pin )
{
digitalWrite( pin, XMC_LED_ON );
}


/* Set LED Off for specified pin */
void LED::Off( int pin )
{
digitalWrite( pin, !XMC_LED_ON );
}


/* Toggle LED state for specified pin */
void LED::Toggle( int pin )
{
digitalToggle( pin );
}

/******************************************
  End of file LED.cpp
*******************************************/
