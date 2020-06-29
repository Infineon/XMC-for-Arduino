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
#include "RingBuffer.h"

//****************************************************************************
// @Local Functions
//****************************************************************************

// Constructors ////////////////////////////////////////////////////////////////

RingBuffer::RingBuffer( int bufferSize )
{
    _bufferSize = bufferSize;
    _aucBuffer = new uint8_t[_bufferSize];
    _iHead = 0 ;
    _iTail = 0 ;
}

// Public Methods //////////////////////////////////////////////////////////////

void RingBuffer::store_char( uint8_t c )
{
    int i = _iHead + 1;
    if( i >= _bufferSize )
      i = 0;

    // if we should be storing the received character into the location
    // just before the tail (meaning that the head would advance to the
    // current location of the tail), we're about to overflow the buffer
    // and so we don't write the character or advance the head.
    if ( i != _iTail )
    {
        _aucBuffer[_iHead] = c ;
        _iHead = i ;
    }
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
