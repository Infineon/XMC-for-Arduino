/**
 * xmc_spi_conf.h - Utility file for the SPI library.
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
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
    XMC_USIC_CH_t*        channel        ;
    XMC_SPI_CH_CONFIG_t   channel_config  ;
    XMC_PORT_PIN_t        mosi            ;
    XMC_GPIO_CONFIG_t     mosi_config     ;
    XMC_PORT_PIN_t        miso            ;
    XMC_GPIO_CONFIG_t     miso_config     ;
    XMC_USIC_INPUT_t      input_source    ;
    XMC_PORT_PIN_t        sclkout         ;
    XMC_GPIO_CONFIG_t     sclkout_config  ;
} XMC_SPI_t;

#define XMC_SPI_default 	XMC_SPI_0

#if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
#define NUM_SPI  			1
extern XMC_SPI_t XMC_SPI_0;

#elif defined(XMC1100_Boot_Kit) || defined(XMC1300_Boot_Kit) || defined(XMC1400_Boot_Kit)
#define NUM_SPI  			1
extern XMC_SPI_t XMC_SPI_0;

#elif defined(XMC4400_Platform2GO)
#define NUM_SPI  			1
extern XMC_SPI_t XMC_SPI_0;

#elif defined(XMC4700_Relax_Kit)
#define NUM_SPI  			3
#define XMC_SPI_for_xmc_SD	XMC_SPI_1
extern XMC_SPI_t XMC_SPI_0;
extern XMC_SPI_t XMC_SPI_1;
extern XMC_SPI_t XMC_SPI_2;
//extern XMC_SPI_t XMC_SPI_3;
//extern XMC_SPI_t XMC_SPI_4;
#else
#error XMC Board not supported
#endif


#endif /* XMC_SPI_CONF_H */
