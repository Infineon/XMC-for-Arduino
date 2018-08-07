
#if (UC_FAMILY == XMC1)
#error "CMSIS DSP not supported on this board"
#else
  
#include "staticAudioInput.h"
#include "audio_left/left0.h"

#define AUDIO_LENGTH 16000
int16_t audio_buffer[AUDIO_LENGTH] = WAV_LEFT;

#define NUM_FEATURES 10

// size of the FFT to compute
const int fftSize = 512;
int8_t features[NUM_FEATURES];
MFCC mfcc(fftSize, NUM_FEATURES);

void setup()
{
  Serial.begin(9600);
  staticAudioInput audioInput(audio_buffer, AUDIO_LENGTH);
  
  mfcc.input(&audioInput);
  
  mfcc.getMfccFeatues(features);
  for (int i = 0; i < NUM_FEATURES; i++)
  {
    Serial.print(features[i]);
    Serial.print("\t");
  }
  Serial.println();  
}

void loop() {}
#endif