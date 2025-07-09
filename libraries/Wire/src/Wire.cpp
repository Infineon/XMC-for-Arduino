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

    rx_ringBuffer.clear();
    tx_ringBuffer.clear();
    pre_rx_ringBuffer.clear();
    // rxBufferIndex = 0;
    // rxBufferLength = 0;
    // txBufferIndex = 0;
    // txBufferLength = 0;
    // pre_rxBufferCount = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

void TwoWire::begin(void) {
    // To-Do for future work need to check
    // Check if desire USIC channel is already in use 
    // if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI) {
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
    //To-Do for future work need to check
    // Check if desire USIC channel is already in use
    // if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) == XMC_USIC_CH_OPERATING_MODE_SPI) {
    //     SPI.end();
    // }
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
    //  Only disable HW when USIC is used for I2C
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

size_t  TwoWire::requestFrom(uint8_t address, size_t quantity, uint32_t iaddress, uint8_t isize, bool sendStop) {
    uint32_t StatusFlag;
    beginTransmission(address);
    // clamp to buffer length
    if (quantity > BUFFER_LENGTH) {
        quantity = BUFFER_LENGTH;
    }
    // send internal address; this mode allows sending a repeated start to access
    // some devices' internal registers. This function is executed by the hardware
    // TWI module on other processors (for example Due's TWI_IADR and TWI_MMR registers)
    if (isize > 0) {

        // the maximum size of internal address is 3 bytes
        if (isize > 3) {
            isize = 3;
        }

        // write internal register address - most significant byte first
        while (isize-- > 0) {
            write((uint8_t)(iaddress >> (isize * 8)));
        }
        endTransmission(false);

        XMC_I2C_CH_MasterRepeatedStart(XMC_I2C_config->channel, (txAddress << 1),
                                       XMC_I2C_CH_CMD_READ);
    } else if (inRepStart) {
        XMC_I2C_CH_MasterRepeatedStart(XMC_I2C_config->channel, (txAddress << 1),
                                       XMC_I2C_CH_CMD_READ);
        inRepStart = false;
    } else {
        XMC_I2C_CH_MasterStart(XMC_I2C_config->channel, (txAddress << 1), XMC_I2C_CH_CMD_READ);
    }

    timeout = WIRE_COMMUNICATION_TIMEOUT;
    // wait for ACK or timeout incase no ACK is received, a time-based wait-state is added since XMC
    // devices run at variable frequencies
    while (((XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel) &
             XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)) {
        delay(1);
        timeout--;
        if (timeout == 0) {
            break;
        }
    }

    for (uint8_t count = 0; count < (quantity - 1); count++) {
        XMC_I2C_CH_MasterReceiveAck(XMC_I2C_config->channel);

        timeout = WIRE_COMMUNICATION_TIMEOUT;
        // Wait for Receive, leave when NACK is detected
        do {
            StatusFlag = XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel);

            // Check for NACK, indicates that no slave with desired address is on the bus
            if (this->hasError == true || timeout == 0) {
                this->hasError = false;
                flush();
                return 0;
            }
            timeout--;
        } while ((StatusFlag & (XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION)) == 0U);
        XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                   XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                       XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);

        rx_ringBuffer.store_char(XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel));
    }

    XMC_I2C_CH_MasterReceiveNack(XMC_I2C_config->channel);

    timeout = WIRE_COMMUNICATION_TIMEOUT;
    // Wait for Receive, leave when NACK is detected
    do {
        StatusFlag = XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel);

        // Check for NACK, indicates that no slave with desired address is on the bus
        if (this->hasError == true || timeout == 0) {
            this->hasError = false;
            flush();
            return 0;
        }
        timeout--;
    } while ((StatusFlag & (XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                            XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION)) == 0U);
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                               XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                   XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);

    rx_ringBuffer.store_char(XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel));

    if (sendStop) {
        XMC_I2C_CH_MasterStop(XMC_I2C_config->channel);

        timeout = WIRE_COMMUNICATION_TIMEOUT;
        while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
               XMC_USIC_CH_TBUF_STATUS_BUSY) {
            if (this->hasError == true || timeout == 0) {
                this->hasError = false;
                inRepStart = false;
                flush();
                return 1;
            }
            timeout--;
        }
    }

   
    // indicate that we are done transmitting
    transmitting = 0;

    return quantity;
}

