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

private:
    XMC_ARD_CAN_t *_XMC_CAN_config;
};

extern CANXMC CAN;