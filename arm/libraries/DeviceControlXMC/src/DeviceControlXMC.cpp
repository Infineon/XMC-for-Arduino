/**
 * DeviceControlXMC.h - Library for Arduino to control the IFX9201 H-Bridge.
 * 
 * The IFX9201 is a general purpose 6A H-Bridge for industrial applications, home appliance and building 
 * automation, power tools battery management and medical applications, designed for the control of small 
 * DC motors and inductive loads.
 * 
 * Have a look at the application note/datasheet for more information.
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */

#include "DeviceControlXMC.h"

//****************************************************************************
// @Local Functions
//****************************************************************************
void XMCClass::init()
{}

//****************************************************************************
// @Public Methods
//****************************************************************************

void XMCClass::begin()
{}

/* Wake up from sleep mode*/
void XMCClass::enterActiveMode()
{
	 SCB->SCR = 0x00;
}

/* Software Reset of MCU*/
void XMCClass::reset()
{
   NVIC_SystemReset();
}

/**
 *  Get Die temperature in Celsius
 * @return temp_celsius: Die temperature in Celsius
 */
uint32_t XMCClass::getTemperature()
{
	uint32_t temp_calc = 0, temp_celsius = 0;
	temp_measurement_s = XMC_SCU_STATUS_ERROR;

#if (UC_FAMILY == XMC4)
	while(temp_calc == 0)	{
		if(temp_measurement_s == XMC_SCU_STATUS_OK)
			temp_calc = XMC_SCU_GetTemperatureMeasurement();
		else if(temp_measurement_s == XMC_SCU_STATUS_ERROR)
			XMC_SCU_EnableTemperatureSensor();
		else if(temp_measurement_s == XMC_SCU_STATUS_BUSY)
			while(XMC_SCU_IsTemperatureSensorBusy()) {};
		temp_measurement_s = XMC_SCU_StartTemperatureMeasurement();
	}
	temp_celsius = (temp_calc - 605)/2.05;

#elif(UC_FAMILY == XMC1)
	while(temp_calc == 0)	{
			XMC_SCU_StartTempMeasurement();
			temp_calc = XMC_SCU_CalcTemperature();
	}
	temp_celsius = temp_calc - 273;
#endif

	return temp_celsius;
}

/**
 *  Get free heap memory.
 * @return heap_free_s: Value of free bytes in heap.
 */
size_t XMCClass::freeRAM_Heap()	{
	/*Only possible to check for chunks. Good Method is to do a for loop trying to allocate maximum size of heap,
	 * decreasing the size, until we succeed, this is equal to the free amount, deallocate it and return free size of heap*/
	extern caddr_t Heap_Bank1_Start;
	extern caddr_t Heap_Bank1_End;

	size_t heap_total_s = (caddr_t)&Heap_Bank1_End - (caddr_t)&Heap_Bank1_Start;
	size_t heap_free_s = 0;
	char *pnt = 0;

	for(heap_free_s=heap_total_s; heap_free_s>0; heap_free_s--){
		pnt = (char*)malloc(heap_free_s);
		if (pnt != 0)
			break;
	}
	free(pnt);
	return heap_free_s;
}

/**
 *  Get free stack memory.
 * @return expression: Value of free bytes in stack.
 */