size_t  TwoWire::requestFrom(uint8_t address, size_t quantity, bool sendStop) {
    return requestFrom((uint8_t)address, quantity, (uint32_t)0, (uint8_t)0,
                       sendStop);
}

size_t  TwoWire::requestFrom(uint8_t address, size_t quantity) {
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

//  Originally, 'endTransmission' was an f(void) function.
//  It has been modified to take one parameter indicating
//  whether or not a STOP should be performed on the bus.
//  Calling endTransmission(false) allows a sketch to
//  perform a repeated start.
//
//  WARNING: Nothing in the library keeps track of whether
//  the bus tenure has been properly ended with a STOP. It
//  is very possible to leave the bus in a hung state if
//  no call to endTransmission(true) is made. Some I2C
//  devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(bool sendStop) {
    uint32_t StatusFlag;

    XMC_I2C_CH_MasterStart(XMC_I2C_config->channel, (txAddress << 1), XMC_I2C_CH_CMD_WRITE);

    while(tx_ringBuffer.available()) {
        uint8_t data = tx_ringBuffer.read_char();
        XMC_I2C_CH_MasterTransmit(XMC_I2C_config->channel, data);

        timeout = WIRE_COMMUNICATION_TIMEOUT;
        // Wait for ACK, leave when NACK is detected
        do {
            StatusFlag = XMC_I2C_CH_GetStatusFlag(XMC_I2C_config->channel);

            // Check for NACK, indicates that no slave with desired address is on the bus
            if (this->hasError == true || timeout == 0) {
                this->hasError = false;
                inRepStart = false;
                flush();
                return 1;
            }
            timeout--;
        } while ((StatusFlag & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U);
        XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);
    }

    if (sendStop) {
        XMC_I2C_CH_MasterStop(XMC_I2C_config->channel);
        timeout = WIRE_COMMUNICATION_TIMEOUT;
        while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
               XMC_USIC_CH_TBUF_STATUS_BUSY) {
            if (this->hasError == true || timeout == 0) {
                this->hasError = false;
                inRepStart = false;
                flush();
                return 1;
            }
            timeout--;
        }
        inRepStart = false;
    } else {
        inRepStart = true;
    }

    
    // indicate that we are done transmitting
    transmitting = 0;
    return 0;
}

//  This provides backwards compatibility with the original
//  definition, and expected behaviour, of endTransmission
uint8_t TwoWire::endTransmission(void) { return endTransmission(true); }

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data) {
    if (transmitting) {
        // in master transmitter mode
        // don't bother if buffer is full
        if (tx_ringBuffer.isFull()) {
            // TODO: setWriteError();
            return 0;
        }
        // put byte in tx buffer
        tx_ringBuffer.store_char(data);
    } else {
        // in slave send mode
        // reply to master
        if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) !=
            XMC_USIC_CH_OPERATING_MODE_I2C) {
            if (isMaster) {
                Wire.begin();
            } else {
                Wire.begin(slaveAddress);
            }
        }

        XMC_I2C_CH_SlaveTransmit(XMC_I2C_config->channel, data);

        timeout = WIRE_COMMUNICATION_TIMEOUT;
        while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
               XMC_USIC_CH_TBUF_STATUS_BUSY) {
            if (this->hasError == true || timeout == 0) {
                this->hasError = false;
                inRepStart = false;
                flush();
                return 0;
            }
            timeout--;
        }
    }
    return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity) {
    if (transmitting) {
        // in master transmitter mode
        for (size_t i = 0; i < quantity; ++i) {
            if(!write(data[i])) {
                return 1;
        }
    }
    } else {
        // in slave send mode
        // reply to master
        if ((XMC_I2C_config->channel->CCR & USIC_CH_CCR_MODE_Msk) !=
            XMC_USIC_CH_OPERATING_MODE_I2C) {
            if (isMaster) {
                Wire.begin();
            } else {
                Wire.begin(slaveAddress);
            }
        }

        for (uint8_t c = 0; c < quantity; c++) {
            XMC_I2C_CH_SlaveTransmit(XMC_I2C_config->channel, data[c]);
        }

        timeout = WIRE_COMMUNICATION_TIMEOUT;
        while (XMC_USIC_CH_GetTransmitBufferStatus(XMC_I2C_config->channel) ==
               XMC_USIC_CH_TBUF_STATUS_BUSY) {
            if (this->hasError == true || timeout == 0) {
                this->hasError = false;
                inRepStart = false;
                flush();
                return 0;
            }
            timeout--;
        }
    }
    return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void) { return rx_ringBuffer.available(); }

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void) {
    if(rx_ringBuffer.available() == 0){
        // read from ring buffer
       return -1;
}
return rx_ringBuffer.read_char();
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void) {
    if(rx_ringBuffer.available() == 0){
        // read from ring buffer
        return -1;
    }
    return rx_ringBuffer.peek();
}

