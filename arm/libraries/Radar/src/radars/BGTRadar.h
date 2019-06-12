
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