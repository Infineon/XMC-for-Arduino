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

/* Includes Co-operative Scheduler for XMC-for-Arduino

   Using COMPILE time scheduling table

Version V1.00
Author: Paul Carpenter, PC Services, <sales@pcserviceselectronics.co.uk>
Date    March 2018

Co-operative scheduler library that has some support functions and main
schedule function meant to be run as the Systick scheduler event handler, the
support functions should be used to get status on, start, stop, or configure tasks.

The schedule code is designed for MINIMAL overhead and SPEED.

The time interval of calling the schedule loop is determined by Systick timer
interval currently 1 ms, and calls a selection of tasks determined by two
parameters for each task

    callback    function address
    parameter   INTEGER to pass to function

From this we get TWO types of function calls when a task event happens

1/ callback and parameter are set gives a function call of

    int callback( int ID, int16_t param )
            function to use as this task that accepts TWO integer parameters
            and MUST return an integer

   (even if parameter not set it is initialised to task_id AT compile TIME)

2/ Special case if ANY task has its callback set to NULL a special variable
   in wiring_time is set to TRUE. This enables the delay() function to work
   for ms delays. As a side effect it stops runaway tasks for callback set to
   NULL.

Callback functions in list
--------------------------
    For different processors speeds it is suggested to keep the number of
    total tasks (callback functions) to following limits -

    Speed               Max Tasks
    < 50 MHz            8
    > 50 MHz < 100 MHz  12
    > 100 MHz           16

Callback function structure
---------------------------
    Task is actually calling a function that should be defined as
    function that returns int and takes TWO integer parameter

    e.g.    int func( int TaskId, int16_t Parameter )
    First parameter is TaskId,
    Second parameter is user defined parameter (int16_t)

    If interval of a task has to change call setInterval during task execution
    NOT to STOP task use return code

Callback functions Contents
---------------------------
    Callback functions are effectively interrupt routines so care should be taken
    about which variables and flags set in these functions are volatiles.

    Functions MUST be VERY SMALL as many tasks have to run in less than 1 ms as
    well as the main code.

    Do NOT use blocking or slow callbacks that use AT LEAST the following Arduino
    functions
        delay           (this would become recursive)
        .print, .write, println on Serial or Liquid Crystal
        analogread
        PulseIn
        Liquid Crystal  ANY function
        I2C or SPI      ANY function
        SD/MMC          ANY function

    All of these and maybe others are SLOW, block waiting for I/O or time
    delays often MUCH longer than 1 ms

Callback Function Return value
------------------------------
    The returned value is the NEW status for that task which tells scheduler
    what to do next time. Values are

      < 0 User error status (stops task execution)
        0  Task stopped (if needed to be run will have to be started by Start)
      > 0 Next status this can be used by call back function for state machines
          Task runs again at the interval set

Scheduling Functions
--------------------
setInterval Set a task's NEW interval and schedule new time from now if not
            already running
getInterval Get a task's interval
setParam    Set a task's callback function parameter (signed int16_t)
getParam    Get a task's callback function parameter (signed int16_t)
getTime     Get a task's next time to execute
getStatus   Get a particular task status word
addTask     Add a task to the task list
deleteTask  Delete a task from the task list
startTask   Start a task (if not already running)
findID      Get ID of first task from task address
*/
//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Arduino.h"
extern int  tone_irq_action( int, int16_t );

//****************************************************************************
// @Macros
//****************************************************************************
// number of tasks = number of tones plus delay task plus any others added later
#define _MAX_TASKS   NUM_TASKS_VARIANT

#define SYSTIMER_PRIORITY  (4U)
/* Millisecond to Microsecond ratio */
#define TIMER_1mSec 1000

//****************************************************************************
// @Global Variables
//****************************************************************************
/* Array of tasks which are addresses to functions.
    Each function returns int and takes TWO integer parameter
        e.g.    int func( int TaskId, int16_t Parameter )
     First parameter is TaskId,
     second is current status is user defined parameter (int16_t)

    Tasklist order is ALWAYS
            Tone    callbacks ( 0 to NUM_TONE_PINS )
            Any additional tasks
            delay() callback

    This way last is always delay and first 'n' are always Tone pins i.e. 0 - n
    last is _MAX_TASKS - 1
*/
int (* tasks[_MAX_TASKS])( int, int16_t );

/* Structure for task details next run, status etc.. */
struct TaskList taskTable[ _MAX_TASKS ];

unsigned long old_ms = 0;   // last execution time
int running = _MAX_TASKS;   // Current task ID being checked or run
                            // Initialise to avoid fast CPU EXTREME edge case of
                            // requesting task (mainly first Tone task) BEFORE the
                            // FIRST SysTick interrupt (1 ms) after power up.

