/*
 *	Arduino library to control Infineon's Magnetic 3D Sensor TLV493D-A1B6
 *
 *	Have a look at the datasheet for more information. 
 */


#ifndef MAGNETICSENSOR3D_H_INCLUDED
#define MAGNETICSENSOR3D_H_INCLUDED


#include <Arduino.h>
#include <Wire.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif



class MagneticSensor3d
{
public: 
	MagneticSensor3d(TwoWire &bus);
	MagneticSensor3d(TwoWire &bus, uint8_t address);
	~MagneticSensor3d(void);
	void begin(void);
	void end(void);
	
	//read data from sensor
	void updateData(void);
	
	// fieldvector in Cartesian coordinates
	float getX(void);
	float getY(void);
	float getZ(void);
	
	// fieldvector in spherical coordinates
	float getAmount(void);
	float getAzimuth(void);
	float getPolar(void);
	
	float getTemp(void);
private: 
	TwoWire *mBus;
	uint8_t mSlaveAddress;
	int16_t mXdata;
	int16_t mYdata;
	int16_t mZdata;
	int16_t	mTempdata;
};

extern MagneticSensor3d magnetic3dSensor;

#endif		/* MAGNETICSENSOR3D_H_INCLUDED */