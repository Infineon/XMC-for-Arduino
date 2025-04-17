/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//****************************************************************************
// @Project Includes
//****************************************************************************
#include "Uart.h"
#include "Arduino.h"

//****************************************************************************
// @Local Functions
//****************************************************************************

// Constructors ////////////////////////////////////////////////////////////////

Uart::Uart(XMC_UART_t *xmc_uart_config, RingBuffer *rx_buffer) {
    _XMC_UART_config = xmc_uart_config;
    _rx_buffer = rx_buffer;
}

// Public Methods //////////////////////////////////////////////////////////////

void Uart::begin(unsigned long baud) { begin(baud, SERIAL_8N1); }

void Uart::begin(unsigned long baud, unsigned short config) {
    begin(baud, static_cast<XMC_UART_MODE_t>(config));
}

void Uart::begin(unsigned long baud, XMC_UART_MODE_t config) {
    XMC_UART_CH_CONFIG_t uart_ch_config;
    uart_ch_config.oversampling = 0; // Must be 0 or valid oversample for baud rate calculations
    uart_ch_config.baudrate = baud;
    uart_ch_config.data_bits = (uint8_t)(config & 0x00fU);
    uart_ch_config.frame_length = uart_ch_config.data_bits; // Set same as data bits length
    uart_ch_config.parity_mode = (XMC_USIC_CH_PARITY_MODE_t)(config & ~0xffU);
    uart_ch_config.stop_bits = (uint8_t)((config & 0x0f0U) >> 4);

    XMC_UART_CH_Init(_XMC_UART_config->channel, &uart_ch_config);

    // dx0 is UART RX: source must be set
    XMC_USIC_CH_SetInputSource(_XMC_UART_config->channel, XMC_USIC_CH_INPUT_DX0,
                               _XMC_UART_config->input_source_dx0);

    // Additional input multiplexing
    // Check if dx1 is used
    if (_XMC_UART_config->input_source_dx1 != XMC_INPUT_INVALID)
        XMC_USIC_CH_SetInputSource(_XMC_UART_config->channel, XMC_USIC_CH_INPUT_DX1,
                                   _XMC_UART_config->input_source_dx1);

    // Check if dx2 is used
    if (_XMC_UART_config->input_source_dx2 != XMC_INPUT_INVALID)
        XMC_USIC_CH_SetInputSource(_XMC_UART_config->channel, XMC_USIC_CH_INPUT_DX2,
                                   _XMC_UART_config->input_source_dx2);

    // Check if dx3 is used
    if (_XMC_UART_config->input_source_dx3 != XMC_INPUT_INVALID)
        XMC_USIC_CH_SetInputSource(_XMC_UART_config->channel, XMC_USIC_CH_INPUT_DX3,
                                   _XMC_UART_config->input_source_dx3);

    XMC_UART_CH_EnableEvent(_XMC_UART_config->channel, XMC_UART_CH_EVENT_ALTERNATIVE_RECEIVE |
                                                           XMC_UART_CH_EVENT_STANDARD_RECEIVE);
    XMC_USIC_CH_SetInterruptNodePointer(_XMC_UART_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE,
                                        _XMC_UART_config->irq_service_request);
    XMC_USIC_CH_SetInterruptNodePointer(_XMC_UART_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_ALTERNATE_RECEIVE,
                                        _XMC_UART_config->irq_service_request);
    XMC_USIC_CH_SetInterruptNodePointer(_XMC_UART_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_TRANSMIT_BUFFER,
                                        _XMC_UART_config->irq_service_request);
    NVIC_SetPriority(_XMC_UART_config->irq_num, 3);
    NVIC_EnableIRQ(_XMC_UART_config->irq_num);

    XMC_UART_CH_Start(_XMC_UART_config->channel);

    // TX pin setup put here to avoid startup corrupted characters being first sent
    XMC_GPIO_Init(_XMC_UART_config->tx.port, _XMC_UART_config->tx.pin,
                  &(_XMC_UART_config->tx_config));

    XMC_GPIO_Init(_XMC_UART_config->rx.port, _XMC_UART_config->rx.pin,
                  &(_XMC_UART_config->rx_config));
}

void Uart::end(void) {
    // Wait for any outstanding data to be sent
    flush();
    // Disable UART interrupt in NVIC
    NVIC_DisableIRQ(_XMC_UART_config->irq_num);
    // Clear any received data after stopping interrupts
    _rx_buffer->clear();
}

void Uart::setInterruptPriority(uint32_t priority) {
    NVIC_SetPriority(_XMC_UART_config->irq_num, priority & 0x03);
}

uint32_t Uart::getInterruptPriority() { return NVIC_GetPriority(_XMC_UART_config->irq_num); }

int Uart::available(void) { return _rx_buffer->available(); }

int Uart::availableForWrite(void) {
    return 1;
} // TODO: there are no tx buffer so we awaly have 1 byte available

int Uart::peek(void) { return _rx_buffer->peek(); }

int Uart::read(void) { return _rx_buffer->read_char(); }

void Uart::flush(void) {
    while (XMC_USIC_CH_GetTransmitBufferStatus(_XMC_UART_config->channel) ==
           XMC_USIC_CH_TBUF_STATUS_BUSY) {
    };
}

size_t Uart::write(const uint8_t uc_data) {
    // For sending, write immediately
    // This API already have a check for available buffer
    XMC_UART_CH_Transmit(_XMC_UART_config->channel, uc_data);
    return 1;
}

void Uart::IrqHandler(void) {
    // Receive data Interrupt handler
    uint32_t status = XMC_UART_CH_GetStatusFlag(_XMC_UART_config->channel);

    // Did we receive data?
    if ((status & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                   XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) != 0U) {
        XMC_UART_CH_ClearStatusFlag(_XMC_UART_config->channel,
                                    (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                     XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION));

        while (_XMC_UART_config->channel->RBUFSR &
               (USIC_CH_RBUFSR_RDV0_Msk | USIC_CH_RBUFSR_RDV1_Msk))
            _rx_buffer->store_char(XMC_UART_CH_GetReceivedData(_XMC_UART_config->channel));
    }
}

//****************************************************************************
//                                 END OF FILE
//****************************************************************************