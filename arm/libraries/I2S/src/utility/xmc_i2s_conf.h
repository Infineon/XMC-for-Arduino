/**
 * xmc_i2s_conf.h - Auxiliary file for the I2S library for Arduino.
 * 
 * Have a look at the application note/datasheet for more information.
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

#ifndef XMC_I2S_CONF_H
#define XMC_I2S_CONF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xmc_i2s.h"

#define BUFFER_SIZE 512

// Only tested with XMC4700
/*U2C0*/
/*DX0C -> P3.7*/
/*SCLKOUT(ALT1) -> P3.9*/
/*WA(ALT1) -> P3.10*/
#if defined(XMC4700_Relax_Kit)
#define MASTER_CHANNEL XMC_I2S2_CH0
// master transmit slave receive
#define MASTER_MTSR PORT3, 8
// master receive slave transmit
#define MASTER_MRST PORT3, 7
#define INPUT_SOURCE USIC2_C0_DX0_P3_7
#define MASTER_SCLK PORT3, 9
#define MASTER_WACLK PORT3, 10

#elif defined(XMC1100_XMC2GO) || defined(XMC1100_Boot_Kit)
/*U0C1*/
/*DX0C(Input) -> P0.6*/
/*SCLKOUT(ALT6) -> P0.8*/
/*WA(ALT6) -> P0.9*/
#define MASTER_CHANNEL XMC_I2S0_CH1
#define MASTER_MRST PORT0, 6
#define INPUT_SOURCE USIC0_C1_DX0_P0_6
#define MASTER_SCLK PORT0, 8
#define MASTER_WACLK PORT0, 9

#elif defined(XMC1100_Boot_Kit)
/*U0C0*/
/*DX0C(Input) -> P1.0*/
/*SCLKOUT(ALT6) -> P0.7*/
/*WA(ALT6) -> P0.9*/
#define MASTER_CHANNEL XMC_I2S0_CH0
#define MASTER_MRST PORT0, 11
#define INPUT_SOURCE USIC0_C0_DX0_P1_0
#define MASTER_SCLK PORT0, 7
#define MASTER_WACLK PORT0, 9

#endif

typedef struct XMC_I2S
{
    XMC_GPIO_CONFIG_t input_config;
    XMC_GPIO_CONFIG_t sclk_config;
    XMC_GPIO_CONFIG_t wa_config;
    IRQn_Type protocol_irq_num;
    uint32_t protocol_irq_service_request;
} XMC_I2S_t;

extern XMC_I2S_t i2s_config; 

#ifdef __cplusplus
}
#endif

#endif
