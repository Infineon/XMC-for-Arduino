/**
 * @file xmc_spi_conf.c
 * @date 2016-11-18
 *
 * @cond
 */

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "xmc_spi_conf.h"

#if defined(XMC1100_XMC2GO)
XMC_SPI_t XMC_SPI_default =
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
        .pin  = (uint8_t)6
    },
    .mosi_config      = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    },
    .miso             = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)7
    },
    .miso_config      = {
        .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
    },
    .input_source     = XMC_INPUT_D,
    .sclkout          = {
        .port = (XMC_GPIO_PORT_t*)PORT0_BASE,
        .pin  = (uint8_t)8
    },
    .sclkout_config   = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7,
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    }
};

#elif defined(XMC1100_Boot_Kit)
XMC_SPI_t XMC_SPI_default =
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
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
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
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    }
};

#elif defined(XMC1300_Boot_Kit)
XMC_SPI_t XMC_SPI_default =
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
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
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
        .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
    }
};

#elif defined(XMC4700_Relax_Kit)
XMC_SPI_t XMC_SPI_default =
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

XMC_SPI_t XMC_SPI_for_xmc4_SD =
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
#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
