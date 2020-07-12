/**
 * RTC.h - Library for Arduino to control the RTC (Real Time Clock) of the XMC microcontroller series.
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

/*!	\file RTC.h
 *	\brief This file has to be included in projects that use Infineon's XMC RTC module
 */
#ifndef _RTC_H_INCLUDED
#define _RTC_H_INCLUDED

#include "xmc_device.h"
#include "utility/xmc_rtc_conf.h"

//****************************************************************************
// @Board Check
//****************************************************************************
#if !defined(XMC1) || !defined(XMC4)
#error Only XMC microcontrollers are supported by this library
#endif

//****************************************************************************
// @Defines
//****************************************************************************
// Define alarm handler routine, if nothing declared by user then it comes here 
// so the execution  will not crash
#ifdef __cplusplus
extern "C" {
	void alarm_handler(void);
}
#endif

typedef void (*interrupt_t)(void);

//****************************************************************************
// @Class Definitions
//****************************************************************************
class RTCClass
{	
	public:

	enum Alarm: int 
  	{ 
	     MATCH_OFF          = NULL,          						// Never 
	     PERIODIC_SECONDS   = XMC_RTC_EVENT_PERIODIC_SECONDS,  		// Every Second		 
		 PERIODIC_MINUTES   = XMC_RTC_EVENT_PERIODIC_MINUTES,      	// Every Minute 
		 PERIODIC_HOURS     = XMC_RTC_EVENT_PERIODIC_HOURS,         // Every Hour 
		 PERIODIC_DAYS      = XMC_RTC_EVENT_PERIODIC_DAYS,       	// Every Day 
		 PERIODIC_MONTHS    = XMC_RTC_EVENT_PERIODIC_MONTHS,     	// Every Month 
		 PERIODIC_YEARS   	= XMC_RTC_EVENT_PERIODIC_YEARS,   		// Every Year 
		 ALARM 				= XMC_RTC_EVENT_ALARM 					// Once, on a specific date and a specific time 
	 };
	 	 
		// Constructors
		RTCClass()
		{
			// default RTC
		    XMC_RTC_config = &XMC_RTC_default_t;
		}

		RTCClass(XMC_RTC_CONFIG_t* conf)
		{
			XMC_RTC_config = conf;
		}
		
		void begin();
		
		// Set values for time & date
		void setHours(byte hours);
		void setMinutes(byte minutes);
		void setSeconds(byte seconds);
		void setTime(byte hours, byte minutes, byte seconds);
		void setYear(uint16_t year);
		void setMonth(uint8_t month);
		void setDay(byte day);
		void setDate(byte day, byte month, uint16_t year);
		
		// Get values for time & date
		byte getHours();
		byte getMinutes();
		byte getSeconds();
		uint16_t getYear();
		uint8_t	getMonth();
		byte getDay();
		
		// Set values  for time & date of alarm
		void setAlarmHours(byte hours);
		void setAlarmMinutes(byte minutes);
		void setAlarmSeconds(byte seconds);
		void setAlarmTime(byte hours, byte minutes, byte seconds);
		void setAlarmYear(uint16_t year);
		void setAlarmMonth(uint8_t month);
		void setAlarmDay(byte day);
		void setAlarmDate(byte day, byte month, uint16_t year);
		
		void enableAlarm(Alarm alarm);
		void disableAlarm();
		
		void attachInterrupt(XMC_SCU_INTERRUPT_EVENT_HANDLER_t handler);
		void detachInterrupt();
		void end();
		
		// Configure alarm clock prescaler 0-777F
		void setPrescaler(uint16_t presc);
		uint32_t getPrescaler();
		
	private:
		
		void init();
		void fillOtherAlarmData();
		XMC_RTC_ALARM_t alarmNow;
		XMC_RTC_TIME_t timeNow;
		XMC_RTC_CONFIG_t* XMC_RTC_config;
		bool initialized;
		/* Internal variable used to store type of alarm when enabled, so we can attach interrupt */
		XMC_SCU_INTERRUPT_EVENT_t event_interrupt; 

};
#endif /* _RTC_H_INCLUDED */
