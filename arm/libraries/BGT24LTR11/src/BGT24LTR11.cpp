/**
 * BGT24LTR11.cpp - Library for Arduino to control the BGT24LTR11 in combination with the Sense2GoL evaluation board.
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

#include "BGT24LTR11.h"

extern "C"{
	void BGT24LTR11_CYCLE_TIMER_IRQHandler(void)
	{
		RadarBGT24LTR11.startAcq();
		RadarBGT24LTR11.sampleInQ();
		RadarBGT24LTR11.endAcq();  
	}
}

BGT24LTR11::BGT24LTR11(void)
{
		_bgt24ltr11_initialized	= BGT24LTR11_DISABLED;
		_bgt24ltr11_motion	= BGT24LTR11_NO_MOTION_DETECT;
		_bgt24ltr11_timing	= {};
		_bgt24ltr11_alg		= {};
}

BGT24LTR11::~BGT24LTR11(void)
{
	end();
}

void BGT24LTR11::begin(void)
{
	_bgt24ltr11_initialized	= BGT24LTR11_ENABLED;
	
	_bgt24ltr11_timing.t_sample_us			= 710;
	_bgt24ltr11_timing.t_cycle_ms			= 350;
	_bgt24ltr11_timing.N_samples			= 128;
	
	_bgt24ltr11_alg.hold_on_cycles			= 1;
	_bgt24ltr11_alg.trigger_det_level		= 200;
	_bgt24ltr11_alg.rootcalc_enable			= BGT24LTR11_DISABLED;
	
	_bgt24ltr11_contiguous_acq = false;
	
    memset( (void*)_bgt24ltr11_channel_I, 0, BGT24LTR11_MAX_SAMPLES ) ;
	
    memset( (void*)_bgt24ltr11_channel_Q, 0, BGT24LTR11_MAX_SAMPLES ) ;
	
	_bgt24ltr11_cyle_timer_id = 0;
	
	_bgt24ltr11_dataAvailable = false;
	
	pinMode(BGT24LTR11_BGT_ON_PIN, OUTPUT);	
	digitalWrite(BGT24LTR11_BGT_ON_PIN, HIGH);
	analogReadResolution(12u);
}

void BGT24LTR11::end(void)
{

}
		
BGT24LTR11_ERROR_t BGT24LTR11::start(BGT24LTR11_ACQ_MODE_t acq_mode)
{
	BGT24LTR11_ERROR_t error = BGT24LTR11_ERROR;
	
	if(_bgt24ltr11_initialized != BGT24LTR11_ENABLED)
	{
		error = BGT24LTR11_NOT_INITIALIZED;
	}
	else
	{
		switch(acq_mode)
		{
			case BGT24LTR11_SINGLE_ACQ:
				startAcq();
				sampleInQ();
				endAcq();  
				break;
			case BGT24LTR11_CONTIGUOUS_ACQ:
				digitalToggle(LED3);
				_bgt24ltr11_contiguous_acq = true;        
				_bgt24ltr11_cyle_timer_id = XMC_SYSTIMER_CreateTimer(_bgt24ltr11_timing.t_cycle_ms, XMC_SYSTIMER_MODE_PERIODIC, (XMC_SYSTIMER_CALLBACK_t) BGT24LTR11_CYCLE_TIMER_IRQHandler, NULL);
				if (_bgt24ltr11_cyle_timer_id != 0)
				{
					XMC_SYSTIMER_StartTimer(_bgt24ltr11_cyle_timer_id);
				}
				// Start timer -> interrupt contains acq 
				break;
			default:
				error = BGT24LTR11_INVALID_ACQ_MODE;
				break;
		}
	
	}
	return error;
}
	
BGT24LTR11_ERROR_t BGT24LTR11::stop(void)
{
	BGT24LTR11_ERROR_t error = BGT24LTR11_ERROR;
	
	if(_bgt24ltr11_initialized != BGT24LTR11_ENABLED)
	{
		error = BGT24LTR11_NOT_INITIALIZED;
	}
	else if(_bgt24ltr11_contiguous_acq)
	{
		error = BGT24LTR11_NOT_IN_CONTIGUOUS_MODE;
	}
	else
	{
		// Delete timer
	}
	
	return error;
}

void BGT24LTR11::startAcq(void)
{
  static uint32_t BGT24_settle;
  digitalWrite(BGT24LTR11_BGT_ON_PIN, LOW);
  delayMicroseconds(250000u);
}
void BGT24LTR11::endAcq(void)
{
  digitalWrite(BGT24LTR11_BGT_ON_PIN, HIGH);
}

void BGT24LTR11::sampleInQ(void)
{
  for(uint16_t i = 0; i < _bgt24ltr11_timing.N_samples; i++)
  {
    _bgt24ltr11_channel_I[i] = analogRead(CH_I);
    _bgt24ltr11_channel_Q[i] = analogRead(CH_Q);
    delayMicroseconds(_bgt24ltr11_timing.t_sample_us);
  }
  _bgt24ltr11_dataAvailable = true;
}

bool BGT24LTR11::dataAvailable(void)
{
	return _bgt24ltr11_dataAvailable;
}

BGT24LTR11_ERROR_t BGT24LTR11::motionDetection(void)
{
	BGT24LTR11_ERROR_t error = BGT24LTR11_ERROR;
	
	if(_bgt24ltr11_initialized != BGT24LTR11_ENABLED)
	{
		error = BGT24LTR11_NOT_INITIALIZED;
	}
	else if (_bgt24ltr11_dataAvailable == false)
	{
		error = BGT24LTR11_NO_dataAvailable;
	}
	else	
	{		
		int8_t motion = 0;
		
		bool next_is_max = true;
		
		if(_bgt24ltr11_channel_I[0] > _bgt24ltr11_channel_I[1] )
		{	
			next_is_max = false;
		}
		
		for(uint16_t i = 0; i < (_bgt24ltr11_timing.N_samples - 1); i++)
		{
			if( (_bgt24ltr11_channel_I[i] < (2048 - _bgt24ltr11_alg.trigger_det_level)) || \
					(_bgt24ltr11_channel_I[i] > (2048 + _bgt24ltr11_alg.trigger_det_level)) )
			{
				if(next_is_max)
				{
					if(_bgt24ltr11_channel_I[i] > _bgt24ltr11_channel_I[i+1] )
					{
						if(_bgt24ltr11_channel_Q[i] > _bgt24ltr11_channel_Q[i+1])
						{
							motion++;
						}
						else if(_bgt24ltr11_channel_Q[i] < _bgt24ltr11_channel_Q[i+1])
						{
							motion--;
						}
						next_is_max = false;
					}
				}
				else
				{
					if(_bgt24ltr11_channel_I[i] < _bgt24ltr11_channel_I[i+1] )
					{
						if(_bgt24ltr11_channel_Q[i] > _bgt24ltr11_channel_Q[i+1])
						{
							motion--;
						}
						else if(_bgt24ltr11_channel_Q[i] < _bgt24ltr11_channel_Q[i+1])
						{
							motion++;
						}
						next_is_max = true;
					}
				}
			}
				
			if(motion < -MAGIC_NUMBER_FOR_MOTION_DETECTION)
			{
				_bgt24ltr11_motion = BGT24LTR11_MOTION_DETECT_DEPARTING;
				break;
			}
			else if(motion > MAGIC_NUMBER_FOR_MOTION_DETECTION)
			{
				_bgt24ltr11_motion = BGT24LTR11_MOTION_DETECT_APPROACHING;
				break;
			}
			else
			{
				_bgt24ltr11_motion = BGT24LTR11_NO_MOTION_DETECT;
			}	
		}
		
		error = BGT24LTR11_OK;
	}
	return error;
}

BGT24LTR11_MOTION_t BGT24LTR11::getMotion(void)
{
	motionDetection();
	_bgt24ltr11_dataAvailable = false;
	return _bgt24ltr11_motion;
}

BGT24LTR11_ERROR_t BGT24LTR11::getChannelData(uint16_t * ch_I_ptr, uint16_t * ch_Q_ptr)
{
	BGT24LTR11_ERROR_t error = BGT24LTR11_ERROR;
	
	if(_bgt24ltr11_initialized != BGT24LTR11_ENABLED)
	{
		error = BGT24LTR11_NOT_INITIALIZED;
	}
	else	
	{
		for(uint16_t index = 0u; index < _bgt24ltr11_timing.N_samples; index++)
		{
			ch_I_ptr[index] = _bgt24ltr11_channel_I[index];
			ch_Q_ptr[index] = _bgt24ltr11_channel_Q[index];
		}
		
		_bgt24ltr11_dataAvailable = false;
		
		error = BGT24LTR11_OK;
	}
	return error;
}