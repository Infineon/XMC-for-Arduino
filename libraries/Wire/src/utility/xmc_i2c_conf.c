/**
 * xmc_i2c_conf.c - Utility file for the I2C/Wire library.
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

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "xmc_i2c_conf.h"

#if defined(XMC1100_XMC2GO)
XMC_I2C_t XMC_I2C_0 =
{
    .channel          = XMC_I2C0_CH1,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)10
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)11
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source_dx0 = XMC_INPUT_F,
    .input_source_dx1 = XMC_INPUT_E,
    .slave_receive_irq_num                    = (IRQn_Type) USIC0_4_IRQn,
    .slave_receive_irq_service_request        = 4 ,
    .protocol_irq_num                   	  = (IRQn_Type) USIC0_5_IRQn,
    .protocol_irq_service_request       	  = 5
};

XMC_I2C_t XMC_I2C_1 =
{
    .channel          = XMC_I2C0_CH0,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)15
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)14
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source_dx0 = XMC_INPUT_B,
    .input_source_dx1 = XMC_INPUT_A,
    .slave_receive_irq_num                    = (IRQn_Type) USIC0_2_IRQn,
    .slave_receive_irq_service_request        = 2 ,
    .protocol_irq_num                   	  = (IRQn_Type) USIC0_3_IRQn,
    .protocol_irq_service_request       	  = 3
};

#elif defined(XMC1100_H_BRIDGE2GO)
XMC_I2C_t XMC_I2C_0 =
{
    .channel          = XMC_I2C0_CH1,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)7
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)8
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source_dx0 = XMC_INPUT_D,
    .input_source_dx1 = XMC_INPUT_B,
    .slave_receive_irq_num                    = (IRQn_Type) USIC0_4_IRQn,
    .slave_receive_irq_service_request        = 4 ,
    .protocol_irq_num                   	  = (IRQn_Type) USIC0_5_IRQn,
    .protocol_irq_service_request       	  = 5
};

XMC_I2C_t XMC_I2C_1 =
{
    .channel          = XMC_I2C0_CH0,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)15
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)14
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source_dx0 = XMC_INPUT_B,
    .input_source_dx1 = XMC_INPUT_A,
    .slave_receive_irq_num                    = (IRQn_Type) USIC0_2_IRQn,
    .slave_receive_irq_service_request        = 2 ,
    .protocol_irq_num                   	  = (IRQn_Type) USIC0_3_IRQn,
    .protocol_irq_service_request       	  = 3
};

#elif defined(XMC1100_Boot_Kit) || defined(XMC1300_Boot_Kit) || defined(XMC1400_Boot_Kit) 
XMC_I2C_t XMC_I2C_0 =
{
    .channel          = XMC_I2C0_CH0,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)1
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)0
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source_dx0 = XMC_INPUT_F,
    .input_source_dx1 = XMC_INPUT_E,
    .slave_receive_irq_num                    = (IRQn_Type) USIC0_4_IRQn,
    .slave_receive_irq_service_request        = 4 ,
    .protocol_irq_num                   	  = (IRQn_Type) USIC0_5_IRQn,
    .protocol_irq_service_request       	  = 5
};


#elif defined (XMC4400_Platform2GO)
XMC_I2C_t XMC_I2C_0 =
{
    .channel          = XMC_I2C0_CH1,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)5
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)0
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0 = XMC_INPUT_B,
    .input_source_dx1 = XMC_INPUT_B,
    .slave_receive_irq_num                    = (IRQn_Type) 91,
    .slave_receive_irq_service_request        = 1 ,
    .protocol_irq_num                   	  = (IRQn_Type) 92,
    .protocol_irq_service_request       	  = 2
};


#elif defined(XMC4700_Relax_Kit)
XMC_I2C_t XMC_I2C_0 =
{
    .channel          = XMC_I2C1_CH1,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)15
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)13
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0 = XMC_INPUT_A,
    .input_source_dx1 = XMC_INPUT_B,
    .slave_receive_irq_num                    = (IRQn_Type) 91,
    .slave_receive_irq_service_request        = 1 ,
    .protocol_irq_num                		  = (IRQn_Type) 92,
    .protocol_irq_service_request     		  = 2
};
XMC_I2C_t XMC_I2C_1 =
{
    .channel          = XMC_I2C1_CH0,
    .channel_config   = {
        .baudrate = (uint32_t)(100000U),
        .address = 0U
    },
    .sda              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)5
    },
    .sda_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)11
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0 = XMC_INPUT_B,
    .input_source_dx1 = XMC_INPUT_A,
    .slave_receive_irq_num                    = (IRQn_Type) 93,
    .slave_receive_irq_service_request        = 3 ,
    .protocol_irq_num                  		  = (IRQn_Type) 94,
    .protocol_irq_service_request     		  = 4
};
#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
