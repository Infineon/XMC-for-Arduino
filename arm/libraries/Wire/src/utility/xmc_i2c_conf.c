/**
 * @file xmc_i2c_conf.c
 * @date 2016-11-18
 *
 * @cond
 */


//****************************************************************************
// @Project Includes
//****************************************************************************
#include "xmc_i2c_conf.h"

#if defined(XMC1100_XMC2GO)
XMC_I2C_t XMC_I2C_default =
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
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)11
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0 = XMC_INPUT_F,
    .input_source_dx1 = XMC_INPUT_E,
    .slave_receive_irq_num                    = (IRQn_Type) 13,
    .slave_receive_irq_service_request        = 4 ,
    .slave_protocol_irq_num                   = (IRQn_Type) 14,
    .slave_protocol_irq_service_request       = 5
};

#elif defined(XMC1100_Boot_Kit)
XMC_I2C_t XMC_I2C_default =
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
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .scl              = {
        .port = (XMC_GPIO_PORT_t*)PORT2_BASE,
        .pin  = (uint8_t)0
    },
    .scl_config       = {
        .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .input_source_dx0 = XMC_INPUT_F,
    .input_source_dx1 = XMC_INPUT_E,
    .slave_receive_irq_num                    = (IRQn_Type) 13,
    .slave_receive_irq_service_request        = 4 ,
    .slave_protocol_irq_num                   = (IRQn_Type) 14,
    .slave_protocol_irq_service_request       = 5
};
#elif defined(XMC4700_Relax_Kit)
XMC_I2C_t XMC_I2C_default =
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
    .slave_protocol_irq_num                   = (IRQn_Type) 92,
    .slave_protocol_irq_service_request       = 2
};
#else
#error I2C not specified for selected board type
#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
