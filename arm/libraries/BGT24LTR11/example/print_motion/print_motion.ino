#include <BGT24LTR11.h>

BGT24LTR11 RadarBGT24LTR11 = BGT24LTR11();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  RadarBGT24LTR11.begin();

  Serial.println("Init done!");

  RadarBGT24LTR11.start(BGT24LTR11_CONTIGUOUS_ACQ);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(RadarBGT24LTR11.dataAvailable())
  {
    uint8_t motion = RadarBGT24LTR11.getMotion();
    if(motion == BGT24LTR11_MOTION_DETECT_APPROACHING)
    {
      Serial.println("APPROACH");
    }
    else if(motion == BGT24LTR11_MOTION_DETECT_DEPARTING)
    {
      Serial.println("DEPART");
    }
  }  
}