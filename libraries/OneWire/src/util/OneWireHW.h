#ifndef ONEWIRE_HW_H
#define ONEWIRE_HW_H

#include "OneWireTiming.h"
#include "OneWireImpl.h"
#include "SPI.h"

namespace onewire
{
	class OneWireHW : public OneWireImpl
	{
	private: 
		SPISettings mSpiConf;
		SPIClass mSpiHW;
		uint8_t mSpiCodes[2];
		uint8_t mSpiResetTime;
		uint8_t mByteBuffer[8];
		
	public: 
		OneWireHW(XMC_SPI_t *spiConf, const Timing_t *timing);
		~OneWireHW();
		// begin and end do not appear in the original version
		// they are called automatically in our implementation
		virtual void begin(void) override;
		virtual void end(void) override;
		virtual uint8_t reset(void) override;
		virtual void write(uint8_t v, uint8_t power = 0) override;
		virtual void write_bytes(const uint8_t *buf, uint16_t count, bool power = 0) override;
		virtual uint8_t read(void) override;
		virtual void read_bytes(uint8_t *buf, uint16_t count) override;
		virtual void write_bit(uint8_t v) override;
		virtual uint8_t read_bit(void) override;
		virtual void depower(void) override;
	};
}
#endif