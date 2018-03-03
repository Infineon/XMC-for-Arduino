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
#include "wiring_time.h"

//****************************************************************************
// @Macros
//****************************************************************************
/**< Maximum No of timer **/
#define SYSTIMER_CFG_MAX_TMR  (8U)

#define SYSTIMER_PRIORITY  (4U)

#define HW_TIMER_ADDITIONAL_CNT (1U)

//****************************************************************************
// @Defines
//****************************************************************************
/*!< Millisecond to Microsecond ratio */
#define TIMER_1mSec 1000
/*!< The ISR divider */
#define TIMER_ISR_RATIO 1
/*!< mS to uS scaling factor*/
#define TIMER_mSecTouSec_RATIO  ( TIMER_1mSec / TIMER_ISR_RATIO )

//****************************************************************************
// @Typedefs
//****************************************************************************
/* SYSTIMER_OBJECT structure acts as the timer control block */
typedef struct XMC_SYSTIMER_OBJECT
    {
    struct XMC_SYSTIMER_OBJECT* next;   /**< pointer to next timer control block */
    struct XMC_SYSTIMER_OBJECT* prev;   /**< Pointer to previous timer control block */
    XMC_SYSTIMER_CALLBACK_t callback;   /**< Callback function pointer */
    XMC_SYSTIMER_MODE_t mode;           /**< timer Type (single shot or periodic) */
    XMC_SYSTIMER_STATE_t state;         /**< timer state */
    void* args;                         /**< Parameter to callback function */
    uint32_t id;                        /**< timer ID */
    uint32_t count;                     /**< timer count value */
    uint32_t reload;                    /**< timer Reload count value */
    bool delete_swtmr;                  /**< To delete the timer */
    } XMC_SYSTIMER_OBJECT_t;

//****************************************************************************
// @Global Variables
//****************************************************************************
/** Table which save timer control block. */
XMC_SYSTIMER_OBJECT_t g_timer_tbl[ SYSTIMER_CFG_MAX_TMR ];

/* The header of the timer Control list. */
XMC_SYSTIMER_OBJECT_t* g_timer_list = NULL;

/* Timer ID tracker */
uint32_t g_timer_tracker = 0U;

/* Tracker if Timer Handler as already been entered -> avoid recursion */
volatile uint16_t g_timer_entered_handler = 0u;

/* SysTick counter */
volatile uint32_t g_systick_count = 0U;

// Should be volatile as updated in IRQ handler or callback from IRQ handler
volatile __IO bool delay_timer_expired;

//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

/* This function is called to insert a timer into the timer list. */
static void XMC_SYSTIMER_lInsertTimerList( uint32_t tbl_index );

/* This function is called to remove a timer from the timer list. */
static void XMC_SYSTIMER_lRemoveTimerList( uint32_t tbl_index );

/* Handler function  called from SysTick event handler. */
static void XMC_SYSTIMER_lTimerHandler( void );

/* SysTick handler which is the main interrupt service routine to service the
 * system timer's configured */
void SysTick_Handler( void );


//****************************************************************************
// @Local Functions
//****************************************************************************
void wiring_time_init( void )
{
/* Initialize the header of the list */
g_timer_list = NULL;
/* Initialize SysTick timer for 1ms (1kHz) interval */
SysTick_Config( (uint32_t)SYSTICK_MS );

/* setting of First SW Timer period is always and sub-priority value for XMC4000 devices */
/* setting of priority value for XMC1000 devices */
NVIC_SetPriority( SysTick_IRQn, SYSTIMER_PRIORITY );
g_timer_tracker = 0U;
}


void delay( uint32_t dwMs )
{
uint32_t TimerId;

delay_timer_expired = FALSE;
/* This function uses SysTick Exception for controlling the timer list. Call back function
 * registered through this function will be called in SysTick exception when the timer is expired.
 * One shot timers are removed from the timer list, if it expires. To use
 * this SW timer again it has to be first deleted and then created again.
 *
 *  @param[in]  Period Timer period value in microseconds
 *  @param[in]  TimerType Type of Timer(ONE_SHOT/PERIODIC)
 *  @param[in]  TimerCallBack Call back function of the timer(No Macros are allowed)
 *  @param[in]  pCallBackArgPtr Call back function parameter
 *
 * Special cases for callback action processing
 *      args is NULL means a function with VOID parameter list called e.g function()
 *      callback is NULL boolean delay_timer_expired is set to true
 *
 */
TimerId = XMC_SYSTIMER_CreateTimer( dwMs * TIMER_mSecTouSec_RATIO, XMC_SYSTIMER_MODE_ONE_SHOT,
                                            NULL, NULL );
if( TimerId != 0 )
  {
  //Timer is created successfully
  XMC_SYSTIMER_StartTimer( TimerId );
  // Wait until timer expires
  do
    yield( );
  while( !delay_timer_expired );
  // Delete Timer since is One-Shot
  XMC_SYSTIMER_DeleteTimer( TimerId );
  }
}


