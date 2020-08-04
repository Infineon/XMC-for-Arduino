/**
 * DeviceControlXMC.h - Library for Arduino to control extra device functions.
 *
 * The XMC series devices combine the extended functionality and performance of
 * the ARM Cortex-M0/4 core with powerful on-chip peripheral subsystems and on-chip
 * memory units. This library helps to control basic device functionalities.
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

#ifndef _DEVICECONTROLXMC_H_INCLUDED
#define _DEVICECONTROLXMC_H_INCLUDED
//****************************************************************************
// @Project Includes
//****************************************************************************
#include <xmc_scu.h>

extern const size_t total_heap_s;

//****************************************************************************
// @Enums
//****************************************************************************

enum sleepMode_t {
	SLEEP_MODE = 0 ,
	DEEP_SLEEP_MODE = SCB_SCR_SLEEPDEEP_Msk,
};

#if (UC_FAMILY == XMC4)
	enum  WakeupSource
	{
		WAKEUP_ON_RTC = XMC_SCU_HIB_EVENT_WAKEUP_ON_RTC,
		WAKEUP_ON_WATCHDOG = XMC_SCU_HIB_EVENT_ULPWDG,
		WAKEUP_ON_IN_SIGNAL_POS_EDGE = XMC_SCU_HIB_EVENT_WAKEUP_ON_POS_EDGE,
		WAKEUP_ON_IN_SIGNAL_NEG_EDGE = XMC_SCU_HIB_EVENT_WAKEUP_ON_NEG_EDGE,	//WAKEUP_ON_ANALOG_IN_SIGNAL,
		/*#if (defined(DOXYGEN) || (UC_SERIES == XMC44) || (UC_SERIES == XMC42) || (UC_SERIES == XMC41))
			WAKEUP_ON_VBAT_POSEDGE = XMC_SCU_HIB_EVENT_LPAC_VBAT_POSEDGE,
			WAKEUP_ON_VBAT_NEGEDGE = XMC_SCU_HIB_EVENT_LPAC_VBAT_NEGEDGE,
		#endif*/
	};

	enum sysclock_t {
		SYSCLK_FOFI = XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_SYSCLK_FOFI,
		SYSCLK_FPLL = XMC_SCU_CLOCK_SLEEP_MODE_CONFIG_SYSCLK_FPLL,
	};
	enum usb_t {
		USB_ON = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_ENABLE_USB,
		USB_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_USB,

	};
	enum sdmmc_t {
		SDMMC_ON = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_ENABLE_SDMMC,
		SDMMC_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_SDMMC,

	};
	enum eth0_t {
		ETH_ON = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_ENABLE_ETH,
		ETH_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_ETH,

	};
	enum ebu_t {
		EBU_ON = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_ENABLE_EBU,
		EBU_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_EBU,
	};
	enum ccu_t {
		CCU_ON = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_ENABLE_CCU,
		CCU_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_CCU,
	};
	enum wdt_t {
		WDT_ON = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_ENABLE_WDT,
		WDT_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_DISABLE_WDT,
	};
	enum flash_t {
		FLASH_ON ,
		FLASH_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_FLASH_POWERDOWN,
	};
	enum clkpll_t {
		PLL_ON,
		PLL_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_PLL_POWERDOWN,
	};
	enum vco_t {
		VCO_ON ,
		VCO_OFF = XMC_SCU_CLOCK_DEEPSLEEP_MODE_CONFIG_VCO_POWERDOWN,
	};

#elif(UC_FAMILY == XMC1)
	enum usic_t {
		USIC_ON = XMC_SCU_PERIPHERAL_CLOCK_USIC0 ,
		USIC_OFF = 0x00,
	};
	enum ledt_t {
	#if (defined (LEDTS0) || ( LEDTS1 )|| ( LEDTS2))
		LEDT_ON = XMC_SCU_PERIPHERAL_CLOCK_LEDTS0 | XMC_SCU_PERIPHERAL_CLOCK_LEDTS1,
	#endif
		LEDT_OFF = 0x00,
	};
	enum ccu_t {
	#if defined(CCU40)
		CCU_ON = XMC_SCU_PERIPHERAL_CLOCK_CCU40 ,
	#endif
		CCU_OFF = 0x00,
	};
	enum wdt_t {
		WDT_ON = SCU_CLK_CGATSTAT0_WDT_Msk,
		WDT_OFF = 0x00,
	};
	enum flash_t {
		FLASH_ON,
		FLASH_OFF = SCU_CLK_PWRSVCR_FPD_Msk,
	};
#endif

//****************************************************************************
// @Class Definitions
//****************************************************************************
class XMCClass
{
		// TODO: DMA is only available for M-M, or UART-M, M-UART
	public:
		/* Constructor */
		XMCClass()
		{
			temp_measurement_s = XMC_SCU_STATUS_ERROR;
			sleep = false;
			deep_sleep = false;
			sleep_config = 0x00;
			sleep_mode = SLEEP_MODE;
#if (UC_FAMILY == XMC4)
			power_mode = XMC_SCU_POWER_MODE_SLEEP;
#endif
		}

		void begin(); 				// Nothing in this function yet
		/* State Control*/
		int32_t getTemperature();	// Device Temperature control
		/*Power Control*/
		void enterActiveMode();		// Wake up from sleep. This function should be called in interrupt handler.
		void reset();				// Software reset of device

   		size_t freeHeapRAM();

#if (UC_FAMILY == XMC4)
		/* State Control*/
		void calibrateTemperatureSensor(uint32_t offset, uint32_t gain);	// Calibrate temperature
		/*Power Control*/
		void configureSleepMode(sleepMode_t type, sysclock_t clk, usb_t usb0, sdmmc_t sdmmc, eth0_t ethernet, ebu_t  ebu, ccu_t ccu , wdt_t wdt, flash_t flash, clkpll_t pll, vco_t vco);	// Configure sleep mode type & peripherals status on sleep/deep sleep mode
#elif(UC_FAMILY == XMC1)
		void configureSleepMode(sleepMode_t type, usic_t usic, ledt_t ledt, ccu_t ccu,wdt_t wdt, flash_t flash);	// Configure sleep mode type & peripherals status on sleep/deep sleep mode
#endif
		void enterSleepMode();							// Enter Sleep Mode, called after sleep mode is configured

	private:
		void init();							// Nothing in this function yet
		bool sleep;								// Set if sleep mode is active
		bool deep_sleep;						// Set if deep sleep mode is active
		int32_t sleep_config;					// Stores sleep configuration
		sleepMode_t sleep_mode;					// Stores type of sleep mode
		XMC_SCU_STATUS_t temp_measurement_s;	// Temperature measurement status

#if (UC_FAMILY == XMC4)
		XMC_SCU_POWER_MODE_t power_mode;
#endif
};

#endif /* _DEVICECONTROL_XMC_H_INCLUDED */
