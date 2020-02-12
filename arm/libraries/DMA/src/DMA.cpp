/**
 * DMA.cpp - Library for Arduino to control the GPDMA of the XMC4000 series.
 *
 * The General Purposes Direct Memory Access (GPDMA) is a module within the XMC4000 series to transfer data
 * without any CPU interference. When a DMA transfer request is generated, the GPDMA transfers data stored
 * at the source address to the destination address.
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
#include <Arduino.h>
#include "DMA.h"

static interrupt_cb_t event_handler = NULL;
event_t event;

void DMA::beginDMA(XMC_DMA_t *const dma)
{
	XMC_DMA_Init(dma);
	setupPeripherialAddresses();
}

/* Configure DMA to copy data from memory to memory
 * @param (value)
 * 				dma	 	(DMA0 or DMA1)
 * 				channel (0-7  or  0-3)
 * 				src_addr() data source address
 * 				dst_addr() data destination address
 * 				block_size() block size
 * 				transfer_width (8 - 16 - 32)
 * 				burst_length (1 - 4 - 8)
 * 				enable_interrupt 1:enabled, 0:disabled
 *
 * */
void DMA::configDMA_M2M(XMC_DMA_t *const dma, uint8_t channel, uint32_t src_addr, uint32_t dst_addr, uint16_t block_size, transferwidth_t transfer_width, burstlength_t burst_length, bool enable_interrupt)
{
	dma_ch_config.src_addr = src_addr;
	dma_ch_config.dst_addr = dst_addr;
	dma_ch_config.block_size = block_size;
	dma_ch_config.src_transfer_width = transfer_width;
	dma_ch_config.dst_transfer_width = transfer_width;
	dma_ch_config.enable_interrupt = enable_interrupt;
	dma_ch_config.src_burst_length = burst_length;
	dma_ch_config.dst_burst_length = burst_length;
	dma_ch_config.transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
	dma_ch_config.transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2M_DMA;
	XMC_DMA_CH_Init(dma, channel, &dma_ch_config);
}

/* Configure DMA to copy data from memory to peripheral as single block
 * @param (value)
 * 				dma	 	(DMA0 or DMA1)
 * 				channel (0-7  or  0-3)
 * 				src_addr() data source address
 * 				periph() destination data address / peripheral tx
 * 				block_size() block size
 * 				m_transfer_width (8 - 16 - 32) memory transfer width
 * 				p_transfer_width (8 - 16 - 32) peripheral transfer width
 * 				m_burst_length (1 - 4 - 8)	memory burst length
 * 				p_burst_length (1 - 4 - 8) peripheral burst length
 * 				enable_interrupt 1:enabled, 0:disabled
 *
 * */
void DMA::configDMA_M2P(XMC_DMA_t *const dma, uint8_t channel, periph_t periph, uint32_t src_addr, uint16_t block_size, transferwidth_t m_transfer_width, transferwidth_t p_transfer_width, burstlength_t m_burst_length, burstlength_t p_burst_length, bool enable_interrupt)
{
	dma_ch_config.src_addr = src_addr;
	// map the address from 11 to [1][1]
	dma_ch_config.dst_addr = periph_address[periph / 10][periph % 10].transmitt_add;
	dma_ch_config.block_size = block_size;
	dma_ch_config.src_transfer_width = m_transfer_width;
	dma_ch_config.dst_transfer_width = p_transfer_width;
	dma_ch_config.src_burst_length = m_burst_length;
	dma_ch_config.dst_burst_length = p_burst_length;
	dma_ch_config.enable_interrupt = enable_interrupt;
	// If peripheral is used, then peripheral request should be set up
	dma_ch_config.dst_peripheral_request = periph_address[periph / 10][periph % 10].request;

	// For single block data transfer these are constant settings:
	dma_ch_config.src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
	dma_ch_config.dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
	dma_ch_config.transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA;
	dma_ch_config.transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
	dma_ch_config.dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE;

	XMC_DMA_CH_Init(dma, channel, &dma_ch_config);
	XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t *const)periph_address[periph/10][periph % 10].base_add, periph/10);
}

/* Configure DMA to copy data from peripheral to memory as single block
 * @param (value)
 * 				dma	 	(DMA0 or DMA1)
 * 				channel (0-7  or  0-3)
 * 				periph() source data address / peripheral rx
 * 				dst_addr() data destination address
 * 				block_size() block size
 * 				m_transfer_width (8 - 16 - 32) memory transfer width
 * 				p_transfer_width (8 - 16 - 32) peripheral transfer width
 * 				m_burst_length (1 - 4 - 8)	memory burst length
 * 				p_burst_length (1 - 4 - 8) peripheral burst length
 * 				enable_interrupt 1:enabled, 0:disabled *
 * */
