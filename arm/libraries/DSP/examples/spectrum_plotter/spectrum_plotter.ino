/*Caution: this example has only been tested with XMC4700 relax kit. For the XMC1100 2go board and boot kit the code 
size is too big*/


#if (UC_FAMILY == XMC1)
#error "CMSIS DSP not supported on this board"
#else
  
#include <FFTAnalyzer.h>
#include <I2S.h>
// size of the FFT to compute. It is padded to the nearest power of 2, i.e. 512. The uC might not be able to deal with 
// arrays that are too large
const int fftSize = 320;

// create an FFT analyzer to be used with the I2S input
FFTAnalyzer fftAnalyzer(fftSize);

const int spectrumSize = fftAnalyzer.getSpectrumLength();

// array to store spectrum output
float *spectrum = new float[spectrumSize];

void setup()
{
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
    for (int i = 0; i < spectrumSize; i++)
    {
      // Serial.print((i * 22050) / spectrumSize); // frequency bins
      // Serial.print("\t");                  
      Serial.println(spectrum[i]); 
    }
  }
}
#endif