/* This function is called to insert a timer into the timer list. */
static void XMC_SYSTIMER_lInsertTimerList( uint32_t tbl_index )
{
XMC_SYSTIMER_OBJECT_t* object_ptr;
int32_t delta_ticks;
int32_t timer_count;
bool found_flag = false;
/* Get timer time */
timer_count = (int32_t)g_timer_tbl[ tbl_index ].count;
/* Check if Timer list is NULL */
if( NULL == g_timer_list )
  /* Set this as first Timer */
  g_timer_list = &g_timer_tbl[ tbl_index ];
/* If not, find the correct place, and insert the specified timer */
else
  {
  object_ptr = g_timer_list;
  /* Get timer tick */
  delta_ticks = timer_count;
  /* Find correct place for inserting the timer */
  while( ( NULL != object_ptr ) && ( false == found_flag ) )
    {
    /* Get timer Count Difference */
    delta_ticks -= (int32_t)object_ptr->count;
    /* Check for delta ticks < 0 */
    if( delta_ticks <= 0)
      {
      /* Check If head item */
      if( NULL != object_ptr->prev )
        {
        /* If Insert to list */
        object_ptr->prev->next = &g_timer_tbl[ tbl_index ];
        g_timer_tbl[ tbl_index ].prev = object_ptr->prev;
        g_timer_tbl[ tbl_index ].next = object_ptr;
        object_ptr->prev = &g_timer_tbl[ tbl_index ];
        }
      else
        {
        /* Set Timer as first item */
        g_timer_tbl[ tbl_index ].next = g_timer_list;
        g_timer_list->prev = &g_timer_tbl[ tbl_index ];
        g_timer_list = &g_timer_tbl[ tbl_index ];
        }
      g_timer_tbl[ tbl_index ].count = g_timer_tbl[ tbl_index ].next->count
                                                    + (uint32_t)delta_ticks;
      g_timer_tbl[ tbl_index ].next->count  -= g_timer_tbl[ tbl_index ].count;
      found_flag = true;
      }
    /* Check for last item in list */
    else
      {
      if( ( delta_ticks > 0 ) && ( NULL == object_ptr->next ) )
        {
        /* Yes, insert into */
        g_timer_tbl[ tbl_index ].prev = object_ptr;
        object_ptr->next = &g_timer_tbl[ tbl_index ];
        g_timer_tbl[ tbl_index ].count = (uint32_t)delta_ticks;
        found_flag = true;
        }
      }
    /* Get the next item in timer list */
    object_ptr = object_ptr->next;
    }
  }
}


/* This function is called to remove a timer from the timer list. */
static void XMC_SYSTIMER_lRemoveTimerList( uint32_t tbl_index )
{
XMC_SYSTIMER_OBJECT_t* object_ptr;
object_ptr = &g_timer_tbl[ tbl_index ];
/* Check whether only one timer available */
if( ( NULL == object_ptr->prev ) && ( NULL == object_ptr->next ) )
  /* set timer list as NULL */
  g_timer_list = NULL;
/* Check if the first item in timer list */
else
  if( NULL == object_ptr->prev )
    {
    /* Remove timer from list, and reset timer list */
    g_timer_list  = object_ptr->next;
    g_timer_list->prev = NULL;
    g_timer_list->count += object_ptr->count;
    object_ptr->next    = NULL;
    }
    /* Check if the last item in timer list */
  else
    {
    if( NULL == object_ptr->next )
      {
      /* Remove timer from list */
      object_ptr->prev->next = NULL;
      object_ptr->prev = NULL;
      }
    else
      {
      /* Remove timer from list */
      object_ptr->prev->next  =  object_ptr->next;
      object_ptr->next->prev  =  object_ptr->prev;
      object_ptr->next->count += object_ptr->count;
      object_ptr->next = NULL;
      object_ptr->prev = NULL;
      }
    }
}


