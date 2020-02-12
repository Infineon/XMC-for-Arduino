/**
    @file: arduino_adapter.c

    @brief: Adapter for Arduino type applications
*/

/* ===========================================================================
** Copyright (C) 2019 Infineon Technologies AG
** All rights reserved.
** ===========================================================================
**
** ===========================================================================
** This document contains proprietary information of Infineon Technologies AG.
** Passing on and copying of this document, and communication of its contents
** is not permitted without Infineon's prior written authorization.
** ===========================================================================
*/
#ifndef ARDUINO_ADAPTER_H_
#define ARDUINO_ADAPTER_H_

/* Enable C linkage if header is included in C++ files */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*
==============================================================================
   1. INCLUDE FILES
==============================================================================
*/

#include <stdint.h>

/*
==============================================================================
   2. DEFINES
==============================================================================
*/

/* Possible error codes, returned by the system, via the error handler */

#define RADAR_ERR_OK                          	0x0000  /**< No error has
                                                           occurred. */
#define RADAR_ERR_DEVICE_DOES_NOT_EXIST       	0x0001  /**< The device number
                                                           requested to open
                                                           does not exist. */
#define RADAR_ERR_BUSY                        	0x0002  /**< The requested
                                                           operation can't be
                                                           executed. A
                                                           possible reason is
                                                           that a certain test
                                                           mode is activated
                                                           or the automatic
                                                           trigger is active.
                                                           */
#define RADAR_ERR_INCOMPATIBLE_MODE           	0x0003  /**< The requested
                                                           operation is not
                                                           supported by the
                                                           currently active
                                                           mode of operation.
                                                           */
#define RADAR_ERR_TIMEOUT                     	0x0004  /**< A timeout has
                                                           occurred while
                                                           waiting for
                                                           a data frame to be
                                                           acquired. */
#define RADAR_ERR_UNSUPPORTED_FRAME_INTERVAL  	0x0005  /**< The requested time
                                                           interval between
                                                           two frames is out
                                                           of range. */
#define RADAR_ERR_ANTENNA_DOES_NOT_EXIST      	0x0006  /**< One or more of the
                                                           selected RX or TX
                                                           antennas is not
                                                           present on the
                                                           device. */
#define RADAR_ERR_SENSOR_DOES_NOT_EXIST       	0x0007  /**< The requested
                                                           temperature sensor
                                                           does not exist. */
#define RADAR_ERR_UNSUPPORTED_FRAME_FORMAT    	0x0008  /**< The combination of
                                                           chirps per frame,
                                                           samples per chirp
                                                           and number of
                                                           antennas is not
                                                           supported by the
                                                           driver. A possible
                                                           reason is the limit
                                                           of the driver
                                                           internal data
                                                           memory. */
#define RADAR_ERR_FREQUENCY_OUT_OF_RANGE      	0x0009  /**< The specified RF
                                                           frequency is not in
                                                           the supported range
                                                           of the device. */
#define RADAR_ERR_POWER_OUT_OF_RANGE          	0x000A  /**< The specified
                                                           transmission power
                                                           is not in the valid
                                                           range of
                                                           0...max_tx_power
                                                           (see \ref
                                                           Device_Info_t). */
#define RADAR_ERR_UNAVAILABLE_SIGNAL_PART     	0x000B  /**< The device is not
                                                           capable to capture
                                                           the requested part
                                                           of the complex
                                                           signal (see \ref
                                                           Device_Info_t). */

#define RADAR_ERR_PARAMETER_OUT_OF_RANGE      	0x000C  /**< The specified
                                                           parameter is out of
                                                           range */

#define RADAR_ERR_FEATURE_UNAVAILABLE     	  	0x8000  /**< If feature is currently
                                                           not available in the API. */

#define RADAR_ERR_UNSUPPORTED_DIRECTION       	0x0020  /**< The specified FMCW ramp
                                                           direction is not
                                                           supported by the device. */

