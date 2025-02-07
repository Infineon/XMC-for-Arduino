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
/* Tones are Systick timer event related not hardware timer related
   So take care in selecting frequencies range of 1 - 500 Hz supported */

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"

//****************************************************************************
// @Macros
//****************************************************************************
#define FREQUENCY_TO_MILLIS(f)   (SYSTIMER_TICK_PERIOD_US/(2*f))

//****************************************************************************
// @Defines
//****************************************************************************

//****************************************************************************
// @Global Variables
//****************************************************************************
// Valid Arduino pin or 255 for not allocated
volatile uint8_t tone_pins[ NUM_TONE_PINS ];
// Toggle counts > 0 toggles to do
// 0 is next time stop
// < 0 is continuous running
volatile long timer_toggle_count[ NUM_TONE_PINS ];
// arrays initialised
uint8_t tone_init = 0;

//****************************************************************************
// @Local Functions
//****************************************************************************

static int8_t toneBegin( uint8_t _pin )
{
int8_t i;

// check all arrays initialised
if( tone_init == 0 )
  {
  // No preset them for number of Tine pins
  memset( (void *)tone_pins, 255, sizeof( tone_pins ) );
  memset( (void *)timer_toggle_count, 0, sizeof( timer_toggle_count ) );
  tone_init++;
  }

// Once initialised
// if we're already using the pin, the timer should be configured.
for( i = 0; i < NUM_TONE_PINS; i++ )
    if( tone_pins[ i ] == _pin)
        return i;

// search for an unused timer.
for( i = 0; i < NUM_TONE_PINS; i++ )
   if( tone_pins[ i ] == 255 )
     {
     tone_pins[ i ] = _pin;
     pinMode( _pin, OUTPUT );
     break;
     }
 
return ( i < NUM_TONE_PINS ) ? i : -1;
}


// Frequency (in hertz) and duration (in milliseconds).
// Max frequency usable = 500 Hz
// Min frequency usable = 1 Hz
// Duration default of 0 for permanently on
// Timer task ID is tone pin index _timer
void tone( uint8_t _pin, unsigned int frequency, unsigned long duration )
{
int8_t _timer;

// Check valid frequency range first
if( frequency > 0 && frequency <= 500 )
  {
  _timer = toneBegin( _pin );

  if( _timer >= 0 && _timer < NUM_TONE_PINS )
    {
    // Calculate the toggle count
    if( duration > 0 )
      timer_toggle_count[ _timer ] = 2 * frequency * duration/1000;
    else
      timer_toggle_count[ _timer ] = -1;        // Continuous
    // Set internal task parameters
    setParam( _timer, _timer );
    setInterval( _timer, (unsigned int)FREQUENCY_TO_MILLIS( frequency ) );
    startTask( _timer );
    }
  }
}


// Stops tone at next 1ms Systick
void noTone( uint8_t _pin )
{
int8_t i;

for( i = 0; i < NUM_TONE_PINS; i++ )
   if( tone_pins[ i ] == _pin )
     {
     tone_pins[ i ] = 255;
     break;
     }

if( i < NUM_TONE_PINS )   // Only if found set to stop at max next Systick event
  {    
  noInterrupts( );              // Interrupt disable guard to be safe
  timer_toggle_count[ i ] = 0;  // Stop on next Systick
  setInterval( i, 1 );
  interrupts( );
  }
}


/* Interrupt GPIO action
     On normal operation to continue returns 1
     On end of operations returns 0 to stop tasks   
*/
int tone_irq_action( int ID, int16_t tone )
{
if( timer_toggle_count[ tone ] )
  {
  digitalToggle( tone_pins[ tone ] );
  if( timer_toggle_count[ tone ] > 0 )
    timer_toggle_count[ tone ]--;
  }
else
  {
  setInterval( ID, 0 );         // no longer wanted to run
  digitalWrite( tone_pins[ tone ], LOW );
  return 0;
  }
return 1;  
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
