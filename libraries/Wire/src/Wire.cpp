#include "Arduino.h"
#include "Wire.h"

TwoWire::TwoWire(XMC_I2C_t *conf) {
    XMC_I2C_config = conf;

    hasError = false;
    isMaster = false;
    inRepStart = false;

    transmitting = 0;
    timeout = WIRE_COMMUNICATION_TIMEOUT;

    slaveAddress = 0;
    txAddress = 0;

    user_onReceive = nullptr;
    user_onRequest = nullptr;
    rx_ringBuffer.clear();
    tx_ringBuffer.clear();
    pre_rx_ringBuffer.clear();
}

void TwoWire::begin(void) {
    // To-Do for future work need to check
    // Check if desire USIC channel is already in use
    // if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI)
    // {
    //     SPI.end();
    // }
    hasError = false;
    isMaster = true;

    XMC_I2C_CH_Init(XMC_I2C_config->channel, &(XMC_I2C_config->channel_config));
    XMC_USIC_CH_SetInputSource(XMC_I2C_config->channel, XMC_USIC_CH_INPUT_DX0,
                               XMC_I2C_config->input_source_dx0);
    XMC_USIC_CH_SetInputSource(XMC_I2C_config->channel, XMC_USIC_CH_INPUT_DX1,
                               XMC_I2C_config->input_source_dx1);
    /* configure i2c tx fifo */
    XMC_USIC_CH_TXFIFO_Configure(XMC_I2C_config->channel, 16, XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                 (uint32_t)15);
    /* configure i2c rx fifo */
    XMC_USIC_CH_RXFIFO_Configure(XMC_I2C_config->channel, 0, XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                 (uint32_t)(15));

    XMC_USIC_CH_SetInterruptNodePointer(XMC_I2C_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL,
                                        XMC_I2C_config->protocol_irq_service_request);

    NVIC_SetPriority((IRQn_Type)XMC_I2C_config->protocol_irq_num, 3U);
    NVIC_EnableIRQ((IRQn_Type)XMC_I2C_config->protocol_irq_num);

    XMC_I2C_CH_EnableEvent(XMC_I2C_config->channel,
                           (uint32_t)(XMC_I2C_CH_EVENT_NACK | XMC_I2C_CH_EVENT_DATA_LOST |
                                      XMC_I2C_CH_EVENT_ARBITRATION_LOST | XMC_I2C_CH_EVENT_ERROR));

    XMC_I2C_CH_Start(XMC_I2C_config->channel);

    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_I2C_config->sda.port, (uint8_t)XMC_I2C_config->sda.pin,
                  &(XMC_I2C_config->sda_config));
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_I2C_config->scl.port, (uint8_t)XMC_I2C_config->scl.pin,
                  &(XMC_I2C_config->scl_config));
}

