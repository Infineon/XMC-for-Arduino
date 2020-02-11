/**
 * LED.h - Library for Arduino to control the on board LEDs of the XMC microcontroller series.
 *
 * On board LEDs on the XMC boards do not always operate the same way
 * This library encapsulates LED functions for on board LEDs to work the same
 * way on ALL boards
 *
 * Copyright (c) 2018 Infineon Technologies AG
 *
 * This library is based on the RTCZero implementation for Arduino:
 *
 * Copyright (c) 2015 Arduino LLC. All right reserved.
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

/*!	\file LED.h
 *	\brief This file has to be included in projects that use Infineon's XMC on board LEDs
 */

#ifndef _LED_H_INCLUDED
#define _LED_H_INCLUDED

//****************************************************************************
// @Board Check
//****************************************************************************
#if !defined( XMC1 ) || !defined( XMC4 )
#error Only XMC microcontrollers are supported by this library
#endif

#if !defined XMC_LED_ON
#error This board NOT supported by this library (Check pins_arduino.h)
#endif

//****************************************************************************
// @Project Includes
//****************************************************************************

//****************************************************************************
// @Defines
//****************************************************************************

//****************************************************************************
// @Class Definitions
//****************************************************************************
class LED
{
public:

    // Constructors and initialisers that do nothing
    LED( )
        {
        }

    void begin( );
    void end( );

    // Useful methods
    void Add( int );        // Configure digital output
    void On( int );         // Set LED ON
    void Off( int );        // Set LED OFF
    void Toggle( int );     // Toggle state of LED
};
#endif /* _LED_H_INCLUDED */
