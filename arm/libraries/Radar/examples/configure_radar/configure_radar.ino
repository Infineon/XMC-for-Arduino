// Demonstrates how to change radar configuration. Be aware that some config might not work.

#include <RadarDataProcessor.h>

#define DETECTING_MAG_THRESH 100
// for displaying
#define SPECTRUM_RANGE SENSE2GO_BUFFER_SIZE / 4

#define SPECTRUM_SIZE SENSE2GO_BUFFER_SIZE / 2

int16_t magnitudes[SPECTRUM_SIZE];
bool available = false;

BGT_RADAR_CONFIG_t user_config = {radar_buffersize : 128,
                                  cycle_time : 100,
                                  sampling_rate : 3000};

// this routine shouldn't take too long
void callback(RESULT_t * result)
{
  for (int i = 0; i < SPECTRUM_SIZE; i++)
  {
    magnitudes[i] = result->magnitudes[i];
  }
  available = true;
}

void setup()
{
  Serial.begin(115200);
  RadarDataProcessor.begin(RADAR_BGT24LTR11, callback);
  RadarDataProcessor.enableSpeedDetection();
  RadarDataProcessor.configureRadar(user_config);
  Serial.println("Init done!");
}

void loop()
{
  if (available)
  {
    for (int i = 0; i < SENSE2GO_BUFFER_SIZE/4; i++)
      Serial.println(magnitudes[i]);
    available = false;
  }
}