#include "IFXRadarPulsedDoppler.h"

IFXRadarPulsedDoppler::IFXRadarPulsedDoppler()
{

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
	Serial.println("Low level HW initialization failed\n");
    while (1U);
  }
  else
  {
	Serial.println("HW init success");
  }
}

void IFXRadarPulsedDoppler::begin(void) // trigger algo_process() and init()
{
  radar_ard_init();
  if (radar_ard_is_initalized())
  {
	  /* the follow code, shows how to get and set all the possible parameters of the solution */
	  /* variables are declared as volatile, to easy debugging, in real project that is not required! */

	  volatile float motion_sensitivity = radar_ard_get_motion_sensitivity();
	  volatile float doppler_sensitivity = radar_ard_get_doppler_sensitivity();
	  volatile float min_speed_kmph = radar_ard_get_min_speed_kmph();
	  volatile float max_speed_kmph = radar_ard_get_max_speed_kmph();
	  volatile uint32_t adc_sampling_freq_Hz = radar_ard_get_adc_sampling_freq_hz();
	  volatile uint32_t frame_period_usec = radar_ard_get_frame_period_usec();
	  volatile uint32_t num_skip_samples = radar_ard_get_num_skip_samples();
	  volatile uint32_t num_samples = radar_ard_get_num_samples();
	  volatile uint32_t pulse_width_usec = radar_ard_get_pulse_width_usec();
	  volatile uint32_t min_frame_period_usec = radar_ard_get_min_frame_period_usec();
	  volatile float current_consumsumption_mA = radar_ard_get_current_consumption_mA();

	  volatile uint8_t error = 0;

	  error |= radar_ard_set_motion_sensitivity(motion_sensitivity + 1);
	  error |= radar_ard_set_doppler_sensitivity(doppler_sensitivity + 1);
	  error |= radar_ard_set_min_speed_kmph(min_speed_kmph + 1);
	  error |= radar_ard_set_max_speed_kmph(max_speed_kmph);
	  error |= radar_ard_set_adc_sampling_freq_Hz(adc_sampling_freq_Hz + 1);
	  error |= radar_ard_set_frame_period_usec(frame_period_usec + 1);
	  error |= radar_ard_set_num_skip_samples(num_skip_samples);
	  error |= radar_ard_set_num_samples(128);  // other values the 64, 128, 256 will cause an error
	  error |= radar_ard_set_pulse_width_usec(pulse_width_usec + 1);

	  /* add here other settings that are different from default/stored settings */
	  if (!error)
	  {
		  /* start the radar acquisition and processing */
		  Serial.println("Starting radar...");
		  radar_ard_start();
	  }
	  else
	  {
		  Serial.println("Init Error occured!\n");

	  }
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
