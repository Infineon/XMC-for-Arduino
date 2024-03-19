#include "CANController.h"
#include "xmc_can.h"

#ifndef CAN_h
#define CAN_h

namespace ifx {
class CANXMC : public CANControllerClass {


public:
      // CANXMC();   
      CANXMC(XMC_ARD_CAN_t* conf);
      ~CANXMC() final;

      int begin(long baudRate) final;
      void end() final;

      int endPacket() final;
      
      int parsePacket() final;

      void onReceive(void (*callback)(int)) final;

      using CANControllerClass::filter;
      int filter(int id, int mask) final;
      using CANControllerClass::filterExtended;
      int filterExtended(long id, long mask) final;

      int observe() final;
      int loopback() final;
      int sleep() final;
      int wakeup() final;
      static void onInterrupt(); //TODO: callback works, but ugly

private:
      XMC_ARD_CAN_t* _XMC_CAN_config;
      void CAN0_7_IRQHandler(void);  
};

extern CANXMC CAN;

};
#endif /* CAN_h */