#define RADAR_ERR_SAMPLERATE_OUT_OF_RANGE     	0x0050  /**< The specified sample
                                                            rate is out of range. */

#define RADAR_ERR_UNSUPPORTED_RESOLUTION      	0x0051  /**< The specified sample
                                                           resolution is out of
                                                           range. */
#define   RF_SHIELD_BOARD_INVALID_PARAM     	0xFE01   /**< Status in case of invalid parameter */
#define   RF_SHIELD_BOARD_SUPPORTED         	0xFE02   /**< Status for supported RF shield with valid board ID */
#define   RF_SHIELD_BOARD_UNSUPPORTED      		0xFE03   /**< Status for unsupported RF shield board
                                              	  	  	  	  RF shield board is not compatible and is not supported in the current Firmware
                                              	  	  	  	  Shield programmed with the wrong ID, For example RBBxxxxxx */
#define   RF_SHIELD_BOARD_NOT_PROGRAMMED    	0xFE04   /**< Status for unsupported RF shield board
                                              	  	  	  	  RF shield is not programmed or it contains invalid data */
#define   RF_SHIELD_BOARD_NOT_CONNECTED     	0xFE05   /**< Status when RF shield board is not plugged into */


/*
==============================================================================
   3. CUSTOM TYPES
==============================================================================
*/

typedef void(*ard_error_handler_cb)(uint32_t error);
typedef void(*ard_result_handler_cb)( void );

/*
==============================================================================
   5. FUNCTIONS
==============================================================================
*/

ard_error_handler_cb radar_ard_register_error_handler( ard_error_handler_cb handler );

ard_result_handler_cb radar_ard_register_result_handler( ard_result_handler_cb handler);

void radar_ard_init(void);

uint8_t radar_ard_is_initalized( void );

void radar_ard_stop( void );

uint8_t radar_ard_start( void );

uint32_t radar_ard_hw_init(void);

void radar_ard_time_delay_msec( uint32_t delay_value );

/* loop processing */

void radar_ard_process(void);

/* get and set the parameters */

float radar_ard_get_min_speed_kmph( void );

uint8_t radar_ard_set_min_speed_kmph(float speed_kmph);

float radar_ard_get_max_speed_kmph( void );

uint8_t radar_ard_set_max_speed_kmph(float speed_kmph);

float radar_ard_get_motion_sensitivity( void );

uint8_t radar_ard_set_motion_sensitivity(float sensitivity);

float radar_ard_get_doppler_sensitivity( void );

uint8_t radar_ard_set_doppler_sensitivity(float sensitivity);

uint32_t radar_ard_get_adc_sampling_freq_hz( void );

uint8_t radar_ard_set_adc_sampling_freq_Hz(uint32_t value);

uint32_t radar_ard_get_frame_period_usec( void );

uint8_t radar_ard_set_frame_period_usec(uint32_t value);

uint32_t radar_ard_get_num_skip_samples( void );

uint8_t radar_ard_set_num_skip_samples(uint32_t value);

uint32_t radar_ard_get_num_samples( void );

uint8_t radar_ard_set_num_samples(uint32_t value);

uint32_t radar_ard_get_pulse_width_usec( void );

uint8_t radar_ard_set_pulse_width_usec(uint32_t value);

uint32_t radar_ard_get_min_frame_period_usec( void );

float radar_ard_get_current_consumption_mA( void );

/* functions to get the processing results */

float radar_ard_get_doppler_level( void );

float radar_ard_get_doppler_speed_kmph( void );

float radar_ard_get_doppler_frequency_hz( void );

uint8_t radar_ard_is_target_departing( void );

uint8_t radar_ard_is_target_approaching( void );

uint8_t radar_ard_is_motion( void );

uint32_t radar_ard_get_frame_count( void );

/* --- Close open blocks -------------------------------------------------- */
/* Disable C linkage for C++ files */
#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif
/* ARDUINO_ADAPTER_H_ */
/* --- End of File -------------------------------------------------------- */
