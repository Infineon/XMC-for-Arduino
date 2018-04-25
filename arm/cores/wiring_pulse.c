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

// Ensure we do not wait here forever by setting maximum and default
// timeouts for 3 minutes and 1 second (in micro-seconds)
// Default used if timeout is set at < 6 microseconds
#define MAX_PULSE_TIMEOUT   ( 3 * 60 * 1000 * 1000 )
#define DEF_PULSE_TIMEOUT   ( 1000 * 1000 )

uint32_t pulse_state;           // State to measure pin input HIGH or LOW
uint32_t mask;                  // bit mask for relevant pin
XMC_GPIO_PORT_t *pulsePort;     // Pointer to GPIO port register structure
uint32_t start_time;            // start time of measured pulse
uint32_t end_time;              // start time of measured pulse

//****************************************************************************
// @Local Functions
//****************************************************************************

/* Measures the length (in microseconds) of a pulse on the Arduino pin; 
 * Works on pulses from 6 microseconds to 3 minutes in length, 
 * but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * Waits for input signal to be at opposite level to being measured
 * to avoid getting short measurements of wrong pulse.
 *
 * Parameters
 *          pin     - which pin to monitor
 *          state   - HIGH or LOW, for the level of pulse to measure.  
 *          timeout - max time in microseconds to wait for whole process
 *
 * Returns  0 for timeout reached or INVALID pin number
 *
 * ATTENTION:
 * This function relies on the SysTick timer in function micros() so is
 * LESS prone to interrupts or other activity interfering. However there
 * will always be the possibility of at LEAST +/- 1 counts difference to
 * actual signal time. If you need high accuracy use another solution
 * with hardware timers in capture mode.
 *
 * Use of SysTick hardware timer and micros( ) function makes the function
 * more portable across various micros and CPU clock frequencies.
 *
 * Assumptions]
 *      As per AVR Arduino PulseIn pin is expected to be in input mode already
 *      No major interrupt activity while measurement is taken (including Serial)
 *
 *  Do NOT make changes to use local (stack) variables as this WILL ADD overhead
 *  to any operations.
 *  To improve accuracy beyond this will probably need hard coded assembler
 */
uint32_t pulseIn( uint32_t pin, uint32_t state, uint32_t timeout )
{
// check pin is valid by NUM_DIGITAL_PINS, return 0 if invalid
#ifdef NUM_DIGITAL_PINS
if( pin >= NUM_DIGITAL_PINS )
  return 0;
#endif

// Set up pin details for faster port read in loops
pulsePort = mapping_port_pin[ pin ].port;
// configure register pin mask to check against
mask = 1UL << mapping_port_pin[ pin ].pin;

// Check timeout is NOT too small or > Maximum 
// if so use default 1 second or MAX respectively
if( timeout < 6 )
  timeout = DEF_PULSE_TIMEOUT;
else
  if( timeout > MAX_PULSE_TIMEOUT )
    timeout = MAX_PULSE_TIMEOUT;

// Initialise conditions
pulse_state = ( state ) ? mask : 0; // level to measure

timeout = micros( ) + timeout;  // Set timeout for whole process

// If already at measurement level we have a problem
// So wait for pulse to go to OPPOSITE level required (idle) first
while( ( ( pulsePort->IN & mask ) == pulse_state ) )
   if( micros( ) > timeout )
     return 0;

// Wait for pulse to go to level required
while( ( ( pulsePort->IN & mask ) != pulse_state ) )
   if( micros( ) > timeout )
     return 0;

// measure pulse length of required level
start_time = micros( );
while( ( ( pulsePort->IN & mask ) == pulse_state ) )
   if( micros( ) > timeout )
     return 0;
end_time = micros( );

// Return time difference
return( end_time - start_time );
}     

//****************************************************************************
//                                 END OF FILE
//****************************************************************************