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
 
/*!	\file IfxMcsUniDirectionalMotor.cpp
 *	\brief This file defines the functions for the class IfxMcsUniDirectionalMotor
 */
 
 
#include "util/IfxMcsUniDirectionalMotor.h"



//pre-instantiated objects
IfxMcsUniDirectionalMotor ifxMcsUniDirectionalMotor1 = IfxMcsUniDirectionalMotor(&(IfxMcs::out1));
IfxMcsUniDirectionalMotor ifxMcsUniDirectionalMotor2 = IfxMcsUniDirectionalMotor(&(IfxMcs::out2));


IfxMcsUniDirectionalMotor::IfxMcsUniDirectionalMotor(IfxMcs::Halfbridge *out)
{
	mEnabled = FALSE;
	mSpeed = 0U;
	mOut = out;
}


IfxMcsUniDirectionalMotor::~IfxMcsUniDirectionalMotor(void)
{
	end();
}


bool IfxMcsUniDirectionalMotor::begin(void)
{
	if(mOut->active == TRUE)
	{
		// It might be more intuitive to return true on success and not on fail
		// The advantage of using true on fail is that you can use an if-block as catch-block
		// Also this is for compatibility with other environments that use (int)0 to indicate
		// success and negative numbers to indicate fail		
		return TRUE;
	}
	mOut->active = TRUE;
	mEnabled = TRUE;
	pinMode(mOut->pinIn, OUTPUT);
	pinMode(mOut->pinInh, OUTPUT);
	pinMode(mOut->pinIs, INPUT);
	setSpeed(IFX_MCS_INITIALSPEED);
	stop();
	return FALSE;
}


void IfxMcsUniDirectionalMotor::end(void)
{
	if(mEnabled == FALSE)
	{
		return;
	}
	stop();
	mOut->active = FALSE;
	mEnabled = FALSE;
}


void IfxMcsUniDirectionalMotor::start(uint8_t speed)
{
	setSpeed(speed);
	start();
}


void IfxMcsUniDirectionalMotor::start(void)
{
	mRunning = TRUE;
	update();
}


void IfxMcsUniDirectionalMotor::stop(void)
{
	mRunning = FALSE;
	update();
}


void IfxMcsUniDirectionalMotor::setSpeed(uint8_t speed)
{
	mSpeed = speed;
	update();
}


bool IfxMcsUniDirectionalMotor::getEnabled()
{
	return mEnabled;
}


bool IfxMcsUniDirectionalMotor::getRunning()
{
	return mRunning;
}


uint8_t IfxMcsUniDirectionalMotor::getSpeed()
{
	return mSpeed;
}


uint32_t IfxMcsUniDirectionalMotor::getCurrentSense(void)
{
	return analogRead(mOut->pinIs);
}


void IfxMcsUniDirectionalMotor::update(void)
{
	if(mEnabled == FALSE)
	{
		return;
	}
	if(mSpeed < IFX_MCS_LOWESTSPEED)
	{
		mRunning = FALSE;
	}
	if(mRunning == FALSE)
	{
		// stop condition is different from running with speed 0 for two reasons: 
		// First, it does not use PWM. 
		// Second, it also sets INH to LOW, which seems more tidy in an off-condition. 
		digitalWrite(mOut->pinInh, LOW);
		pinMode(mOut->pinIn, OUTPUT);
		digitalWrite(mOut->pinIn, LOW);
		return;
	}
	if(mSpeed > IFX_MCS_HIGHESTSPEED)
	{
		// On-Off-Transitions are waste of power, especially for the BTN8982. 
		// On some devices there are even very short LOW peaks on the highest possible duty cycle. 
		// For very high duty cycles (which are close to 100%) it is better
		// to disable PWM, save energy and stop the motor completely. 
		pinMode(mOut->pinIn, OUTPUT);
		digitalWrite(mOut->pinIn, HIGH);
	}
	else
	{
		// this is actually not really analogue but PWM as expected by the BTN8982
		IfxMcs::ouputHfPwm(mOut->pinIn, mSpeed);
	}
	digitalWrite(mOut->pinInh, HIGH);
}

