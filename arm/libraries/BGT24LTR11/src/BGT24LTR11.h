/**
 * BGT24LTR11.h - Library for Arduino to control the BGT24LTR11 in combination with the Sense2GoL evaluation board.
 *
 * The General Purposes Direct Memory Access (GPDMA) is a module within the XMC4000 series to transfer data
 * without any CPU interference. When a DMA transfer request is generated, the GPDMA transfers data stored
 * at the source address to the destination address.
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

#include <Arduino.h>

#define BGT24LTR11_MAX_SAMPLES		256
#define BGT24LTR11_BGT_ON_PIN		BGT_ON
#define BGT24LTR11_TX_ON_PIN		TX_ON

#define MAGIC_NUMBER_FOR_MOTION_DETECTION 3

typedef enum {
	BGT24LTR11_DISABLED = 0,
	BGT24LTR11_ENABLED = 1
} BGT24LTR11_ENABLE_t;

typedef enum {
	BGT24LTR11_OK = 0,
	BGT24LTR11_ERROR = 1,
	BGT24LTR11_NOT_INITIALIZED = 2,
	BGT24LTR11_INVALID_ACQ_MODE  = 3,
	BGT24LTR11_NOT_IN_CONTINUOUS_MODE  = 4,
	BGT24LTR11_NO_dataAvailable  = 5
} BGT24LTR11_ERROR_t;

typedef enum {
	BGT24LTR11_MOTION_DETECT_APPROACHING = 0,
	BGT24LTR11_MOTION_DETECT_DEPARTING = 1,
	BGT24LTR11_NO_MOTION_DETECT = 2
} BGT24LTR11_MOTION_t;

typedef enum {
	BGT24LTR11_SINGLE_ACQ = 0,			// One time
	BGT24LTR11_CONTINUOUS_ACQ = 1,		// Every t_cylce
	BGT24LTR11_FALSE = 2
} BGT24LTR11_ACQ_MODE_t;

typedef struct {
	uint32_t t_sample_us;
	uint32_t t_cycle_ms;
	uint8_t N_samples;
} BGT24LTR11_TIMING_t;

typedef struct {
	uint8_t  hold_on_cycles;
	uint32_t trigger_det_level;
	BGT24LTR11_ENABLE_t rootcalc_enable;
} BGT24LTR11_ALG_t;

extern int BGT24LTR11_CYCLE_TIMER_IRQHandler(int, int16_t);

class BGT24LTR11
{
	public:
		BGT24LTR11(void);
		~BGT24LTR11(void);
		void begin(void);
		void end(void);
		
		BGT24LTR11_ERROR_t start(BGT24LTR11_ACQ_MODE_t acq_mode);
		
		BGT24LTR11_ERROR_t stop(void);
		
		void startAcq(void);
		
		void endAcq(void);
			
		void sampleInQ(void);
		
		bool dataAvailable(void);
				
		BGT24LTR11_MOTION_t getMotion(void);
		
		BGT24LTR11_ERROR_t getChannelData(uint16_t *, uint16_t *);
		

	private:
		
		BGT24LTR11_ENABLE_t _bgt24ltr11_initialized;
		
		BGT24LTR11_MOTION_t _bgt24ltr11_motion;
		
		BGT24LTR11_TIMING_t _bgt24ltr11_timing;
		
		BGT24LTR11_ALG_t _bgt24ltr11_alg;
		
		bool _bgt24ltr11_continuous_acq;
		
		uint32_t _bgt24ltr11_cyle_timer_id;
		
		uint16_t _bgt24ltr11_channel_I[BGT24LTR11_MAX_SAMPLES];
		
		uint16_t _bgt24ltr11_channel_Q[BGT24LTR11_MAX_SAMPLES];
		
		bool _bgt24ltr11_dataAvailable;

		BGT24LTR11_ERROR_t motionDetection(void);

		BGT24LTR11_ACQ_MODE_t _acq_mode;
};

#endif