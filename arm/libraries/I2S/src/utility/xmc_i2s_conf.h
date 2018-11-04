#ifndef XMC_I2C_CONF_H
#define XMC_I2C_CONF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xmc_common.h"
#include "xmc_gpio.h"
#include "xmc_i2s.h"

#define BUFFER_SIZE 512

// only tested with 4700
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
/*U2C0*/
/*DX0C(Inpunt) -> P0.6*/
/*SCLKOUT(ALT6) -> P0.8*/
/*WA(ALT6) -> P0.9*/
#define MASTER_CHANNEL XMC_I2S0_CH1
#define MASTER_MRST PORT0, 6
#define INPUT_SOURCE USIC0_C1_DX0_P0_6
#define MASTER_SCLK PORT0, 8
#define MASTER_WACLK PORT0, 9

#endif

typedef struct XMC_I2S
{
    XMC_GPIO_CONFIG_t input_config;
    XMC_GPIO_CONFIG_t sclk_config;
    XMC_GPIO_CONFIG_t wa_config;
    XMC_I2S_CH_CONFIG_t i2s_ch_config;
    IRQn_Type receive_irq_num;
    uint32_t receive_irq_service_request;
    IRQn_Type protocol_irq_num;
    uint32_t protocol_irq_service_request;
} XMC_I2S_t;

extern XMC_I2S_t i2s_config;

#ifdef __cplusplus
}
#endif

#endif