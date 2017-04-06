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
 
 
/*!	\file IfxMcsUniDirectionalMotor.h
 *	\brief This file declares the class IfxMcsUniDirectionalMotor
 *	
 *	It is automatically included by IfxMotorControlShield.h
 *	You can also directly include this file if you know 
 *	that you only want to use unidirectional motors
 *
 *	\see IfxMotorControlShield.h
 */
 
 
#ifndef IFX_MCS_UNIDIRECTIONALMOTOR_H_INCLUDED
#define IFX_MCS_UNIDIRECTIONALMOTOR_H_INCLUDED

#include "util/IfxMotorControlShieldUtil.h"



/*!	\brief	Class that represents a unidirectional DC motor that is connected 
 *			to the MotorControlShield
 */
class IfxMcsUniDirectionalMotor
{
public: 

	/*!	\brief	Basic Constructor
	 *
	 *	This constructor requires a pointer to a Halfbridge instance. 
	 *	This instance can be shared with other motors, but only one 
	 *	of them can be active at the same time. Call begin() and end()
	 *	to set the IfxMcsUniDirectionalMotor active and inactive. 
	 *
	 *	\param out	a pointer to a Halfbridge instance
	 *
	 *	\see begin
	 *	\see end
	 */
	IfxMcsUniDirectionalMotor(IfxMcs::Halfbridge *out);
	
	/*!	\brief	Destructor
	 *
	 *	Makes sure the motor is stopped and inactive before deleting
	 */
	~IfxMcsUniDirectionalMotor(void);
	
	/*!	\brief	Prepares the IfxMcsUniDirectionalMotor for operation
	 *
	 *  The IfxMcsUniDirectionalMotor is set to active state. 
	 * 	This will fail if the corresponding Halfbridge instance is 
	 * 	already used by another active motor. 
	 *
	 *	\return bool that indicates a fail when true
	 */
	bool begin(void);
	
	/*!	\brief	Disables the IfxMcsUniDirectionalMotor
	 *
	 *	Sets the IfxMcsUniDirectionalMotor to inactive state.
	 *	This is necessary if you want to activate another motor using 
	 *	the same Halfbridge instance. 
	 */
	void end(void);
	
	/*!	\brief	Starts the IfxMcsUniDirectionalMotor with maximum speed
	 *
	 *	Starts the motor with the last used or configured speed
	 *	On the first start, IFX_MCS_INITIALSPEED is used as default preconfiguration
	 *	or does nothing if the IfxMcsUniDirectionalMotor has not been enabled yet. 
	 *
	 *	\see IFX_MCS_INITIALSPEED
	 */
	void start(void);
	
	/*!	\brief	Starts the IfxMcsUniDirectionalMotor with custom speed
	 *
	 *	Starts the motor with custom speed 
	 *	or does nothing if the IfxMcsUniDirectionalMotor has not been enabled yet. 
	 *
	 *	\param speed	A numeric value from 0 (off) to 255 (highspeed)
	 */
	void start(uint8_t speed);
	
	/*!	\brief	Stops the IfxMcsUniDirectionalMotor
	 *
	 *	Stops the motor 
	 *	or does nothing if the IfxMcsUniDirectionalMotor has not been enabled yet. 
	 */
	void stop(void);
	
	/*!	\brief	Sets the speed of the motor
	 *	
	 *	can be called before or after start()
	 *
	 *	\param speed	A numeric value from 0 (off) to 255 (highspeed)
	 */
	void setSpeed(uint8_t speed);
	
	/*!	\brief	Indicates if the motor is enabled for usage
	 *
	 *	\see begin()
	 *	\see end()
	 *	\see mSpeed
	 *
	 *	\return The motors current or preconfigured speed
	 */
	bool getEnabled(void);
	
	/*!	\brief	Indicates if the motor is currently running
	 *
	 *	\see mRunning
	 *	\see start()
	 *	\see start(uint8_t)
	 *	\see stop()
	 *
	 *	\return TRUE if the motor is running, FALSE otherwise
	 */
	bool getRunning(void);
	
	/*!	\brief	Get-accessor for the motors speed
	 *
	 *	\see mSpeed
	 *	\see setSpeed(uint8_t)
	 *
	 *	\return The motors current or preconfigured speed
	 */
	uint8_t getSpeed(void);

	
	/*!	\brief Returns a value proportional to the load current of the BTN8982
	 *	
	 *	Performs an analogRead on the CurrentSense pin and returns the result
	 *	The Output of this pin does not only depend on the load current, but also 
	 *	on other factors like temperature, voltage, etc
	 *	If the returned value is greater than IFX_MCS_CRITICALCURRENTSENSE, 
	 *	the BTN8982 is in an error condition (e.g. overtemperature, shortcircuit, undervoltage)
	 *	In this case, you should call stop() for at least 4 microseconds. 
	 * 	The IS pin might keep indicating an error condition for up to 420 microseconds
	 *	after the error has been cleared. 
	 *
	 *	\see IFX_MCS_CRITICALCURRENTSENSE
	 *
	 *	\return a value proportional to the load current of the BTN8982
	 */
	uint32_t getCurrentSense(void);
	
	
private: 

	//!	\brief	Indicates if the IfxMcsUniDirectionalMotor is in active state
	bool mEnabled;
	
	//! \brief Indicates if the motor is currently running
	bool mRunning;
	
	/*!	\brief	The motors current or preconfigured speed
	 *
	 *	If the motor is stopped, the speed will not be set to 0. 
	 *	It will be saved for the next start. 
	 */
	uint8_t mSpeed;
	
	//!	\brief	Pointer to the Halfbridge instance which is connected to this motor
	IfxMcs::Halfbridge *mOut;
	
	//!	\brief	private function that writes out configuration to the motor
	void update(void);
};



//!	\brief	Pre-instantiated object for a unidirectional motor that can be connected at OUT1
extern IfxMcsUniDirectionalMotor ifxMcsUniDirectionalMotor1;

//!	\brief	Pre-instantiated object for a unidirectional motor that can be connected at OUT2
extern IfxMcsUniDirectionalMotor ifxMcsUniDirectionalMotor2;


#endif		/* IFX_MCS_UNIDIRECTIONALMOTOR_H_INCLUDED */