/* Handler function called from SysTick event handler. */
static void XMC_SYSTIMER_lTimerHandler( void )
{
XMC_SYSTIMER_OBJECT_t* object_ptr;
int found;

/* Handler entered */
g_timer_entered_handler++;
/* Get first item of timer list */
object_ptr = g_timer_list;
while( ( NULL != object_ptr ) && ( 0U == object_ptr->count ) )
    {
    found = 0;
    if( true == object_ptr->delete_swtmr )
      {
      found = 1;
      /* Set timer status as SYSTIMER_STATE_NOT_INITIALIZED */
      object_ptr->state = XMC_SYSTIMER_STATE_NOT_INITIALIZED;
      /* Release resource which are hold by this timer */
      g_timer_tracker &= ~( 1U << object_ptr->id );
      }
    /* Check whether timer is a one shot timer */
    else
      if( XMC_SYSTIMER_MODE_ONE_SHOT == object_ptr->mode )
        {
        if( XMC_SYSTIMER_STATE_RUNNING == object_ptr->state )
          {
          found = 2;
          /* Set timer status as SYSTIMER_STATE_STOPPED */
          object_ptr->state = XMC_SYSTIMER_STATE_STOPPED;
          }
        }
    /* Check whether timer is periodic timer */
      else
        if( XMC_SYSTIMER_MODE_PERIODIC == object_ptr->mode )
          {
          if( XMC_SYSTIMER_STATE_RUNNING == object_ptr->state )
            {
            found = 3;
            /* Reset timer tick */
            object_ptr->count = object_ptr->reload;
            }
          }
        else
          break;
    // process common aspects having found a match
    if( found )
      {
      /* Yes, remove this timer from timer list */
      XMC_SYSTIMER_lRemoveTimerList( (uint32_t)object_ptr->id );
      if( found > 1 )
        {
        /* Call timer callback function */
        if( object_ptr->callback == NULL )
          delay_timer_expired = TRUE;         // Special case of NULL callback function
        else
          if( object_ptr->args != NULL )
            ( object_ptr->callback )( object_ptr->args );
          else                    // Special case NULL arguments address
            ( (XMC_SYSTIMER_CALLBACK_tn)object_ptr->callback )(  );
        if( found == 3 )      // Reinsert into timer list
          XMC_SYSTIMER_lInsertTimerList( (uint32_t)object_ptr->id );
        }
      }
    /* Get first item of timer list */
    object_ptr = g_timer_list;
    }
}


/* SysTick Event Handler. */
void SysTick_Handler( void )
{
XMC_SYSTIMER_OBJECT_t* object_ptr;
object_ptr = g_timer_list;
g_systick_count++;

if( NULL != object_ptr )
  {
  if( object_ptr->count > 1UL )
    object_ptr->count--;
  else
    {
    object_ptr->count = 0U;
    // do not call handler, when still running
    if( g_timer_entered_handler == 0u )
      {
      //g_timer_entered_handler++;
      XMC_SYSTIMER_lTimerHandler();
      g_timer_entered_handler--;
      }
    }
  }
}


/** @ingroup Simple_System_Timer_App PublicFunc
 * @{
 */
/* API for creating a new software Timer instance. */
uint32_t XMC_SYSTIMER_CreateTimer( uint32_t period, XMC_SYSTIMER_MODE_t mode,
                                        XMC_SYSTIMER_CALLBACK_t callback, void* args )
{
uint32_t id = 0U;
uint32_t count = 0U;
uint32_t period_ratio = 0U;

if( period < SYSTIMER_TICK_PERIOD_US )
  id = 0U;
else
  {
  for( count = 0U; count < SYSTIMER_CFG_MAX_TMR; count++ )
    {
    /* Check for free timer ID */
    if( 0U == ( g_timer_tracker & ( 1U << count ) ) )
      {
      /* If yes, assign ID to this timer */
      g_timer_tracker |= ( 1U << count );
      /* Initialize the timer as per input values */
      g_timer_tbl[ count ].id       = count;
      g_timer_tbl[ count ].mode     = mode;
      g_timer_tbl[ count ].state    = XMC_SYSTIMER_STATE_STOPPED;
      period_ratio = (uint32_t)( period / SYSTIMER_TICK_PERIOD_US );
      g_timer_tbl[ count ].count    = ( period_ratio + HW_TIMER_ADDITIONAL_CNT );
      g_timer_tbl[ count ].reload   = period_ratio;
      g_timer_tbl[ count ].callback = callback;
      g_timer_tbl[ count ].args     = args;
      g_timer_tbl[ count ].prev     = NULL;
      g_timer_tbl[ count ].next     = NULL;
      id = count + 1U;
      break;
      }
    }
  }
return ( id );
}


