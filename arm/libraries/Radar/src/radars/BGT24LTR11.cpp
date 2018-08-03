/**
 * BGT24LTR11.cpp - interface for the 24GHz industrial radar eval board Sense2GoL with chip BGT24LTR11 inside
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */

#include "BGT24LTR11.h"

BGT_RADAR_CONFIG_t BGT24LTR11::default_config = {radar_buffersize : SENSE2GO_BUFFER_SIZE,
												 cycle_time : SENSE2GO_CYCLE_TIME,
												 sampling_rate : SENSE2GO_SAMPLING_RATE,
												 settle_time : SENSE2GO_SETTLE_TIME};

BGT24LTR11::BGT24LTR11(BGT_RADAR_CONFIG_t radarConfig)
{
	_config = radarConfig;

	_samplingTime = int(1000000 / _config.sampling_rate);
}

BGT24LTR11::~BGT24LTR11()
{
}

void BGT24LTR11::begin()
{
// turn on radar
#if (XMC_BOARD == XMC1300_Sense2GoL)
	pinMode(SENSE2GO_ON_PIN, OUTPUT);
	digitalWrite(SENSE2GO_ON_PIN, LOW);
#endif
	analogReadResolution(12u);
}

void BGT24LTR11::startAcq(void)
{
#if (XMC_BOARD == XMC1300_Sense2GoL)
	digitalWrite(SENSE2GO_ON_PIN, LOW);
	// timing of this delay reveals that the actual delay is much less than specified
	delayMicroseconds(SENSE2GO_SETTLE_TIME);
#endif
}

void BGT24LTR11::endAcq(void)
{
#if (XMC_BOARD == XMC1300_Sense2GoL)
	digitalWrite(SENSE2GO_ON_PIN, HIGH);
#endif
}

void BGT24LTR11::sampleInQ(int16_t *bufferI, int16_t *bufferQ)
{
	for (uint16_t i = 0; i < _config.radar_buffersize; i++)
	{
		bufferI[i] = analogRead(CH_I);
		bufferQ[i] = analogRead(CH_Q);
		delayMicroseconds(_samplingTime);
	}
}