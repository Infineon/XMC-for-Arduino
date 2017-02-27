/**
 * @file xmc_spi_conf.h
 * @date 2016-11-18
 *
 * @cond
 */

#ifndef XMC_SPI_CONF_H
#define XMC_SPI_CONF_H

//****************************************************************************
// @Project Includes
//****************************************************************************
#include <Arduino.h>
#include <xmc_spi.h>

//****************************************************************************
// @Typedefs
//****************************************************************************

typedef struct XMC_SPI
{
    XMC_USIC_CH_t*         channel        ;
    XMC_SPI_CH_CONFIG_t   channel_config  ;
    XMC_PORT_PIN_t        mosi            ;
    XMC_GPIO_CONFIG_t     mosi_config     ;
    XMC_PORT_PIN_t        miso            ;
    XMC_GPIO_CONFIG_t     miso_config     ;
    XMC_USIC_INPUT_t      input_source    ;
    XMC_PORT_PIN_t        sclkout         ;
    XMC_GPIO_CONFIG_t     sclkout_config  ;
} XMC_SPI_t;


#if defined(XMC1100_XMC2GO)
#define NUM_SPI  1
extern XMC_SPI_t XMC_SPI_default;

#elif defined(XMC1100_Boot_Kit)
#define NUM_SPI  1
extern XMC_SPI_t XMC_SPI_default;
#elif defined(XMC4700_Relax_Kit)
#define NUM_SPI  2
extern XMC_SPI_t XMC_SPI_default;
extern XMC_SPI_t XMC_SPI_for_xmc4_SD;
#else
#error XMC Board not supported
#endif


#endif /* XMC_SPI_CONF_H */