void TwoWire::flush(void) {
    // Reset buffer and clear all Status Flags
    if (isMaster == true) {
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
}

// behind the scenes function that is called after each received byte
void TwoWire::ReceiveHandler(void) {
    // no stop or read request
    pre_rx_ringBuffer.store_char(XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel));
  
}

// behind the scenes function that is called after receiving stop or read request
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
        } else if (flag_status & (uint32_t)XMC_I2C_CH_STATUS_FLAG_SLAVE_READ_REQUESTED) {
            XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                       XMC_I2C_CH_STATUS_FLAG_SLAVE_READ_REQUESTED);
            OnReceiveService();

            OnRequestService();
        } else if (flag_status & (uint32_t)XMC_I2C_CH_STATUS_FLAG_STOP_CONDITION_RECEIVED) {
            XMC_I2C_CH_ClearStatusFlag(XMC_I2C_config->channel,
                                       XMC_I2C_CH_STATUS_FLAG_STOP_CONDITION_RECEIVED);
            
            OnReceiveService();
        }
    }
}

// behind the scenes callback function that is called when a data block is received
void TwoWire::OnReceiveService() {
    // don't bother if user hasn't registered a callback
    if (!user_onReceive) {
        return;
    }
    uint8_t count = pre_rx_ringBuffer.available();
    while(pre_rx_ringBuffer.available()>0 && rx_ringBuffer.availableForStore()>0) {      
        rx_ringBuffer.store_char(pre_rx_ringBuffer.read_char());
        } 
    
    // alert user program
    user_onReceive(count);

    /*Flush receive buffer*/
    (void)XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
    (void)XMC_I2C_CH_GetReceivedData(XMC_I2C_config->channel);
}

// behind the scenes function that is called when data is requested
void TwoWire::OnRequestService(void) {
    // don't bother if user hasn't registered a callback
    if (!user_onRequest) {
        return;
    }
    // reset tx buffer iterator vars
    // !!! this will kill any pending pre-master sendTo() activity
    tx_ringBuffer.clear();
    // alert user program
    user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive(void (*function)(int)) { user_onReceive = function; }

// sets function called on slave read
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

    #if defined(XMC1100_XMC2GO) || defined(XMC1100_H_BRIDGE2GO)
void USIC0_2_IRQHandler() { Wire1.ReceiveHandler(); }

void USIC0_3_IRQHandler() { Wire1.ProtocolHandler(); }
    #endif

    #if defined(XMC4400_Platform2GO)
void USIC1_1_IRQHandler() { Wire.ReceiveHandler(); }

void USIC1_2_IRQHandler() { Wire.ProtocolHandler(); }
    #endif

#elif defined(XMC4700_Relax_Kit)
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
