/*
 *	Arduino library to control Infineons DC Motor Control Shield with BTN8982
 *
 *	The shield contains two independent halfbridges, 
 *	so it can drive two unidirectional or one bidirectional DC motor(s). 
 *	Each halfbridge provides a high-Voltage (nominal 8-18 V) and high-Current (max 30 A due to limited power dissipation) tristate output,  
 *	which is also capable of high frequency PWM. 
 *	There are also two analog diagnostic outputs which indicate the temperature of both BTN8982
 *
 *	Have a look at the datasheet for more information. 
 */
 
/*!	\file IfxMotorControlShieldUtil.cpp
 *	This file contains some non-public utilities for Infineons DC Motor Control Shield with BTN8982
 */

 
#include "util/IfxMotorControlShieldUtil.h"




static uint8_t _writeResolution = 8;


namespace IfxMcs
{
	
	// pre-instantiated Halfbridge instances
	Halfbridge out1 = { .active = FALSE, .pinIn = 3, .pinInh = 12, .pinIs = A0 };
	Halfbridge out2 = { .active = FALSE, .pinIn = 11, .pinInh = 13, .pinIs = A1 };
	
	
	
	//private helpfunction to replace analogWrite on PWM4 for XMC Controllers
	void outputHfPwmOnPwm4(XMC_PWM4_t *pwm4, uint16_t value)
	{
		uint32_t compare_reg = 0;
		
		if (!pwm4->enabled) 
		{
			// Slice not yet initialized
			XMC_CCU4_SLICE_COMPARE_CONFIG_t pwm_config = {0};
			pwm_config.passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_HIGH;
			pwm_config.prescaler_initval = pwm4->prescaler;
			
			XMC_CCU4_Init(pwm4->ccu, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
			XMC_CCU4_SLICE_CompareInit(pwm4->slice, &pwm_config);
			XMC_CCU4_EnableClock(pwm4->ccu, pwm4->slice_num);
			XMC_CCU4_SLICE_SetTimerPeriodMatch(pwm4->slice, pwm4->period_timer_val);
			
			pwm4->enabled = ENABLED;
		} 
	
		if (value != 0)
		{
			compare_reg  = (((value + 1) * pwm4->period_timer_val) >> _writeResolution);
		}
		
		XMC_CCU4_SLICE_SetTimerCompareMatch(pwm4->slice, compare_reg);
		XMC_CCU4_EnableShadowTransfer(pwm4->ccu, (CCU4_GCSS_S0SE_Msk << (4*pwm4->slice_num)));
		XMC_GPIO_SetMode(pwm4->port_pin.port,pwm4->port_pin.pin, static_cast<XMC_GPIO_MODE_t>(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | static_cast<uint32_t>(pwm4->port_mode)));
		XMC_CCU4_SLICE_StartTimer(pwm4->slice);
	}
	
	
	
	void ouputHfPwm(uint8_t pin, uint8_t dutyCycle)
	{
#ifdef ARDUINO_ARM_XMC
		
#ifdef XMC1100_Boot_Kit
		if(pin == 3)
		{
			//mapping_pwm4[0] is the entry for pin 3
			XMC_PWM4_t pwm4 = mapping_pwm4[0];
			//change some presettings for this slice
			//this should increase the frequency to 8kHz
			pwm4.prescaler = XMC_CCU4_SLICE_PRESCALER_4;
			//pwm4.period_timer_val = 125U;
			
			outputHfPwmOnPwm4(&pwm4, dutyCycle);
		}
		else if(pin == 11)
		{
			//mapping_pwm4[1] has to be the entry for pin 11
			XMC_PWM4_t pwm4 = mapping_pwm4[1];
			//change some presettings for this slice
			//the ccu4 slice we need for this pin is originally assigned to pin 4
			//we have to correct this and hope that no one will need a PWM on pin 4
			pwm4.port_pin = mapping_port_pin[11];
			pwm4.port_mode = P1_1_AF_CCU40_OUT1;
			//this should increase the frequency to 8kHz
			pwm4.prescaler = XMC_CCU4_SLICE_PRESCALER_4;
			//pwm4.period_timer_val = 125U;
			
			outputHfPwmOnPwm4(&pwm4, dutyCycle);
		}	
		else
		{
			//not expected. use standard behaviour
			analogWrite(pin, dutyCycle);
		}
		return;
#endif	/* XMC1100_Boot_Kit */

#ifdef XMC4700_Relax_Kit
		if(pin == 3)
		{
			XMC_PWM4_t pwm4 = mapping_pwm4[0];
			pwm4.prescaler = XMC_CCU4_SLICE_PRESCALER_4;
			//pwm4.period_timer_val = 125U;			
			outputHfPwmOnPwm4(&pwm4, dutyCycle);
		}
		else if(pin == 11)
		{
			XMC_PWM4_t pwm4 = mapping_pwm4[2];
			pwm4.prescaler = XMC_CCU4_SLICE_PRESCALER_4;
			//pwm4.period_timer_val = 125U;
			outputHfPwmOnPwm4(&pwm4, dutyCycle);
		}	
		else
		{
			//not expected. use standard behaviour
			analogWrite(pin, dutyCycle);
		}
		return;
#endif	/* XMC4700_Relax_Kit */

#ifdef XMC4800_Relax_Kit
		if(pin == 3)
		{
			XMC_PWM4_t pwm4 = mapping_pwm4[0];
			pwm4.prescaler = XMC_CCU4_SLICE_PRESCALER_4;
			//pwm4.period_timer_val = 125U;			
			outputHfPwmOnPwm4(&pwm4, dutyCycle);
		}
		else if(pin == 11)
		{
			XMC_PWM4_t pwm4 = mapping_pwm4[2];
			pwm4.prescaler = XMC_CCU4_SLICE_PRESCALER_4;
			//pwm4.period_timer_val = 125U;
			outputHfPwmOnPwm4(&pwm4, dutyCycle);
		}	
		else
		{
			//not expected. use standard behaviour
			analogWrite(pin, dutyCycle);
		}
		return;
#endif	/* XMC4800_Relax_Kit */


#endif	/* ARDUINO_ARM_XMC */
		//no special support for this board. Use standard PWM
		analogWrite(pin, dutyCycle);
	}
	


	
}