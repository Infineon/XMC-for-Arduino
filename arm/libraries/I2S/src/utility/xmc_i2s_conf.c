
#include "xmc_i2s_conf.h"

XMC_I2S_t i2s_config = {

    .input_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
#if (UC_FAMILY == XMC4)
    .sclk_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .wa_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .protocol_irq_num = (IRQn_Type)USIC2_2_IRQn,
    .protocol_irq_service_request = 2,
// .receive_irq_num = (IRQn_Type)USIC2_1_IRQn,
// .receive_irq_service_request = 1,
#else
    .sclk_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .wa_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .protocol_irq_num = (IRQn_Type)USIC0_2_IRQn,
    .protocol_irq_service_request = 2,
#endif
    .i2s_ch_config = {
// Specs for the Adafruit mic
// 1 frame = 32 bits, 1 data word = 16 bits => 1 frame = 2 words
// 1411200 = 44.1 kHz * 32 bits/sample, 2 channels
#if (UC_FAMILY == XMC4)
        .baudrate = 1411200U * 2,
#else
        .baudrate = 768000,
#endif
        .data_bits = 16,
        .frame_length = 32,
        .data_delayed_sclk_periods = 1, // minimum delay, might need to be adjusted for different mics
        .bus_mode = XMC_I2S_CH_BUS_MODE_MASTER,
        .wa_inversion = XMC_I2S_CH_WA_POLARITY_DIRECT}};
