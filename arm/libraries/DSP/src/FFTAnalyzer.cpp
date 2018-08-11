/*
  Addapted from https://github.com/arduino-libraries/ArduinoSound/blob/master/src/FFTAnalyzer.h
*/
#if defined(XMC4700_Relax_Kit)

#include "FFTAnalyzer.h"

FFTAnalyzer::FFTAnalyzer(int length) : _length(length),
                                       _bitsPerSample(-1),
                                       _channels(-1),
                                       _available(0)
{
  _paddedLen = pow(2, ceil((log(_length) / log(2))));
  _sampleBuffer = new q15_t[_length];
  _fftBuffer = new float[_paddedLen];
  _normSampleBuffer = new float[_paddedLen];

  rfft = new arm_rfft_fast_instance_f32;
  arm_rfft_fast_init_f32(rfft, _paddedLen);
}

FFTAnalyzer::~FFTAnalyzer()
{
  delete[] _signalInput;
  delete[] _sampleBuffer;
  delete[] _fftBuffer;
  delete[] _normSampleBuffer;
  delete[] rfft;
}

int FFTAnalyzer::readMagnitude(float spectrum[], int size)
{
  if (!_available)
  {
    return 0;
  }
  if (size > (_paddedLen / 2))
  {
    size = _paddedLen / 2;
  }

  for (int i = 1; i < size; i++)
  {
    float real = _fftBuffer[i * 2 - 1], im = _fftBuffer[i * 2];
    spectrum[i] = sqrt(real * real + im * im);
  }
  // X[0] = _fftBuffer[0] + j*_fftBuffer[_length/2-1]
  float first_energy = _fftBuffer[0] * _fftBuffer[0] + _fftBuffer[_paddedLen / 2 - 1] * _fftBuffer[_paddedLen / 2 - 1];
  spectrum[0] = sqrt(first_energy);
  _available = 0;

  return size;
}

int FFTAnalyzer::configure(int bitsPerSample, int channels)
{
  if (bitsPerSample != 16 && bitsPerSample != 32)
  {
    return 0;
  }

  if (channels != 1 && channels != 2)
  {
    return 0;
  }

  _bitsPerSample = bitsPerSample;
  _channels = channels;

  // get a full buffer of samples to start
  if (!_signalInput->available())
  {
    return 0;
  }
  else
  {
    while (_signalInput->available() < _length)
      ;
  }
  return 1;
}

int FFTAnalyzer::input(SignalInput *signalInput, bool intrEnabled)
{
  _signalInput = signalInput;
  if (intrEnabled)
  {
    _signalInput->_outputBuffer = _sampleBuffer;
    _signalInput->_intrEnbaled = intrEnabled;
  }
  return _signalInput->setAnalyzer(this);
}

int FFTAnalyzer::getSpectrumLength()
{
  return _paddedLen / 2;
}

void FFTAnalyzer::update(float *window)
{
  uint16_t avail = _signalInput->available();
  if (!avail)
  {
    return;
  }
  // the i2s buffer might be larger than fft size
  if (avail > _length)
    avail = _length;

  uint16_t offset = _length - avail;
  if (offset)
  {
    memmove(_sampleBuffer, _sampleBuffer + avail, offset * sizeof(int16_t));
  }
  _signalInput->read(((q15_t *)_sampleBuffer) + offset, avail);

  // TODO: if double channel enabled, average every 2 samples in the buffer
  q15_t _mean;
  // center the signal values around zero
  arm_mean_q15(_sampleBuffer, _length, &_mean);

  // for 16-bit data downscaling by 2^15 gives the range [-1,1]
  if (window != nullptr)
  {
    for (int i = 0; i < _length; i++)
    {
      _normSampleBuffer[i] = (float)(_sampleBuffer[i]) * window[i] / (1 << 15);
    }
  }

  else
  {
    for (int i = 0; i < _length; i++)
    {
      _normSampleBuffer[i] = (float)(_sampleBuffer[i] - _mean) / (1 << 15);
    }
  }

  // must be done in loop since arm_rfft_fast_f32() modifies the input as well
  for (int i = _length; i < _paddedLen; i++)
    _normSampleBuffer[i] = 0;

  arm_rfft_fast_f32(rfft, _normSampleBuffer, _fftBuffer, 0);

  _available = 1;
}

void FFTAnalyzer::update2(float *window)
{
  // TODO: if double channel enabled, average every 2 samples in the buffer
  q15_t _mean;
  // center the signal values around zero
  arm_mean_q15(_sampleBuffer, _length, &_mean);

  // for 16-bit data downscaling by 2^15 gives the range [-1,1]
  if (window != nullptr)
  {
    for (int i = 0; i < _length; i++)
    {
      _normSampleBuffer[i] = (float)(_sampleBuffer[i]) * window[i] / (1 << 15);
    }
  }

  else
  {
    for (int i = 0; i < _length; i++)
    {
      _normSampleBuffer[i] = (float)(_sampleBuffer[i] - _mean) / (1 << 15);
    }
  }

  // must be done in loop since arm_rfft_fast_f32() modifies the input as well
  for (int i = _length; i < _paddedLen; i++)
    _normSampleBuffer[i] = 0;

  arm_rfft_fast_f32(rfft, _normSampleBuffer, _fftBuffer, 0);

  _available = 1;
}

#endif