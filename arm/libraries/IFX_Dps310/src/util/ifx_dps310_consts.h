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

#ifndef IFX_DPS310_CONSTS_H_
#define IFX_DPS310_CONSTS_H_


	//general Constants
#define IFX_DPS310__PROD_ID						0U
#define IFX_DPS310__STD_SLAVE_ADDRESS 			0x77U
#define IFX_DPS310__SPI_WRITE_CMD 				0x00U
#define IFX_DPS310__SPI_READ_CMD 				0x80U
#define IFX_DPS310__SPI_RW_MASK 				0x80U
#define IFX_DPS310__SPI_MAX_FREQ 				100000U

#define IFX_DPS310__LSB 0x01U

#define IFX_DPS310__TEMP_STD_MR					2U
#define IFX_DPS310__TEMP_STD_OSR				3U
#define IFX_DPS310__PRS_STD_MR					2U
#define IFX_DPS310__PRS_STD_OSR					3U
#define IFX_DPS310__OSR_SE 						3U
//we use 0.1 mS units for time calculations, so 10 units are one millisecond
#define IFX_DPS310__BUSYTIME_SCALING 			10U
// DPS310 has 10 milliseconds of spare time for each synchronous measurement / per second for asynchronous measurements
// this is for error prevention on friday-afternoon-products :D
// you can set it to 0 if you dare, but there is no warranty that it will still work
#define IFX_DPS310__BUSYTIME_FAILSAFE			10U
#define IFX_DPS310__MAX_BUSYTIME 				((1000U-IFX_DPS310__BUSYTIME_FAILSAFE)*IFX_DPS310__BUSYTIME_SCALING)
#define IFX_DPS310__NUM_OF_SCAL_FACTS			8

#define IFX_DPS310__SUCCEEDED 					0
#define IFX_DPS310__FAIL_UNKNOWN 				-1
#define IFX_DPS310__FAIL_INIT_FAILED 			-2
#define IFX_DPS310__FAIL_TOOBUSY 				-3
#define IFX_DPS310__FAIL_UNFINISHED 			-4


	//Constants for register manipulation
			//SPI mode (3 or 4 wire)
#define IFX_DPS310__REG_ADR_SPI3W 				0x09U
#define IFX_DPS310__REG_CONTENT_SPI3W 			0x01U


			//product id
#define IFX_DPS310__REG_INFO_PROD_ID 			IFX_DPS310__REG_ADR_PROD_ID, \
												IFX_DPS310__REG_MASK_PROD_ID, \
												IFX_DPS310__REG_SHIFT_PROD_ID
#define IFX_DPS310__REG_ADR_PROD_ID 			0x0DU
#define IFX_DPS310__REG_MASK_PROD_ID 			0x0FU
#define IFX_DPS310__REG_SHIFT_PROD_ID 			0U

			//revision id
#define IFX_DPS310__REG_INFO_REV_ID 			IFX_DPS310__REG_ADR_REV_ID, \
												IFX_DPS310__REG_MASK_REV_ID, \
												IFX_DPS310__REG_SHIFT_REV_ID
#define IFX_DPS310__REG_ADR_REV_ID 				0x0DU
#define IFX_DPS310__REG_MASK_REV_ID 			0xF0U
#define IFX_DPS310__REG_SHIFT_REV_ID 			4U

			//operating mode
#define IFX_DPS310__REG_INFO_OPMODE 			IFX_DPS310__REG_ADR_OPMODE, \
												IFX_DPS310__REG_MASK_OPMODE, \
												IFX_DPS310__REG_SHIFT_OPMODE
#define IFX_DPS310__REG_ADR_OPMODE 				0x08U
#define IFX_DPS310__REG_MASK_OPMODE 			0x07U
#define IFX_DPS310__REG_SHIFT_OPMODE 			0U


			//temperature measure rate
#define IFX_DPS310__REG_INFO_TEMP_MR 			IFX_DPS310__REG_ADR_TEMP_MR, \
												IFX_DPS310__REG_MASK_TEMP_MR, \
												IFX_DPS310__REG_SHIFT_TEMP_MR