void TwoWire::begin(uint8_t address) {
    // To-Do for future work need to check
    //  Check if desire USIC channel is already in use
    //  if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI)
    //  {
    //      SPI.end();
    //  }
    isMaster = false;
    slaveAddress = address;

    XMC_I2C_CH_Init(XMC_I2C_config->channel, &(XMC_I2C_config->channel_config));
    XMC_USIC_CH_SetInputSource(XMC_I2C_config->channel, XMC_USIC_CH_INPUT_DX0,
                               XMC_I2C_config->input_source_dx0);
    XMC_USIC_CH_SetInputSource(XMC_I2C_config->channel, XMC_USIC_CH_INPUT_DX1,
                               XMC_I2C_config->input_source_dx1);

    XMC_USIC_CH_SetInterruptNodePointer(XMC_I2C_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE,
                                        XMC_I2C_config->slave_receive_irq_service_request);
    XMC_USIC_CH_SetInterruptNodePointer(XMC_I2C_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_ALTERNATE_RECEIVE,
                                        XMC_I2C_config->slave_receive_irq_service_request);
    XMC_USIC_CH_SetInterruptNodePointer(XMC_I2C_config->channel,
                                        XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL,
                                        XMC_I2C_config->protocol_irq_service_request);

    NVIC_SetPriority((IRQn_Type)XMC_I2C_config->slave_receive_irq_num, 3U);
    NVIC_EnableIRQ((IRQn_Type)XMC_I2C_config->slave_receive_irq_num);
    NVIC_SetPriority((IRQn_Type)XMC_I2C_config->protocol_irq_num, 3U);
    NVIC_EnableIRQ((IRQn_Type)XMC_I2C_config->protocol_irq_num);

    XMC_I2C_CH_SetSlaveAddress(XMC_I2C_config->channel, (address << 1));
    /*Flush receive buffer*/
    (void)XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
    (void)XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);

    XMC_I2C_CH_EnableEvent(XMC_I2C_config->channel,
                           (uint32_t)(XMC_I2C_CH_EVENT_DATA_LOST |
                                      XMC_I2C_CH_EVENT_ARBITRATION_LOST | XMC_I2C_CH_EVENT_ERROR));
    XMC_I2C_CH_EnableEvent(XMC_I2C_config->channel,
                           (uint32_t)((uint32_t)XMC_I2C_CH_EVENT_STANDARD_RECEIVE |
                                      (uint32_t)XMC_I2C_CH_EVENT_ALTERNATIVE_RECEIVE));
    XMC_I2C_CH_EnableEvent(XMC_I2C_config->channel,
                           (uint32_t)((uint32_t)XMC_I2C_CH_EVENT_SLAVE_READ_REQUEST |
                                      (uint32_t)XMC_I2C_CH_EVENT_STOP_CONDITION_RECEIVED));

    XMC_I2C_CH_Start(XMC_I2C_config->channel);

    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_I2C_config->sda.port, (uint8_t)XMC_I2C_config->sda.pin,
                  &(XMC_I2C_config->sda_config));
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)XMC_I2C_config->scl.port, (uint8_t)XMC_I2C_config->scl.pin,
                  &(XMC_I2C_config->scl_config));
}

void TwoWire::end(void) {
    if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_I2C) {
        XMC_I2C_CH_Stop(XMC_I2C_config->channel);

        XMC_USIC_CH_SetInputSource(XMC_I2C_config->channel, XMC_USIC_CH_INPUT_DX0, XMC_INPUT_A);
        XMC_USIC_CH_SetInputSource(XMC_I2C_config->channel, XMC_USIC_CH_INPUT_DX1, XMC_INPUT_A);

        NVIC_DisableIRQ((IRQn_Type)XMC_I2C_config->protocol_irq_num);
        XMC_I2C_CH_DisableEvent(XMC_I2C_config->channel,
                                (uint32_t)(XMC_I2C_CH_EVENT_NACK | XMC_I2C_CH_EVENT_DATA_LOST |
                                           XMC_I2C_CH_EVENT_ARBITRATION_LOST |
                                           XMC_I2C_CH_EVENT_ERROR));

        if (isMaster == false) {
            XMC_I2C_CH_DisableEvent(XMC_I2C_config->channel,
                                    (uint32_t)((uint32_t)XMC_I2C_CH_EVENT_SLAVE_READ_REQUEST |
                                               (uint32_t)XMC_I2C_CH_EVENT_STOP_CONDITION_RECEIVED));
            NVIC_DisableIRQ((IRQn_Type)XMC_I2C_config->slave_receive_irq_num);
            XMC_I2C_CH_DisableEvent(XMC_I2C_config->channel,
                                    (uint32_t)((uint32_t)XMC_I2C_CH_EVENT_STANDARD_RECEIVE |
                                               (uint32_t)XMC_I2C_CH_EVENT_ALTERNATIVE_RECEIVE));
        }

        flush();
        /* Disable i2c tx fifo */
        XMC_USIC_CH_TXFIFO_Configure(XMC_I2C_config->channel, 16, XMC_USIC_CH_FIFO_DISABLED,
                                     (uint32_t)15);

        /* Disable i2c rx fifo */
        XMC_USIC_CH_RXFIFO_Configure(XMC_I2C_config->channel, 0, XMC_USIC_CH_FIFO_DISABLED,
                                     (uint32_t)(15));
    }
}

void TwoWire::setClock(uint32_t clock) { XMC_I2C_CH_SetBaudrate(XMC_I2C_config->channel, clock); }

