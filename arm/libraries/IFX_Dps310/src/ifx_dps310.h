/**
 * Arduino library to control IFX_DPS310
 *
 * "IFX_DPS310" represents Infineon's high-sensetive pressure and temperature sensor. 
 * It measures in ranges of 300 - 1200 hPa and -40 and 85 °C. 
 * The sensor can be connected via SPI or I2C. 
 * It is able to perform single measurements
 * or to perform continuous measurements of temperature and pressure at the same time, 
 * and stores the results in a FIFO to reduce bus communication. 
 *
 * Have a look at the datasheet for more information. 
 */

#ifndef DPS310_ARDUINO_H_INCLUDED
#define DPS310_ARDUINO_H_INCLUDED

#include <SPI.h>
#include <Wire.h>
#include "util/ifx_dps310_consts.h"


class IFX_Dps310
{
	public:
		//constructor
		IFX_Dps310(void);
		//destructor
		~IFX_Dps310(void);
		//begin
		void begin(TwoWire &bus);
		void begin(TwoWire &bus, uint8_t slaveAddress);
		void begin(SPIClass &bus, int32_t chipSelect);
		void begin(SPIClass &bus, int32_t chipSelect, uint8_t threeWire);
		//end
		void end(void);

		//general
		uint8_t getProductId(void);
		uint8_t getRevisionId(void);

		//Idle Mode
		int16_t standby(void);

		//Command Mode
		int16_t measureTempOnce(int32_t &result);
		int16_t measureTempOnce(int32_t &result, uint8_t oversamplingRate);
		int16_t startMeasureTempOnce(void);
		int16_t startMeasureTempOnce(uint8_t oversamplingRate);
		int16_t measurePressureOnce(int32_t &result);
		int16_t measurePressureOnce(int32_t &result, uint8_t oversamplingRate);
		int16_t startMeasurePressureOnce(void);
		int16_t startMeasurePressureOnce(uint8_t oversamplingRate);
		int16_t getSingleResult(int32_t &result);

		//Background Mode
		int16_t startMeasureTempCont(uint8_t measureRate, uint8_t oversamplingRate);
		int16_t startMeasurePressureCont(uint8_t measureRate, uint8_t oversamplingRate);
		int16_t startMeasureBothCont(uint8_t tempMr, uint8_t tempOsr, uint8_t prsMr, uint8_t prsOsr);
		int16_t getContResults(int32_t *tempBuffer, uint8_t &tempCount, int32_t *prsBuffer, uint8_t &prsCount);

		//Interrupt Control
		int16_t setInterruptPolarity(uint8_t polarity);
		int16_t setInterruptSources(uint8_t fifoFull, uint8_t tempReady, uint8_t prsReady);
		int16_t getIntStatusFifoFull(void);
		int16_t getIntStatusTempReady(void);
		int16_t getIntStatusPrsReady(void);

		//function to fix a hardware problem on some devices
		int16_t correctTemp(void);

	private:
		//scaling factor table
		//for initialization see ifx_dps310.cpp
		static const int32_t scaling_facts[IFX_DPS310__NUM_OF_SCAL_FACTS];

		//enum for operating mode
		enum Mode
		{
			IDLE=0x00,
			CMD_PRS=0x01,
			CMD_TEMP=0x02,
			INVAL_OP_CMD_BOTH=0x03,		//invalid
			INVAL_OP_CONT_NONE=0x04, 	//invalid
			CONT_PRS=0x05,
			CONT_TMP=0x06,
			CONT_BOTH=0x07
		};
		Mode m_opMode;

		//flags
		uint8_t m_initFail;
		uint8_t m_productID;
		uint8_t m_revisionID;

		//settings
		uint8_t m_tempMr;
		uint8_t m_tempOsr;
		uint8_t m_prsMr;
		uint8_t m_prsOsr;
		uint8_t m_tempSensor;

		//compensation coefficients
		int32_t m_c0Half;
		int32_t m_c1;
		int32_t m_c00;
		int32_t m_c10;
		int32_t m_c01;
		int32_t m_c11;
		int32_t m_c20;
		int32_t m_c21;
		int32_t m_c30;
		//last measured scaled temperature
		//(necessary for pressure compensation)
		double m_lastTempScal;

		//bus specific
		uint8_t m_SpiI2c;	//0=SPI, 1=I2C
			//used for I2C
		TwoWire *m_i2cbus;
		uint8_t m_slaveAddress;
			//used for SPI
		SPIClass *m_spibus;
		int32_t m_chipSelect;
		uint8_t m_threeWire;


		//measurement
		void init(void);
		int16_t readcoeffs(void);
		int16_t setOpMode(uint8_t background, uint8_t temperature, uint8_t pressure);
		int16_t setOpMode(uint8_t opMode);
		int16_t configTemp(uint8_t temp_mr, uint8_t temp_osr);
		int16_t configPressure(uint8_t prs_mr, uint8_t prs_osr);
		uint16_t calcBusyTime(uint16_t temp_rate, uint16_t temp_osr);
		int16_t getTemp(int32_t *result);
		int16_t getPressure(int32_t *result);
		int16_t getFIFOvalue(int32_t *value);
		int32_t calcTemp(int32_t raw);
		int32_t calcPressure(int32_t raw);

		//bus specific
		int16_t readByte(uint8_t regAddress);
		int16_t readByteSPI(uint8_t regAddress);
		int16_t readBlock(uint8_t regAddress, uint8_t length, uint8_t *buffer);
		int16_t readBlockSPI(uint8_t regAddress, uint8_t length, uint8_t *readbuffer);
		int16_t writeByte(uint8_t regAddress, uint8_t data);
		int16_t writeByte(uint8_t regAddress, uint8_t data, uint8_t check);
		int16_t writeByteSpi(uint8_t regAddress, uint8_t data, uint8_t check);
		int16_t writeByteBitfield(uint8_t data, uint8_t regAddress, uint8_t mask, uint8_t shift);
		int16_t writeByteBitfield(uint8_t data, uint8_t regAddress, uint8_t mask, uint8_t shift, uint8_t check);
		int16_t readByteBitfield(uint8_t regAddress, uint8_t mask, uint8_t shift);

};


//preinstantiated object
extern IFX_Dps310 ifxDps310;

#endif	//DPS310_ARDUINO_H_INCLUDED