#define IFX_DPS310__REG_ADR_TEMP_MR 			0x07U
#define IFX_DPS310__REG_MASK_TEMP_MR 			0x70U
#define IFX_DPS310__REG_SHIFT_TEMP_MR 			4U

			//temperature oversampling rate
#define IFX_DPS310__REG_INFO_TEMP_OSR 			IFX_DPS310__REG_ADR_TEMP_OSR, \
												IFX_DPS310__REG_MASK_TEMP_OSR, \
												IFX_DPS310__REG_SHIFT_TEMP_OSR
#define IFX_DPS310__REG_ADR_TEMP_OSR 			0x07U
#define IFX_DPS310__REG_MASK_TEMP_OSR 			0x07U
#define IFX_DPS310__REG_SHIFT_TEMP_OSR 			0U

			//temperature sensor
#define IFX_DPS310__REG_INFO_TEMP_SENSOR 		IFX_DPS310__REG_ADR_TEMP_SENSOR, \
												IFX_DPS310__REG_MASK_TEMP_SENSOR, \
												IFX_DPS310__REG_SHIFT_TEMP_SENSOR
#define IFX_DPS310__REG_ADR_TEMP_SENSOR 		0x07U
#define IFX_DPS310__REG_MASK_TEMP_SENSOR 		0x80U
#define IFX_DPS310__REG_SHIFT_TEMP_SENSOR 		7U

			//temperature sensor recommendation
#define IFX_DPS310__REG_INFO_TEMP_SENSORREC 	IFX_DPS310__REG_ADR_TEMP_SENSORREC, \
												IFX_DPS310__REG_MASK_TEMP_SENSORREC, \
												IFX_DPS310__REG_SHIFT_TEMP_SENSORREC
#define IFX_DPS310__REG_ADR_TEMP_SENSORREC 		0x28U
#define IFX_DPS310__REG_MASK_TEMP_SENSORREC 	0x80U
#define IFX_DPS310__REG_SHIFT_TEMP_SENSORREC 	7U

			//temperature shift enable (if temp_osr>3)
#define IFX_DPS310__REG_INFO_TEMP_SE 			IFX_DPS310__REG_ADR_TEMP_SE, \
												IFX_DPS310__REG_MASK_TEMP_SE, \
												IFX_DPS310__REG_SHIFT_TEMP_SE
#define IFX_DPS310__REG_ADR_TEMP_SE 			0x09U
#define IFX_DPS310__REG_MASK_TEMP_SE 			0x08U
#define IFX_DPS310__REG_SHIFT_TEMP_SE 			3U


			//pressure measure rate
#define IFX_DPS310__REG_INFO_PRS_MR 			IFX_DPS310__REG_ADR_PRS_MR, \
												IFX_DPS310__REG_MASK_PRS_MR, \
												IFX_DPS310__REG_SHIFT_PRS_MR
#define IFX_DPS310__REG_ADR_PRS_MR 				0x06U
#define IFX_DPS310__REG_MASK_PRS_MR 			0x70U
#define IFX_DPS310__REG_SHIFT_PRS_MR 			4U

			//pressure oversampling rate
#define IFX_DPS310__REG_INFO_PRS_OSR 			IFX_DPS310__REG_ADR_PRS_OSR, \
												IFX_DPS310__REG_MASK_PRS_OSR, \
												IFX_DPS310__REG_SHIFT_PRS_OSR
#define IFX_DPS310__REG_ADR_PRS_OSR 			0x06U
#define IFX_DPS310__REG_MASK_PRS_OSR 			0x07U
#define IFX_DPS310__REG_SHIFT_PRS_OSR 			0U

			//pressure shift enable (if prs_osr>3)
#define IFX_DPS310__REG_INFO_PRS_SE 			IFX_DPS310__REG_ADR_PRS_SE, \
												IFX_DPS310__REG_MASK_PRS_SE, \
												IFX_DPS310__REG_SHIFT_PRS_SE
