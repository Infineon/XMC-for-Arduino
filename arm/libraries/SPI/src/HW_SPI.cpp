/*
 * SPI Master library.
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * This library has been modified for the XMC microcontroller series.
 */

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "SPI.h"
#if !defined(USE_SW_SPI)
#include "Wire.h"

//swap SPI_default and SPI_for_xmc_SD if desired by user
#if defined(USE_XMC_RELAX_KIT_SD) && defined(XMC_SPI_for_xmc_SD)
SPIClass SPI(&XMC_SPI_for_xmc_SD);
#if (NUM_SPI > 1)
SPIClass SPI1(&XMC_SPI_default);
#endif
uint8_t SS   = PIN_SPI_SS_SD  ;
uint8_t MOSI = PIN_SPI_MOSI_SD;
uint8_t MISO = PIN_SPI_MISO_SD;
uint8_t SCK  = PIN_SPI_SCK_SD ;
#else // normal behaviour 
SPIClass SPI(&XMC_SPI_default);
#if (NUM_SPI > 1)
SPIClass SPI1(&XMC_SPI_1);
#endif
uint8_t SS   = PIN_SPI_SS   ;
uint8_t MOSI = PIN_SPI_MOSI ;
uint8_t MISO = PIN_SPI_MISO ;
uint8_t SCK  = PIN_SPI_SCK  ;
#endif

#if (NUM_SPI > 2)
SPIClass SPI2(&XMC_SPI_2);
#if (NUM_SPI > 3)
SPIClass SPI3(&XMC_SPI_3);
#if (NUM_SPI > 4)
SPIClass SPI4(&XMC_SPI_4);
#endif
#endif
#endif



SPISettings DEFAULT_SPI_SETTINGS;

//****************************************************************************
// @Local Functions
//****************************************************************************


// Public Methods //////////////////////////////////////////////////////////////

void SPIClass::begin()
{
    // Check if desire USIC channel is already in use
	if((XMC_SPI_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_I2C)
	{
		Wire.end();
	}

    init();

    setBitOrder(DEFAULT_SPI_SETTINGS.bitOrder);

    setDataMode(DEFAULT_SPI_SETTINGS.dataMode);

    XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, DEFAULT_SPI_SETTINGS.clockFreq);
}

void SPIClass::init()
{
    if (initialized)
    {
        return;
    }

    /* LLD initialization */
    XMC_SPI_CH_Init(XMC_SPI_config->channel, &(XMC_SPI_config->channel_config));

    /* Configure the data input line selected */
    XMC_SPI_CH_SetInputSource(XMC_SPI_config->channel, XMC_SPI_CH_INPUT_DIN0, (uint8_t)XMC_SPI_config->input_source);

    /* Configure the input pin properties */
    XMC_GPIO_Init((XMC_GPIO_PORT_t*)XMC_SPI_config->miso.port, (uint8_t)XMC_SPI_config->miso.pin, &(XMC_SPI_config->miso_config));

    /* Configure the output pin properties */
    XMC_GPIO_Init((XMC_GPIO_PORT_t*)XMC_SPI_config->mosi.port, (uint8_t)XMC_SPI_config->mosi.pin, &(XMC_SPI_config->mosi_config));

    /* Initialize SPI SCLK out pin */
    XMC_GPIO_Init((XMC_GPIO_PORT_t*)XMC_SPI_config->sclkout.port, (uint8_t)XMC_SPI_config->sclkout.pin, &(XMC_SPI_config->sclkout_config));

    /* Start the SPI_Channel */
    XMC_SPI_CH_Start(XMC_SPI_config->channel);

    interruptMode = SPI_IMODE_NONE;
    interruptSave = 0;
    interruptMask = 0;
    initialized = true;
}

