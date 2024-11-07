#include "CANXMC.h"
#include <Arduino.h>

/* Flag for receive interrupt*/
static volatile bool can_frame_received = false;

/* construct with configuration of different target */
CANXMC::CANXMC(XMC_ARD_CAN_t *conf)
    : _XMC_CAN_config(conf) {
    memset(&CAN_msg_rx, 0, sizeof(CAN_msg_rx));
    memset(&CAN_msg_tx, 0, sizeof(CAN_msg_tx));

    /* CAN Transmit Message Object definition */

    CAN_msg_tx.can_mo_ptr = (CAN_MO_TypeDef *)CAN_MO1;
    CAN_msg_tx.can_identifier = 0xFFFU;
    CAN_msg_tx.can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS;           // Extended ID mode
    CAN_msg_tx.can_priority = XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1; // Priority level 1
    CAN_msg_tx.can_id_mask = 0x00000000U;                                  // Identifier mask
    CAN_msg_tx.can_ide_mask = 0U;                         // Identifier extension mask
    CAN_msg_tx.can_data_length = 0U;                      // Data length of 0
    CAN_msg_tx.can_mo_type = XMC_CAN_MO_TYPE_TRANSMSGOBJ; // Message Object type

    /* CAN Receive Message Object definition, can also be used for transmit remote
     * frame*/
    CAN_msg_rx.can_mo_ptr = (CAN_MO_TypeDef *)CAN_MO0;
    CAN_msg_rx.can_identifier = 0xFFFU;
    CAN_msg_rx.can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS;
    CAN_msg_rx.can_priority = XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1;
    CAN_msg_rx.can_id_mask = 0x00000000U;
    CAN_msg_rx.can_ide_mask = 0U;
    CAN_msg_rx.can_data_length = 0U;
    CAN_msg_rx.can_mo_type = XMC_CAN_MO_TYPE_RECMSGOBJ;
}

CANXMC::~CANXMC() { end(); }

/* Getter function for CAN_msg_tx */
XMC_CAN_MO_t *CANXMC::getTxMessage() { return &CAN_msg_tx; }

/* Getter function for CAN_msg_rx */
XMC_CAN_MO_t *CANXMC::getRxMessage() { return &CAN_msg_rx; }

/*
int CANXMC::setIdentifier(long id) { // TODO: delete in the future!
                                     // figure out filtering problem for xmc4700
    XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
    return 0;
};
*/

/**
 * @brief Initializes the CAN interface with the specified baudrate.
 *
 * This function configures the CAN bit time, enables the CAN node, and sets up
 * the necessary pin configurations.
 *
 * @param baudRate The desired baudrate for the CAN interface. The default value
 * is 500,000 bps.
 * @return Returns 1 if the initialization is successful, 0 otherwise.
 */
