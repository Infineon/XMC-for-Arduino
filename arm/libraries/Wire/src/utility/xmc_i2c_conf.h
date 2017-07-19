/**
 * @file xmc_i2c_conf.h
 * @date 2016-11-18
 *
 * @cond
 */

#ifndef XMC_I2C_CONF_H
#define XMC_I2C_CONF_H

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <Arduino.h>
#include <xmc_i2c.h>


//****************************************************************************
// @Typedefs
//****************************************************************************
typedef struct XMC_I2C
{
    XMC_USIC_CH_t* channel;
    XMC_I2C_CH_CONFIG_t   channel_config;
    XMC_PORT_PIN_t        sda;
    XMC_GPIO_CONFIG_t     sda_config;
    XMC_PORT_PIN_t        scl;
    XMC_GPIO_CONFIG_t     scl_config;
    XMC_USIC_INPUT_t      input_source_dx0;
    XMC_USIC_INPUT_t      input_source_dx1;
    IRQn_Type             slave_receive_irq_num;
    uint32_t              slave_receive_irq_service_request;
    IRQn_Type             protocol_irq_num;
    uint32_t              protocol_irq_service_request;
} XMC_I2C_t;

#define XMC_I2C_default 	XMC_I2C_0

#if defined(XMC1100_XMC2GO)
#define NUM_I2C  1
extern XMC_I2C_t XMC_I2C_0;

#elif defined(XMC1100_Boot_Kit)
#define NUM_I2C  1
extern XMC_I2C_t XMC_I2C_0;

#elif defined(XMC1300_Boot_Kit)
#define NUM_I2C  1
extern XMC_I2C_t XMC_I2C_0;

#elif defined(XMC4700_Relax_Kit)
#define NUM_I2C  2
extern XMC_I2C_t XMC_I2C_0;
extern XMC_I2C_t XMC_I2C_1;


#else
#error XMC Board not supported
#endif

#endif /* XMC_I2C_CONF_H */
