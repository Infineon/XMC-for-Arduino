#include "CANController.h"
#include "xmc_can.h"

class CANXMC : public CANControllerClass {

public:
    CANXMC(XMC_ARD_CAN_t *conf);
    ~CANXMC() final;

    int begin(long baudRate = 500E3) final;
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
    int setIdentifier(long);
    static void onInterrupt();

    // Getter functions for CAN_msg_rx and CAN_msg_tx
    XMC_CAN_MO_t *getRxMessage();
    XMC_CAN_MO_t *getTxMessage();

private:
    XMC_ARD_CAN_t *_XMC_CAN_config;
    XMC_CAN_MO_t CAN_msg_rx;
    XMC_CAN_MO_t CAN_msg_tx;
};

extern CANXMC CAN;