int CANXMC::begin(long baudRate /*= 500e3*/) {
    /* reset CAN nodes*/
    XMC_CAN_Disable(CAN_xmc);

    /* CAN bit time configuration*/
    XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_NODE_bit_time_config = {
        .can_frequency = _XMC_CAN_config->can_frequency,
        .baudrate = (uint32_t)baudRate,
        .sample_point = (uint16_t)(80 * 100),
        .sjw = (uint16_t)1,
    };

    XMC_CAN_Enable(CAN_xmc);

    /* Configuration of CAN Node and enable the clock */
    XMC_CAN_InitEx(CAN_xmc, _XMC_CAN_config->can_clock, _XMC_CAN_config->can_frequency);
    if (XMC_CAN_STATUS_SUCCESS == XMC_CAN_NODE_NominalBitTimeConfigureEx(
                                      _XMC_CAN_config->can_node, &CAN_NODE_bit_time_config)) {
        XMC_CAN_NODE_EnableConfigurationChange(_XMC_CAN_config->can_node);
        XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
        XMC_CAN_NODE_ReSetAnalyzerMode(_XMC_CAN_config->can_node);

        /* Configure CAN NODE input pin */
        XMC_GPIO_Init(_XMC_CAN_config->tx.port, _XMC_CAN_config->tx.pin,
                      &(_XMC_CAN_config->tx_config));
        XMC_GPIO_SetHardwareControl(_XMC_CAN_config->tx.port, _XMC_CAN_config->tx.pin,
                                    XMC_GPIO_HWCTRL_DISABLED);
        XMC_GPIO_Init(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin,
                      &(_XMC_CAN_config->rx_config));
        XMC_GPIO_SetHardwareControl(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin,
                                    XMC_GPIO_HWCTRL_DISABLED);
        XMC_CAN_NODE_SetReceiveInput(_XMC_CAN_config->can_node, _XMC_CAN_config->node_input);

        /* Allocate the rx and tx message object*/
        XMC_CAN_MO_Config(&CAN_msg_rx);
        XMC_CAN_AllocateMOtoNodeList(CAN_xmc, _XMC_CAN_config->can_node_num, 0);
        XMC_CAN_MO_Config(&CAN_msg_tx);
        XMC_CAN_AllocateMOtoNodeList(CAN_xmc, _XMC_CAN_config->can_node_num, 1);

        /* Message object accepts the reception of both, standard and extended
         * frames */
        XMC_CAN_MO_AcceptStandardAndExtendedID(&CAN_msg_rx);

#if (UC_SERIES == XMC14)
        // select interrupt source (A,B,C etc) input to NVIC node (only for XMC1400
        // devices)
        XMC_SCU_SetInterruptControl(_XMC_CAN_config->irq_num, _XMC_CAN_config->irq_source);
#endif

        XMC_CAN_MO_SetEventNodePointer(&CAN_msg_rx, XMC_CAN_MO_POINTER_EVENT_RECEIVE,
                                       _XMC_CAN_config->irq_service_request);
        XMC_CAN_MO_EnableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);
        XMC_CAN_NODE_DisableConfigurationChange(_XMC_CAN_config->can_node);
        XMC_CAN_NODE_ResetInitBit(_XMC_CAN_config->can_node);

        return 1;
    } else {
        return 0;
    }
};

/**
 * @brief Disables the CAN module and ends the CANXMC object.
 *
 * This function disables the CAN module and ends the CANXMC object. It disables
 * the receive event for the CAN message object and disables the CAN module
 * using the XMC_CAN_Disable function.
 */
void CANXMC::end() {
    XMC_CAN_MO_DisableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);
    XMC_CAN_Disable(CAN_xmc);
    CANControllerClass::end();
};

/**
 * Ends the packet transmission on the CAN bus.
 *
 * @return 1 if the packet was successfully transmitted, 0 otherwise.
 */
int CANXMC::endPacket() {
    if (!CANControllerClass::endPacket()) {
        return 0;
    }

    if (_txRtr) {
        // TODO: LJ: how to receive remote frame? and response...

        /* Configure remote frame to be transmitted and data length code */
        if (_txExtended) {
            XMC_CAN_MO_SetExtendedID(&CAN_msg_rx);
        } else {
            XMC_CAN_MO_SetStandardID(&CAN_msg_rx);
        }
        XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, _txId);
        XMC_CAN_MO_SetDataLengthCode(&CAN_msg_rx, _txLength);
        XMC_CAN_MO_UpdateData(&CAN_msg_rx);

        /* Send remote frame */
        XMC_CAN_STATUS_t send_status = XMC_CAN_MO_Transmit(&CAN_msg_rx);

        if (send_status == XMC_CAN_STATUS_SUCCESS) {
            return 1;
        } else {
            return 0;
        }

    } else {
        /* Configure data frame to be transmitted and data length code */
        if (_txExtended) {
            XMC_CAN_MO_SetExtendedID(&CAN_msg_tx);
        } else {
            XMC_CAN_MO_SetStandardID(&CAN_msg_tx);
        }
        XMC_CAN_MO_SetIdentifier(&CAN_msg_tx, _txId);
        memcpy(CAN_msg_tx.can_data_byte, _txData, _txLength);
        XMC_CAN_MO_SetDataLengthCode(&CAN_msg_tx, _txLength);

        XMC_CAN_MO_UpdateData(&CAN_msg_tx);

        /* Send data frame */
        XMC_CAN_STATUS_t send_status = XMC_CAN_MO_Transmit(&CAN_msg_tx);

        if (send_status == XMC_CAN_STATUS_SUCCESS) {
            return 1;
        } else {
            return 0;
        }
    }
};

