#include <Arduino.h>
#include "OneWireSW.h"

#define IFX_ONEWIRE_MODE_OD		0xC0C0C0C0
#define IFX_ONEWIRE_PINOUTPUT	*mPortModeReg |= mPinModeMask & IFX_ONEWIRE_MODE_OD
#define IFX_ONEWIRE_PININPUT	*mPortModeReg &= ~mPinModeMask
#define IFX_ONEWIRE_PINOUTLOW	*mPortOutReg &= ~mPinMask
#define IFX_ONEWIRE_PINOUTHIGH	*mPortOutReg |= mPinMask
#define IFX_ONEWIRE_PINREAD		((*mPortInReg & mPinMask) > 0)


namespace onewire
{

	OneWireSW::OneWireSW(uint8_t pin, const Timing_t *timing) : OneWireImpl()
	{
		if(!isValid(timing))
		{
			timing = &timingStd;
		}
		mLowtimeShort = timing->lowtimeShort;
		mHightimeShort = timing->bitDuration - timing->lowtimeShort;
		mLowtimeLong = timing->lowtimeLong;
		mHightimeLong = timing->bitDuration - timing->lowtimeLong;
		mWaitBeforeCheck = timing->checkAfter - timing->lowtimeShort;
		mWaitAfterCheck = timing->bitDuration - timing->checkAfter;
		mResetDuration = timing->resetDuration;
		
		mActive = FALSE;
		mPortOutReg = &(mapping_port_pin[pin].port->OUT);
		mPortInReg = &(mapping_port_pin[pin].port->IN);
		mPortModeReg = &(mapping_port_pin[pin].port->IOCR[mapping_port_pin[pin].pin>>2]);
		mPinMask = 1 << mapping_port_pin[pin].pin;
		mPinModeMask = 0xF8 << ((mapping_port_pin[pin].pin&0x03)<<3);
	}
	
	OneWireSW::~OneWireSW()
	{
		end();
	}
	
	void OneWireSW::begin(void)
	{
		IFX_ONEWIRE_PININPUT;
		IFX_ONEWIRE_PINOUTHIGH;
		IFX_ONEWIRE_PINOUTPUT;
		mActive = TRUE;
		//reset();
	}
	
	void OneWireSW::end(void)
	{
		IFX_ONEWIRE_PININPUT;
		mActive = FALSE;
	}
	
	uint8_t OneWireSW::reset(void)
	{
		noInterrupts();
		IFX_ONEWIRE_PINOUTLOW;
		delayMicroseconds(mResetDuration);
		IFX_ONEWIRE_PINOUTHIGH;
		delayMicroseconds(mHightimeShort+mWaitBeforeCheck);
		// test if slave holds the line down to indicate presence
		uint8_t ret = !IFX_ONEWIRE_PINREAD;
		//wait for the end of the presence pulse
		delayMicroseconds(mResetDuration/2);
		interrupts();
		// bus should already have come up
		// if it does not come up return 0 to indicate a short circuit
		if(IFX_ONEWIRE_PINREAD)
		{
			// return 1 if slave has indicated presence, 0 otherwise
			return ret;
		}
		else
		{
			return 0;
		}
	}
	
	void OneWireSW::write(uint8_t v, uint8_t power /* = 0 */)
	{
		for(uint8_t i=0x01; i>0; i<<=1)
		{
			write_bit((v&i)?1:0);
		}
		// We don't have to care about powering and depowering on XMC controllers
		// We are using open-drain outputs with pull-ups to prevent short circuits. 
	}

	void OneWireSW::write_bytes(const uint8_t *buf, uint16_t count, bool power /* = 0 */)
	{
		for(uint8_t i=0; i<count; i++)
		{
			write(buf[i]);
		}
		// We don't have to care about powering and depowering on XMC controllers
		// We are using open-drain outputs with pull-ups to prevent short circuits. 
	}

	uint8_t OneWireSW::read(void)
	{
		uint8_t ret = 0;
		for(uint8_t i=0x01; i>0; i<<=1)
		{
			if(read_bit())
			{
				ret |= i;
			}
		}
		return ret;
	}

	void OneWireSW::read_bytes(uint8_t *buf, uint16_t count)
	{
		for(uint8_t i=0; i<count; i++)
		{
			buf[i] = read();
		}
	}

	void OneWireSW::write_bit(uint8_t v)
	{
		noInterrupts();
		if(v&0x01)
		{
			IFX_ONEWIRE_PINOUTLOW;
			delayMicroseconds(mLowtimeShort);
			IFX_ONEWIRE_PINOUTHIGH;
			delayMicroseconds(mHightimeShort);
		}
		else
		{
			IFX_ONEWIRE_PINOUTLOW;
			delayMicroseconds(mLowtimeLong);
			IFX_ONEWIRE_PINOUTHIGH;
			delayMicroseconds(mHightimeLong);
		}
		interrupts();
	}

	uint8_t OneWireSW::read_bit(void)
	{
		uint8_t ret;
		noInterrupts();
		IFX_ONEWIRE_PINOUTLOW;
		delayMicroseconds(mLowtimeShort);
		IFX_ONEWIRE_PINOUTHIGH;
		delayMicroseconds(mWaitBeforeCheck);
		// test if slave holds the line down to send a 0
		ret = IFX_ONEWIRE_PINREAD;
		delayMicroseconds(mWaitAfterCheck);
		interrupts();
		return ret;
	}

	void OneWireSW::depower(void)
	{
		// We don't have to care about powering and depowering on XMC controllers
		// We are using open-drain outputs with pull-ups to prevent short circuits. 
	}
	
}