uint32_t XMCClass::freeRAM_Stack()	{
	extern uint32_t stack_size;
	uint32_t stack_end;
#if (UC_FAMILY == XMC4)
	extern uint32_t __stack_end;
	stack_end = (uint32_t)&__stack_end;

#elif	(UC_FAMILY == XMC1)
	stack_end = 536872216; // TODO: this value is hard coded, because no variable that stores this value
#endif
	return ((uint32_t)&stack_size - (stack_end - __get_MSP())); // total size minus the size of stack used up to now.
}
#if (UC_FAMILY == XMC4)	
/**
 * Configure hibernate. Set the wakeup source.
 * @param wkpsrc:
 * 			-RTC event (example is already given)
 * 			-Watchdog of RTC external crystal oscillator
 * 			-Digital Input Signal (HIB_IO_0 or HIB_IO_1)
 * 			-Analog Input Signal (HIB_IO_0 or HIB_IO_1)
 * 			-VBAT Supply Level Detection (VBAT)
*/
void XMCClass::configureHibernate(WakeupSource wkpsrc)
{

	/* Enable Hibernate Domain & Release reset of Hibernate Domain (if asserted) */
	XMC_SCU_HIB_EnableHibernateDomain();
	/* Configure the 32khz Ultra Low Power oscillator */
	XMC_SCU_CLOCK_EnableLowPowerOscillator();
	/* Select fSTDBY */
	XMC_SCU_HIB_SetStandbyClockSource(XMC_SCU_HIB_STDBYCLKSRC_OSCULP);
	
	switch (wkpsrc)	{
	case (WAKEUP_ON_RTC):	{
		/*Enable the RTC with Ultra Low Power Clock*/
		XMC_SCU_HIB_SetRtcClockSource(XMC_SCU_HIB_RTCCLKSRC_ULP);
		delay(3);
		/* Configure wake-up on RTC event*/
		XMC_SCU_HIB_EnableEvent(XMC_SCU_HIB_EVENT_WAKEUP_ON_RTC);
	}  break;  
	// TODO: Implement wake up on these other methods
	case (WAKEUP_ON_WATCHDOG):{}  break;  
	case (WAKEUP_ON_IN_SIGNAL_POS_EDGE):{}  break;  
	case (WAKEUP_ON_IN_SIGNAL_NEG_EDGE):{}  break;  
#if (defined(DOXYGEN) || (UC_SERIES == XMC44) || (UC_SERIES == XMC42) || (UC_SERIES == XMC41))
	case (WAKEUP_ON_VBAT_POSEDGE):{}  break;  
	case (WAKEUP_ON_VBAT_NEGEDGE):{}  break;  
#endif	
	}
	/*Digital outputs polarity*/
	XMC_SCU_HIB_SetPinOutputLevel(XMC_SCU_HIB_IO_0,XMC_SCU_HIB_IO_OUTPUT_LEVEL_LOW);
	
	/*Select hibernate control output and driver properties*/
	XMC_SCU_HIB_SetPinMode(XMC_SCU_HIB_IO_0,XMC_SCU_HIB_PIN_MODE_OUTPUT_PUSH_PULL_HIBCTRL);
	
	/*If necessary store data in retention memory */
}

/**
 *  Enter hibernate mode.
 * @param: mode: (check which one is supported on device)
 * 			EXTERNAL "1"
 * 			INTERNAL "2"
 */
void XMCClass::enterHibernate(int mode)
{
	hibernate = true;
	if(mode == 1)
		hibernate_mode = XMC_SCU_HIB_HIBERNATE_MODE_EXTERNAL;
#if ((UC_SERIES == XMC44) || (UC_SERIES == XMC42) || (UC_SERIES == XMC41))
	else if(mode == 2)
		hibernate_mode = XMC_SCU_HIB_HIBERNATE_MODE_INTERNAL;
#endif
	XMC_SCU_HIB_EnterHibernateStateEx(hibernate_mode);
}

/**
 *  Configure sleep mode.
 * @param 	type   (SLEEP_MODE or DEEP_SLEEP_MODE)
 * 			clk    (SYSCLK_FOFI or SYSCLK_FPLL)
 * 			usb    (USB_ON	or USB_OFF)
 * 			sdmmc  (ETH_ON or ETH_OFF)
 * 			ebu	   (EBU_ON or EBU_OFF)
 * 			ccu    (CCU_ON or CCU_OFF)
 * 			wdt    (WDT_ON or WDT_OFF)
 * 			flash  (FLASH_ON or FLASH_OFF) 	-- possible to turn off only on deep sleep mode
 * 			clkpll (PLL_ON or PLL_OFF)		-- possible to turn off only on deep sleep mode
 * 			vco    (VCO_ON or VCO_OFF)		-- possible to turn off only on deep sleep mode
 */