/**
 * @brief Parses a CAN packet received by the XMC_CAN module.
 *
 * This function waits until a new CAN packet is available in the receive
 * buffer, then retrieves the packet information such as the identifier, frame
 * type, remote transmission request (RTR), data length code (DLC), and data
 * payload. If the packet is an extended frame, the `_rxExtended` flag is set to
 * true. If the packet is an RTR frame, the `_rxRtr` flag is set to true and the
 * `_rxLength` is set to 0. Otherwise, the `_rxLength` is set to the DLC and the
 * data payload is copied to the `_rxData` buffer. Finally, the function resets
 * the receive flag and returns the length of the received packet.
 *
 * @return The length of the received packet.
 */
int CANXMC::parsePacket() {
    while ((XMC_CAN_MO_GetStatus(&CAN_msg_rx) & CAN_MO_MOSTAT_NEWDAT_Msk) >>
               CAN_MO_MOSTAT_NEWDAT_Pos !=
           1)
        ;
    XMC_CAN_MO_Receive(&CAN_msg_rx);

    /* check CAN frame type */
    _rxId = XMC_CAN_MO_GetIdentifier(&CAN_msg_rx);

    if (CAN_msg_rx.can_id_mode == XMC_CAN_FRAME_TYPE_EXTENDED_29BITS) {
        _rxExtended = true;
    } else {
        _rxExtended = false;
    };

    _rxRtr = CAN_msg_rx.can_mo_ptr->MOFCR & (uint32_t)CAN_MO_MOFCR_RMM_Msk;
    _rxDlc = CAN_msg_rx.can_data_length;
    if (_rxRtr) {
        _rxLength = 0;
    } else {
        _rxLength = _rxDlc;
        memcpy(_rxData, CAN_msg_rx.can_data_byte, _rxLength);
    }
    /* set the flag back and wait for next receive */
    can_frame_received = false;

    _rxIndex = 0;

    return _rxLength;
};

/**
 * Sets the callback function to be called when a CAN message is received.
 *
 * @param callback A pointer to the function to be called when a CAN message is
 * received. The function should take an integer parameter. Pass nullptr to
 * disable the callback.
 */
void CANXMC::onReceive(void (*callback)(int)) {
    CANControllerClass::onReceive(callback);
    if (callback) {
        NVIC_EnableIRQ(_XMC_CAN_config->irq_num);
    } else {
        NVIC_DisableIRQ(_XMC_CAN_config->irq_num);
    }
};

/**
 * Sets the filter for the CAN message object.
 *
 * @param id The identifier to match against incoming messages.
 * @param mask The mask to apply to the identifier for filtering.
 * @return 1 if the filter was set successfully, 0 otherwise.
 */
int CANXMC::filter(int id, int mask) {
    XMC_CAN_MO_SetStandardID(&CAN_msg_rx);
    XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
    XMC_CAN_MO_AcceptOnlyMatchingIDE(&CAN_msg_rx);
    XMC_CAN_MO_SetAcceptanceMask(&CAN_msg_rx, mask);

    return 1;
};

/**
 * Sets the filter for extended CAN messages.
 *
 * @param id The identifier to match against the received message.
 * @param mask The mask to apply to the identifier for filtering.
 * @return 1 if the filter was set successfully, 0 otherwise.
 */
int CANXMC::filterExtended(long id, long mask) {
    XMC_CAN_MO_SetExtendedID(&CAN_msg_rx);
    XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
    XMC_CAN_MO_AcceptOnlyMatchingIDE(&CAN_msg_rx);
    XMC_CAN_MO_SetAcceptanceMask(&CAN_msg_rx, mask);
    return 1;
};

int CANXMC::observe() {
    // TODO: LJ: no idea what this is
    return 0;
};

/**
 * Puts the CAN module into loopback mode.
 * This function puts the CAN module into loopback mode by enabling the loopback
 * mode for both CAN nodes. It also initializes the CAN message objects for
 * loopback mode.
 * @return true if the CAN module is successfully put into loopback mode, false
 * otherwise.
 */
