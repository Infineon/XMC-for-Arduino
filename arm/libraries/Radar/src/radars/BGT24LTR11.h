/**
 * BGT24LTR11.h - interface for the 24GHz industrial radar eval board Sense2GoL with chip BGT24LTR11 inside
 *
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

#ifndef BGT24LTR11_H
#define BGT24LTR11_H
#include "BGTRadar.h"

/**
 * @brief Analog channels for reading raw I and Q data. if you connect the output of CH_I and CH_Q to other boards, be sure to choose A0 and A1 on the connected board; on XMC4700 Relax Kit those are P14.0 and P14.1
 * 
 */
#define CH_I A0
#define CH_Q A1

#if (XMC_BOARD == XMC1300_Sense2GoL)
/**
 * @brief The pin to turn on the radar chip. This is used when you are using the original Sense2GoL board
 * 
 */
#define SENSE2GO_ON_PIN BGT_ON
#endif

#define SENSE2GO_BUFFER_SIZE 128

/**
 * @brief Cycle time must be larger than t_sampling * no_samples + adc_settle_time
 * 
 */
#define SENSE2GO_CYCLE_TIME 140

#define SENSE2GO_SAMPLING_RATE 1408

/**
 * @brief Time (us) for the ADC of one single sample; e.g: f_adc = 1.408kHz -> 1/f_adc = 710 us, with a buffer size of 128: 710*128 = 90880 us = 90.88 ms
 * 
 */
#define SENSE2GO_SAMPLING_TIME int(1000000 / SENSE2GO_SAMPLING_RATE)


/**
 * @brief A delay is needed for the chip to settle after being turned on. You might turn on/off the chip only for a fraction of the duty cycle in order to save energy, in which case you need to make sure that 
 * this constant, as well as the cycle time, is set appropriately (from my experiments it should be around 200 ms, then the cycle time should be more than 300 ms). This has no effect if the chip is left on all time.
 * 
 */
#define SENSE2GO_SETTLE_TIME 220000

class BGT24LTR11 : public BGTRadar
{
	static BGT_RADAR_CONFIG_t default_config;

  public:
	BGT24LTR11(BGT_RADAR_CONFIG_t radarConfig = default_config);
	~BGT24LTR11();
	void begin();

	void startAcq(void);

	void endAcq(void);

	void sampleInQ(int16_t *bufferI, int16_t *bufferQ);
};

#endif