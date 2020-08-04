#include <Arduino.h>
#include "OneWireHW.h"

// SPI frequency to transmit 1 byte per microsecond
// this means 1 onewire bit per microsecond
#define ONEWIRE_1BIT_PER_MICROSSEC		8000000

namespace onewire
{
	//these are patterns for low-pulses with different lengths
	//the index equals the length of the low-pulse in bits (0 and 8 is forbidden and repalced by 1 and 7)
	uint8_t pulses[9] = {
		0x7F, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x01
	};
	
	OneWireHW::OneWireHW(XMC_SPI_t *spiConf, const Timing_t *timing) : OneWireImpl()
	{
		if(!isValid(timing))
		{
			timing = &timingStd;
		}
		mSpiHW = SPIClass(spiConf);
		mSpiConf = SPISettings(ONEWIRE_1BIT_PER_MICROSSEC/timing->bitDuration, MSBFIRST, SPI_MODE3);
		mSpiCodes[0] = pulses[(timing->lowtimeLong<<3) / timing->bitDuration];
		mSpiCodes[1] = pulses[(timing->lowtimeShort<<3) / timing->bitDuration];
		mSpiResetTime = timing->resetDuration / timing->bitDuration + 1;
	}
	
	void OneWireHW::begin(void)
	{
		mSpiHW.begin();
		mSpiHW.beginTransaction(mSpiConf);
		//reset();
	}
	
	OneWireHW::~OneWireHW()
	{
		end();
	}
	
	void OneWireHW::end(void)
	{
		mSpiHW.end();
	}
	
	uint8_t OneWireHW::reset(void)
	{
		noInterrupts();
		for(uint8_t i=0; i<mSpiResetTime; i++)
		{
			mSpiHW.transfer(0x00);
		}
		//test if slave sends a low pulse to indicate presence
		uint8_t ret =  (mSpiHW.transfer(0xFF) != 0xFF);
		interrupts();
		//wait for the maximum presence pulse time
		for(uint8_t i=1; i<(mSpiResetTime/2); i++)
		{
			mSpiHW.transfer(0xFF);
		}
		// bus should already have come up
		// wait some more time to be sure
		// if it does not come up return 0 to indicate a short circuit
		if((mSpiHW.transfer(0xFF)&(0x01)))
		{
			// return 1 if slave has indicated presence, 0 otherwise
			return ret;
		}
		else
		{
			return 0;
		}
	}
	
	void OneWireHW::write(uint8_t v, uint8_t power /*= 0*/)
	{
		for(uint8_t i=0; i<8; i++)
		{
			mByteBuffer[i] = mSpiCodes[v&(0x01<<i)];
		}
		mSpiHW.transfer(mByteBuffer, 8);
		// We don't have to care about powering and depowering on XMC controllers
		// We are using open-drain outputs with pull-ups to prevent short circuits. 
	}

	void OneWireHW::write_bytes(const uint8_t *buf, uint16_t count, bool power /*= 0*/)
	{
		for(uint16_t i=0; i<count; i++)
		{
			write(buf[i], power);
		}
		// We don't have to care about powering and depowering on XMC controllers
		// We are using open-drain outputs with pull-ups to prevent short circuits. 
	}

	uint8_t OneWireHW::read(void)
	{
		uint8_t i, ret=0;
		for(i=0; i<8; i++)
		{
			mByteBuffer[i] = mSpiCodes[1];
		}
		mSpiHW.transfer(mByteBuffer, 8);
		for(i=0; i<8; i++)
		{
			ret |= (mByteBuffer[i] == mSpiCodes[1]) << i;
		}
		return ret;
	}

	void OneWireHW::read_bytes(uint8_t *buf, uint16_t count)
	{
		for(uint16_t i=0; i<count; i++)
		{
			buf[i] = read();
		}
	}

	void OneWireHW::write_bit(uint8_t v)
	{
		mSpiHW.transfer(mSpiCodes[v&0x01]);
	}

	uint8_t OneWireHW::read_bit(void)
	{
		// if we get something else than we have sent, slave has held down the line(sent 0)
		return (mSpiHW.transfer(mSpiCodes[1]) == mSpiCodes[1]);
	}

	void OneWireHW::depower(void)
	{
		// We don't have to care about powering and depowering on XMC controllers
		// We are using open-drain outputs with pull-ups to prevent short circuits. 
	}
	
}
