/**
 * RTC.cpp - Library for Arduino to control the RTC (Real Time Clock) of the XMC microcontroller series.
 * 
 * Real-time clock (RTC) is a clock that keeps track of the current time. RTCs are present
 * in almost any electronic device which needs to keep accurate time in a digital format for
 * clock displays and computer systems.
 * 
 * Have a look at the application note/datasheet for more information.
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
 
/*!	\file RTC.cpp
 *	\brief This file defines functions and predefined instances from RTC.h
 */
#include <Arduino.h>
#include "RTC.h"

//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************
static interrupt_t alarm_interrupt = NULL;

//****************************************************************************
// @Local Functions
//****************************************************************************

extern "C"	{
#if (UC_FAMILY == XMC4)
	void SCU_0_IRQHandler(void)
	{
		XMC_SCU_IRQHandler(0);
	}
#elif (UC_FAMILY == XMC1)
	void SCU_1_IRQHandler(void)
	{
		XMC_SCU_IRQHandler(1);
	}
#endif
	void alarm_handler(void)
	{
		
		if(alarm_interrupt)
			alarm_interrupt();
		else
		{}
	}
}

void RTCClass::init()
{
    if (initialized)
    {
        return;
    }
#if (UC_FAMILY == XMC4)
    XMC_SCU_HIB_EnableHibernateDomain();
   	XMC_SCU_HIB_SetRtcClockSource(XMC_SCU_HIB_RTCCLKSRC_OSI);
#endif
	/*Set default time 01-01-2017 01:00*/
	XMC_RTC_Init(&XMC_RTC_default_t);
	XMC_RTC_Start();
    initialized = true;
}

void RTCClass::fillOtherAlarmData()
{
	XMC_RTC_GetTime(&timeNow);
	alarmNow.days		= timeNow.days;
	alarmNow.month 		= timeNow.month;
	alarmNow.year 		= timeNow.year;
	alarmNow.seconds 	= timeNow.seconds;
	alarmNow.minutes	= timeNow.minutes;
	alarmNow.hours 		= timeNow.hours;
}

//****************************************************************************
// @Public Methods
//****************************************************************************

void RTCClass::begin()
{
    init();
}
void RTCClass::end()
{
	initialized = false;
    XMC_RTC_Stop();
}

void RTCClass::setHours(byte hours)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.hours = hours;
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setMinutes(byte minutes)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.minutes = minutes;
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setSeconds(byte seconds)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.seconds = seconds;
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setTime(byte hours, byte minutes, byte seconds)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.seconds = seconds;
	timeNow.minutes = minutes;
	timeNow.hours = hours;
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setYear(uint16_t year)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.year = year;
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setMonth(uint8_t month)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.month = month;
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setDay(byte day)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.days = day;
	// If day of the week (M,T,W,TH,F,S,S) is needed, calculate and change also day of the week
	XMC_RTC_SetTime(&timeNow);
}
void RTCClass::setDate(byte day, byte month, uint16_t year)
{
	XMC_RTC_GetTime(&timeNow);
	timeNow.days = day;
	timeNow.month = month;
	timeNow.year = year;
	// If day of the week (M,T,W,TH,F,S,S) is needed, calculate and change also day of the week
	XMC_RTC_SetTime(&timeNow);
}

byte RTCClass::getHours()
{
	XMC_RTC_GetTime(&timeNow);
	return timeNow.hours;
}
byte RTCClass::getMinutes()
{
	XMC_RTC_GetTime(&timeNow);
	return timeNow.minutes;
}
byte RTCClass::getSeconds()
{
	XMC_RTC_GetTime(&timeNow);
	return timeNow.seconds;
}
uint16_t RTCClass::getYear()
{	
	XMC_RTC_GetTime(&timeNow);
	return timeNow.year;
}
uint8_t	RTCClass::getMonth()
{
	XMC_RTC_GetTime(&timeNow);
	return timeNow.month;
}
byte RTCClass::getDay()
{
	XMC_RTC_GetTime(&timeNow);
	return timeNow.days;
}

// Alarm functions 
void RTCClass::setAlarmHours(byte hours)
{
	fillOtherAlarmData();
	alarmNow.hours = hours;
	XMC_RTC_SetAlarm(&alarmNow);
}
void RTCClass::setAlarmMinutes(byte minutes)
{
	fillOtherAlarmData();
	alarmNow.minutes = minutes;
	XMC_RTC_SetAlarm(&alarmNow);
}
void RTCClass::setAlarmSeconds(byte seconds)
{
	fillOtherAlarmData();
	alarmNow.seconds = seconds;
	XMC_RTC_SetAlarm(&alarmNow);
}
void RTCClass::setAlarmTime(byte hours, byte minutes, byte seconds)
{
	fillOtherAlarmData();
	alarmNow.hours = hours;
	alarmNow.seconds = seconds;
	alarmNow.minutes = minutes;
	XMC_RTC_SetAlarm(&alarmNow);
}
void RTCClass::setAlarmYear(uint16_t year)
{
	fillOtherAlarmData();
	alarmNow.year = year;
	XMC_RTC_SetAlarm(&alarmNow);
}

void RTCClass::setAlarmMonth(uint8_t month)
{
	fillOtherAlarmData();
	alarmNow.month = month;
	XMC_RTC_SetAlarm(&alarmNow);
}

void RTCClass::setAlarmDay(byte day)
{
	fillOtherAlarmData();
	alarmNow.days = day;
	XMC_RTC_SetAlarm(&alarmNow);
}

void RTCClass::setAlarmDate(byte day, byte month, uint16_t year)
{
	fillOtherAlarmData();
	alarmNow.days = day;
	alarmNow.month = month;
	alarmNow.year = year;
	XMC_RTC_SetAlarm(&alarmNow);
}

void RTCClass::enableAlarm(Alarm alarm)
{
	XMC_RTC_EnableEvent(alarm ); 		
	if(alarm == XMC_RTC_EVENT_ALARM)
		event_interrupt = XMC_SCU_INTERRUPT_EVENT_RTC_ALARM;
	else
		event_interrupt = XMC_SCU_INTERRUPT_EVENT_RTC_PERIODIC;
}
void RTCClass::disableAlarm()
{
	
}
void RTCClass::setPrescaler(uint16_t presc)
{	
	XMC_RTC_Stop();
	XMC_RTC_SetPrescaler(presc);
	XMC_RTC_Start();
}
uint32_t RTCClass::getPrescaler()
{	
	return XMC_RTC_GetPrescaler();
}

void RTCClass::attachInterrupt(XMC_SCU_INTERRUPT_EVENT_HANDLER_t handler)
{
	/* If these two lines are used, the other set event handler has to be commented	*/
	//	alarm_interrupt = handler;
	// XMC_SCU_INTERRUPT_SetEventHandler(event_interrupt, alarm_handler);
	XMC_SCU_INTERRUPT_SetEventHandler(event_interrupt, handler);
	XMC_SCU_INTERRUPT_EnableEvent(event_interrupt);
#if (UC_FAMILY == XMC4)
	NVIC_SetPriority(SCU_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
	NVIC_EnableIRQ(SCU_0_IRQn);
#elif (UC_FAMILY == XMC1)
	NVIC_SetPriority(SCU_1_IRQn, 3);
	NVIC_EnableIRQ(SCU_1_IRQn);
#endif	
	
}
void RTCClass::detachInterrupt()
{
	//alarm_interrupt = NULL;
}
