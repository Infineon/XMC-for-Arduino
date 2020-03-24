#ifndef STATIC_AUDIO_INPUT_H
#define STATIC_AUDIO_INPUT_H

#include <Arduino.h>
#include <SignalInput.h>

class staticAudioInput : public SignalInput
{
private:
  uint16_t _readOffset;
  uint16_t _bufferSize;

public:
  // pure virtual functions must be implemented
  void begin() {}

  void end() {}

  int peek() {}

  staticAudioInput(int16_t *inputBuffer, uint16_t bufferSize);

  void read(int16_t *readBuffer, uint16_t readSize);

  uint16_t available();
};

#endif