size_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool sendStop) {
    if (quantity == 0) {
        if (sendStop) {
            XMC_I2C_CH_MasterStop(XMC_I2C_config->channel);
        }
        return 0;
    }
    if (quantity > BUFFER_LENGTH) {
        quantity = BUFFER_LENGTH;
    }

    rx_ringBuffer.clear();
    if (inRepStart) {
        XMC_I2C_CH_MasterRepeatedStart(XMC_I2C_config->channel, (txAddress << 1),
                                       XMC_I2C_CH_CMD_READ);
        inRepStart = false;
    } else {
        XMC_I2C_CH_MasterStart(XMC_I2C_config->channel, (txAddress << 1), XMC_I2C_CH_CMD_READ);
    }

    uint32_t start = millis();
    while (!(XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel) &
             XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED)) {
        if (millis() - start > timeout || hasError) {
            flush();
            return 0;
        }
    }

    for (uint8_t count = 0; count < (quantity - 1); count++) {
        XMC_I2C_CH_MasterReceiveAck(XMC_I2C_config->channel);

        start = millis();
        // Wait for Receive, leave when NACK is detected
        while (!(XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel) &
                 (XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                  XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION))) {
            if (millis() - start > timeout || hasError) {
                flush();
                return count;
            }
        }
        XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                   XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                       XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
        uint8_t data = XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
        if (rx_ringBuffer.isFull()) {
            flush();
            return count;
        }
        rx_ringBuffer.store_char(data);
    }
    XMC_I2C_CH_MasterReceiveNack(XMC_I2C_config->channel);

    start = millis();
    // Wait for Receive, leave when NACK is detected
    while (!(XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel) &
             (XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
              XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION))) {
        if (millis() - start > timeout || hasError) {
            flush();
            return quantity - 1;
        }
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                               XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                   XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
    uint8_t data = XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
    if (rx_ringBuffer.isFull()) {
        flush();
        return quantity - 1;
    }
    rx_ringBuffer.store_char(data);

    if (sendStop) {
        XMC_I2C_CH_MasterStop(XMC_I2C_config->channel);
        start = millis();
        while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
               XMC_USIC_CH_TBUF_STATUS_BUSY) {
            if (this->hasError == true || (millis() - start > timeout)) {
                inRepStart = false;
                flush();
                return quantity - 1; // return the number of bytes received before timeout
            }
        }
    }
    // indicate that we are done transmitting
    return rx_ringBuffer.available();
}

size_t TwoWire::requestFrom(uint8_t address, size_t quantity) {
    return requestFrom((uint8_t)address, quantity, true);
}

void TwoWire::beginTransmission(uint8_t address) {
    if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) != XMC_USIC_CH_OPERATING_MODE_I2C) {
        if (isMaster) {
            Wire.begin();
        } else {
            Wire.begin(slaveAddress);
        }
    }
    // indicate that we are transmitting
    transmitting = 1;
    // set address of targeted slave
    txAddress = address;
    // reset tx buffer iterator vars
    tx_ringBuffer.clear();
    // Clear all Status Flags
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel, 0xFFFFFFFF);
}

uint8_t TwoWire::endTransmission(bool sendStop) {
    uint32_t StatusFlag;
    XMC_I2C_CH_MasterStart(XMC_I2C_config->channel, (txAddress << 1), XMC_I2C_CH_CMD_WRITE);
    while (tx_ringBuffer.available() > 0) {
        uint8_t data = tx_ringBuffer.read_char();
        XMC_I2C_CH_MasterTransmit(XMC_I2C_config->channel, data);
        uint32_t start = millis();
        // Wait for ACK, leave when NACK is detected
        do {
            StatusFlag = XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel);
            // Check for NACK, indicates that no slave with desired address is on the bus
            if (hasError || (millis() - start > timeout)) {
                flush();
                return 5; // NACK received
            }
        } while (!(StatusFlag & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED));

        if (StatusFlag & XMC_I2C_CH_STATUS_FLAG_NACK_RECEIVED) {
            // NACK received, slave is not present
            flush();
            return 2; // NACK received
        }
        XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);
    }

    if (sendStop) {
        XMC_I2C_CH_MasterStop(XMC_I2C_config->channel);
        uint32_t start = millis();
        while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
               XMC_USIC_CH_TBUF_STATUS_BUSY) {
            if (this->hasError == true || (millis() - start > timeout)) {
                flush();
                return 5;
            }
        }
        inRepStart = false;
    } else {
        inRepStart = true;
    }
    // indicate that we are done transmitting
    transmitting = 0;
    return 0;
}

