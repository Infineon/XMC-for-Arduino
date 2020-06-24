/* This example shows you how to get your XMC board to detect finger snapping. In this simple demo you can snap your fingers to turn on/off the on-board LED  
   It's been tested with an XMC4700 relax kit and should also work with other 4000 boards. However it can't be run on XMC1100 boards.
 */

#if (UC_FAMILY == XMC1)
#error "CMSIS DSP not supported on this board"
#else
  
#include <FFTAnalyzer.h>
#include <I2S.h>

// This threshold might need to be adjusted. Use the spectrum plotting example to find suitable thresholds for detection
#define DETECTION_THRESHOLD 30
#define FREQUENCY_BIN_OFFSET 50
// size of the FFT to compute
const int fftSize = 256;

// create an FFT analyzer to be used with the I2S input
FFTAnalyzer fftAnalyzer(fftSize);

const int spectrumSize = fftAnalyzer.getSpectrumLength();

// array to store spectrum output
float *spectrum = new float[spectrumSize];

float freq_var;
float freq_mean;
bool detected_flag, last_flag = false;

void setup()
{
  pinMode(LED2, OUTPUT);  
  Serial.begin(115200);
  Serial.println("begins");

  I2S.begin();
  fftAnalyzer.input(&I2S);
}

void loop()
{
  fftAnalyzer.update();

  if (fftAnalyzer.readMagnitude(spectrum, spectrumSize))
  {
    // figer snapping has a highly variant frequency response
    arm_var_f32(spectrum + FREQUENCY_BIN_OFFSET, spectrumSize - FREQUENCY_BIN_OFFSET, &freq_var);
    arm_mean_f32(spectrum + FREQUENCY_BIN_OFFSET, spectrumSize - FREQUENCY_BIN_OFFSET, &freq_mean);
    if (100*freq_var/freq_mean > DETECTION_THRESHOLD)
    {
      detected_flag = true;
      if(!last_flag)
       digitalToggle(LED2);
    }
    else{
      detected_flag = false;
    }
    last_flag = detected_flag;
  }
}
#endif