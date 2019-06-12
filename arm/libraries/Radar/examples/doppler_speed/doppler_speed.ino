#include <RadarDataProcessor.h>
// TODO detecting threshold & spectrum range should be adjustable
#define DETECTING_MAG_THRESH 100
// for displaying
#define SPECTRUM_RANGE SENSE2GO_BUFFER_SIZE / 4

#define SPECTRUM_SIZE SENSE2GO_BUFFER_SIZE / 2

int16_t magnitudes[SPECTRUM_SIZE];
bool available = false;
int max_mag;
float speed;

// this routine shouldn't take too long
void callback(RESULT_t *result)
{
  for (int i = 0; i < SPECTRUM_SIZE; i++)
  {
    magnitudes[i] = result->magnitudes[i];
  }
  max_mag = result->max_magnitude;
  speed = result->speed;
  available = true;
}

void setup()
{
  Serial.begin(115200);
  RadarDataProcessor.begin(RADAR_BGT24LTR11, callback);
  RadarDataProcessor.enableSpeedDetection();
  Serial.println("Init done!");
}

void loop()
{
  if (available)
  {
    if (max_mag > DETECTING_MAG_THRESH)
      Serial.println(speed);
    else
      Serial.println(0);

    // for (int i = 0; i < SENSE2GO_BUFFER_SIZE/4; i++)
    //   Serial.println(magnitudes[i]);
    available = false;
  }
}