#include "CANXMC.h"
#include <Arduino.h>


namespace ifx {

/* CAN Receive Message Object definition */
XMC_CAN_MO_t CAN_msg_rx = {
    .can_mo_ptr = (CAN_MO_TypeDef *)CAN_MO0,
    {0xFF, XMC_CAN_FRAME_TYPE_STANDARD_11BITS, // {can_identifier, can_id_mode
     XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1}, // can_priority}
    {0xFFU, 1U}, // {can_id_mask, can_ide_mask}
    .can_data_length = 0U,
    .can_mo_type = XMC_CAN_MO_TYPE_RECMSGOBJ,
};

/* CAN Transmit Message Object definition */
XMC_CAN_MO_t CAN_msg_tx = {
    .can_mo_ptr = (CAN_MO_TypeDef *)CAN_MO1,
    {0xFF, XMC_CAN_FRAME_TYPE_STANDARD_11BITS, // {can_identifier, can_id_mode
     XMC_CAN_ARBITRATION_MODE_ORDER_BASED_PRIO_1}, // can_priority}
    {0xFFU, 1U}, // {can_id_mask, can_ide_mask}
    .can_data_length = 1U,
    .can_mo_type = XMC_CAN_MO_TYPE_TRANSMSGOBJ,
};

/* Flag for receive interrupt*/
static volatile bool can_frame_received = false;

/* construct with configuration of different target */
CANXMC::CANXMC(XMC_ARD_CAN_t *conf) { _XMC_CAN_config = conf; }
CANXMC::~CANXMC() {}

  int CANXMC::setIdentifier(long id) { // TODO: delete in the future!
                                            // figure out filtering problem
    XMC_CAN_MO_SetIdentifier(&CAN_msg_rx, id);
    return 0;
  };