void DMA::configDMA_P2M(XMC_DMA_t *const dma, uint8_t channel, periph_t periph, uint32_t dst_addr, uint16_t block_size, transferwidth_t m_transfer_width, transferwidth_t p_transfer_width, burstlength_t m_burst_length, burstlength_t p_burst_length, bool enable_interrupt)
{
	dma_ch_config.dst_addr = dst_addr;
	dma_ch_config.src_addr = periph_address[periph / 10][periph % 10].receive_add;
	dma_ch_config.block_size = block_size;
	dma_ch_config.src_transfer_width = p_transfer_width;
	dma_ch_config.dst_transfer_width = m_transfer_width;
	dma_ch_config.src_burst_length = p_burst_length;
	dma_ch_config.dst_burst_length = m_burst_length;
	dma_ch_config.enable_interrupt = enable_interrupt;
	// If peripheral is used, then peripheral request should be set up
		// dma_ch_config.dst_peripheral_request =  periph_address[periph/10][periph - (periph/10)*10].request;	// DMA in P2M mode, therefore source sends service request
	dma_ch_config.src_peripheral_request = periph_address[periph / 10][periph % 10].request;

	// For single block data transfer these are constant settings:
	dma_ch_config.dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
	dma_ch_config.src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
	dma_ch_config.transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_P2M_DMA;
	dma_ch_config.transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
	dma_ch_config.src_handshaking = XMC_DMA_CH_SRC_HANDSHAKING_HARDWARE;

	XMC_DMA_CH_Init(dma, channel, &dma_ch_config);
	XMC_USIC_CH_TriggerServiceRequest((XMC_USIC_CH_t *const)XMC_USIC2_CH0, periph/10);
}

/* Configure DMA to copy data from peripheral to peripheral as single block
 * @param (value)
 * 				dma	 	(DMA0 or DMA1)
 * 				channel (0-7  or  0-3)
 * 				src_periph() source data address / peripheral rx
 * 				dst_periph() source data address / peripheral tx
 * 				block_size() block size
 * 				src_transfer_width (8 - 16 - 32) source transfer width
 * 				dst_transfer_width (8 - 16 - 32) destination transfer width
 * 				src_burst_length (1 - 4 - 8)	source burst length
 * 				dst_burst_length (1 - 4 - 8) 	destination burst length
 * 				enable_interrupt 1:enabled, 0:disabled *
 * */
void DMA::configDMA_P2P(XMC_DMA_t *const dma, uint8_t channel, periph_t src_periph, periph_t dst_periph, uint16_t block_size, transferwidth_t src_transfer_width, transferwidth_t dst_transfer_width, burstlength_t src_burst_length, burstlength_t dst_burst_length, bool enable_interrupt)
{
	dma_ch_config.dst_addr = periph_address[dst_periph / 10][dst_periph % 10].transmitt_add;
	dma_ch_config.src_addr = periph_address[src_periph / 10][src_periph % 10].receive_add;
	dma_ch_config.block_size = block_size;
	dma_ch_config.src_transfer_width = src_transfer_width;
	dma_ch_config.dst_transfer_width = dst_transfer_width;
	dma_ch_config.src_burst_length = src_burst_length;
	dma_ch_config.dst_burst_length = dst_burst_length;
	dma_ch_config.enable_interrupt = enable_interrupt;
	dma_ch_config.dst_peripheral_request = periph_address[dst_periph / 10][dst_periph % 10].request;
	dma_ch_config.dst_peripheral_request = periph_address[src_periph / 10][src_periph % 10].request;

	// For single block data transfer these are constant settings:
	dma_ch_config.dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
	dma_ch_config.src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE;
	dma_ch_config.transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_P2M_DMA;
	dma_ch_config.transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
	dma_ch_config.dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE;

	XMC_DMA_CH_Init(dma, channel, &dma_ch_config);
}

