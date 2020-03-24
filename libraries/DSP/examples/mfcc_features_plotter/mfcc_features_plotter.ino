/*Caution: this example has only been tested with XMC4700 relax kit.*/

#if (UC_FAMILY == XMC1)
#error "CMSIS DSP not supported on this board"
#else
  
#include <MFCC.h>
#include <I2S.h>

#define NUM_FEATURES 10

// size of the FFT to compute
const int fftSize = 512;

int8_t features[NUM_FEATURES];

MFCC mfcc(fftSize, NUM_FEATURES);
void callback()
{
  mfcc.getMfccFeatues(features);
  for (int i = 0; i < NUM_FEATURES; i++)
  {
    Serial.print(features[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  Serial.println("begins");
  I2S.begin(32000); // adafruit mic only supports 32khz to 64khz
  mfcc.input(&I2S);
  I2S.configureInterrupt(callback);
}

void loop()
{
  // do something else
}

#endif