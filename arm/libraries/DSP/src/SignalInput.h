#ifndef SIGNAL_INPUT_H
#define SIGNAL_INPUT_H

#include <Arduino.h>
// forward declaration
#if defined(XMC4700_Relax_Kit)
class FFTAnalyzer;
class MFCC;
#endif

typedef enum {
	ASYNC = 0,
	SYNC = 1
} FFT_UPDATE_METHOD_t;

class SignalInput
{
private:
#if defined(XMC4700_Relax_Kit)
  // so that fft analyzer can access _outputBuffer
  friend class FFTAnalyzer;
  FFTAnalyzer *_analyzer;

  friend class MFCC;
#endif

protected:
  int _alpha = 0;
  int16_t *_inputSignalBuffer;

  // for 32-bit data
  int32_t *_inputSignalBuffer32;

  int16_t *_outputBuffer;
  bool _intrEnbaled;
  bool _fftUpdateMethod;

public:
  // tentative
  //x[n]-(1-1/2^4)x[n-1]
  void enablePreEmphasizing(int factor);

  virtual void begin() = 0;

  virtual void end() = 0;

  virtual int peek() = 0;

  // TODO: read 32 bits samples
  virtual void read(int16_t *readBuffer, uint16_t readSize) = 0;

  virtual uint16_t available() = 0;

#if defined(XMC4700_Relax_Kit)
  int setAnalyzer(FFTAnalyzer *analyzer);
#endif
};

#endif