void DMA::attachDMAInterrupt(XMC_DMA_t *const dma, uint8_t channel, interrupt_cb_t _event_handler, event_t _event)
{
	event = _event;
	XMC_DMA_CH_EnableEvent(dma, channel, event);

	/* Enable DMA event handling */
	if (dma == DMA0)
	{
		NVIC_SetPriority(GPDMA0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
		NVIC_EnableIRQ(GPDMA0_0_IRQn);
	}
	else
	{
		NVIC_SetPriority(GPDMA1_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
		NVIC_EnableIRQ(GPDMA1_0_IRQn);
	}
	if (_event_handler != NULL)
		event_handler = _event_handler;
}

void DMA::detachDMAInterrupt(XMC_DMA_t *const dma, uint8_t channel, XMC_DMA_CH_EVENT_t event)
{
	XMC_DMA_CH_DisableEvent(dma, channel, event);

	/* Enable DMA event handling */
	if (dma == DMA0)
	{
		NVIC_DisableIRQ(GPDMA0_0_IRQn);
	}
	else
	{
		NVIC_DisableIRQ(GPDMA1_0_IRQn);
	}
	event_handler = NULL;
}

void DMA::beginDMATransaction(XMC_DMA_t *const _dma, uint8_t channel)
{
	XMC_DMA_CH_Enable(_dma, channel);
}

// TODO: Optimize this routine
void DMA::setupPeripherialAddresses()
{

	// i.e map 10 to [1][0] : buggy? index overwritten

	periph_address[UART0_CH0 / 10][UART0_CH0 % 10] = {(uint32_t)(XMC_USIC0_CH0), (uint32_t) & (XMC_USIC0_CH0->RBUF), (uint32_t) & (XMC_USIC0_CH0->TBUF[0]), DMA_PERIPHERAL_REQUEST(0, 10)};
	periph_address[UART0_CH1 / 10][UART0_CH1 % 10] = {(uint32_t)(XMC_USIC0_CH1), (uint32_t) & (XMC_USIC0_CH1->RBUF), (uint32_t) & (XMC_USIC0_CH1->TBUF[0]), DMA_PERIPHERAL_REQUEST(1, 10)};

	periph_address[UART1_CH0 / 10][UART1_CH0 % 10] = {(uint32_t)(XMC_USIC1_CH0), (uint32_t) & (XMC_USIC1_CH0->RBUF), (uint32_t) & (XMC_USIC1_CH0->TBUF[0]), DMA_PERIPHERAL_REQUEST(0, 11)};
	periph_address[UART1_CH1 / 10][UART1_CH1 % 10] = {(uint32_t)(XMC_USIC1_CH1), (uint32_t) & (XMC_USIC1_CH1->RBUF), (uint32_t) & (XMC_USIC1_CH1->TBUF[0]), DMA_PERIPHERAL_REQUEST(1, 11)};

	periph_address[SPI0_CH0 / 10][SPI0_CH0 % 10] = {(uint32_t)(XMC_USIC0_CH0), (uint32_t) & (XMC_USIC0_CH0->RBUF), (uint32_t) & (XMC_USIC0_CH0->TBUF[0]), DMA_PERIPHERAL_REQUEST(0, 10)};
	periph_address[SPI0_CH1 / 10][SPI0_CH1 % 10] = {(uint32_t)(XMC_USIC0_CH1), (uint32_t) & (XMC_USIC0_CH1->RBUF), (uint32_t) & (XMC_USIC0_CH1->TBUF[0]), DMA_PERIPHERAL_REQUEST(1, 10)};

	periph_address[SPI2_CH0 / 10][SPI2_CH0 % 10] = {(uint32_t)(XMC_USIC2_CH0), (uint32_t) & (XMC_USIC2_CH0->RBUF1), (uint32_t) & (XMC_USIC2_CH0->TBUF[4]), DMA1_PERIPHERAL_REQUEST_USIC2_SR0_8}; // The DMA_PERIPHERAL REQUEST value has been tested with SPI2_CH0
	periph_address[SPI2_CH1 / 10][SPI2_CH1 % 10] = {(uint32_t)(XMC_USIC2_CH1), (uint32_t) & (XMC_USIC2_CH1->RBUF), (uint32_t) & (XMC_USIC2_CH1->TBUF[4]), DMA_PERIPHERAL_REQUEST(0, 7)};

	// for I2S
	periph_address[I2S2_CH0 / 10][I2S2_CH0 % 10] = {(uint32_t)(XMC_USIC2_CH0), (uint32_t) & (XMC_USIC2_CH0->OUTR), (uint32_t) & (XMC_USIC2_CH0->TBUF[4]), DMA_PERIPHERAL_REQUEST(0, 7)}; // service request number?
}

#ifdef __cplusplus
extern "C"
{
#endif

	void GPDMA0_0_IRQHandler(void)
	{
		XMC_DMA_CH_ClearEventStatus(XMC_DMA0, 0, event);
		if (event_handler)
			event_handler();
	}
	void GPDMA1_0_IRQHandler(void)
	{
		XMC_DMA_CH_ClearEventStatus(XMC_DMA1, 0, event);
		if (event_handler)
			event_handler();
	}
#ifdef __cplusplus
}
#endif
