#include "CANXMC.h"

CANXMC::CANXMC():
  CANControllerClass(),
{

}


int CANXMC::begin(uint32_t baudrate) {
    XMC_CAN_InitEx(CAN, XMC_CAN_CANCLKSRC_FOHP, OSCHP_GetFrequency());
        
    XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t CAN_NODE_bit_time_config = 
    {
        .can_frequency = CAN_FREQUENCY_VALUE,
        .baudrate = (uint32_t)baudrate,
        .sample_point = (uint16_t)(80 * 100),
        .sjw = (uint16_t)1,
    };

    XMC_CAN_NODE_NominalBitTimeConfigureEx(CAN_NODE0, &CAN_NODE_bit_time_config)

    	
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE0);
  XMC_CAN_NODE_SetInitBit(CAN_NODE0);


}
