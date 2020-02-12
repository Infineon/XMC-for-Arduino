#include <Arduino.h>
#include "IFXRadarPulsedDoppler.h"

IFXRadarPulsedDoppler::IFXRadarPulsedDoppler()
{
	this->result_handler_registered = false;
	this->error_handler_registered = false;
	this->outDev = NULL;
}

uint8_t IFXRadarPulsedDoppler::setMinSpeed(float speedMs)
{
  uint8_t status;
  // convert speed from mps to kmph
  float speedKm = (speedMs * 18) / 5;
  status = radar_ard_set_min_speed_kmph(speedKm);
  return status;
}

float IFXRadarPulsedDoppler::getMinSpeed(void)
{
  float speedKm = radar_ard_get_min_speed_kmph();
  // convert speed from mps to kmph
  float speedMs = (speedKm * 5) / 18;
  return speedMs;
}

uint8_t IFXRadarPulsedDoppler::setMaxSpeed(float speedMs)
{
  uint8_t status;
  // convert speed from mps to kmph
  float speedKm = (speedMs * 18) / 5;
  status = radar_ard_set_max_speed_kmph(speedKm);
  return status;
}

float IFXRadarPulsedDoppler::getMaxSpeed(void)
{
  float speedKm = radar_ard_get_max_speed_kmph();
  // convert speed from mps to kmph
  float speedMs = (speedKm * 5) / 18;
  return speedMs;
}

uint8_t IFXRadarPulsedDoppler::setMotionSensitivity(float threshold)
{
  uint8_t status = radar_ard_set_motion_sensitivity(threshold);
  return status;
}

float IFXRadarPulsedDoppler::getMotionSensitivity(void)
{
  float threshold = radar_ard_get_motion_sensitivity();
  return threshold;
}

uint8_t IFXRadarPulsedDoppler::setDopplerSensitivity(float threshold)
{
  uint8_t status = radar_ard_set_doppler_sensitivity(threshold);
  return status;
}

float IFXRadarPulsedDoppler::getDopplerSensitivity(void)
{
  float threshold = radar_ard_get_doppler_sensitivity();
  return threshold;
}

uint8_t IFXRadarPulsedDoppler::setFramePeriod(uint8_t periodUs)
{
  uint8_t status = radar_ard_set_frame_period_usec(periodUs);
  return status;
}

uint8_t IFXRadarPulsedDoppler::getFramePeriod(void)
{
  uint8_t periodUs = radar_ard_get_frame_period_usec();
  return periodUs;
}

uint8_t IFXRadarPulsedDoppler::setSampleFreq(uint32_t frequencyHz)
{
  uint8_t status = radar_ard_set_adc_sampling_freq_Hz(frequencyHz);
  return status;
}

uint32_t IFXRadarPulsedDoppler::getSampleFreq(void)
{
  uint32_t frequencyHz = radar_ard_get_adc_sampling_freq_hz();
  return frequencyHz;
}

uint8_t IFXRadarPulsedDoppler::setSkipSamples(uint32_t numSamples)
{
  uint8_t status = radar_ard_set_num_skip_samples(numSamples);
  return status;
}

uint32_t IFXRadarPulsedDoppler::getSkipSamples(void)
{
  uint32_t numSamples = radar_ard_get_num_skip_samples();
  return numSamples;
}

uint8_t IFXRadarPulsedDoppler::setNumSamples(uint32_t numSamples)
{
  uint8_t status = radar_ard_set_num_samples(numSamples);
  return status;
}

uint32_t IFXRadarPulsedDoppler::getNumSamples(void)
{
  uint32_t numSamples = radar_ard_get_num_samples();
  return numSamples;
}

uint8_t IFXRadarPulsedDoppler::setPulseWidth(uint32_t widthUs)
{
  uint8_t status = radar_ard_set_pulse_width_usec(widthUs);
  return status;
}

uint32_t IFXRadarPulsedDoppler::getPulseWidth(void)
{
  uint32_t widthUs = radar_ard_get_pulse_width_usec();
  return widthUs;
}

uint32_t IFXRadarPulsedDoppler::getMinFramePeriod(void)
{
  uint32_t periodUs = radar_ard_get_min_frame_period_usec();
  return periodUs;
}

float IFXRadarPulsedDoppler::getCurrentConsumption(void)
{
  float currentMA = radar_ard_get_current_consumption_mA();
  return currentMA;
}

