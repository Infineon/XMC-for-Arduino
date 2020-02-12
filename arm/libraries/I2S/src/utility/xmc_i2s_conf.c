#include <Arduino.h>
#include "xmc_i2s_conf.h"

XMC_I2S_t i2s_config = {
#if defined(XMC4700_Relax_Kit)
    .input_config = {.mode = XMC_GPIO_MODE_INPUT_TRISTATE, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .sclk_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .wa_config = {.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .protocol_irq_num = (IRQn_Type)USIC2_2_IRQn,
    .protocol_irq_service_request = 2
#elif defined(XMC1100_XMC2GO) || defined(XMC1100_Boot_Kit)
    .input_config = {.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD, .mode = XMC_GPIO_MODE_INPUT_TRISTATE, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .sclk_config = {.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD, .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .wa_config = {.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD, .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7, .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH},
    .protocol_irq_num = (IRQn_Type)USIC0_2_IRQn,
    .protocol_irq_service_request = 2
#endif
};