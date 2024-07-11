#include "CANXMC.h"
#include <Arduino.h>


/* CAN Receive Message Object definition, can also be used for transmit remote
 * frame*/
XMC_CAN_MO_t CAN_msg_rx = {
    .can_mo_ptr = (CAN_MO_TypeDef *)CAN_MO0,
    {0xFF, XMC_CAN_FRAME_TYPE_STANDARD_11BITS, // {can_identifier, can_id_mode
     XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1}, // can_priority}
    {0x000, 1U}, // {can_id_mask, can_ide_mask}
    .can_data_length = 0U,
    .can_mo_type = XMC_CAN_MO_TYPE_RECMSGOBJ,
};

/* CAN Transmit Message Object definition */
XMC_CAN_MO_t CAN_msg_tx = {
    .can_mo_ptr = (CAN_MO_TypeDef *)CAN_MO1,
    {0xFF, XMC_CAN_FRAME_TYPE_STANDARD_11BITS, // {can_identifier, can_id_mode
     XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1}, // can_priority}
    {0x7FFU, 1U}, // {can_id_mask, can_ide_mask}
    .can_data_length = 0U,
    .can_mo_type = XMC_CAN_MO_TYPE_TRANSMSGOBJ,
};

/* Flag for receive interrupt*/
static volatile bool can_frame_received = false;

/* construct with configuration of different target */
CANXMC::CANXMC(XMC_ARD_CAN_t *conf) { _XMC_CAN_config = conf; }
CANXMC::~CANXMC() {}

int CANXMC::setIdentifier(long id) { // TODO: delete in the future!
                                     // figure out filtering problem for xmc4700
  XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
  return 0;
};

int CANXMC::begin(long baudrate /*= 500e3*/) {
  /* CAN bit time configuration*/
  XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_NODE_bit_time_config = {
      .can_frequency = _XMC_CAN_config->can_frequency,
      .baudrate = (uint32_t)baudrate,
      .sample_point = (uint16_t)(80 * 100),
      .sjw = (uint16_t)1,
  };

  XMC_CAN_Enable(CAN_xmc);

  /* Configuration of CAN Node and enable the clock */
  XMC_CAN_InitEx(CAN_xmc, _XMC_CAN_config->can_clock,
                 _XMC_CAN_config->can_frequency);
  if (XMC_CAN_STATUS_SUCCESS ==
      XMC_CAN_NODE_NominalBitTimeConfigureEx(_XMC_CAN_config->can_node,
                                             &CAN_NODE_bit_time_config)) {
    XMC_CAN_NODE_EnableConfigurationChange(_XMC_CAN_config->can_node);
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    XMC_CAN_NODE_ReSetAnalyzerMode(_XMC_CAN_config->can_node);

    /* Configure CAN NODE input pin */
    XMC_GPIO_Init(_XMC_CAN_config->tx.port, _XMC_CAN_config->tx.pin,
                  &(_XMC_CAN_config->tx_config));
    XMC_GPIO_SetHardwareControl(_XMC_CAN_config->tx.port,
                                _XMC_CAN_config->tx.pin,
                                XMC_GPIO_HWCTRL_DISABLED);
    XMC_GPIO_Init(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin,
                  &(_XMC_CAN_config->rx_config));
    XMC_GPIO_SetHardwareControl(_XMC_CAN_config->rx.port,
                                _XMC_CAN_config->rx.pin,
                                XMC_GPIO_HWCTRL_DISABLED);
    XMC_CAN_NODE_SetReceiveInput(_XMC_CAN_config->can_node,
                                 _XMC_CAN_config->node_input);

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
    XMC_SCU_SetInterruptControl(_XMC_CAN_config->irq_num,
                                _XMC_CAN_config->irq_source);
#endif

    XMC_CAN_MO_SetEventNodePointer(&CAN_msg_rx,
                                   XMC_CAN_MO_POINTER_EVENT_RECEIVE,
                                   _XMC_CAN_config->irq_service_request);
    XMC_CAN_MO_EnableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);

    XMC_CAN_NODE_DisableConfigurationChange(_XMC_CAN_config->can_node);
    XMC_CAN_NODE_ResetInitBit(_XMC_CAN_config->can_node);

    /* enable the interrupt for receive 11bits message*/
    return 1;
  } else {
    return 0;
  }
};

void CANXMC::end() {
  XMC_CAN_MO_DisableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);
  XMC_CAN_Disable(CAN_xmc);
  CANControllerClass::end();
};

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

  // if((XMC_CAN_MO_GetStatus(&CAN_msg_rx) & CAN_MO_MOSTAT_NEWDAT_Msk) >>
  // CAN_MO_MOSTAT_NEWDAT_Pos){
  //   // return CAN message data length
  //   return _rxLength;
  // } else {
  //   return 0;
  // };
};

void CANXMC::onReceive(void (*callback)(int)) {
  CANControllerClass::onReceive(callback);
  if (callback) {
    NVIC_EnableIRQ(_XMC_CAN_config->irq_num);
  } else {
    NVIC_DisableIRQ(_XMC_CAN_config->irq_num);
  }
};

int CANXMC::filter(int id, int mask) {
  XMC_CAN_MO_SetStandardID(&CAN_msg_rx);
  XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
  XMC_CAN_MO_AcceptOnlyMatchingIDE(&CAN_msg_rx);
  XMC_CAN_MO_SetAcceptanceMask(&CAN_msg_rx, mask);

  return 1;
};

int CANXMC::filterExtended(long id, long mask) {
  XMC_CAN_MO_SetExtendedID(&CAN_msg_rx);
  XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
  XMC_CAN_MO_AcceptOnlyMatchingIDE(&CAN_msg_rx);
  XMC_CAN_MO_SetAcceptanceMask(&CAN_msg_rx, mask);
  return 0;
};

int CANXMC::observe() {
  // TODO: LJ: no idea what this is
  return 0;
};

int CANXMC::loopback() {
  // TODO: LJ: It is actually only some application level... it is not
  // library...
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
  XMC_CAN_InitEx(CAN_xmc, _XMC_CAN_config->can_clock,
                 _XMC_CAN_config->can_frequency);
  if (XMC_CAN_STATUS_SUCCESS == XMC_CAN_NODE_NominalBitTimeConfigureEx(
                                    CAN_NODE1, &CAN_NODE_bit_time_config)) {

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

  if (XMC_CAN_STATUS_SUCCESS == XMC_CAN_NODE_NominalBitTimeConfigureEx(
                                    CAN_NODE0, &CAN_NODE_bit_time_config)) {
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
    XMC_CAN_MO_SetEventNodePointer(&CAN_msg_rx,
                                   XMC_CAN_MO_POINTER_EVENT_RECEIVE,
                                   _XMC_CAN_config->irq_service_request);
    XMC_CAN_MO_EnableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);

    return 1;
  } else {
    return 0;
  }
};

int CANXMC::sleep() {
  XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
  return 0;
};

int CANXMC::wakeup() {
  XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
  return 0;
};

void CANXMC::onInterrupt() {
  if (can_frame_received == true) {
    CAN.parsePacket();
    CAN._onReceive(CAN.available());
  }
};

/* Interrupt Handler */
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