void XMCClass::configureSleepMode(sleepMode_t type, sysclock_t clk, usb_t usb, sdmmc_t sdmmc, eth0_t ethernet, ebu_t  ebu, ccu_t ccu , wdt_t wdt, flash_t flash, clkpll_t pll, vco_t vco)
{
	sleep_config |= clk;
#if defined(USB0)
	sleep_config |= usb;
#endif  
#if defined(SDMMC)
	sleep_config |= sdmmc;
#endif  		
#if defined(ETH0)
	sleep_config |= ethernet;
#endif
#if defined(EBU)
	sleep_config |= ebu;
#endif

	sleep_config |= ccu;
	sleep_config |= wdt;

	if(type == SLEEP_MODE )				{
		power_mode = XMC_SCU_POWER_MODE_SLEEP ;
		XMC_SCU_CLOCK_SetSleepConfig(sleep_config);
	}
	else if( type == DEEP_SLEEP_MODE)	{
		
		if(flash == FLASH_OFF)
			sleep_config |= flash;
		if(pll == PLL_OFF)
			sleep_config |= pll;
		if(vco == VCO_OFF)
			sleep_config |=vco;

		power_mode = XMC_SCU_POWER_MODE_DEEPSLEEP ;
		XMC_SCU_CLOCK_SetDeepSleepConfig(sleep_config);
	}
}

/* Device sleeps on exit of this function*/
void XMCClass::enterSleepMode()
{
	XMC_SCU_POWER_WaitForInterrupt(power_mode,1);
}

/**
 * Calibrate temperature sensor for more accurate measurement.
 * @param 	offset	- The range of the offset adjustment is 7 bits with a resolution that corresponds to +/- 12.5�C.
 * 					  The offset value gets added to the measure result.
 * 			gain	- 0, result is generated with maximum gain;  63, result is generated with least gain.
 */
void XMCClass::calibrateTemperatureSensor(uint32_t offset, uint32_t gain)
{
	//XMC_SCU_DisableTemperatureSensor();
	/*Stop measurement*/
	SCU_GENERAL-> DTSCON &= (uint32_t)~SCU_GENERAL_DTSCON_START_Msk;
	/*Calibrate*/
	XMC_SCU_CalibrateTemperatureSensor(offset,gain);
	/*Start measurements*/
	XMC_SCU_StartTemperatureMeasurement();
}
#endif

#if (UC_FAMILY == XMC1)
/**
 *  Configure sleep mode.
 * @param 	type   (SLEEP_MODE or DEEP_SLEEP_MODE)
 * 			usic   (USIC_ON or USIC_OFF)
 * 			ledt   (LEDT_ON	or LEDT_OFF)
 * 			wdt    (WDT_ON or WDT_OFF)
 * 			flash  (FLASH_ON or FLASH_OFF) -- possible to turn off only on deep sleep mode
 */
void XMCClass::configureSleepMode(sleepMode_t type, usic_t usic, ledt_t ledt, ccu_t ccu, wdt_t wdt, flash_t flash)
{
	sleep_config |= usic;
#if (defined (LEDTS0) || ( LEDTS1 )|| ( LEDTS2))
	sleep_config |= ledt;
#endif

	sleep_config |= wdt;
	sleep_config |= ccu;

	if(type == DEEP_SLEEP_MODE ){
		if(flash == FLASH_OFF)
			SCU_CLK -> PWRSVCR |= flash ;
	}

	SCU_CLK->CGATSET0 = sleep_config;	// Set sleep configuration
	VADC->CLC &= ~VADC_CLC_EDIS_Msk;	// Enable sleep control
	sleep_mode = type;					// Store sleep type
}
/* Device sleeps on exit of this function*/
void XMCClass::enterSleepMode()
{
		SCB->SCR = sleep_mode | SCB_SCR_SLEEPONEXIT_Msk;
	  __WFI();
}
#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
