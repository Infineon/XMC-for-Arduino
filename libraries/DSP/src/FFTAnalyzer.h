
/*
  Addapted from https://github.com/arduino-libraries/ArduinoSound/blob/master/src/FFTAnalyzer.h

  FFT is computed with float numbers, since arm_rfft_fast_f32() is a more efficient implementation than arm_rfft_q31(), the later computes the whole (mirrored) spectrum
  whereas FFT can be uniquely represented only by half of the spectrum due to symmetry.
  With identical algorithm the implementation with floats even uses less space. 
*/

// TODO: switch between 16/32 bits
#ifndef _FFT_ANALYZER_H_INCLUDED
#define _FFT_ANALYZER_H_INCLUDED

#if defined(XMC4700_Relax_Kit)
#include <SignalInput.h>

// arm_math.h has name conflict with arduino analogue pins
#undef A0
#undef A1
#undef A2
#include <arm_math.h>

class FFTAnalyzer
{
  friend class SignalInput;

public:
  FFTAnalyzer(int length);
  virtual ~FFTAnalyzer();
  int available();
  int readMagnitude(float spectrum[], int size);
  int configure(int bitsPerSample = 16, int channels = 1);

  /**
   * @brief Reads all available samples manually from the signal input, and might be out of sync with the signal input
   * 
   * @param window window function to be applied to the input signal; must be of the sample length as sample buffer
   */
  void update(float *window = nullptr);

  /**
   * @brief Updates fft values syncronously; should be called in a callback function that is called when when buffer of input samples is full
   * 
   * @param window window function
   */
  void update2(float *window = nullptr);

  /**
   * @brief Sets the input to  FFT analyzer
   * 
   * @param signalInput 
   * @param intrEnabled if the interrupt is enabled. If it is set to true update2 should be used instead of update.
   * @return int 
   */
  int input(SignalInput *signalInput, bool intrEnabled = false);
  int getSpectrumLength();

private:
  SignalInput *_signalInput;
  uint16_t _length;
  int _bitsPerSample;
  int _channels;
  int _paddedLen;
  arm_rfft_fast_instance_f32 *rfft;

  int _available;
  q15_t *_sampleBuffer;
  float *_fftBuffer;
  float *_normSampleBuffer;
};

#endif
#endif