int CANXMC::loopback() {

    /* reset CAN nodes*/
    XMC_CAN_Disable(CAN_xmc);
    /* CAN bit time configuration*/
    XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_NODE_bit_time_config = {
        .can_frequency = _XMC_CAN_config->can_frequency,
        .baudrate = (uint32_t)50000, // TODO: LJ: need to be changed
        .sample_point = (uint16_t)(80 * 100),
        .sjw = (uint16_t)1,
    };

    XMC_CAN_Enable(CAN_xmc);
    /* Configuration of CAN Node and enable the clock */
    XMC_CAN_InitEx(CAN_xmc, _XMC_CAN_config->can_clock, _XMC_CAN_config->can_frequency);
    if (XMC_CAN_STATUS_SUCCESS ==
        XMC_CAN_NODE_NominalBitTimeConfigureEx(CAN_NODE1, &CAN_NODE_bit_time_config)) {

        /* Enable CAN node 1 for Loop-back mode */
        XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE1);
        XMC_CAN_NODE_EnableLoopBack(CAN_NODE1);
        XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE1);
        XMC_CAN_NODE_ResetInitBit(CAN_NODE1);

        /* Initializes CAN tx Message Object for loopback */
        XMC_CAN_MO_Config(&CAN_msg_tx);
        /* Allocate tx Message object to Node 1 */
        XMC_CAN_AllocateMOtoNodeList(CAN_xmc, 1, 1);
    } else {
        return 0;
    }

    if (XMC_CAN_STATUS_SUCCESS ==
        XMC_CAN_NODE_NominalBitTimeConfigureEx(CAN_NODE0, &CAN_NODE_bit_time_config)) {
        /* Enable CAN node 0 for Loop-back mode */
        XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE0);
        XMC_CAN_NODE_EnableLoopBack(CAN_NODE0);
        XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE0);
        XMC_CAN_NODE_ResetInitBit(CAN_NODE0);

        /* Initializes CAN rx Message Object for loopback */
        XMC_CAN_MO_Config(&CAN_msg_rx);
        /*Allocate rx Message object to Node 0 */
        XMC_CAN_AllocateMOtoNodeList(CAN_xmc, 0, 0);
        XMC_CAN_MO_AcceptStandardAndExtendedID(&CAN_msg_rx);
        /* Enable receive event */
        XMC_CAN_MO_SetEventNodePointer(&CAN_msg_rx, XMC_CAN_MO_POINTER_EVENT_RECEIVE,
                                       _XMC_CAN_config->irq_service_request);
        XMC_CAN_MO_EnableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);

        return 1;
    } else {
        return 0;
    }
};

/**
 * Puts the CAN module into sleep mode.
 * This function disables the CAN module by setting the EDIS bit in the CLC
 * register.
 * @return 1 if the CAN module is successfully put into sleep mode, 0
 * otherwise.
 */
int CANXMC::sleep() {
    CAN_xmc->CLC |= CAN_CLC_EDIS_Msk;
    return CAN_xmc->CLC & CAN_CLC_EDIS_Msk != 0 ? 1 : 0;
};

/**
 * @brief Wakes up the CAN module.
 * This function is used to wake up the CAN module by clearing the EDIS bit in
 * the CLC register.
 * @return 1 if the CAN module is successfully woken up, 0 otherwise.
 */
int CANXMC::wakeup() {
    CAN_xmc->CLC &= ~CAN_CLC_EDIS_Msk;
    return CAN_xmc->CLC & CAN_CLC_EDIS_Msk == 0 ? 1 : 0;
};

/**
 * @brief This function is called when an interrupt is triggered for the CANXMC
 * module. It checks if a CAN frame has been received and if so, it parses the
 * packet and calls the _onReceive() function with the number of available
 * frames.
 */
void CANXMC::onInterrupt() {
    if (can_frame_received == true) {
        CAN.parsePacket();
        CAN._onReceive(CAN.available());
    }
};

/* Interrupt Handler */
/**
 * @brief Interrupt handler for CAN0_7_IRQHandler (XMC4 series) or
 * CAN0_3_IRQHandler (XMC1 series).
 *
 * This function is called when a CAN frame is received. It sets the
 * can_frame_received flag to true and calls the onInterrupt() function of the
 * CAN object.
 *
 * @note This function is intended to be used as an interrupt handler and should
 * not be called directly.
 */
extern "C" {
#if (UC_FAMILY == XMC4)
void CAN0_7_IRQHandler() {
    /* Set the frame received flag to true */
    can_frame_received = true;

    CAN.onInterrupt();
}
#endif

#if (UC_SERIES == XMC14)
void CAN0_3_IRQHandler() {
    /* Set the frame received flag to true */
    can_frame_received = true;

    CAN.onInterrupt();
}
#endif
}

CANXMC CAN(&XMC_CAN_0);
