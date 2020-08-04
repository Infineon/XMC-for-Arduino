#include <Arduino.h>
#include "OneWireTiming.h"

namespace onewire
{

	uint8_t isValid(const Timing_t *timing)
	{
		if(timing->lowtimeShort < timing->checkAfter
			&& timing->checkAfter < timing->lowtimeLong
			&& timing->lowtimeLong < timing->bitDuration
			&& timing->bitDuration < timing->resetDuration )
		{
			return TRUE;	
		}
		else
		{
			return FALSE;
		}
	}

	Timing_t timingStd = { 10, 65, 20, 70, 480 };
	Timing_t timingOverdrive = { 1, 8, 5, 15, 52 };

}