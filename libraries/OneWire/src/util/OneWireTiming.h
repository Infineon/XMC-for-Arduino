#ifndef ONEWIRE_TIMING_H
#define ONEWIRE_TIMING_H

namespace onewire
{
	typedef struct
	{
		uint16_t lowtimeShort;
		uint16_t lowtimeLong;
		uint16_t checkAfter;
		uint16_t bitDuration;
		uint16_t resetDuration;
	} Timing_t;

	uint8_t isValid(const Timing_t *timing);

	extern Timing_t timingStd;
	extern Timing_t timingOverdrive;
}
#endif