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
#include <xmc_spi.h>
#include <xmc_i2c.h>
#include <xmc_i2s.h>
#include <xmc_can.h>

//****************************************************************************
// @Defines
//****************************************************************************
#define clockCyclesPerMicrosecond() (F_CPU / 1000000L)
#define clockCyclesToMicroseconds(a) (((a) * 1000L) / (F_CPU / 1000L))
#define microsecondsToClockCycles(a) ((a) * (F_CPU / 1000000L))

// default XMC_SPI instance is XMC_SPI_0 for all variants
#define XMC_SPI_default XMC_SPI_0
// default XMC_I2C instance is XMC_I2C_0 for all variants
#define XMC_I2C_default XMC_I2C_0
// used by XMC_I2S
#define BUFFER_SIZE 512

//****************************************************************************
// @Typedefs
//****************************************************************************
/*
 * XMC USIC channel input selection types
 */
typedef enum {
    XMC_INPUT_A = 0U, /*< Input-A */
    XMC_INPUT_B,      /*< Input-B */
    XMC_INPUT_C,      /*< Input-C */
    XMC_INPUT_D,      /*< Input-D */
    XMC_INPUT_E,      /*< Input-E */
    XMC_INPUT_F,      /*< Input-F */
    XMC_INPUT_G,      /*< Input-G */
    XMC_INPUT_INVALID /*< This is to check during mode switch */
} XMC_USIC_INPUT_t;

/*
 * XMC port pin type
 */
typedef struct {
    XMC_GPIO_PORT_t *port;
    unsigned pin;
} XMC_PORT_PIN_t;

/*
 * XMC pin interrupt type
 */
#if defined(INTERRUPT_USE_ERU)
typedef struct {
    XMC_ERU_t *eru;
    XMC_ERU_ETL_INPUT_A_t input_a;
    XMC_ERU_ETL_INPUT_B_t input_b;
    uint8_t etl;
    uint8_t ogu;
    uint8_t irq_num;
} XMC_PIN_INTERRUPT_t;
#else
typedef struct {
    XMC_CCU4_MODULE_t *ccu;
    XMC_CCU4_SLICE_t *slice;
    uint8_t slice_num;
    uint8_t irq_num;
    XMC_CCU4_SLICE_INPUT_t input;
} XMC_PIN_INTERRUPT_t;
#endif

/*
 * XMC PWM type (CCU4)
 */
typedef struct {
    XMC_CCU4_MODULE_t *ccu;
    XMC_CCU4_SLICE_t *slice;
    uint8_t slice_num;
    XMC_PORT_PIN_t port_pin;
    XMC_GPIO_MODE_t port_mode;
    XMC_CCU4_SLICE_PRESCALER_t prescaler;
    uint32_t period_timer_val;
    bool enabled;
} XMC_PWM4_t;

#if defined(CCU8V2) || defined(CCU8V3) || defined(CCU8V1)
/*
 * XMC PWM type (CCU8)
 */
typedef struct {
    XMC_CCU8_MODULE_t *ccu;
    XMC_CCU8_SLICE_t *slice;
    uint8_t slice_num;
    XMC_CCU8_SLICE_COMPARE_CHANNEL_t slice_channel;
    XMC_PORT_PIN_t port_pin;
    XMC_GPIO_MODE_t port_mode;
    XMC_CCU8_SLICE_PRESCALER_t prescaler;
    uint32_t period_timer_val;
    bool enabled;
} XMC_PWM8_t;
#endif

#ifdef DAC
// TODO: find a better name; XMC_DAC_t is already used by XMCLib
/*
 * XMC DAC type
 */
typedef struct {
    XMC_DAC_t *group;
    uint8_t channel;
    uint8_t resolution; // number of resolution bits
} XMC_ARD_DAC_t;
#endif

/*
 * XMC VADC type (with or without adc grouping)
 */
typedef struct {
    XMC_VADC_GLOBAL_t *global;
    uint8_t channel_num;
#if (XMC_VADC_GROUP_AVAILABLE == 1U)
    XMC_VADC_GROUP_t *group;
    uint8_t group_num;
    uint32_t result_reg_num;
#endif
    bool enabled;
} XMC_ADC_t;

/*
 * XMC UART type
 */
typedef struct {
    XMC_USIC_CH_t *channel;
    XMC_PORT_PIN_t rx;
    XMC_GPIO_CONFIG_t rx_config;
    XMC_PORT_PIN_t tx;
    XMC_GPIO_CONFIG_t tx_config;
    XMC_USIC_INPUT_t input_source_dx0;
    // Use to activate additional Input MUXs to select input pin (if not used if use:
    // XMC_INPUT_INVALID)
    XMC_USIC_INPUT_t input_source_dx1;
    XMC_USIC_INPUT_t input_source_dx2;
    XMC_USIC_INPUT_t input_source_dx3;
    IRQn_Type irq_num;
    uint32_t irq_service_request;
} XMC_UART_t;

