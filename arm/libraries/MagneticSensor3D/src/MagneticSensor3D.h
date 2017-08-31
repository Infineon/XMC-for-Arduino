/*
 *	Arduino library to control Infineon's Magnetic 3D Sensor TLV493D-A1B6
 *
 *	Have a look at the datasheet for more information. 
 */


#ifndef MAGNETICSENSOR3D_H_INCLUDED
#define MAGNETICSENSOR3D_H_INCLUDED


#include <Arduino.h>
#include <Wire.h>
#include "./util/BusInterface.h"
#include "./util/TLV493D.h"
#include "./util/TLV493D_conf.h"

typedef enum Tlv493d_Address
{
	TLV493D_ADDRESS1	=	0x1F,
	TLV493D_ADDRESS2	=	0x5E
}Tlv493d_Address_t;


/*
 * TLV493D_ACCELERATE_READOUT lets the controller just read out the first 3 bytes when in fast mode. 
 * This makes the readout faster (half of usual transfer duration), but there is no way to get 
 * temperature, current channel or high precision (only 8 instead of 12 bits for x, y, z)
 * It is necessary for slow I2C busses to read the last result before the new measurement is completed. 
 * It only takes effect in FASTMODE, not in other modes. 
 *
 * Feel free to undefine this and increase your I2C bus speed if you need to. 
 */
#define TLV493D_ACCELERATE_READOUT


class Tlv493d
{
public: 

	Tlv493d(void);
	~Tlv493d(void);
	void begin(void);
	void begin(TwoWire &bus);
	void begin(TwoWire &bus, Tlv493d_Address_t slaveAddress, bool reset);
	void end(void);
	
	// sensor configuration
	/* sets the data access mode for TLE493D
	 * Tle493d is initially in POWERDOWNMODE
	 * use POWERDOWNMODE for rare and infrequent measurements 
	 * 	Tle493d will automatically switch to MASTERCONTROLLEDMODE for one measurement if on a readout
	 *	measurements are quite slow in this mode. The power consumption is very low between measurements. 
	 * use MASTERCONTROLLEDMODE for low measurement frequencies where results do not have to be up-to-date
	 *	In this mode a new measurement starts directly after the last result has been read out. 
	 * use LOWPOWERMODE and ULTRALOWPOWERMODE for continuous measurements
	 *	each readout returns the latest measurement results
	 * use FASTMODE for for continuous measurements on high frequencies
	 *	measurement time might be higher than the time necessary for I2C-readouts in this mode. 
	 */
	enum AccessMode_e
	{
		POWERDOWNMODE = 0,
		FASTMODE,
		LOWPOWERMODE,
		ULTRALOWPOWERMODE,
		MASTERCONTROLLEDMODE,
	};
	void setAccessMode(AccessMode_e mode);
	// interrupt is disabled by default
	// it is recommended for FASTMODE, LOWPOWERMODE and ULTRALOWPOWERMODE
	// the interrupt is indicated with a short(1.5 us) low pulse on SCL
	// you need to capture and react(read the new results) to it by yourself
	void enableInterrupt(void);
	void disableInterrupt(void);
	// temperature measurement is enabled by default
	// it can be disabled to reduce power consumption
	void enableTemp(void);
	void disableTemp(void);
	
	// returns the recommended time between two readouts for the sensor's current configuration
	uint16_t getMeasurementDelay(void);
	// read measurement results from sensor
	uint8_t updateData(void);
	
	// fieldvector in Cartesian coordinates
	float getX(void);
	float getY(void);
	float getZ(void);
	
	// fieldvector in spherical coordinates
	float getAmount(void);
	float getAzimuth(void);
	float getPolar(void);
	
	// temperature
	float getTemp(void);
	
private: 
	tlv493d::BusInterface_t mInterface;
	AccessMode_e mMode;
	int16_t mXdata;
	int16_t mYdata;
	int16_t mZdata;
	int16_t	mTempdata;
	

	void resetSensor(uint8_t adr);
	void setRegBits(uint8_t regMaskIndex, uint8_t data);
	uint8_t getRegBits(uint8_t regMaskIndex);
	void calcParity(void);
	int16_t concatResults(uint8_t upperByte, uint8_t lowerByte, bool upperFull);
};

extern Tlv493d magnetic3dSensor;

#endif		/* MAGNETICSENSOR3D_H_INCLUDED */
