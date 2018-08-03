#include <RadarDataProcessor.h>

bool available = false;
int motion;
// this routine shouldn't take too long
void callback(RESULT_t *result)
{
  motion = result->motion;
  available = true;
}

void setup()
{
  Serial.begin(115200);
  RadarDataProcessor.begin(RADAR_BGT24LTR11, callback);
  RadarDataProcessor.enableMotionDetection();
  Serial.println("Init done!");
}

void loop()
{
  if (available)
  {
    if (motion == APPROACHING)
      Serial.println("approching");
    else if (motion == DEPARTING)
      Serial.println("departing");
    available = false;
  }
}