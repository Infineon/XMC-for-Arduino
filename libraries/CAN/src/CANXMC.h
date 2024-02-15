#include "CANController.h"

class CANXMC : public CANControllerClass {
      CANSAME5x();
        CANSAME5x(uint8_t tx_pin, uint8_t rx_pin);
        ~CANSAME5x() final;

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
}