/*
 * XMC SPI type
 */
typedef struct {
    XMC_USIC_CH_t *channel;
    XMC_SPI_CH_CONFIG_t channel_config;
    XMC_PORT_PIN_t mosi;
    XMC_GPIO_CONFIG_t mosi_config;
    XMC_PORT_PIN_t miso;
    XMC_GPIO_CONFIG_t miso_config;
    XMC_USIC_INPUT_t input_source;
    XMC_PORT_PIN_t sclkout;
    XMC_GPIO_CONFIG_t sclkout_config;
} XMC_SPI_t;

/*
 * XMC I2C type
 */
typedef struct {
    XMC_USIC_CH_t *channel;
    XMC_I2C_CH_CONFIG_t channel_config;
    XMC_PORT_PIN_t sda;
    XMC_GPIO_CONFIG_t sda_config;
    XMC_PORT_PIN_t scl;
    XMC_GPIO_CONFIG_t scl_config;
    XMC_USIC_INPUT_t input_source_dx0;
    XMC_USIC_INPUT_t input_source_dx1;
    IRQn_Type slave_receive_irq_num;
    uint32_t slave_receive_irq_service_request;
    IRQn_Type protocol_irq_num;
    uint32_t protocol_irq_service_request;
} XMC_I2C_t;

/*
 * XMC I2S type
 */
typedef struct {
    XMC_GPIO_CONFIG_t input_config;
    XMC_GPIO_CONFIG_t sclk_config;
    XMC_GPIO_CONFIG_t wa_config;
    IRQn_Type protocol_irq_num;
    uint32_t protocol_irq_service_request;
#if (UC_SERIES == XMC14)
    XMC_SCU_IRQCTRL_t protocol_irq_source;
#endif
} XMC_I2S_t;

#ifdef CAN_xmc
/*
 * XMC (Arduino) CAN type
 */

typedef enum { XMC_NODE_NUM_0, XMC_NODE_NUM_1 } XMC_CAN_NODE_NUM_t;

typedef struct {
    CAN_NODE_TypeDef *can_node;
    XMC_CAN_NODE_NUM_t can_node_num;
    XMC_CAN_CANCLKSRC_t can_clock;
    uint32_t can_frequency;
    XMC_PORT_PIN_t rx;
    XMC_GPIO_CONFIG_t rx_config;
    XMC_PORT_PIN_t tx;
    XMC_GPIO_CONFIG_t tx_config;
    XMC_CAN_NODE_RECEIVE_INPUT_t node_input;
    IRQn_Type irq_num;
    uint32_t irq_service_request;
    #if (UC_SERIES == XMC14)
    XMC_SCU_IRQCTRL_t irq_source;
    #endif
} XMC_ARD_CAN_t;
#endif

//****************************************************************************
// @Imported Global Variables
//****************************************************************************
extern const XMC_PORT_PIN_t mapping_port_pin[];
extern const XMC_PIN_INTERRUPT_t mapping_interrupt[];
extern const uint8_t mapping_pin_PWM4[][2];
extern XMC_PWM4_t mapping_pwm4[];
extern XMC_ADC_t mapping_adc[];
#if defined(CCU8V2) || defined(CCU8V3) || defined(CCU8V1)
extern const uint8_t mapping_pin_PWM8[][2];
extern XMC_PWM8_t mapping_pwm8[];
#endif
#ifdef DAC
extern const uint8_t mapping_pin_DAC[][2];
extern XMC_ARD_DAC_t mapping_dac[];
#endif
extern XMC_UART_t XMC_UART_debug;
extern XMC_UART_t XMC_UART_on_board;

extern XMC_SPI_t XMC_SPI_0;
// Some boards for eg. XMC4700 Relax Kit has more than one SPI instance
extern XMC_SPI_t XMC_SPI_1;
extern XMC_SPI_t XMC_SPI_2;

extern XMC_I2C_t XMC_I2C_0;
// Some boards for eg. XMC4700 Relax Kit has more than one I2C instance
extern XMC_I2C_t XMC_I2C_1;

extern XMC_I2S_t i2s_config;

#ifdef CAN_xmc
extern XMC_ARD_CAN_t XMC_CAN_0;
#endif
//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

/*
 * \brief Arduino yield function.
 */
void yield(void);

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
#endif // __cplusplus

#include "Print.h"
#include "HardwareSerial.h"

//****************************************************************************
// @Board Variant Includes
//****************************************************************************
#include <pins_arduino.h>

#endif /*_ARDUINO_H_ */