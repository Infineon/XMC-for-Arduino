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

#ifndef WIRING_TIME_H_
#define WIRING_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// @Defines
//****************************************************************************
/**< SysTick interval in microseconds */
#define SYSTIMER_TICK_PERIOD_US (1000U)
/**< value for Systick counts per ms **/
#define SYSTICK_MS (F_CPU / SYSTIMER_TICK_PERIOD_US)
/**< value for Systick counts per us **/
#define SYSTICK_US (SYSTICK_MS / SYSTIMER_TICK_PERIOD_US)

#if ((UC_FAMILY == XMC4) && (F_CPU == 144000000U))
    // 142 NOPS
    #define NOPS_FOR_USEC()      \
        {                        \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
        }

#elif ((UC_FAMILY == XMC4) && (F_CPU == 80000000U))
    // 80 NOPS
    #define NOPS_FOR_USEC()      \
        {                        \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
        }

#elif ((UC_FAMILY == XMC1) && (F_CPU == 32000000U))
    // 16 NOPS
    #define NOPS_FOR_USEC()      \
        {                        \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
        }
#elif ((UC_FAMILY == XMC1) && (F_CPU == 48000000U))
    // 24 NOPS
    #define NOPS_FOR_USEC()      \
        {                        \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
            asm volatile("nop"); \
        }
#else
    #error wiring_time: NOPS_FOR_USEC not defined
#endif

//****************************************************************************
// @Typedefs
//****************************************************************************
/* Structures  for task details next run, status etc.. */
struct TaskList {
    uint32_t next;     // next execution time in ms
    uint32_t interval; // interval between schedule starts in ms
    int16_t param;     // User defined parameter
    int16_t status;    // current task status 0 stopped,
                       // -ve stopped with error,
                       // > 0 user status (and active)
};

/* SysTick counter */
extern volatile uint32_t g_systick_count;

//****************************************************************************
// @External Prototypes
//****************************************************************************
/*
 * \brief Initialize the time module.
 */
extern void wiring_time_init(void);

extern int setInterval(int, uint32_t);
extern uint32_t getInterval(int);
extern int setParam(int, int16_t);
extern int16_t getParam(int);
extern uint32_t getTime(int);
extern int16_t getStatus(int);
extern int addTask(int (*)(int, int16_t));
extern int deleteTask(int (*)(int, int16_t));
extern int startTask(int);
extern int findID(int (*)(int, int16_t));

#ifdef __cplusplus
}
#endif

#endif /* WIRING_TIME_H_ */
