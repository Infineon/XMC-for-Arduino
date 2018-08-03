#include <staticAudioInput.h>

staticAudioInput::staticAudioInput(int16_t *inputBuffer, uint16_t bufferSize) 
{
    _fftUpdateMethod = ASYNC;
    _readOffset = 0;
    _inputSignalBuffer = inputBuffer;
    _bufferSize = bufferSize;
}

void staticAudioInput::read(int16_t *readBuffer, uint16_t readSize)
{
    if (readSize > available())
        readSize = available();
    memcpy(readBuffer, _inputSignalBuffer + _readOffset, readSize * sizeof(int16_t));
    _readOffset += readSize;
}

uint16_t staticAudioInput::available()
{
    return (_bufferSize - _readOffset);
}