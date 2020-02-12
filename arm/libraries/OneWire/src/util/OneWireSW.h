#ifndef ONEWIRE_SW_H
#define ONEWIRE_SW_H

#include "OneWireTiming.h"
#include "OneWireImpl.h"

namespace onewire
{
	class OneWireSW : public OneWireImpl
	{
	private: 
		//implementation-specific pin description
		uint8_t mActive;
		uint32_t mPinMask;
		volatile uint32_t *mPortInReg;
		volatile uint32_t *mPortOutReg;
		volatile uint32_t *mPortModeReg;
		uint32_t mPinModeMask;
		
		//implementation-specific timing description
		uint16_t mLowtimeShort;
		uint16_t mHightimeShort;
		uint16_t mLowtimeLong;
		uint16_t mHightimeLong;
		uint16_t mWaitBeforeCheck;
		uint16_t mWaitAfterCheck;
		uint16_t mResetDuration;
		
	public: 
		OneWireSW(uint8_t pin, const Timing_t *timing);
		~OneWireSW();
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