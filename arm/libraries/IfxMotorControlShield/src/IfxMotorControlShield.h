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
 
/*!	\file IfxMotorControlShield.h
 *	\brief This file has to be included in projects that use Infineons DC Motor Control Shield with BTN8982
 */

#ifndef IFX_MOTORCONTROLSHIELD_H_INCLUDED
#define IFX_MOTORCONTROLSHIELD_H_INCLUDED


#include "util/IfxMcsUniDirectionalMotor.h"
#include "util/IfxMcsBiDirectionalMotor.h"


#endif		/* IFX_MOTORCONTROLSHIELD_H_INCLUDED */