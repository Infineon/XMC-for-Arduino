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

#ifndef W_INTERRUPTS_H
#define W_INTERRUPTS_H

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <inttypes.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define INT0 0
#define INT1 1

#define PIN_INTERRUPT_NO_MODE 5
#define FALLING     0       // same define as for LOW 
#define RISING      1       // same define as for HIGH 
#define CHANGE      2

//****************************************************************************
// @Typedefs
//****************************************************************************
typedef void (*interrupt_cb_t)(void);

//****************************************************************************
// @External Prototypes
//****************************************************************************
void attachInterrupt(uint32_t, interrupt_cb_t, uint32_t);
void detachInterrupt(uint32_t);

#endif /* W_INTERRUPTS_H */
