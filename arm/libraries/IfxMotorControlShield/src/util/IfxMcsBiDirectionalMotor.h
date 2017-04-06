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
 
 
/*!	\file IfxMcsBiDirectionalMotor.h
 *	\brief This file declares the class IfxMcsBiDirectionalMotor
 *	
 *	It is automatically included by IfxMotorControlShield.h
 *	You can also directly include this file if you know 
 *	that you only want to use bidirectional motors
 *
 *	\see IfxMotorControlShield.h
 */
 
 
#ifndef IFX_MCS_BIDIRECTIONALMOTOR_H_INCLUDED
#define IFX_MCS_BIDIRECTIONALMOTOR_H_INCLUDED

#include "util/IfxMotorControlShieldUtil.h"



/*!	\brief	The rotation direction of a bidirectional motor	
 *
 *	Of course, the actual rotation direction depends on the way
 *	you connect the motor. Change the polarity of your motor if
 *	you want to swap LEFT and RIGHT. 
 */
enum IfxMcsDirection
{
	IFXMCS_LEFT,	//!< \brief anti-clockwise rotation
	IFXMCS_RIGHT	//!< \brief clockwise rotation
};

//!	\brief	The initial rotation direction of a bidirectional motor	
#define IFXMCS_DIRECTION_DEFAULT IFXMCS_RIGHT


/*!	\brief	Class that represents a bidirectional DC motor that is connected 
 *			to the MotorControlShield
 */
class IfxMcsBiDirectionalMotor
{
public: 

	/*!	\brief	Basic Constructor
	 *
	 *	This constructor requires two pointers two Halfbridge instances. 
	 *	These instances can be shared with other motors, but only one 
	 *	of them can be active at the same time. Call begin() and end()
	 *	to set the IfxMcsBiDirectionalMotor active and inactive. 
	 *
	 *	\param out1	a pointer to the first Halfbridge instance
	 *	\param out2 a pointer to the second Halfbridge instance
	 *
	 *	\see begin
	 *	\see end
	 */
	IfxMcsBiDirectionalMotor(IfxMcs::Halfbridge *out1, IfxMcs::Halfbridge *out2);
	
	/*!	\brief	Destructor
	 *
	 *	Makes sure the motor is stopped and inactive before deleting
	 */
	~IfxMcsBiDirectionalMotor(void);
	
	/*!	\brief	Prepares the IfxMcsBiDirectionalMotor for operation
	 *
	 *  The IfxMcsBiDirectionalMotor is set to active state. 
	 * 	This will fail if one of the corresponding Halfbridge instances is 
	 * 	already used by another active motor. 
	 *
	 *	\return bool that indicates a fail when true
	 */
	bool begin(void);
	
	/*!	\brief	Disables the IfxMcsBiDirectionalMotor
	 *
	 *	Sets the IfxMcsBiDirectionalMotor to inactive state.
	 *	This is necessary if you want to activate another motor using 
	 *	one of the corresponding Halfbridge instances. 
	 */
	void end(void);
	
	/*!	\brief	Starts the IfxMcsBiDirectionalMotor with maximum speed
	 *
	 *	Starts the motor with the highest available speed 
	 *	or does nothing if the IfxMcsBiDirectionalMotor has not been enabled yet. 
	 */
	void start();
	
	/*!	\brief	Starts the IfxMcsBiDirectionalMotor with custom speed
	 *
	 *	Starts the motor with custom speed 
	 *	or does nothing if the IfxMcsBiDirectionalMotor has not been enabled yet. 
	 *
	 *	\param direction	enum Value to indicate the rotation direction
	 *	\param speed		A numeric value from 0 (off) to 255 (highspeed)
	 */
	void start(IfxMcsDirection direction, uint8_t speed);
	
	/*!	\brief	Stops the IfxMcsBiDirectionalMotor
	 *
	 *	Stops the motor 
	 *	or does nothing if the IfxMcsBiDirectionalMotor has not been enabled yet. 
	 */
	void stop(void);
	
	/*!	\brief	Sets the direction of the motor
	 *	
	 *	can be called before or after start()
	 *
	 *	\param direction	A value from enum IfxMcsDirection
	 */
	void setDirection(IfxMcsDirection direction);
	
	/*!	\brief	Sets the speed of the motor
	 *	
	 *	can be called before or after start()
	 *
	 *	\param speed	A numeric value from 0 (off) to 255 (highspeed)
	 */
	void setSpeed(uint8_t speed);
	
	/*!	\brief	Sets the speed and direction of the motor
	 *	
	 *	can be called before or after start()
	 *
	 *	\param directedSpeed	A numeric value from -255 (full left) to 255 (full right)
	 */
	void setBiDirectionalSpeed(int32_t directedSpeed);
	
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
	
	/*!	\brief	Get-accessor for the motors direction
	 *
	 *	\see mDirection
	 *	\see IfxMcsDirection
	 *	\see setSpeed(uint8_t)
	 *
	 *	\return The motors current or preconfigured direction
	 */
	IfxMcsDirection getDirection(void);
	
	/*!	\brief	Get-accessor for the motors speed
	 *
	 *	\see mSpeed
	 *	\see setSpeed(uint8_t)
	 *
	 *	\return The motors current or preconfigured speed
	 */
	uint8_t getSpeed(void);
	
	/*!	\brief	Returns the speed and direction of the motor
	 *
	 *	\return A numeric value from -255 (full left) to 255 (full right)
	 */
	int32_t getBiDirectionalSpeed(void);
	
	/*!	\brief Returns a value proportional to the load current of the BTN8982
	 *	
	 *	Performs an analogRead on both CurrentSense pins and returns the highest result
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

	//!	\brief	Indicates if the IfxMcsBiDirectionalMotor is in active state
	bool mEnabled;
	
	//! \brief Indicates if the motor is currently running
	bool mRunning;
	
	//!	\brief	enum Value to indicate the rotation direction
	IfxMcsDirection mDirection;
	
	/*!	\brief	The motors current or preconfigured speed
	 *
	 *	If the motor is stopped, the speed will not be set to 0. 
	 *	It will be saved for the next start. 
	 */
	uint8_t mSpeed;
	
	//!	\brief	Pointer to the first Halfbridge instance which is connected to this motor
	IfxMcs::Halfbridge *mOut1;
	
	//!	\brief	Pointer to the first Halfbridge instance which is connected to this motor
	IfxMcs::Halfbridge *mOut2;
	
	//!	\brief	private function that writes out configuration to the motor
	void update(void);
};



//!	\brief	Pre-instantiated object for a bidirectional motor that can be connected between OUT1 and OUT2
extern IfxMcsBiDirectionalMotor ifxMcsBiDirectionalMotor;



#endif		/* IFX_MCS_BIDIRECTIONALMOTOR_H_INCLUDED */