/**
 * xmc_spi_conf.c - Utility file for the SPI library.
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
#include "xmc_spi_conf.h"

#if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
XMC_SPI_t XMC_SPI_0 =
{
	.channel          = XMC_SPI0_CH1,
	.channel_config   = {
		.baudrate = 15984375U,
		.bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
		.selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
		.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
	},
	.mosi             = {
		.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
		.pin  = (uint8_t)7
	},
	.mosi_config      = {
		.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	},
	.miso             = {
		.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
		.pin  = (uint8_t)6
	},
	.miso_config      = {
		.mode = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	},
	.input_source     = XMC_INPUT_C,
	.sclkout          = {
		.port = (XMC_GPIO_PORT_t*)PORT0_BASE,
		.pin  = (uint8_t)8
	},
	.sclkout_config   = {
		.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	}
};

#elif defined(XMC1100_Boot_Kit) || defined(XMC1300_Boot_Kit) || defined(XMC1400_Boot_Kit)
XMC_SPI_t XMC_SPI_0 =
{
    .channel          = XMC_SPI0_CH0,
    .channel_config   = {
        .baudrate = 15984375U,
        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
    },
    .mosi             = {
        .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
        .pin  = (uint8_t)1
    },
    .mosi_config      = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .miso             = {
        .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
        .pin  = (uint8_t)0
    },
    .miso_config      = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source     = XMC_INPUT_C,
    .sclkout          = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)7
    },
    .sclkout_config   = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    }
};

#elif defined(XMC4400_Platform2GO)
XMC_SPI_t XMC_SPI_0 =
{
    .channel          = XMC_SPI1_CH1,
    .channel_config   = {
        .baudrate = 20003906U,
        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
    },
    .mosi             = {
        .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
        .pin  = (uint8_t)9
    },
    .mosi_config      = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
    .miso             = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)0
    },
    .miso_config      = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
    },
    .input_source     = XMC_INPUT_D,
    .sclkout = {
        .port = (XMC_GPIO_PORT_t*)PORT1_BASE,
        .pin  = (uint8_t)8
    },
    .sclkout_config   = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
};

#elif defined(XMC4700_Relax_Kit)
XMC_SPI_t XMC_SPI_0 =
{
    .channel          = XMC_SPI2_CH0,
    .channel_config   = {
        .baudrate = 20003906U,
        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
    },
    .mosi             = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)8
    },
    .mosi_config      = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
    .miso             = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)7
    },
    .miso_config      = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
    },
    .input_source     = XMC_INPUT_C,
    .sclkout = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)9
    },
    .sclkout_config   = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
};

XMC_SPI_t XMC_SPI_1 =
{
    .channel          = XMC_SPI0_CH1,
    .channel_config   = {
        .baudrate = 20003906U,
        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
    },
    .mosi = {
        .port   = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin    = (uint8_t)5
    },
    .mosi_config      = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
    .miso             = {
        .port = (XMC_GPIO_PORT_t*)PORT4_BASE,
        .pin  = (uint8_t)0
    },
    .miso_config      = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
    },
    .input_source     = XMC_INPUT_E,
    .sclkout = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)6
    },
    .sclkout_config   = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT4,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
};

XMC_SPI_t XMC_SPI_2 =
{
    .channel          = XMC_SPI2_CH1,
    .channel_config   = {
        .baudrate = 20003906U,
        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
    },
    .mosi             = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)11
    },
    .mosi_config      = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
    .miso             = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)12
    },
    .miso_config      = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
    },
    .input_source     = XMC_INPUT_D,
    .sclkout = {
        .port = (XMC_GPIO_PORT_t*)PORT3_BASE,
        .pin  = (uint8_t)13
    },
    .sclkout_config   = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
    },
};

// Will overwrite Serial
//XMC_SPI_t XMC_SPI_3 =
//{
//    .channel          = XMC_SPI0_CH0,
//    .channel_config   = {
//        .baudrate = 20003906U,
//        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
//        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
//        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
//    },
//    .mosi             = {
//        .port = (XMC_GPIO_PORT_t*)PORT5_BASE,
//        .pin  = (uint8_t)1
//    },
//    .mosi_config      = {
//        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,
//        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//    },
//    .miso             = {
//        .port = (XMC_GPIO_PORT_t*)PORT5_BASE,
//        .pin  = (uint8_t)0
//    },
//    .miso_config      = {
//        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
//    },
//    .input_source     = XMC_INPUT_D,
//    .sclkout = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)8
//    },
//    .sclkout_config   = {
//        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
//        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//    },
//};

// Will overwrite Serial1
//XMC_SPI_t XMC_SPI_4 =
//{
//    .channel          = XMC_SPI1_CH0,
//    .channel_config   = {
//        .baudrate = 20003906U,
//        .bus_mode = (XMC_SPI_CH_BUS_MODE_t)XMC_SPI_CH_BUS_MODE_MASTER,
//        .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
//        .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
//    },
//    .mosi             = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)5
//    },
//    .mosi_config      = {
//        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
//        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//    },
//    .miso             = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)4
//    },
//    .miso_config      = {
//        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
//    },
//    .input_source     = XMC_INPUT_A,
//    .sclkout = {
//        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
//        .pin  = (uint8_t)11
//    },
//    .sclkout_config   = {
//        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
//        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
//        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
//    },
//};
#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
