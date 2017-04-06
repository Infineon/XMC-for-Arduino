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
 
/*!	\file IfxMcsBiDirectionalMotor.cpp
 *	\brief This file defines the functions for the class IfxMcsBiDirectionalMotor
 */
 
 
#include "util/IfxMcsBiDirectionalMotor.h"


//pre-instantiated object
IfxMcsBiDirectionalMotor ifxMcsBiDirectionalMotor = IfxMcsBiDirectionalMotor(&(IfxMcs::out1), &(IfxMcs::out2));


IfxMcsBiDirectionalMotor::IfxMcsBiDirectionalMotor(IfxMcs::Halfbridge *out1, IfxMcs::Halfbridge *out2)
{
	mEnabled = FALSE;
	mDirection = IFXMCS_RIGHT;
	mSpeed = 0U;
	mOut1 = out1;
	mOut2 = out2;
}


IfxMcsBiDirectionalMotor::~IfxMcsBiDirectionalMotor(void)
{
	end();
}


bool IfxMcsBiDirectionalMotor::begin(void)
{
	if(mOut1->active == TRUE || mOut2->active)
	{
		// It might be more intuitive to return true on success and not on fail
		// The advantage of using true on fail is that you can use an if-block as catch-block
		// Also this is for compatibility with other environments that use (int)0 to indicate
		// success and negative numbers to indicate fail		
		return TRUE;
	}
	mOut1->active = TRUE;
	mOut2->active = TRUE;
	mEnabled = TRUE;
	pinMode(mOut1->pinIn, OUTPUT);
	pinMode(mOut1->pinInh, OUTPUT);
	pinMode(mOut1->pinIs, INPUT);
	pinMode(mOut2->pinIn, OUTPUT);
	pinMode(mOut2->pinInh, OUTPUT);
	pinMode(mOut2->pinIs, INPUT);
	setDirection(IFXMCS_DIRECTION_DEFAULT);
	setSpeed(IFX_MCS_INITIALSPEED);
	stop();
	return FALSE;
}


void IfxMcsBiDirectionalMotor::end(void)
{
	if(mEnabled == FALSE)
	{
		return;
	}
	stop();
	mOut1->active = FALSE;
	mOut2->active = FALSE;
	mEnabled = FALSE;
}


void IfxMcsBiDirectionalMotor::start(IfxMcsDirection direction, uint8_t speed)
{
	setDirection(direction);
	setSpeed(speed);
	start();
}


void IfxMcsBiDirectionalMotor::start(void)
{
	mRunning = TRUE;
	update();
}


void IfxMcsBiDirectionalMotor::stop(void)
{
	mRunning = FALSE;
	update();
}


void IfxMcsBiDirectionalMotor::setDirection(IfxMcsDirection direction)
{
	mDirection = direction;
	update();
}


void IfxMcsBiDirectionalMotor::setSpeed(uint8_t speed)
{
	mSpeed = speed;
	update();
}


void IfxMcsBiDirectionalMotor::setBiDirectionalSpeed(int32_t directedSpeed)
{	
	if(directedSpeed < 0)
	{
		setDirection(IFXMCS_LEFT);
		setSpeed((uint8_t)(-directedSpeed));
	}
	else
	{
		setDirection(IFXMCS_RIGHT);
		setSpeed((uint8_t)directedSpeed);
	}
}


bool IfxMcsBiDirectionalMotor::getEnabled(void)
{
	return mEnabled;
}


bool IfxMcsBiDirectionalMotor::getRunning(void)
{
	return mRunning;
}


IfxMcsDirection IfxMcsBiDirectionalMotor::getDirection(void)
{
	return mDirection;
}


uint8_t IfxMcsBiDirectionalMotor::getSpeed(void)
{
	return mSpeed;
}

int32_t IfxMcsBiDirectionalMotor::getBiDirectionalSpeed(void)
{
	if(mDirection == IFXMCS_LEFT)
	{
		return -mSpeed;
	}
	else
	{
		return mSpeed;
	}
}

uint32_t IfxMcsBiDirectionalMotor::getCurrentSense(void)
{
	uint32_t a = analogRead(mOut1->pinIs);
	uint32_t b = analogRead(mOut2->pinIs);
	return (a > b ? a : b);
}


void IfxMcsBiDirectionalMotor::update(void)
{
	IfxMcs::Halfbridge *pwmOut;
	IfxMcs::Halfbridge *gndOut;
	
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
		digitalWrite(mOut1->pinInh, LOW);
		pinMode(mOut1->pinIn, OUTPUT);
		digitalWrite(mOut1->pinIn, LOW);
		digitalWrite(mOut2->pinInh, LOW);
		pinMode(mOut2->pinIn, OUTPUT);
		digitalWrite(mOut2->pinIn, LOW);
		return;
	}
	if(mDirection == IFXMCS_RIGHT)
	{
		pwmOut = mOut1;
		gndOut = mOut2;
	}
	else
	{
		pwmOut = mOut2;
		gndOut = mOut1;
	}
	if(mSpeed > IFX_MCS_HIGHESTSPEED)
	{
		// on some devices, PWM still has very short low peaks even on the highest possible
		// duty cycles. On-Off transitions are a waste of power, especially for the BTN8982. 
		// To avoid this, we disable PWM, which would not have anything to do here anyway. 
		pinMode(pwmOut->pinIn, OUTPUT);
		digitalWrite(pwmOut->pinIn, HIGH);
	}
	else
	{
		// this is actually not really analogue but PWM as expected by the BTN8982
		IfxMcs::ouputHfPwm(pwmOut->pinIn, mSpeed);
	}
	pinMode(gndOut->pinIn, OUTPUT);
	digitalWrite(gndOut->pinIn, LOW);
	digitalWrite(mOut1->pinInh, HIGH);
	digitalWrite(mOut2->pinInh, HIGH);
}

