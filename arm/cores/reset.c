/**
 * reset.c - Handling the reset for the XMC1100 Boot Kit.
 *
 * Have a look at the application note/reference manual for more information.
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
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
#include <reset.h>
#ifdef XMC1100_Boot_Kit
#include <xmc_eru.h>
#include <xmc_scu.h>

//****************************************************************************
// @Local Functions
//****************************************************************************

void ERU0_0_IRQHandler(void)
{
    XMC_SCU_RESET_ClearDeviceResetReason();
    XMC_SCU_RESET_AssertMasterReset();
}

void reset_init(void) {
    // Configuring the generation of the reset event
    static XMC_ERU_ETL_CONFIG_t reset_event_generator_config;
    reset_event_generator_config.enable_output_trigger = true;
    reset_event_generator_config.status_flag_mode = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL;
    reset_event_generator_config.edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING;
    reset_event_generator_config.output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0;  
    reset_event_generator_config.source = XMC_ERU_ETL_SOURCE_A;
    reset_event_generator_config.input = ERU0_ETL0_INPUTA_P2_4;
    // Configuring the detection of the reset event
    static XMC_ERU_OGU_CONFIG_t reset_event_detection_config;
    reset_event_detection_config.service_request = XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER;

    XMC_ERU_ETL_Init(ERU0_ETL0, &reset_event_generator_config);
    XMC_ERU_OGU_Init(ERU0_OGU0, &reset_event_detection_config);

    XMC_GPIO_CONFIG_t config_reset;
    config_reset.mode = XMC_GPIO_MODE_INPUT_PULL_UP;
    // Set large threshold for improved noise immunity on reset pin
    config_reset.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_LARGE;
    XMC_GPIO_Init(P2_4, &config_reset);

    NVIC_SetPriority(ERU0_0_IRQn, 3U);
    NVIC_EnableIRQ(ERU0_0_IRQn);
}
#endif