#define IFX_DPS310__REG_ADR_PRS_SE 				0x09U
#define IFX_DPS310__REG_MASK_PRS_SE 			0x04U
#define IFX_DPS310__REG_SHIFT_PRS_SE 			2U


			//temperature ready flag
#define IFX_DPS310__REG_INFO_TEMP_RDY 			IFX_DPS310__REG_ADR_TEMP_RDY, \
												IFX_DPS310__REG_MASK_TEMP_RDY, \
												IFX_DPS310__REG_SHIFT_TEMP_RDY
#define IFX_DPS310__REG_ADR_TEMP_RDY 			0x08U
#define IFX_DPS310__REG_MASK_TEMP_RDY			0x20U
#define IFX_DPS310__REG_SHIFT_TEMP_RDY 			5U

			//pressure ready flag
#define IFX_DPS310__REG_INFO_PRS_RDY 			IFX_DPS310__REG_ADR_PRS_RDY, \
												IFX_DPS310__REG_MASK_PRS_RDY, \
												IFX_DPS310__REG_SHIFT_PRS_RDY
#define IFX_DPS310__REG_ADR_PRS_RDY 			0x08U
#define IFX_DPS310__REG_MASK_PRS_RDY 			0x10U
#define IFX_DPS310__REG_SHIFT_PRS_RDY 			4U

			//pressure value
#define IFX_DPS310__REG_ADR_PRS 				0x00U
#define IFX_DPS310__REG_LEN_PRS 				3U

			//temperature value
#define IFX_DPS310__REG_ADR_TEMP 				0x03U
#define IFX_DPS310__REG_LEN_TEMP 				3U

			//compensation coefficients
#define IFX_DPS310__REG_ADR_COEF 				0x10U
#define IFX_DPS310__REG_LEN_COEF 				18


			//FIFO enable
#define IFX_DPS310__REG_INFO_FIFO_EN 			IFX_DPS310__REG_ADR_FIFO_EN, \
												IFX_DPS310__REG_MASK_FIFO_EN, \
												IFX_DPS310__REG_SHIFT_FIFO_EN
#define IFX_DPS310__REG_ADR_FIFO_EN 			0x09U
#define IFX_DPS310__REG_MASK_FIFO_EN 			0x02U
#define IFX_DPS310__REG_SHIFT_FIFO_EN 			1U

			//FIFO flush
#define IFX_DPS310__REG_INFO_FIFO_FL 			IFX_DPS310__REG_ADR_FIFO_EN, \
												IFX_DPS310__REG_MASK_FIFO_EN, \
												IFX_DPS310__REG_SHIFT_FIFO_EN
#define IFX_DPS310__REG_ADR_FIFO_FL 			0x0CU
#define IFX_DPS310__REG_MASK_FIFO_FL 			0x80U
#define IFX_DPS310__REG_SHIFT_FIFO_FL 			7U

			//FIFO empty
#define IFX_DPS310__REG_INFO_FIFO_EMPTY 		IFX_DPS310__REG_ADR_FIFO_EMPTY, \
												IFX_DPS310__REG_MASK_FIFO_EMPTY, \
												IFX_DPS310__REG_SHIFT_FIFO_EMPTY
#define IFX_DPS310__REG_ADR_FIFO_EMPTY 			0x0BU
#define IFX_DPS310__REG_MASK_FIFO_EMPTY 		0x01U
#define IFX_DPS310__REG_SHIFT_FIFO_EMPTY 		0U

			//FIFO full
#define IFX_DPS310__REG_INFO_FIFO_FULL 			IFX_DPS310__REG_ADR_FIFO_FULL, \
												IFX_DPS310__REG_MASK_FIFO_FULL, \
												IFX_DPS310__REG_SHIFT_FIFO_FULL
#define IFX_DPS310__REG_ADR_FIFO_FULL 			0x0BU
#define IFX_DPS310__REG_MASK_FIFO_FULL 			0x02U
#define IFX_DPS310__REG_SHIFT_FIFO_FULL 		1U


			//INT HL
