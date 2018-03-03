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
#include "pins_arduino.h"

//****************************************************************************
// @Macros
//****************************************************************************
#define FREQUENCY_TO_MILLIS(f)   (1000/(2*f))
#define TIMER_TO_IRQ_HANDLER(t)  t==0?TIMER_0_IRQHandler:t==1?TIMER_1_IRQHandler:t==2?TIMER_2_IRQHandler:t==3?TIMER_3_IRQHandler:NULL

//****************************************************************************
// @Defines
//****************************************************************************
// Max num of timer: 8 (- 1 for delay funct.)
#define AVAILABLE_TONE_PINS 4

//****************************************************************************
// @Global Variables
//****************************************************************************
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255, 255, 255, 255 };
static uint32_t timer_ids[AVAILABLE_TONE_PINS] = { 0, 0, 0, 0 };
static long timer_toggle_count[AVAILABLE_TONE_PINS] = { 0, 0, 0, 0 };

//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
void TIMER_0_IRQHandler(void);
void TIMER_1_IRQHandler(void);
void TIMER_2_IRQHandler(void);
void TIMER_3_IRQHandler(void);

void timer_irq_action(uint8_t);

//****************************************************************************
// @Local Functions
//****************************************************************************

static int8_t toneBegin(uint8_t _pin)
{
    int8_t _timer = -1;

    // if we're already using the pin, the timer should be configured.
    for (int i = 0; i < AVAILABLE_TONE_PINS; i++)
    {
        if (tone_pins[i] == _pin)
        {
            return i;
        }
    }

    // search for an unused timer.
    for (int i = 0; i < AVAILABLE_TONE_PINS; i++)
    {
        if (tone_pins[i] == 255)
        {
            tone_pins[i] = _pin;
            pinMode(_pin, OUTPUT);
            _timer = i;
            break;
        }
    }

    return _timer;
}

// frequency (in hertz) and duration (in milliseconds).
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
    long toggle_count = 0;
    int8_t _timer;

    _timer = toneBegin(_pin);

    if (_timer >= 0 && _timer < AVAILABLE_TONE_PINS)
    {

        // Calculate the toggle count
        if (duration > 0)
        {
            toggle_count = 2 * frequency * duration / 1000;
        }
        else
        {
            toggle_count = -1;
        }

        timer_ids[_timer] = XMC_SYSTIMER_CreateTimer((uint32_t)FREQUENCY_TO_MILLIS(frequency), XMC_SYSTIMER_MODE_PERIODIC, (XMC_SYSTIMER_CALLBACK_t) (TIMER_TO_IRQ_HANDLER(_timer)), NULL);
        if (timer_ids[_timer] != 0)
        {
            //Timer is created successfully
            timer_toggle_count[_timer] = toggle_count;
            XMC_SYSTIMER_StartTimer(timer_ids[_timer]);
        }
    }
}

void disableTimer(uint8_t _timer)
{
    if (_timer >= 0 && _timer < AVAILABLE_TONE_PINS)
    {
        XMC_SYSTIMER_DeleteTimer(timer_ids[_timer]);
    }
}


void noTone(uint8_t _pin)
{
    int8_t _timer = -1;

    for (int i = 0; i < AVAILABLE_TONE_PINS; i++)
    {
        if (tone_pins[i] == _pin)
        {
            _timer = i;
            tone_pins[i] = 255;
            break;
        }
    }

    disableTimer(_timer);

    digitalWrite(_pin, 0);
}

void TIMER_0_IRQHandler(void)
{
    timer_irq_action(0);
}

void TIMER_1_IRQHandler(void)
{
    timer_irq_action(1);
}

void TIMER_2_IRQHandler(void)
{
    timer_irq_action(2);
}

void TIMER_3_IRQHandler(void)
{
    timer_irq_action(3);
}

void timer_irq_action(uint8_t _timer)
{
    if (timer_toggle_count[_timer])
    {
        XMC_GPIO_ToggleOutput(mapping_port_pin[tone_pins[_timer]].port, mapping_port_pin[tone_pins[_timer]].pin);
        timer_toggle_count[_timer]--;
    }
    else
    {
        disableTimer(_timer);
        timer_ids[_timer] = 0;
        digitalWrite(tone_pins[_timer], LOW);
    }
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
