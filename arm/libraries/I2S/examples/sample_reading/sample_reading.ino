#include <I2S.h>

// Note that if 2 channels are used the values returned will be from both channels and thus look noisy

void setup(){
  Serial.begin(115200);
  Serial.println("begins");
  I2S.begin();
  
  // the following lines show how to sample at 16000 Hz
  // I2S.downScaleByTwo();
  // I2S.begin(32000);
}

void loop()
{
  int sample = I2S.peek();
  Serial.println(sample);
}

