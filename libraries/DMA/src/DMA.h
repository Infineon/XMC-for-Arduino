/**
 * DMA.h - Library for Arduino to control the GPDMA of the XMC4000 series.
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
#ifndef DMA_H_
#define DMA_H_

#if (UC_FAMILY == XMC4)

#include <xmc_dma.h>

#define PERIPH_SUPPORTED 9

// check if supported by board
#define DMA0  	XMC_DMA0
#define DMA1 	XMC_DMA1

typedef struct
{
	uint32_t 				base_add;
	uint32_t 				receive_add;
	uint32_t 				transmitt_add;
	uint8_t 				request;	// DMA_PERIPHERAL REQUEST
} peripherial_t;

enum burstlength_t	{
	BURST_LENGTH_1 = XMC_DMA_CH_BURST_LENGTH_1,
	BURST_LENGTH_4 =  XMC_DMA_CH_BURST_LENGTH_4,
	BURST_LENGTH_8 =  XMC_DMA_CH_BURST_LENGTH_8
};
enum transferwidth_t	{
	TRANSFER_WIDTH_8 = XMC_DMA_CH_TRANSFER_WIDTH_8,
	TRANSFER_WIDTH_16 =  XMC_DMA_CH_TRANSFER_WIDTH_16,
	TRANSFER_WIDTH_32 =  XMC_DMA_CH_TRANSFER_WIDTH_32
};
enum  event_t{
	TRANSFER_COMPLETE = XMC_DMA_CH_EVENT_TRANSFER_COMPLETE       	 	,	/**< Transfer complete event */
	BLOCK_TRANSFER_COMPLETE = XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE  ,	/**< Block transfer complete event */
	SRC_TRANSACTION_COMPLETE = XMC_DMA_CH_EVENT_SRC_TRANSACTION_COMPLETE ,	/**< Source transaction complete event */
	DST_TRANSACTION_COMPLETE = XMC_DMA_CH_EVENT_DST_TRANSACTION_COMPLETE ,	/**< Destination transaction complete event */
	ERROR =	XMC_DMA_CH_EVENT_ERROR     										/**< DMA error event */
};


/* Include only these peripherals for now : USIC- SPI  UART;
 * Check for later I2C I2S CCU40, ADC, CAN, HWPR, ERU  */


enum periph_t {
	UART0_CH0 = 00,
	UART0_CH1 = 01,
	UART1_CH0 = 10,
	UART1_CH1 = 11,
	UART2_CH0 = 20,	// SPI_2 and UART2 only with DMA1
	UART2_CH1 = 21,	// SPI_2 and UART2 only with DMA1
	SPI0_CH0  = 00,
	SPI0_CH1  = 01,
	SPI1_CH0  = 10,
	SPI1_CH1  = 11,
	SPI2_CH0  = 20,	// SPI_2 and UART2 only with DMA1
	SPI2_CH1  = 21,	// SPI_2 and UART2 only with DMA1

	I2S2_CH0 = 20,
};


class DMA {
	
private:
	void setupPeripherialAddresses();
	XMC_DMA_CH_CONFIG_t dma_ch_config;
	peripherial_t   periph_address[3][3];

public:	
	DMA()
	{}

	void beginDMA(XMC_DMA_t *const _dma);
	void endDMA();
	
	// Configure DMA 
	void configDMA_M2M(XMC_DMA_t *const dma, uint8_t channel, uint32_t src_addr, uint32_t dst_addr, uint16_t block_size, transferwidth_t transfer_width, burstlength_t burst_length, bool enable_interrupt);
	void configDMA_M2P(XMC_DMA_t *const dma, uint8_t channel, periph_t periph, uint32_t src_addr, uint16_t block_size, transferwidth_t m_transfer_width, transferwidth_t p_transfer_width, burstlength_t m_burst_length, burstlength_t p_burst_length, bool enable_interrupt);
	void configDMA_P2M(XMC_DMA_t *const dma, uint8_t channel, periph_t periph, uint32_t dst_addr, uint16_t block_size, transferwidth_t m_transfer_width, transferwidth_t p_transfer_width, burstlength_t m_burst_length, burstlength_t p_burst_length, bool enable_interrupt);
	// TODO: P2P not tested. Since only UART worked. After finishing SPI or I2C, test this method
	void configDMA_P2P(XMC_DMA_t *const dma, uint8_t channel, periph_t src_periph, periph_t dst_periph, uint16_t block_size, transferwidth_t m_transfer_width, transferwidth_t p_transfer_width, burstlength_t m_burst_length, burstlength_t p_burst_length, bool enable_interrupt);


	// If wanted to control other possibilities, this form should be used 
	// TODO:
	void configDMA(XMC_DMA_t *const dma, uint8_t channel, XMC_DMA_CH_CONFIG_t dma_config);

	// Interrupt configuration
	void attachDMAInterrupt(XMC_DMA_t *const  dma, uint8_t channel, interrupt_cb_t _event_handler,event_t event);
	void detachDMAInterrupt(XMC_DMA_t *const  dma, uint8_t channel,  XMC_DMA_CH_EVENT_t event);

	void beginDMATransaction(XMC_DMA_t *const _dma, uint8_t channel);
};

#else // UC_FAMILY != XMC4
#error "DMA is not supported on your board!"
#endif

#endif /* DMA_H_ */

