/**
 * xmc_i2c_conf.h - Utility file for the I2C/Wire library.
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

#if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
#define NUM_I2C  2
extern XMC_I2C_t XMC_I2C_0;
extern XMC_I2C_t XMC_I2C_1;

#elif defined(XMC1100_Boot_Kit) || defined(XMC1300_Boot_Kit) || defined(XMC1400_Boot_Kit)
#define NUM_I2C  1
extern XMC_I2C_t XMC_I2C_0;

#elif defined(XMC4400_Platform2GO)
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