#define IFX_DPS310__REG_INFO_INT_HL 			IFX_DPS310__REG_ADR_INT_HL, \
												IFX_DPS310__REG_MASK_INT_HL, \
												IFX_DPS310__REG_SHIFT_INT_HL
#define IFX_DPS310__REG_ADR_INT_HL 				0x09U
#define IFX_DPS310__REG_MASK_INT_HL 			0x80U
#define IFX_DPS310__REG_SHIFT_INT_HL 			7U

			//INT FIFO enable
#define IFX_DPS310__REG_INFO_INT_EN_FIFO 		IFX_DPS310__REG_ADR_INT_EN_FIFO, \
												IFX_DPS310__REG_MASK_INT_EN_FIFO, \
												IFX_DPS310__REG_SHIFT_INT_EN_FIFO
#define IFX_DPS310__REG_ADR_INT_EN_FIFO 		0x09U
#define IFX_DPS310__REG_MASK_INT_EN_FIFO 		0x40U
#define IFX_DPS310__REG_SHIFT_INT_EN_FIFO 		6U

			//INT TEMP enable
#define IFX_DPS310__REG_INFO_INT_EN_TEMP 		IFX_DPS310__REG_ADR_INT_EN_TEMP, \
												IFX_DPS310__REG_MASK_INT_EN_TEMP, \
												IFX_DPS310__REG_SHIFT_INT_EN_TEMP
#define IFX_DPS310__REG_ADR_INT_EN_TEMP 		0x09U
#define IFX_DPS310__REG_MASK_INT_EN_TEMP 		0x20U
#define IFX_DPS310__REG_SHIFT_INT_EN_TEMP 		5U

			//INT PRS enable
#define IFX_DPS310__REG_INFO_INT_EN_PRS 		IFX_DPS310__REG_ADR_INT_EN_PRS, \
												IFX_DPS310__REG_MASK_INT_EN_PRS, \
												IFX_DPS310__REG_SHIFT_INT_EN_PRS
#define IFX_DPS310__REG_ADR_INT_EN_PRS 			0x09U
#define IFX_DPS310__REG_MASK_INT_EN_PRS 		0x10U
#define IFX_DPS310__REG_SHIFT_INT_EN_PRS 		4U

			//INT FIFO flag
#define IFX_DPS310__REG_INFO_INT_FLAG_FIFO 		IFX_DPS310__REG_ADR_INT_FLAG_FIFO, \
												IFX_DPS310__REG_MASK_INT_FLAG_FIFO, \
												IFX_DPS310__REG_SHIFT_INT_FLAG_FIFO
#define IFX_DPS310__REG_ADR_INT_FLAG_FIFO 		0x0AU
#define IFX_DPS310__REG_MASK_INT_FLAG_FIFO 		0x04U
#define IFX_DPS310__REG_SHIFT_INT_FLAG_FIFO 	2U

			//INT TMP flag
#define IFX_DPS310__REG_INFO_INT_FLAG_TEMP 		IFX_DPS310__REG_ADR_INT_FLAG_TEMP, \
												IFX_DPS310__REG_MASK_INT_FLAG_TEMP, \
												IFX_DPS310__REG_SHIFT_INT_FLAG_TEMP
#define IFX_DPS310__REG_ADR_INT_FLAG_TEMP 		0x0AU
#define IFX_DPS310__REG_MASK_INT_FLAG_TEMP 		0x02U
#define IFX_DPS310__REG_SHIFT_INT_FLAG_TEMP 	1U

			//INT PRS flag
#define IFX_DPS310__REG_INFO_INT_FLAG_PRS 		IFX_DPS310__REG_ADR_INT_FLAG_PRS, \
												IFX_DPS310__REG_MASK_INT_FLAG_PRS, \
												IFX_DPS310__REG_SHIFT_INT_FLAG_PRS
#define IFX_DPS310__REG_ADR_INT_FLAG_PRS 		0x0AU
#define IFX_DPS310__REG_MASK_INT_FLAG_PRS 		0x01U
#define IFX_DPS310__REG_SHIFT_INT_FLAG_PRS 		0U



#endif /* IFX_DPS310_CONSTS_H_ */
