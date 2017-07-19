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
#ifndef WIRING_TIME_H_
#define WIRING_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// @Defines
//****************************************************************************
#if ((UC_FAMILY == XMC4) && (F_CPU == 144000000U))
// time per loop cycle: 0,0277777777777778 us
#define USEC_TO_N_NOP_CYCLES        36
#elif ((UC_FAMILY == XMC1) && (F_CPU == 32000000U))
// time per loop cycle: 0,375 us
#define USEC_TO_N_NOP_CYCLES        3
#else
#error USEC_TO_N_NOP_CYCLES not calculated
#endif

//****************************************************************************
// @Typedefs
//****************************************************************************
    typedef void (*XMC_SYSTIMER_CALLBACK_t)(void* args);

    typedef enum XMC_SYSTIMER_STATUS
    {
        XMC_SYSTIMER_STATUS_SUCCESS = 0U, /**< Status Success if initialization is successful */
        XMC_SYSTIMER_STATUS_FAILURE  /**< Status Failure if initialization is failed */
    } XMC_SYSTIMER_STATUS_t;

    typedef enum XMC_SYSTIMER_MODE
    {
        XMC_SYSTIMER_MODE_ONE_SHOT = 0U, /**< timer type is one shot */
        XMC_SYSTIMER_MODE_PERIODIC /**< timer type is periodic */
    } XMC_SYSTIMER_MODE_t;

    typedef enum XMC_SYSTIMER_STATE
    {
        XMC_SYSTIMER_STATE_NOT_INITIALIZED = 0U, /**< The timer is in uninitialized state */
        XMC_SYSTIMER_STATE_RUNNING, /**< The timer is in running state */
        XMC_SYSTIMER_STATE_STOPPED /**< The timer is in stop state */
    } XMC_SYSTIMER_STATE_t;

//****************************************************************************
// @External Prototypes
//****************************************************************************

    /*
     * \brief Initialize the time module.
     */
    extern void wiring_time_init(void);

    /*
     * \brief Returns the number of milliseconds since the Arduino board began running the current program.
     *
     * This number will overflow (go back to zero), after approximately 50 days.
     *
     * \return Number of milliseconds since the program started (uint32_t)
     */
    extern uint32_t millis(void) ;

    /*
     * \brief Returns the number of microseconds since the Arduino board began running the current program.
     *
     * This number will overflow (go back to zero), after approximately 70 minutes. On 16 MHz Arduino boards
     * (e.g. Duemilanove and Nano), this function has a resolution of four microseconds (i.e. the value returned is
     * always a multiple of four). On 8 MHz Arduino boards (e.g. the LilyPad), this function has a resolution
     * of eight microseconds.
     *
     * \note There are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
     */
    extern uint32_t micros(void) ;

    /*
     * \brief Pauses the program for the amount of time (in miliseconds) specified as parameter.
     * (There are 1000 milliseconds in a second.)
     *
     * \param dwMs the number of milliseconds to pause (uint32_t)
     */
    extern void delay(uint32_t dwMs) ;

    /*
     * \brief Pauses the program for the amount of time (in microseconds) specified as parameter.
     *
     * \param dwUs the number of microseconds to pause (uint32_t)
     */

    static inline void delayMicroseconds(uint32_t) __attribute__((always_inline));
    static inline void delayMicroseconds(uint32_t usec)
    {

        if (usec == 0)
        {
            return;
        }
        else
        {
            uint32_t number_of_nop_cycles = (uint32_t)(usec * USEC_TO_N_NOP_CYCLES);
            // NOP loop to gnerate delay
            while (number_of_nop_cycles)
            {
                asm volatile("nop");
                number_of_nop_cycles--;
            }
        }
    }
    /*
     * @brief Creates a new software timer.
     * @param period  timer period value in microseconds. Range: (SYSTIMER_TICK_PERIOD_US) to pow(2,32).
     * @param mode  Mode of timer(ONE_SHOT/PERIODIC). Refer @ref XMC_SYSTIMER_MODE_t for details.
     * @param callback  Call back function of the timer(No Macros are allowed).
     * @param args  Call back function parameter.
     */
    uint32_t XMC_SYSTIMER_CreateTimer
    (
        uint32_t period,
        XMC_SYSTIMER_MODE_t mode,
        XMC_SYSTIMER_CALLBACK_t callback,
        void*  args
    );

    /*
     * @brief Starts the software timer.
     * @param id  timer ID obtained from SYSTIMER_CreateTimer. Range : 1 to 16
     * @return XMC_SYSTIMER_STATUS_t APP status. Refer @ref XMC_SYSTIMER_STATUS_t for details.
     */
    XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_StartTimer(uint32_t id);

    /*
     * @brief Stops the software timer.
     * @param id  timer ID obtained from SYSTIMER_CreateTimer. Range : 1 to 16
     * @return XMC_SYSTIMER_STATUS_t APP status. Refer @ref XMC_SYSTIMER_STATUS_t for details.
     */
    XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_StopTimer(uint32_t id);

    /*
     * @brief Function to modify the time interval and restart the timer for the new time interval.<br>
     * @param id ID of already created system timer. Range : 1 to 16
     * @param microsec new time interval. Range: (SYSTIMER_TICK_PERIOD_US) to pow(2,32).
     * @return XMC_SYSTIMER_STATUS_t APP status. Refer @ref XMC_SYSTIMER_STATUS_t for details.
     */
    XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_RestartTimer(uint32_t id, uint32_t microsec);

    /*
     * @brief Deletes the software timer from the timer list.
     * @param id  timer ID obtained from SYSTIMER_CreateTimer. Range : 1 to 16
     * @return XMC_SYSTIMER_STATUS_t APP status. Refer @ref XMC_SYSTIMER_STATUS_t for details.
     */
    XMC_SYSTIMER_STATUS_t XMC_SYSTIMER_DeleteTimer(uint32_t id);

    /*
     * @brief Gives the current hardware SysTick time in microsecond since start of hardware SysTick timer.
     * @return  uint32_t  returns current SysTick time in microsecond. Range: (SYSTIMER_TICK_PERIOD_US) to pow(2,32).
     */
    uint32_t XMC_SYSTIMER_GetTime(void);

    /*
     * @brief Gives the SysTick count.
     * @return  uint32_t  returns SysTick count. Range: 0 to pow(2,32).
     */
    uint32_t XMC_SYSTIMER_GetTickCount(void);

    /*
     * @brief Gives the current state of software timer.
     * @param id  timer ID obtained from SYSTIMER_CreateTimer. Range : 1 to 16
     * @return XMC_SYSTIMER_STATE_t Software timer state. Refer @ref XMC_SYSTIMER_STATE_t for details.
     */
    XMC_SYSTIMER_STATE_t XMC_SYSTIMER_GetTimerState(uint32_t id);

#ifdef __cplusplus
}
#endif


#endif /* WIRING_TIME_H_ */