  int CANXMC::begin(long baudrate /*= 500e3*/)
  {
    /* CAN bit time configuration*/
    XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_NODE_bit_time_config =
    {
        .can_frequency = _XMC_CAN_config->can_frequency,
        .baudrate = (uint32_t)baudrate,
        .sample_point = (uint16_t)(80 * 100),
        .sjw = (uint16_t)1,
    };
    XMC_CAN_Enable(CAN_xmc);
     /* Configuration of CAN Node and enable the clock */ 
    #if (UC_FAMILY == XMC4)
      #define CAN_CLOCK_SOURCE ((XMC_CAN_CANCLKSRC_t)XMC_CAN_CANCLKSRC_FPERI) 
    #else
      #define CAN_CLOCK_SOURCE ((XMC_CAN_CANCLKSRC_t)XMC_CAN_CANCLKSRC_MCLK)
    #endif
    XMC_CAN_InitEx(CAN_xmc, CAN_CLOCK_SOURCE, _XMC_CAN_config->can_frequency); 
    if(XMC_CAN_STATUS_SUCCESS == XMC_CAN_NODE_NominalBitTimeConfigureEx(_XMC_CAN_config->can_node, &CAN_NODE_bit_time_config))
    {
      XMC_CAN_NODE_EnableConfigurationChange(_XMC_CAN_config->can_node);
      XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
      XMC_CAN_NODE_ReSetAnalyzerMode(_XMC_CAN_config->can_node);

      /* Configure CAN NODE input pin */
      XMC_GPIO_Init(_XMC_CAN_config->tx.port, _XMC_CAN_config->tx.pin,  &(_XMC_CAN_config->tx_config));
      XMC_GPIO_SetHardwareControl(_XMC_CAN_config->tx.port, _XMC_CAN_config->tx.pin, XMC_GPIO_HWCTRL_DISABLED);
      XMC_GPIO_Init(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin, &(_XMC_CAN_config->rx_config));
      XMC_GPIO_SetHardwareControl(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin, XMC_GPIO_HWCTRL_DISABLED);
      XMC_CAN_NODE_SetReceiveInput(_XMC_CAN_config->can_node, _XMC_CAN_config->node_input);
      
      XMC_CAN_MO_Config(&CAN_msg_rx);
      XMC_CAN_AllocateMOtoNodeList(CAN_xmc, 1, 0);
      XMC_CAN_MO_Config(&CAN_msg_tx);
      XMC_CAN_AllocateMOtoNodeList(CAN_xmc, 1, 1);
    
      /* Message object accepts the reception of both, standard and extended frames */
      XMC_CAN_MO_AcceptStandardAndExtendedID(&CAN_msg_rx);
      // CAN_msg_rx.can_ide_mask = 0U;
      // CAN_msg_rx.can_mo_ptr->MOAMR = 0x3fffffff & ~(uint32_t)(CAN_MO_MOAMR_MIDE_Msk);
#if (UC_SERIES == XMC14)
    // select interrupt source (A,B,C etc) input to NVIC node (only for XMC1400 devices)  
      XMC_SCU_SetInterruptControl(_XMC_CAN_config->irq_num, _XMC_CAN_config->irq_source);
#endif    
      XMC_CAN_MO_SetEventNodePointer(&CAN_msg_rx, XMC_CAN_MO_POINTER_EVENT_RECEIVE, _XMC_CAN_config->irq_service_request);
      XMC_CAN_MO_EnableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);

      XMC_CAN_NODE_DisableConfigurationChange(_XMC_CAN_config->can_node);
      XMC_CAN_NODE_ResetInitBit(_XMC_CAN_config->can_node);

     /* enable the interrupt for receive 11bits message*/
      return 1;
    }
    else
    {
      return 0;
    } 
  };

  void CANXMC::end(){
    XMC_CAN_MO_DisableEvent(&CAN_msg_rx, XMC_CAN_MO_EVENT_RECEIVE);
    XMC_CAN_Disable(CAN_xmc);
    CANControllerClass::end();

  };

  int CANXMC::endPacket() {
    if (!CANControllerClass::endPacket()) {
      return 0;
    }

    if (!_txRtr) {
      memcpy(CAN_msg_tx.can_data_byte, _txData, _txLength);
    }
    XMC_CAN_MO_SetDataLengthCode(&CAN_msg_tx, _txLength);
    XMC_CAN_MO_SetIdentifier(&CAN_msg_tx, _txId);

    /* Configure data to be transmitted and data length code */
    XMC_CAN_MO_UpdateData(&CAN_msg_tx);

    /* Send data in CAN_NODE_LMO_0 */
    XMC_CAN_MO_Transmit(&CAN_msg_tx);

    return 1;
  };

  int CANXMC::parsePacket()
  {  
    while((XMC_CAN_MO_GetStatus(&CAN_msg_rx) & CAN_MO_MOSTAT_NEWDAT_Msk) >> CAN_MO_MOSTAT_NEWDAT_Pos != 1);
      // XMC_CAN_MO_UpdateData(&CAN_msg_rx);
      XMC_CAN_MO_Receive(&CAN_msg_rx);


      // check CAN frame type
      _rxId = XMC_CAN_MO_GetIdentifier(&CAN_msg_rx);

      if (CAN_msg_rx.can_id_mode == XMC_CAN_FRAME_TYPE_EXTENDED_29BITS){
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
    // set the flag back and wait for next receive 
    can_frame_received = false;
    // XMC_CAN_MO_SetDataLengthCode(&CAN_msg_rx, 0U); 
    _rxIndex = 0;
    
    return _rxLength;

      // if((XMC_CAN_MO_GetStatus(&CAN_msg_rx) & CAN_MO_MOSTAT_NEWDAT_Msk) >> CAN_MO_MOSTAT_NEWDAT_Pos){
      //   // return CAN message data length
      //   return _rxLength;
      // } else {
      //   return 0;
      // };
    
  };

  void CANXMC::onReceive(void (*callback)(int)){
     CANControllerClass::onReceive(callback);
      if (callback) {
          NVIC_EnableIRQ(_XMC_CAN_config->irq_num); 
        } else {
          NVIC_DisableIRQ(_XMC_CAN_config->irq_num);
        }
  };

  int CANXMC::filter(int id, int mask)
  {
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  int CANXMC::filterExtended(long id, long mask)
  {
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  int CANXMC::observe()
  {
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  int CANXMC::loopback()
  {
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  int CANXMC::sleep()
  {
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  int CANXMC::wakeup(){
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  void CANXMC::onInterrupt() {
      if (can_frame_received == true) {
         CAN.parsePacket();
         CAN._onReceive(CAN.available());
      }
  };

  /* Interrupt Handler*/
  extern "C" {
#if defined(XMC4700_Relax_Kit)
  void CAN0_7_IRQHandler() {
    /* Set the frame received flag to true */
    can_frame_received = true;

    CAN.onInterrupt();
  }
#elif defined(XMC1400_XMC2GO) 
  void CAN0_3_IRQHandler() {
    /* Set the frame received flag to true */
    can_frame_received = true;

    CAN.onInterrupt();
  }
#endif
  }

  CANXMC CAN(&XMC_CAN_0);

  }; // namespace ifx
    