uint8_t TwoWire::endTransmission(void) { return endTransmission(true); }

size_t TwoWire::write(uint8_t data) {
    if (transmitting) {
        if (tx_ringBuffer.isFull()) {
            return 0;
        }
        tx_ringBuffer.store_char(data);
        return 1;
    }
    // in slave send mode
    // reply to master
    if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) != XMC_USIC_CH_OPERATING_MODE_I2C) {
        if (isMaster) {
            Wire.begin();
        } else {
            Wire.begin(slaveAddress);
        }
    }
    XMC_I2C_CH_SlaveTransmit(XMC_I2C_config->channel, data);
    uint32_t start = millis();
    while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
           XMC_USIC_CH_TBUF_STATUS_BUSY) {
        if (this->hasError == true || (millis() - start > timeout)) {
            flush();
            return 0;
        }
    }
    return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
    if (transmitting) {
        size_t written = 0;
        for (size_t i = 0; i < quantity; ++i) {
            if (!write(data[i])) {
                break;
            }
            written++;
        }
        return written;
    }
    // in slave send mode
    // reply to master
    if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) != XMC_USIC_CH_OPERATING_MODE_I2C) {
        if (isMaster) {
            Wire.begin();
        } else {
            Wire.begin(slaveAddress);
        }
    }
    for (uint8_t c = 0; c < quantity; c++) {
        XMC_I2C_CH_SlaveTransmit(XMC_I2C_config->channel, data[c]);
    }
    uint32_t start = millis();
    while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
           XMC_USIC_CH_TBUF_STATUS_BUSY) {
        if (this->hasError == true || (millis() - start > timeout)) {
            flush();
            return 0;
        }
    }
    return quantity;
}

int TwoWire::available(void) { return rx_ringBuffer.available(); }

int TwoWire::read(void) {
    if (rx_ringBuffer.available() == 0) {
        return -1;
    }
    return rx_ringBuffer.read_char();
}

int TwoWire::peek(void) {
    if (rx_ringBuffer.available() == 0) {
        return -1;
    }
    return rx_ringBuffer.peek();
}

void TwoWire::flush(void) {
    // Reset buffer and clear all Status Flags
    if (isMaster) {
        XMC_USIC_CH_TXFIFO_Flush(XMC_I2C_config->channel);
        XMC_USIC_CH_RXFIFO_Flush(XMC_I2C_config->channel);
        XMC_USIC_CH_SetTransmitBufferStatus(XMC_I2C_config->channel,
                                            XMC_USIC_CH_TBUF_STATUS_SET_IDLE);
    } else {
        /*Flush receive buffer*/
        (void)XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
        (void)XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel, 0xFFFFFFFF);
    rx_ringBuffer.clear();
    tx_ringBuffer.clear();
    pre_rx_ringBuffer.clear();
    transmitting = 0;
    inRepStart = false;
    hasError = false;
}

void TwoWire::ReceiveHandler(void) {
    uint32_t data = XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
    noInterrupts();
    if (pre_rx_ringBuffer.isFull()) {
        hasError = true;
    } else {
        pre_rx_ringBuffer.store_char(data);
    }
    interrupts();
}