/* API to start the software timer. */
XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_StartTimer( uint32_t id )
{
XMC_SYSTIMER_STATUS_t status;
status = XMC_SYSTIMER_STATUS_FAILURE;

/* Check if timer is running */
id -= 1U;
if( XMC_SYSTIMER_STATE_STOPPED == g_timer_tbl[ id ].state )
  {
  g_timer_tbl[ id ].count = g_timer_tbl[ id ].reload + HW_TIMER_ADDITIONAL_CNT;
  /* set timer status as XMC_SYSTIMER_STATE_RUNNING */
  g_timer_tbl[ id ].state = XMC_SYSTIMER_STATE_RUNNING;
  /* Insert this timer into timer list */
  XMC_SYSTIMER_lInsertTimerList( id );
  status = XMC_SYSTIMER_STATUS_SUCCESS;
  }
return ( status );
}


/* API to stop the software timer.  */
XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_StopTimer( uint32_t id )
{
XMC_SYSTIMER_STATUS_t status;
status = XMC_SYSTIMER_STATUS_SUCCESS;

id -= 1U;
if( XMC_SYSTIMER_STATE_NOT_INITIALIZED == g_timer_tbl[ id ].state )
  status = XMC_SYSTIMER_STATUS_FAILURE;
else
  {
  /* Check whether Timer is in Stop state */
  if( XMC_SYSTIMER_STATE_RUNNING == g_timer_tbl[ id ].state )
    {
    /* Set timer status as SYSTIMER_STATE_STOPPED */
    g_timer_tbl[ id ].state = XMC_SYSTIMER_STATE_STOPPED;

    /* remove Timer from node list */
    XMC_SYSTIMER_lRemoveTimerList( id );
    }
  }
return ( status );
}


/* API to reinitialize the time interval and to start the timer. */
XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_RestartTimer( uint32_t id, uint32_t microsec )
{
uint32_t period_ratio = 0U;
XMC_SYSTIMER_STATUS_t status;
status = XMC_SYSTIMER_STATUS_SUCCESS;

if( XMC_SYSTIMER_STATE_NOT_INITIALIZED == g_timer_tbl[ id - 1U ].state )
  status = XMC_SYSTIMER_STATUS_FAILURE;
else
  {
  /* check whether timer is in run state */
  if( XMC_SYSTIMER_STATE_STOPPED != g_timer_tbl[ id - 1U ].state )
    {
    /* Stop the timer */
    status = XMC_SYSTIMER_StopTimer( id );
    }
  if( XMC_SYSTIMER_STATUS_SUCCESS == status )
    {
    period_ratio = (uint32_t)( microsec / SYSTIMER_TICK_PERIOD_US );
    g_timer_tbl[ id - 1U ].reload = period_ratio;
    /* Start the timer */
    status = XMC_SYSTIMER_StartTimer( id );
    }
  }
return ( status );
}


/* Function to delete the Timer instance. */
XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_DeleteTimer( uint32_t id )
{
XMC_SYSTIMER_STATUS_t status;
status = XMC_SYSTIMER_STATUS_SUCCESS;

/* Check whether Timer is in delete state first change id */
id -= 1U;
if( XMC_SYSTIMER_STATE_NOT_INITIALIZED == g_timer_tbl[ id ].state )
  status = XMC_SYSTIMER_STATUS_FAILURE;
else
  {
  if( XMC_SYSTIMER_STATE_STOPPED == g_timer_tbl[ id ].state )
    {
    /* Set timer status as SYSTIMER_STATE_NOT_INITIALIZED */
    g_timer_tbl[ id ].state = XMC_SYSTIMER_STATE_NOT_INITIALIZED;
    /* Release resource which are hold by this timer */
    g_timer_tracker &= ~( 1U << id );
    }
  else
    {
    /* Yes, remove this timer from timer list during ISR execution */
    g_timer_tbl[ id ].delete_swtmr = true;
    }
  }
return ( status );
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
