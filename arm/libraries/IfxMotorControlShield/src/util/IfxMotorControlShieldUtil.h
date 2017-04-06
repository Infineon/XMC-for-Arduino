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
 
/*!	\file IfxMotorControlShieldUtil.h
 *	This file contains some non-public utilities for Infineons DC Motor Control Shield with BTN8982
 */


#ifndef IFX_MOTORCONTROLSHIELD_UTIL_H_INCLUDED
#define IFX_MOTORCONTROLSHIELD_UTIL_H_INCLUDED


#include <Arduino.h>


/*!	\brief the lowest duty cycle where PWM is used
 *
 *	On-Off-Transitions are waste of power, especially for the BTN8982. 
 *	On some devices there are even very short HIGH peaks on the lowest possible duty cycle. 
 *	For very low duty cycles (which are too low for the motor to run at all) it is better
 *	to disable PWM, save energy and stop the motor completely. 
 *
 *	\warning This has to be more than 0 and much less than IFX_MCS_HIGHESTSPEED
 */
#define IFX_MCS_LOWESTSPEED 1U

/*!	\brief the lowest duty cycle where PWM is used
 *
 *	On-Off-Transitions are waste of power, especially for the BTN8982. 
 *	On some devices there are even very short LOW peaks on the highest possible duty cycle. 
 *	For very high duty cycles (which are close to 100%) it is better
 *	to disable PWM, save energy and stop the motor completely. 
 *
 *	\warning This has to be less than 255 and much more than IFX_MCS_LOWESTSPEED
 */
#define IFX_MCS_HIGHESTSPEED 254U


/*!	\brief the initial speed for motors
 *
 *	If start is called for the first time without any speed configuration, 
 *	this value will be used as default. 
 *
 *	\warning This has to be a number from 0 to 255
 */
#define IFX_MCS_INITIALSPEED 255U


/*! \brief limit for currentSense value
 *
 *	If getCurrentSense() returns a value greater than this, 
 *	the BTN8982 has recognized an error condition. 
 *	It is recommended to call getCurrentSense() periodically while a motor is running
 *	to recognize error conditions by comparing the return with this or a smaller value. 
 *
 *	\see IfxMcsUniDirectionalMotor::getCurrentSense(void)
 *	\see IfxMcsBiDirectionalMotor::getCurrentSense(void)
 */
#define IFX_MCS_CRITICALCURRENTSENSE 800U


//! \brief non-public utilities that are not intended for use outside of this library 
namespace IfxMcs
{
	
	//!	\brief	struct that represents a BTN8982 Halfbridge on the MotorControlShield
	typedef struct {
		bool active;		//!< \brief Indicates if The Halfbridge is in use
		uint8_t pinIn;		//!< \brief Pinnumber of the Input pin
		uint8_t pinInh;		//!< \brief Pinnumber of the Inhibit pin
		uint8_t pinIs;		//!< \brief Pinnumber of the Current Sense and Diagnostic pin
	} Halfbridge;
	
	//!	\brief	pre-instantiated Halfbridge instance for connector OUT1
	extern Halfbridge out1;
	
	//!	\brief	pre-instantiated Halfbridge instance for connector OUT2
	extern Halfbridge out2;
	
	/*!	\brief	output high-frequency PWM
	 *
	 *	high frequency should make the connected DC motor run smoother
	 *
	 *	\param pin	the number of the pin that is set to high-frequency PWM
	 *
	 *	\warning	This is very board-specific and will only work on supported boards
	 *				On other boards, it will call analogWrite instead, which uses 490 Hz
	 *				Unfortunately there is no generic way to set the PWM frequency
	 *				on all Arduino boards. If you want to add support for your
	 *				non-Infineon-Board in your project, feel free to edit the code 
	 *				of this function so that it fits for your purposes. 
	 *				(or buy an Infineon XMC :D)
	 */
	void ouputHfPwm(uint8_t pin, uint8_t dutyCycle);
	
}


#endif		/* IFX_MOTORCONTROLSHIELD_UTIL_H_INCLUDED */