void TwoWire::ProtocolHandler(void) {
    uint32_t flag_status = XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel);
    if (isMaster) {
        if (flag_status &
            (uint32_t)(XMC_I2C_CH_STATUS_FLAG_NACK_RECEIVED |
                       XMC_I2C_CH_STATUS_FLAG_ARBITRATION_LOST | XMC_I2C_CH_STATUS_FLAG_ERROR |
                       XMC_I2C_CH_STATUS_FLAG_DATA_LOST_INDICATION)) {
            XMC_I2C_CH_ClearStatusFlag(
                XMC_I2C_config->channel,
                (XMC_I2C_CH_STATUS_FLAG_NACK_RECEIVED | XMC_I2C_CH_STATUS_FLAG_ARBITRATION_LOST |
                 XMC_I2C_CH_STATUS_FLAG_ERROR | XMC_I2C_CH_STATUS_FLAG_DATA_LOST_INDICATION));
            hasError = true;
        }
    } else {
        if (flag_status &
            (uint32_t)(XMC_I2C_CH_STATUS_FLAG_ARBITRATION_LOST | XMC_I2C_CH_STATUS_FLAG_ERROR |
                       XMC_I2C_CH_STATUS_FLAG_DATA_LOST_INDICATION)) {
            XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                       (XMC_I2C_CH_STATUS_FLAG_ARBITRATION_LOST |
                                        XMC_I2C_CH_STATUS_FLAG_ERROR |
                                        XMC_I2C_CH_STATUS_FLAG_DATA_LOST_INDICATION));
            hasError = true;
        }
        if (flag_status & (uint32_t)XMC_I2C_CH_STATUS_FLAG_SLAVE_READ_REQUESTED) {
            XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                       XMC_I2C_CH_STATUS_FLAG_SLAVE_READ_REQUESTED);

            noInterrupts();
            while (pre_rx_ringBuffer.available()) {
                rx_ringBuffer.store_char(pre_rx_ringBuffer.read_char());
            }
            interrupts();
            OnReceiveService(rx_ringBuffer.available());
            OnRequestService();
        }
        if (flag_status & (uint32_t)XMC_I2C_CH_STATUS_FLAG_STOP_CONDITION_RECEIVED) {
            XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                       XMC_I2C_CH_STATUS_FLAG_STOP_CONDITION_RECEIVED);

            noInterrupts();
            while (pre_rx_ringBuffer.available()) {
                rx_ringBuffer.store_char(pre_rx_ringBuffer.read_char());
            }
            interrupts();
            OnReceiveService(rx_ringBuffer.available());
        }
    }
}

void TwoWire::OnReceiveService(uint8_t numBytes) {
    if (user_onReceive && numBytes > 0) {
        user_onReceive(numBytes);
    }
}

void TwoWire::OnRequestService(void) {
    if (user_onRequest) {
        tx_ringBuffer.clear();
        user_onRequest();
    }
}

void TwoWire::onReceive(void (*function)(int)) { user_onReceive = function; }

void TwoWire::onRequest(void (*function)(void)) { user_onRequest = function; }

/*
 *   Interrupt handler for xmc devices:
 *   XMC1-series: USIC0_4_IRQHandler (rx_irq) and USIC0_4_IRQHandler (protocol_irq)
 *   XMC4-series: USIC1_1_IRQHandler (rx_irq) and USIC1_2_IRQHandler (protocol_irq)
 */
extern "C" {
#if (UC_FAMILY == XMC1)
void USIC0_4_IRQHandler() { Wire.ReceiveHandler(); }

void USIC0_5_IRQHandler() { Wire.ProtocolHandler(); }

    #if defined(KIT_XMC_2GO_XMC1100_V1) || defined(XMC1100_H_BRIDGE2GO)
void USIC0_2_IRQHandler() { Wire1.ReceiveHandler(); }

void USIC0_3_IRQHandler() { Wire1.ProtocolHandler(); }
    #endif

    #if defined(KIT_XMC_PLT2GO_XMC4200)
void USIC1_1_IRQHandler() { Wire.ReceiveHandler(); }

void USIC1_2_IRQHandler() { Wire.ProtocolHandler(); }
    #endif

#elif defined(KIT_XMC47_RELAX)
void USIC1_1_IRQHandler() { Wire.ReceiveHandler(); }

void USIC1_2_IRQHandler() { Wire.ProtocolHandler(); }

void USIC1_3_IRQHandler() { Wire1.ReceiveHandler(); }

void USIC1_4_IRQHandler() { Wire1.ProtocolHandler(); }
#endif
} // extern "C"

TwoWire Wire = TwoWire(&XMC_I2C_default);
#if (NUM_I2C > 1)
TwoWire Wire1 = TwoWire(&XMC_I2C_1);
    #if (NUM_I2C > 2)
TwoWire Wire2 = TwoWire(&XMC_I2C_2);
        #if (NUM_I2C > 3)
TwoWire Wire3 = TwoWire(&XMC_I2C_3);
            #if (NUM_I2C > 4)
TwoWire Wire4 = TwoWire(&XMC_I2C_4);
            #endif
        #endif
    #endif
#endif

//****************************************************************************
//                                 END OF FILE
//****************************************************************************
