/**
 * 
 * Have a look at the application note/reference manual for more information.
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

#ifndef BGT_RADAR_H
#define BGT_RADAR_H
#include <Arduino.h>

typedef struct
{
	int radar_buffersize;
	int cycle_time;
	int sampling_rate;
	int settle_time;
} BGT_RADAR_CONFIG_t;

class RadarDataProcessorClass;

// inherit from a radar class
class BGTRadar
{
  public:
	BGTRadar();
	~BGTRadar();
	virtual void begin() = 0;

	virtual void startAcq(void) = 0;

	virtual void endAcq(void) = 0;

	virtual void sampleInQ(int16_t *bufferI, int16_t *bufferQ) = 0;

	void setConfig(BGT_RADAR_CONFIG_t config);

  protected:
	friend class RadarDataProcessorClass;

	BGT_RADAR_CONFIG_t _config{};
	
	int _samplingTime;
};

#endif