/*
 *	Arduino library to control Infineon's Magnetic 3D Sensor TLV493D-A1B6
 *
 *	Have a look at the datasheet for more information. 
 */


#include "MagneticSensor3D.h"
#include "util/MagneticSensor3Dutil.h"
#include <math.h>


MagneticSensor3d magnetic3dSensor = MagneticSensor3d(Wire);


MagneticSensor3d::MagneticSensor3d(TwoWire &bus) : MagneticSensor3d(bus, MSENS3D_DEFAULTADDRESS)
{
}


MagneticSensor3d::MagneticSensor3d(TwoWire &bus, uint8_t slaveAddress)
{
	mBus = &bus;
	mSlaveAddress = slaveAddress;
}


MagneticSensor3d::~MagneticSensor3d(void)
{
	end();
}


void MagneticSensor3d::begin(void)
{
	delay(MSENS3D_STARTUPDELAY);
	mBus->begin(); 
	mBus->beginTransmission(mSlaveAddress); 
	mBus->write(0x00);
	mBus->write(MSENS3D_LOWPOWERMODECONFIG);
	mBus->endTransmission(TRUE);
	delay(MSENS3D_STARTUPDELAY);
	updateData();
}


void MagneticSensor3d::end(void)
{
	mBus->beginTransmission(mSlaveAddress); 
	mBus->write(0x00);
	mBus->write(MSENS3D_POWERDOWNMODECONFIG);
	mBus->endTransmission(TRUE);
}


void MagneticSensor3d::updateData()
{
	int8_t registers[MSENS3D_UPDATEBLOCKSIZE];
	do
	{
		uint8_t len = Wire.requestFrom(mSlaveAddress, MSENS3D_UPDATEBLOCKSIZE);    //Request data from the Sensor
		for(uint8_t i=0; i<len; i++)
		{
			registers[i] = Wire.read();
		}
		Wire.endTransmission(TRUE);
	} while( (registers[MSENS3D_CHANNEL_REGADR] & MSENS3D_CHANNEL_REGMASK != 0x00)
		||   (registers[MSENS3D_POWERDOWN_REGADR] & MSENS3D_POWERDOWN_REGMASK != 0x00) );
	
	mXdata = (static_cast<int16_t>(registers[MSENS3D_XUPPER_REGADR] & MSENS3D_XUPPER_REGMASK)) << MSENS3D_XUPPER_REGSHIFT;
	mXdata |= static_cast<uint16_t>((registers[MSENS3D_XLOWER_REGADR] >> MSENS3D_XLOWER_REGSHIFT) & MSENS3D_XLOWER_REGMASK);
	if(mXdata > MSENS3D_12BITMSB)
	{
		mXdata -= MSENS3D_13BITMSB;
	}
	
	mYdata = (static_cast<int16_t>(registers[MSENS3D_YUPPER_REGADR] & MSENS3D_YUPPER_REGMASK)) << MSENS3D_YUPPER_REGSHIFT;
	mYdata |= static_cast<uint16_t>((registers[MSENS3D_YLOWER_REGADR] >> MSENS3D_YLOWER_REGSHIFT) & MSENS3D_YLOWER_REGMASK);
	if(mYdata > MSENS3D_12BITMSB)
	{
		mYdata -= MSENS3D_13BITMSB;
	}
	
	mZdata = (static_cast<int16_t>(registers[MSENS3D_ZUPPER_REGADR] & MSENS3D_ZUPPER_REGMASK)) << MSENS3D_ZUPPER_REGSHIFT;
	mZdata |= static_cast<uint16_t>((registers[MSENS3D_ZLOWER_REGADR] >> MSENS3D_ZLOWER_REGSHIFT) & MSENS3D_ZLOWER_REGMASK);
	if(mZdata > MSENS3D_12BITMSB)
	{
		mZdata -= MSENS3D_13BITMSB;
	}
	
	mTempdata = (static_cast<int16_t>(registers[MSENS3D_TUPPER_REGADR] & MSENS3D_TUPPER_REGMASK)) << MSENS3D_TUPPER_REGSHIFT;
	mTempdata |= static_cast<uint16_t>((registers[MSENS3D_TLOWER_REGADR] >> MSENS3D_TLOWER_REGSHIFT) & MSENS3D_TLOWER_REGMASK);
	if(mTempdata > MSENS3D_12BITMSB)
	{
		mTempdata -= MSENS3D_13BITMSB;
	}
}


float MagneticSensor3d::getX(void)
{
	return static_cast<float>(mXdata) * MSENS3D_B_MULT + MSENS3D_B_OFFSET;
}


float MagneticSensor3d::getY(void)
{
	return static_cast<float>(mYdata) * MSENS3D_B_MULT + MSENS3D_B_OFFSET;
}


float MagneticSensor3d::getZ(void)
{
	return static_cast<float>(mZdata) * MSENS3D_B_MULT + MSENS3D_B_OFFSET;
}


float MagneticSensor3d::getTemp(void)
{
	return static_cast<float>(mTempdata) * MSENS3D_TEMP_MULT + MSENS3D_TEMP_OFFSET;
}


float MagneticSensor3d::getAmount(void)
{
	// sqrt(x^2 + y^2 + z^2)
	return MSENS3D_B_MULT * sqrt(pow(static_cast<float>(mXdata), 2) + pow(static_cast<float>(mYdata), 2) + pow(static_cast<float>(mZdata), 2));
}


float MagneticSensor3d::getAzimuth(void)
{
	// arctan(y/x)
	return atan2(static_cast<float>(mYdata), static_cast<float>(mXdata));
}


float MagneticSensor3d::getPolar(void)
{
	// arctan(z/(sqrt(x^2+y^2)))
	return atan2(static_cast<float>(mZdata), sqrt(pow(static_cast<float>(mXdata), 2) + pow(static_cast<float>(mYdata), 2)));
}

