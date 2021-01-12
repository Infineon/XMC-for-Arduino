/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Copyright (c) 2018 Infineon Technologies AG
  This file has been modified for the XMC microcontroller series.
*/
#ifndef _ARDUINO_H_
#define _ARDUINO_H_

#ifdef __cplusplus
extern "C" {
#endif

//****************************************************************************
// @Std Includes
//****************************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <types.h>
#include <math.h>
#include <pgmspace.h>

//****************************************************************************
// @XMC Lib Includes
//****************************************************************************
#include <xmc_common.h>
#include <xmc_gpio.h>
#include <xmc_ccu4.h>
#include <xmc_ccu8.h>
#include <xmc_vadc.h>
#include <xmc_uart.h>
#include <xmc_dac.h>
#include <xmc_eru.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define clockCyclesPerMicrosecond()     ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a)    ( ((a) * 1000L) / (F_CPU / 1000L) )
#define microsecondsToClockCycles(a)    ( (a) * (F_CPU / 1000000L) )

//****************************************************************************
// @Typedefs
//****************************************************************************
    /*
    * XMC USIC channel input selection types
    */
    typedef enum
    {
        XMC_INPUT_A = 0U, /*< Input-A */
        XMC_INPUT_B,      /*< Input-B */
        XMC_INPUT_C,      /*< Input-C */
        XMC_INPUT_D,      /*< Input-D */
        XMC_INPUT_E,      /*< Input-E */
        XMC_INPUT_F,      /*< Input-F */
        XMC_INPUT_G,      /*< Input-G */
        XMC_INPUT_INVALID /*< This is to check during mode switch */
    }
    XMC_USIC_INPUT_t;

    /*
    * XMC port pin type
    */
    typedef struct
    {
        XMC_GPIO_PORT_t* port;
        unsigned          pin;
    } XMC_PORT_PIN_t;

    /*
    * XMC pin interrupt type
    */
#if defined (INTERRUPT_USE_ERU)
	typedef struct
	{
		XMC_ERU_t*              eru;
		XMC_ERU_ETL_INPUT_A_t   input_a;
		XMC_ERU_ETL_INPUT_B_t   input_b;
		uint8_t                 etl;
		uint8_t                 ogu;
		uint8_t                 irq_num;
	} XMC_PIN_INTERRUPT_t;
#else
    typedef struct
    {
        XMC_CCU4_MODULE_t*      ccu         ;
        XMC_CCU4_SLICE_t*       slice       ;
        uint8_t                 slice_num   ;
        uint8_t                 irq_num     ;
        XMC_CCU4_SLICE_INPUT_t  input       ;
    } XMC_PIN_INTERRUPT_t;
#endif

    /*
    * XMC PWM type (CCU4)
    */
    typedef struct
    {
        XMC_CCU4_MODULE_t*              ccu             ;
        XMC_CCU4_SLICE_t*               slice           ;
        uint8_t                         slice_num       ;
        XMC_PORT_PIN_t                  port_pin        ;
        XMC_GPIO_MODE_t                 port_mode       ;
        XMC_CCU4_SLICE_PRESCALER_t      prescaler       ;
        uint32_t                        period_timer_val;
        bool                            enabled         ;
    } XMC_PWM4_t;

#if defined (CCU8V2) ||defined (CCU8V3) || defined(CCU8V1)
    /*
    * XMC PWM type (CCU8)
    */
    typedef struct
    {
        XMC_CCU8_MODULE_t*                  ccu             ;
        XMC_CCU8_SLICE_t*                   slice           ;
        uint8_t                             slice_num       ;
        XMC_CCU8_SLICE_COMPARE_CHANNEL_t    slice_channel   ;
        XMC_PORT_PIN_t                      port_pin        ;
        XMC_GPIO_MODE_t                     port_mode       ;
        XMC_CCU8_SLICE_PRESCALER_t          prescaler       ;
        uint32_t                            period_timer_val;
        bool                                enabled         ;
    } XMC_PWM8_t;
#endif

#ifdef DAC
	//TODO: find a better name; XMC_DAC_t is already used by XMCLib
    /*
    * XMC DAC type
    */
    typedef struct
    {
		XMC_DAC_t *group;
		uint8_t channel;
		uint8_t resolution; 	//number of resolution bits
	} XMC_ARD_DAC_t;
#endif

    /*
    * XMC VADC type (with or without adc grouping)
    */
    typedef struct
    {
        XMC_VADC_GLOBAL_t*      global          ;
        uint8_t                 channel_num     ;
#if(XMC_VADC_GROUP_AVAILABLE == 1U)
        XMC_VADC_GROUP_t*       group           ;
        uint8_t                 group_num       ;
        uint32_t                result_reg_num  ;
#endif
        bool                    enabled         ;
    } XMC_ADC_t;

    /*
    * XMC UART type
    */
    typedef struct
    {
        XMC_USIC_CH_t*          channel             ;
        XMC_PORT_PIN_t          rx                  ;
        XMC_GPIO_CONFIG_t       rx_config           ;
        XMC_PORT_PIN_t          tx                  ;
        XMC_GPIO_CONFIG_t       tx_config           ;
        XMC_USIC_INPUT_t        input_source_dx0    ;
// Use to activate additional Input MUXs to select input pin (if not used if use: XMC_INPUT_INVALID)
        XMC_USIC_INPUT_t        input_source_dx1    ;
        XMC_USIC_INPUT_t        input_source_dx2    ;
        XMC_USIC_INPUT_t        input_source_dx3 ;
        IRQn_Type               irq_num             ;
        uint32_t                irq_service_request ;
    } XMC_UART_t;

//****************************************************************************
// @Imported Global Variables
//****************************************************************************
    extern const XMC_PORT_PIN_t mapping_port_pin[];
    extern const XMC_PIN_INTERRUPT_t mapping_interrupt[];
    extern const uint8_t mapping_pin_PWM4[][ 2 ];
    extern XMC_PWM4_t mapping_pwm4[];
    extern XMC_ADC_t mapping_adc[];
#if defined (CCU8V2) || defined(CCU8V3) || defined(CCU8V1)
    extern const uint8_t mapping_pin_PWM8[][ 2 ];
    extern XMC_PWM8_t mapping_pwm8[];
#endif
#ifdef DAC
    extern const uint8_t mapping_pin_DAC[][ 2 ];
	extern XMC_ARD_DAC_t mapping_dac[];
#endif
	extern XMC_UART_t XMC_UART_debug;
	extern XMC_UART_t XMC_UART_on_board;

//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

	/*
     * \brief Arduino yield function.
     */
	void yield( void );

    /*
     * \brief Arduino Main setup function. Called only once at the beginning.
     */
    extern void setup(void);

    /*
     * \brief Arduino Main loop function. Called in an endless loop.
     */
    extern void loop(void);


//****************************************************************************
// @Arduino Core Includes
//****************************************************************************
#include "wiring_constants.h"
#include "binary.h"
#include "wiring_digital.h"
#include "wiring_analog.h"
#include "wiring_shift.h"
#include "wiring_time.h"
#include "wiring_pulse.h"
#include "itoa.h"
#include "dtostrf.h"
#include "WCharacter.h"
#include "WInterrupts.h"

//****************************************************************************
// @Infineon Core Includes
//****************************************************************************
#include "reset.h"

#ifdef __cplusplus
} // extern "C"
#include "Tone.h"
#include "WMath.h"
#endif	// __cplusplus

#include "Print.h"
#include "HardwareSerial.h"

//****************************************************************************
// @Board Variant Includes
//****************************************************************************
#include <pins_arduino.h>

#endif  /*_ARDUINO_H_ */