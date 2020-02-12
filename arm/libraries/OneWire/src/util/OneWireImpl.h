#ifndef ONEWIRE_IMPL_H
#define ONEWIRE_IMPL_H

#include "SPI.h"
#include "OneWireSettings.h"

namespace onewire
{
	class OneWireImpl
	{
	private: 
#if ONEWIRE_SEARCH
		// global search state
		unsigned char ROM_NO[8];
		uint8_t LastDiscrepancy;
		uint8_t LastFamilyDiscrepancy;
		uint8_t LastDeviceFlag;
#endif

	public: 
		OneWireImpl(void);
		virtual ~OneWireImpl();
		virtual void begin(void) = 0;
		virtual void end(void) = 0;
		virtual uint8_t reset(void) = 0;
		virtual void write(uint8_t v, uint8_t power = 0) = 0;
		virtual void write_bytes(const uint8_t *buf, uint16_t count, bool power = 0) = 0;
		virtual uint8_t read(void) = 0;
		virtual void read_bytes(uint8_t *buf, uint16_t count) = 0;
		virtual void write_bit(uint8_t v) = 0;
		virtual uint8_t read_bit(void) = 0;
		virtual void depower(void) = 0;
	
		// Issue a 1-Wire rom select command, you do the reset first.
		void select(const uint8_t rom[8]);
		// Issue a 1-Wire rom skip command, to address all on bus.
		void skip(void);
		
#if ONEWIRE_SEARCH
		// Clear the search state so that if will start from the beginning again.
		void reset_search();

		// Setup the search to find the device type 'family_code' on the next call
		// to search(*newAddr) if it is present.
		void target_search(uint8_t family_code);

		// Look for the next device. Returns 1 if a new address has been
		// returned. A zero might mean that the bus is shorted, there are
		// no devices, or you have already retrieved all of them.  It
		// might be a good idea to check the CRC to make sure you didn't
		// get garbage.  The order is deterministic. You will always get
		// the same devices in the same order.
		uint8_t search(uint8_t *newAddr, bool search_mode = true);
#endif

#if ONEWIRE_CRC
		// Compute a Dallas Semiconductor 8 bit CRC, these are used in the
		// ROM and scratchpad registers.
		static uint8_t crc8(const uint8_t *addr, uint8_t len);
  #if ONEWIRE_CRC16
		// Compute the 1-Wire CRC16 and compare it against the received CRC.
		static bool check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc = 0);
		// Compute a Dallas Semiconductor 16 bit CRC. 
		static uint16_t crc16(const uint8_t* input, uint16_t len, uint16_t crc = 0);
  #endif
#endif
	};
}
#endif