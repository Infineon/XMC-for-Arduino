#include "CANXMC.h"
#include <Arduino.h>
#define CAN_FREQUENCY_VALUE ((uint32_t)20000000)
namespace ifx
{
  XMC_CAN_MO_t CAN_message_11bits =
      {
        .can_mo_ptr = (CAN_MO_TypeDef*)CAN_MO0,
        {0xFFU, XMC_CAN_FRAME_TYPE_STANDARD_11BITS, XMC_CAN_ARBITRATION_MODE_IDE_DIR_BASED_PRIO_2}, // {can_identifier, can_id_mode, can_priority}
        {0xFFU, 1U}, // {can_id_mask, can_ide_mask}
        .can_data_length = 8U,
        .can_mo_type = XMC_CAN_MO_TYPE_RECMSGOBJ,
      };

  bool can_frame_received = false;

  #ifdef __cplusplus
    extern "C"
    {
#endif
    void  CAN0_7_IRQHandler(void)
    {
        /* Receive the message in the CAN_message MO */
        XMC_CAN_MO_Receive(&CAN_message_11bits);

        /* Set the frame received flag to true */
        can_frame_received = true;
    };
#ifdef __cplusplus
    }
#endif

    
  CANXMC::CANXMC(XMC_ARD_CAN_t *conf)
  {
    _XMC_CAN_config = conf;

  }
  CANXMC::~CANXMC() {}



  int CANXMC::begin(long baudrate)
  {
    
    XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_NODE_bit_time_config =
    {
        .can_frequency = CAN_FREQUENCY_VALUE,
        .baudrate = (uint32_t)baudrate,
        .sample_point = (uint16_t)(80 * 100),
        .sjw = (uint16_t)1,
    };
     /* Configuration of CAN Node and enable the clock */ 
    XMC_CAN_InitEx(CAN_xmc, XMC_CAN_CANCLKSRC_FOHP, OSCHP_GetFrequency()); // TODO: Macro CAN
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
      // XMC_GPIO_SetMode(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin, _XMC_CAN_config->rx_config.mode);
      XMC_CAN_NODE_SetReceiveInput(_XMC_CAN_config->can_node, _XMC_CAN_config->node_input);
      
      XMC_CAN_MO_Config(&CAN_message_11bits);
      XMC_CAN_AllocateMOtoNodeList(CAN_xmc, 1, 0);
     
      XMC_CAN_MO_SetEventNodePointer(&CAN_message_11bits, XMC_CAN_MO_POINTER_EVENT_RECEIVE, 7u);
      XMC_CAN_MO_EnableEvent(&CAN_message_11bits, XMC_CAN_MO_EVENT_RECEIVE);
      NVIC_EnableIRQ(CAN0_7_IRQn);
      XMC_CAN_NODE_DisableConfigurationChange(_XMC_CAN_config->can_node);
      XMC_CAN_NODE_ResetInitBit(_XMC_CAN_config->can_node);

      return 1;
    }
    else
    {
      return 0;
    } 
  };

  void CANXMC::end(){
    CANControllerClass::end();
  };

  int CANXMC::endPacket()
  {
    
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
    return 0;
  };

  int CANXMC::parsePacket()
  {  
     // CAN_message_11bits.can_data_length;
     return XMC_GPIO_GetInput(_XMC_CAN_config->rx.port, _XMC_CAN_config->rx.pin);
  };

  void CANXMC::onReceive(void (*callback)(int)){
    XMC_CAN_NODE_SetInitBit(_XMC_CAN_config->can_node);
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



  CANXMC CAN(&XMC_CAN_0);



};
    