/* SysTick counter */
volatile uint32_t g_systick_count = 0U;

/* Tracker if Timer Handler as already been entered -> avoid recursion */
volatile __IO bool g_timer_entered_handler = FALSE;

// Delay ms function flag for time expired in Systick Event Handler
volatile __IO bool delay_timer_expired = FALSE;


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
/* Handler function  called from SysTick event handler for task scheduling */
int XMC_SYSTIMER_lTimerHandler( void );

/* SysTick handler which is the main interrupt service routine to service the
 * tasks configured */
void SysTick_Handler( void );


//****************************************************************************
// @Local Functions
//****************************************************************************
void wiring_time_init( void )
{
/* Initialise micro/milli second counter as early as possible
   Initialize SysTick timer for 1 ms (1 kHz) interval */
SysTick_Config( (uint32_t)SYSTICK_MS );

// Initialise task control to all off
memset( taskTable, 0, sizeof( taskTable ) );

for( int i = 0; i < _MAX_TASKS; i++ )
   {
   taskTable[ i ].param = i;        // Preset user parameter to task number
   // Fill with call back function addresses
   if( i < NUM_TONE_PINS )
     tasks[ i ] = tone_irq_action;   // Tone callbacks
   else
     tasks[ i ] = NULL;     // Special case delay() ms callback
   }

/* setting of First SW Timer period is always and sub-priority value for XMC4000 devices */
/* setting of priority value for XMC1000 devices */
NVIC_SetPriority( SysTick_IRQn, SYSTIMER_PRIORITY );
}


/* delay - milliseconds
 * This function uses SysTick Exception for controlling the timer list. Call back function
 * registered through this function will be called in SysTick exception when the timer is expired.
 *
 *  @param[in]  Period Timer period value in microseconds
 *
 * Special cases for callback action processing
 *      callback is NULL boolean delay_timer_expired is set to true
 */
void delay( uint32_t dwMs )
{
setInterval( _MAX_TASKS - 1, dwMs );
//Timer is always in list as last
startTask( _MAX_TASKS - 1 );
// Wait until timer expires
do
  yield( );
while( !delay_timer_expired );
delay_timer_expired = FALSE;
}


/* Handler function called from SysTick event handler.
        - Task scheduling loop

   Does ONE pass through scheduling table, checking what tasks are due or
   overdue to run.

   Order of task execution is list of tasks

   When task has completed -
        updates task status with status returned,
        adjusts next run time using interval specified.
            If interval is zero execution time set to zero.

   Parameters - NONE

   Returns  int  0  Processed no tasks to run
                > 0 Number of tasks executed
 */
int XMC_SYSTIMER_TaskLoop( void )
{
int done;
unsigned int overdue;
unsigned long ms;

// Task loop lock
g_timer_entered_handler = TRUE;

// get current time and overdue
ms = g_systick_count;
// Unsigned maths first ensures correct even at wraparound
overdue = (unsigned int)( ms - old_ms );
// save current execution time
old_ms = ms;
done = 0;
for( running = 0; running < _MAX_TASKS; running++ )
   {
   if( taskTable[ running ].status > 0 )    // task enabled
     { // check if time to run as in correct interval or overdue
     if( ms - taskTable[ running ].next <= overdue )
       {
       if( tasks[ running ] == NULL )
         {
         delay_timer_expired = TRUE;        // Special case of NULL callback function
         taskTable[ running ].status = 0;   // One shot event so stop task
         }
       else
         if( ( taskTable[ running ].status =
                ( ( *tasks[ running ])( running, taskTable[ running ].param ) ) ) > 0 )
           taskTable[ running ].next = ms + taskTable[ running ].interval;
       done++;
       }
     }
   }
return done;
}


/* SysTick Event Handler. */
void SysTick_Handler( void )
{
g_systick_count++;          // Another ms has occurred

// do not call handler, when still running
if( g_timer_entered_handler == FALSE )
  {
  XMC_SYSTIMER_TaskLoop();
  g_timer_entered_handler = FALSE;
  }
}


/* checkID - Common ID check for valid and not running

    Parameters  int Task ID to check

    Return int  -1  invalid ID
                 0  current task running
                 1  Valid
*/
int CheckID( int ID )
{
if( ID < 0 || ID >= _MAX_TASKS )
  return -1;
if( ID == running )
  return 0;
return 1;
}