void IFXRadarPulsedDoppler::registerResultCallback(void(*callBackPtr)) // register algo done callback function
{
  radar_ard_register_result_handler(callBackPtr);
}

void IFXRadarPulsedDoppler::registerErrorCallback(void(*callBackPtr))
{
  radar_ard_register_error_handler(callBackPtr);
}

void IFXRadarPulsedDoppler::initHW(void)
{
  uint32_t status = radar_ard_hw_init();
  if (status)
  {
	/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
	if( this->outDev != NULL)
		this->outDev->println("Low level HW initialization failed\n");
	
    while (1U)
		;
  }
}

void IFXRadarPulsedDoppler::begin(void) // trigger algo_process() and init()
{
  radar_ard_init();
  if (radar_ard_is_initalized())
  {
	  uint8_t error = radar_ard_start();
	  if (error > 0 && error_handler_registered == false)
	  {
		  if( this->outDev != NULL) 
		  {
			  this->outDev->print("Error on Start occured (");
			  this->outDev->print(error);
			  this->outDev->println(")");
		  }
		  while(1)
			  ;
	  }
  }
  else
  {
    if( this->outDev != NULL)
		this->outDev->print("Error on Init occured!");
  }
}

void IFXRadarPulsedDoppler::end(void)
{
  radar_ard_stop();
}

void IFXRadarPulsedDoppler::run(void) // run radar process
{
  radar_ard_process();
}

bool IFXRadarPulsedDoppler::targetAvailable(void)
{
  if (radar_ard_is_motion())
  {
	return true;
  }
  else
  {
	return false;
  }
}

float IFXRadarPulsedDoppler::getDopplerLevel(void)
{
  float level = radar_ard_get_doppler_level();
  return level;
}

float IFXRadarPulsedDoppler::getDopplerFreqHz(void)
{
  float frequency = radar_ard_get_doppler_frequency_hz();
  return frequency;
}

float IFXRadarPulsedDoppler::getVelocity(void)
{
  float speed = radar_ard_get_doppler_speed_kmph();
  if (radar_ard_is_target_departing() == 1)
  {
    speed = -speed;
  }
  return speed;
}

float IFXRadarPulsedDoppler::getSpeed(void)
{
  float speed = radar_ard_get_doppler_speed_kmph();
  return speed;
}

uint8_t IFXRadarPulsedDoppler::getDirection(void)
{
  uint8_t direction = 0; 
  if (radar_ard_is_target_departing() == 1)
  {
	direction = 1;
  }
  else if (radar_ard_is_target_approaching() == 1)
  {
	direction = 2;
  }
  return direction;
}

uint32_t IFXRadarPulsedDoppler::getFrameCount(void) 
{
	return radar_ard_get_frame_count( );
}

void IFXRadarPulsedDoppler::parameterDump( void ) 
{
	parameterDump(this->outDev);
}

void IFXRadarPulsedDoppler::parameterDump(Print *outDev) 
{
	
	if( outDev == NULL)
		return;
	
	outDev->print("Motion Sensitivity    : ");
    outDev->print(radar_ard_get_motion_sensitivity());
    outDev->println("");
	
	outDev->print("Doppler Sensitivity   : ");
    outDev->print(radar_ard_get_doppler_sensitivity());
    outDev->println("");
	
	outDev->print("minimum speed         : ");
	outDev->print(radar_ard_get_min_speed_kmph());
	outDev->println(" km/h");
    
	outDev->print("minimum speed         : ");
	outDev->print(radar_ard_get_max_speed_kmph());
	outDev->println(" km/h");
	
	outDev->print("minimum speed         : ");
	outDev->print(radar_ard_get_adc_sampling_freq_hz());
	outDev->println(" Hz");
    
	outDev->print("frame period          : ");
	outDev->print(radar_ard_get_frame_period_usec());
	outDev->println(" usec");
    
	outDev->print("number of skip samples: ");
	outDev->print(radar_ard_get_num_skip_samples());
	outDev->println("");
	
	outDev->print("number of used samples: ");
	outDev->print(radar_ard_get_num_samples());
	outDev->println("");
	
	outDev->print("pulse width           : ");
	outDev->print(radar_ard_get_pulse_width_usec());
	outDev->println(" usec");
    
	outDev->print("min frame period      : ");
	outDev->print(radar_ard_get_min_frame_period_usec());
	outDev->println(" usec");

}

void IFXRadarPulsedDoppler::setPrintDev(Print *outDev)
{
	this->outDev = outDev;
}