void SPIClass::end()
{
    // Only disable HW when USIC is used for SPI
	if((XMC_SPI_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI)
	{
		XMC_GPIO_CONFIG_t default_input_port_config = {
            .mode = XMC_GPIO_MODE_INPUT_TRISTATE,
            .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
#if UC_FAMILY == XMC1
            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
#endif
        };
		
		XMC_GPIO_CONFIG_t default_output_port_config = {
            .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
            .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
#if UC_FAMILY == XMC1
            .input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
#endif
        };

		XMC_SPI_CH_Stop(XMC_SPI_config->channel);

		XMC_GPIO_Init((XMC_GPIO_PORT_t*)XMC_SPI_config->miso.port, (uint8_t)XMC_SPI_config->miso.pin, &default_input_port_config);
		XMC_GPIO_Init((XMC_GPIO_PORT_t*)XMC_SPI_config->mosi.port, (uint8_t)XMC_SPI_config->mosi.pin, &default_output_port_config);
		XMC_GPIO_Init((XMC_GPIO_PORT_t*)XMC_SPI_config->sclkout.port, (uint8_t)XMC_SPI_config->sclkout.pin, &default_output_port_config);

		XMC_SPI_config->channel->DXCR[XMC_USIC_CH_INPUT_DX0] = (uint32_t)(XMC_SPI_config->channel->DXCR[XMC_USIC_CH_INPUT_DX0] | (USIC_CH_DX0CR_DSEN_Msk)) & (~USIC_CH_DX0CR_INSW_Msk);
		XMC_USIC_CH_SetInputSource(XMC_SPI_config->channel, XMC_USIC_CH_INPUT_DX0, XMC_INPUT_A);
	}

    initialized = false;
}

/*
// Function not used here
void SPIClass::usingInterrupt(int interruptNumber)
{

}
*/

void SPIClass::beginTransaction(SPISettings settings)
{
    // Check if desire USIC channel is already in use
	if((XMC_SPI_config->channel->CCR & USIC_CH_CCR_MODE_Msk) != XMC_USIC_CH_OPERATING_MODE_SPI)
	{
		SPI.begin();
	}
    setBitOrder(settings.bitOrder);
    setDataMode(settings.dataMode);
    XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, settings.clockFreq);

    // TODO: Do sth with SS?
}

void SPIClass::endTransaction(void)
{
    // TODO: inTransactionFlag and interrupt not use
}

void SPIClass::setBitOrder(uint8_t order)
{
    if (order == LSBFIRST)
    {
        XMC_SPI_CH_SetBitOrderLsbFirst(XMC_SPI_config->channel);
    }
    else
    {
        XMC_SPI_CH_SetBitOrderMsbFirst(XMC_SPI_config->channel);
    }
}

void SPIClass::setDataMode(uint8_t mode)
{
    switch (mode)
    {
        case SPI_MODE0:
            // Low if inactive, transmit on falling clock, receive on raising clock edge
            XMC_SPI_CH_ConfigureShiftClockOutput(XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
            break;

        case SPI_MODE1:
            // Low if inactive, transmit on rising clock, receive on falling clock edge
            XMC_SPI_CH_ConfigureShiftClockOutput(XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
            break;

        case SPI_MODE2:
            // High if inactive, transmit on rising clock, receive on falling clock edge
            XMC_SPI_CH_ConfigureShiftClockOutput(XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_ENABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
            break;

        case SPI_MODE3:
            // High if inactive, transmit on falling clock, receive on raising clock edge
            XMC_SPI_CH_ConfigureShiftClockOutput(XMC_SPI_config->channel, XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
            break;

        default:
            break;
    }
}

void SPIClass::setClockDivider(uint8_t div)
{
    switch (div)
    {
        case SPI_CLOCK_DIV2:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 8000000U);
            break;

        case SPI_CLOCK_DIV4:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 4000000U);
            break;

        case SPI_CLOCK_DIV8:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 2000000U);
            break;

        case SPI_CLOCK_DIV16:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 1000000U);
            break;

        case SPI_CLOCK_DIV32:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 500000U);
            break;

        case SPI_CLOCK_DIV64:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 250000U);
            break;

        case SPI_CLOCK_DIV128:
            XMC_SPI_CH_SetBaudrate(XMC_SPI_config->channel, 125000U);
            break;

        default:
            break;
    }
}

uint8_t SPIClass::transfer(uint8_t data_out)
{
    uint8_t data_in = 0;

    /* Clear RBF0 */
    (void)XMC_SPI_CH_GetReceivedData(XMC_SPI_config->channel);
    /* Clear RBF1 */
    (void)XMC_SPI_CH_GetReceivedData(XMC_SPI_config->channel);

    /*Sending a byte*/
    XMC_SPI_CH_Transmit(XMC_SPI_config->channel, data_out, XMC_SPI_CH_MODE_STANDARD);

    /*Wait till the byte has been transmitted*/
    while ((XMC_SPI_CH_GetStatusFlag(XMC_SPI_config->channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
    XMC_SPI_CH_ClearStatusFlag(XMC_SPI_config->channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

    while (XMC_USIC_CH_GetReceiveBufferStatus(XMC_SPI_config->channel) == 0U);

    data_in = XMC_SPI_CH_GetReceivedData(XMC_SPI_config->channel);

    XMC_SPI_CH_ClearStatusFlag(XMC_SPI_config->channel, ((uint32_t)XMC_SPI_CH_STATUS_FLAG_RECEIVE_INDICATION | (uint32_t)XMC_SPI_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION));

    return data_in;
}

void SPIClass::attachInterrupt()
{
    // Should be enableInterrupt()
}

void SPIClass::detachInterrupt()
{
    // Should be disableInterrupt()
}

#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