/* setInterval - set the interval time in ms for a task

   If task running just sets interval as next execution will be set at task end.

   When task NOT running, also sets next execution time to now plus interval.

    Parameters  int Task ID to check
                unsigned int interval in ms

    Return int  -1 invalid ID
                 0  task is running
                > 0 task interval and execution time set
*/
int setInterval( int ID, uint32_t interval )
{
int i;

if( ( i = CheckID( ID ) ) < 0 )
  return i;
taskTable[ ID ].interval = interval;
if( i != 0 )
  {
  taskTable[ ID ].next = millis( ) + interval + 1;
  return 1;
  }
return 0;
}

/* getInterval - get the interval time in ms for a task

    Parameters  int Task ID to check
                NO ID validity check

    Return int  Current interval time
*/
uint32_t getInterval( int ID )
{
return taskTable[ ID ].interval;
}


/* setParam - set the param value for a task callback function

   Parameters   int Task ID to check
                int16_t param value

   Return int   -1 invalid ID
                >=0 task param value set
*/
int setParam( int ID, int16_t param )
{
if( ( CheckID( ID ) ) < 0 )
  return -1;
taskTable[ ID ].param = param;
return 0;
}


/* getParam - get the param value for a task callback function

    Parameters  int Task ID to get details of

    Return int  -1 invalid ID or valid param
                All other values assume the param value
    */
int16_t getParam( int ID )
{
if( ( CheckID( ID ) ) < 0 )
  return -1;
return taskTable[ ID ].param;
}


/* getTime - get next execution time in ms of a task

    As value is unsigned long impossible to guarantee error codes
    So if values listed below for errors check current millis() value
    to see if could be real or error.

    Parameters  int Task ID to check

    Return      unsigned long of time (or could be errors)
                0 could be execution time or error of invalid ID
                1 could be execution time or error of NO interval
*/
unsigned long getTime( int ID )
{
if( ( CheckID( ID ) ) < 0 )
  return 0;
return taskTable[ ID ].next;
}


/* getStatus - get task status even if running task

    Parameters  int Task ID to get status for

    Return int  -1  invalid ID
               any other value Status (including other user errors -ve)
*/
int16_t getStatus( int ID )
{
// Check valid ID
if( ( CheckID( ID ) ) < 0 )
  return -1;
return taskTable[ ID ].status;
}

/* addTask - Add a task to the task list

    Parameters  ptr Pointer to callback function

    Return int  -1 No free task available
                 >=0 Number of added task
*/
int addTask( int(* ptr)( int, int16_t ) )
{
  noInterrupts( );
  for( int i = NUM_TONE_PINS; i < _MAX_TASKS - 1; i++ )
    {
    // Fill with call back function address
    if( tasks[ i ] == NULL )
      {
        taskTable[ i ].status = 0;
        tasks[ i ] = ptr;   // Register callback
        interrupts( );
        return i;
      }
    }
    interrupts( );
    return -1;
}

/* deleteTask - Remove a task from the list and delete the callback function

    Parameters  ptr Pointer to callback function

    Return int  -2 No task found
                -1 Invalid task address
                 >=0 Number of deleted task
*/
int deleteTask( int(* ptr)( int, int16_t ) )
{
  noInterrupts( );
  int ID = findID( ptr );

  if( ID >= 0 )
  {
    taskTable[ ID ].status = 0;
    tasks[ ID ] = NULL;
    setInterval(ID, 0);
  }
  interrupts( );
  return ID;
}

/* startTask - Start a task if not running and has interval set

   Cannot start an already started task

   It is responsibility of the task to stop its task and any associated
   resources (GPIO/TWI/SPI etc).

    Parameters  int Task ID to start

    Return int  -3  Task already started
                -2  No interval on task
                -1  invalid ID
                 0  current task running
                > 0 Valid set to run after interval time
*/
int startTask( int ID )
{
// Check valid ID, not running and interval
if( ( CheckID( ID ) ) <= 0 )
  return -1;
if( taskTable[ ID ].interval == 0 )
  return -2;
if( taskTable[ ID ].status  > 0 )
  return -3;
// Start task
taskTable[ ID ].next = old_ms + taskTable[ ID ].interval;
taskTable[ ID ].status = 1;
return 1;
}


/* findID - Find ID for FIRST task with matching function address in Task table

   Scans task table to find a matching function address and return the ID
   NOTE stops at FIRST match.

    Parameters  int Task ID to Stop

    Return int  -2 No task found
                -1 Invalid task address
                >= 0 Valid and stopped
*/
int findID( int(*  ptr)( int, int16_t ) )
{
int i;

if( ptr == NULL )
  return -1;
for( i = 0; i < _MAX_TASKS; i++ )
   if( tasks[ i ] == ptr )
     break;
if( i == _MAX_TASKS )
  return -2;
return i;
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
