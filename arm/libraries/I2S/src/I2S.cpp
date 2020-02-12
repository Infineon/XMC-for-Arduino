/**
 * I2S.cpp - Library for Arduino to interface with I2S devices.
 * 
 * Have a look at the application note/datasheet for more information.
 * Currently, only reading via I2S is supported - no output can be generated.
 * 
 * Copyright (c) 2018 Infineon Technologies AG
 * 
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/** @file I2S.cpp
 *  @brief The I2S library for XMC to process audio data input
 *	@author Yuxi Sun
 *  @author Manuel Hollfelder
 */
#include <Arduino.h>
#include "I2S.h"

I2SClass::I2SClass()
{
    _bufferSize = BUFFER_SIZE;
    _i2sBuffer = new int32_t[_bufferSize];
    for( uint16_t i = 0; i < _bufferSize; i++){
        _i2sBuffer[0] = 0;
    }
    _posHead = 0;
    _posTail = 0;
    _lastValue = 0;    
    _microphoneSelection = 0;
    _onReceiveEvent = NULL;
}

XMC_I2S_CH_STATUS_t I2SClass::begin(I2SMode_t mode, uint32_t samplingRate, uint8_t bitsPerSample){

    // Find frame length closest to bitsPerSample with dataBits equal to 16
    // clocksPerWord fixed to 32
    uint8_t frameLength = 1;
    for(frameLength = 0; frameLength <= 32; frameLength+=16){
        if(frameLength >= bitsPerSample) break;
    }
    // Fixed clocksPerWord
    uint8_t clocksPerWord = 32;

    // If there are less as 16 Bits per sample, reduce the bitsPerWord size as well
    uint8_t bitsPerWord = 16;
    if(bitsPerSample < 16) bitsPerWord = bitsPerSample;

    // Depending on the mode, the right delay needs to be selected
    // One delay clock is standard mode for I2S
    uint8_t delayClocks = 1;
    switch(mode){
        case I2S_PHILIPS_MODE:
            // Nothing to do as default setting is standard mode
            break;
        case I2S_RIGHT_JUSTIFIED_MODE:
            // MSB first with right aligned in each frame
            delayClocks = 32 - bitsPerSample;
            break;
        case I2S_LEFT_JUSTIFIED_MODE:
            // MSB first with left aligned in each frame
            delayClocks = 0;
            break;
        default:
            return XMC_I2S_CH_STATUS_ERROR;
    }
    // The baudrate depends on the sampling rate times two times the clocksPerChannel
    return begin(samplingRate * 2 * clocksPerWord, clocksPerWord, frameLength, bitsPerWord, bitsPerSample, delayClocks);
}

XMC_I2S_CH_STATUS_t I2SClass::begin(uint32_t samplingRate, uint8_t clocksPerWord, uint8_t bitsPerSample){

    // bitsPerSample must be smaller as 32 bits
    if ( bitsPerSample > 32 ){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    // If there are less as 16 Bits per sample, reduce the bitsPerWord size as well
    uint8_t bitsPerWord = 16;
    if(bitsPerSample < 16) bitsPerWord = bitsPerSample;

    uint8_t frameLength = 1;
    for(frameLength = 0; frameLength <= 32; frameLength+=16){
        if(frameLength >= bitsPerSample) break;
    }
    // The baudrate depends on the sampling rate times two times the clocksPerWord
    return begin(samplingRate * 2 * clocksPerWord, clocksPerWord, frameLength, bitsPerWord, bitsPerSample, 1);
}

XMC_I2S_CH_STATUS_t I2SClass::begin(uint32_t baudrate, uint8_t frameLength, uint8_t dataBits, uint8_t bitsPerSample, uint8_t dataDelay)
{

    return begin(baudrate, frameLength, frameLength, dataBits, bitsPerSample, dataDelay);
}

XMC_I2S_CH_STATUS_t I2SClass::begin(uint32_t baudrate, uint8_t systemWordLength, uint8_t frameLength, uint8_t dataBits, uint8_t bitsPerSample, uint8_t dataDelay)
{
    // Oversampling only up to 128 is supported N = (BRG.PCTQ + 1) × (BRG.DCTQ + 1)
    if( (systemWordLength > 128) || (systemWordLength < 1) ){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    // Oversampling only up to 128 is supported N = (BRG.PCTQ + 1) × (BRG.DCTQ + 1)
    if(systemWordLength < frameLength){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    // frameLength must not be above 32 Bits
    if(frameLength > 32) return XMC_I2S_CH_STATUS_ERROR;

    // frameLength must be multiple of dataBits; check by division with rounding and substraction of multiples
    if ( (frameLength - uint8_t(frameLength / dataBits)*dataBits) != 0 ){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    // dataBits must be smaller as 16 Bits
    if ( dataBits > 16 ){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    // Bits per sample cannot be larger as 32
    if(bitsPerSample > 32){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    // Bits per sample cannot be larger as frame length
    if(frameLength < bitsPerSample){
        _initialized = false; 
        return XMC_I2S_CH_STATUS_ERROR;
    }
    _channel_config.baudrate = baudrate;
    _channel_config.data_bits = dataBits;
    _channel_config.frame_length = frameLength;
    _channel_config.data_delayed_sclk_periods = dataDelay;
    _systemWordLength = systemWordLength;
    _bitsPerSample = bitsPerSample;
    return _init();
}

XMC_I2S_CH_STATUS_t I2SClass::_init(){
    // Set up the channel and start it
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)MASTER_MRST, &(i2s_config.input_config));
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)MASTER_SCLK, &(i2s_config.sclk_config));
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)MASTER_WACLK, &(i2s_config.wa_config));

    XMC_I2S_CH_Init(MASTER_CHANNEL, &_channel_config);
    XMC_I2S_CH_SetInputSource(MASTER_CHANNEL, XMC_I2S_CH_INPUT_DIN0, INPUT_SOURCE);

    XMC_I2S_CH_SetBaudrate(MASTER_CHANNEL, _channel_config.baudrate);
    XMC_I2S_CH_SetWordLength(MASTER_CHANNEL, _channel_config.data_bits);
    XMC_I2S_CH_SetFrameLength(MASTER_CHANNEL, _channel_config.frame_length);
    XMC_I2S_CH_SetSystemWordLength(MASTER_CHANNEL, _systemWordLength);

    XMC_I2S_CH_SetBitOrderMsbFirst(MASTER_CHANNEL);

    // Flush the FIFO buffer
    XMC_USIC_CH_RXFIFO_Flush(MASTER_CHANNEL);    
    // Configure the FIFO and activate Receiver Control Information Mode with RCIM = 0b11
    // RCI[4] = PERR, RCI[3] = PAR, RCI[2:1] = 00B, RCI[0] = SOF
    // Once filling level is reached, an STANDARD_RECEIVE interrupt will be generated
    // In Filling Level Mode, only the standard receive event is activated 
    if( _channel_config.frame_length > 16 ){
        XMC_USIC_CH_RXFIFO_Configure(MASTER_CHANNEL, 0, XMC_USIC_CH_FIFO_SIZE_2WORDS, 1);
    } else {
        XMC_USIC_CH_RXFIFO_Configure(MASTER_CHANNEL, 0, XMC_USIC_CH_FIFO_SIZE_2WORDS, 0);
    }
    MASTER_CHANNEL->RBCTR |= USIC_CH_RBCTR_RCIM_Msk;
    // Sets FIFO interrupt
    XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, i2s_config.protocol_irq_service_request);
    XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE, i2s_config.protocol_irq_service_request);
    // Set the channel interrupt
    XMC_I2S_CH_SetInterruptNodePointer(MASTER_CHANNEL, i2s_config.protocol_irq_service_request);

    XMC_USIC_CH_RXFIFO_EnableEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);
    XMC_I2S_CH_EnableEvent(MASTER_CHANNEL, XMC_I2S_CH_EVENT_STANDARD_RECEIVE | XMC_I2S_CH_EVENT_ALTERNATIVE_RECEIVE);

    // Assign real-time sample reading the highest priority
    // NVIC_ClearPendingIRQ((IRQn_Type)i2s_config.protocol_irq_num);
    NVIC_SetPriority((IRQn_Type)i2s_config.protocol_irq_num, 0);
    NVIC_EnableIRQ((IRQn_Type)i2s_config.protocol_irq_num);

    XMC_I2S_CH_Start(MASTER_CHANNEL);
    // Clear master receive data from FIFO
    // XMC_USIC_CH_RXFIFO_Flush(MASTER_CHANNEL);
    while(XMC_USIC_CH_RXFIFO_IsEmpty(MASTER_CHANNEL) != true){
        XMC_I2S_CH_GetReceivedData(MASTER_CHANNEL);
    }

    // Clear all events and status flags
    XMC_USIC_CH_RXFIFO_ClearEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
    XMC_I2S_CH_ClearStatusFlag(MASTER_CHANNEL, XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION  | XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION);
    // If we have less as 16 bits, we shift directly to the top of the buffer
    // If we have more as 16 bits, we can shift the first word directly to position 16
    if(_bitsPerSample < 16){
        _shiftFirst = 32 - _bitsPerSample;
        _firstShiftMask = ~(0x00000001 <<  (_shiftFirst - 1));
        _secondShiftMask = 0x00000000;
        _shiftSecond = _shiftFirst;
    } else {
        _shiftFirst = 16;
        _firstShiftMask = 0xFFFF0000;
        _shiftSecond = 32 - _bitsPerSample; 
        _secondShiftMask = 0x0000FFFF;
    }
    _initialized = true;
    return XMC_I2S_CH_STATUS_OK;
}

XMC_I2S_CH_STATUS_t I2SClass::end()
{
    XMC_I2S_CH_STATUS_t returnValue = XMC_I2S_CH_Stop(MASTER_CHANNEL);
    XMC_USIC_CH_RXFIFO_DisableEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);
    XMC_I2S_CH_DisableEvent(MASTER_CHANNEL, XMC_I2S_CH_EVENT_STANDARD_RECEIVE | XMC_I2S_CH_EVENT_ALTERNATIVE_RECEIVE);
    NVIC_DisableIRQ((IRQn_Type)i2s_config.protocol_irq_num);

    XMC_USIC_CH_RXFIFO_ClearEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
    XMC_I2S_CH_ClearStatusFlag(MASTER_CHANNEL, XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION  | XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION);

    disableMicrophones();
    if( returnValue == XMC_I2S_CH_STATUS_OK){
        _initialized = false;
    }
    return returnValue;
}

uint8_t I2SClass::enableMicrophoneLow(){
    // In the Filling Level Mode, only the standard receive is activated
    // Microphone selection is done in the ISR
    if(_microphoneSelection == MICROPHONE_HIGH){
        _microphoneSelection = MICROPHONE_LOW_HIGH;
    } else {
        _microphoneSelection = MICROPHONE_LOW;       
    }
    return _microphoneSelection;
}

uint8_t I2SClass::enableMicrophoneHigh(){
    // In the Filling Level Mode, only the standard receive is activated
    // Microphone selection is done in the ISR
    if(_microphoneSelection == MICROPHONE_LOW){
        _microphoneSelection = MICROPHONE_LOW_HIGH;
    } else {
        _microphoneSelection = MICROPHONE_HIGH;       
    }
    return _microphoneSelection;
}

uint8_t I2SClass::disableMicrophones(){
    // In the Filling Level Mode, only the standard receive is activated
    // Microphone selection is done in the ISR
    _microphoneSelection = NO_MICROPHONE;
    _sampleInformation = NO_MICROPHONE;
    return _microphoneSelection;
}

uint8_t I2SClass::getMicrophones(){
    return _microphoneSelection;
}

uint16_t I2SClass::read(int32_t *readBuffer, uint16_t readSize)
{
    if(available() == 0) return 0;

    if (readSize > available()){
        readSize = available();
    }

    for(uint16_t i = 0; i < readSize; i++){
        readBuffer[i] = read();
    }
    return readSize;
}

void I2SClass::enableMasterClock()
{
    XMC_I2S_CH_EnableMasterClock(MASTER_CHANNEL);
}

void I2SClass::_onSampleReceived()
{
    // Return immediately if the FIFO is empty or no microphone is selected and clear the flags
    if( (XMC_USIC_CH_RXFIFO_IsEmpty(MASTER_CHANNEL) == true) || (_microphoneSelection == 0) ){
        XMC_I2S_CH_ClearStatusFlag(MASTER_CHANNEL, XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
        XMC_USIC_CH_RXFIFO_ClearEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
        _sampleInformation = NO_MICROPHONE;
        return;
    }

    bool statusReturn = false;
    uint16_t retval1 = 0;
    uint16_t retval2 = 0;
    uint32_t buffer1 = 0;
    uint32_t buffer2 = 0;
    buffer1 = (MASTER_CHANNEL->OUTR);
    buffer2 = (MASTER_CHANNEL->OUTR);
    // Check whether first word is SOF
    if( ((buffer1>>16) & 0x00000001) == 0){
        statusReturn = true;
    } else {
        // Save the FIFO values locally
        retval1 = (uint16_t)(buffer1 & 0x0000FFFF);
        retval2 = (uint16_t)(buffer2 & 0x0000FFFF);
        // Shift the two buffers to simplify calculations
        buffer1 = (buffer1>>16) & 0x0000FFFF;
        buffer2 = (buffer2>>16) & 0x0000FFFF;
    }
    // Proceed with the microphone calculations
    // Check for the microphone data for WA=LOW
    if(((_microphoneSelection & ( MICROPHONE_LOW | MICROPHONE_LOW_HIGH )) != 0) && ( (buffer1 & (uint32_t)0x00000010) == 0) && !statusReturn){
        // Process the FIFO values for WA=HIGH
        _sampleInformation = MICROPHONE_LOW;
        _lastValue = 0;
        _lastValue = ((uint32_t)retval1 << _shiftFirst ) & _firstShiftMask;
        _lastValue |= ((uint32_t)retval2 << _shiftSecond ) & _secondShiftMask;
        _lastValue = _lastValue >> _shiftSecond;
        if(_storeValue(_lastValue) == 0) _overflow = true;
        // Process the defined function if it exists
        if (_onReceiveEvent){
            _onReceiveEvent();
        } 
        XMC_I2S_CH_ClearStatusFlag(MASTER_CHANNEL, XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
        XMC_USIC_CH_RXFIFO_ClearEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
        return;
    }

    // Check for the microphone data for WA=HIGH
    if(((_microphoneSelection & ( MICROPHONE_HIGH | MICROPHONE_LOW_HIGH )) != 0) && ((buffer1 & (uint32_t)0x00000010) != 0) && !statusReturn){
        // Process the FIFO values for WA=HIGH
         _sampleInformation = MICROPHONE_HIGH;
        _lastValue = 0;
        _lastValue = ((uint32_t)retval1 << _shiftFirst ) & _firstShiftMask;
        _lastValue |= ((uint32_t)retval2 << _shiftSecond ) & _secondShiftMask;
        _lastValue = _lastValue >> _shiftSecond;
        if(_storeValue(_lastValue) == 0) _overflow = true;  
        // Process the defined function if it exists
        if (_onReceiveEvent){
            _onReceiveEvent();
        }
        XMC_I2S_CH_ClearStatusFlag(MASTER_CHANNEL, XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
        XMC_USIC_CH_RXFIFO_ClearEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
        return;
    }
    // Process the defined function if it exists
    if (_onReceiveEvent){
        _onReceiveEvent();
    }
    _sampleInformation = NO_MICROPHONE; 
    XMC_USIC_CH_RXFIFO_ClearEvent(MASTER_CHANNEL, XMC_USIC_CH_RXFIFO_EVENT_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
    XMC_I2S_CH_ClearStatusFlag(MASTER_CHANNEL, XMC_I2S_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_I2S_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
    XMC_USIC_CH_RXFIFO_Flush(MASTER_CHANNEL);
    return;
}

extern "C"
{
#if defined(XMC4700_Relax_Kit)
    void USIC2_2_IRQHandler()
    {
        I2S._onSampleReceived();
    }
#elif defined(XMC1100_XMC2GO) || defined(XMC1100_Boot_Kit)
    void USIC0_2_IRQHandler()
    {
        I2S._onSampleReceived();
    }
#endif
}

uint8_t I2SClass::_storeValue(int32_t value)
{
    uint16_t i = _posHead + 1;
    if(i >= _bufferSize){
      i = 0;
    }
    if (i != _posTail)
    {
        _i2sBuffer[_posHead] = value;
        _posHead = i;
        return 1;
    } else {
        return 0;
    }
}

uint16_t I2SClass::available(void)
{
    uint16_t _posHeadSnap = _posHead;
    if( _posHeadSnap >= _posTail ){
        return _posHeadSnap - _posTail;
    } else {
    return _bufferSize - _posTail + _posHeadSnap;
    }
}

int32_t I2SClass::peek(void){
    return _lastValue;
}

int32_t I2SClass::read(void)
{
    if(_posHead == _posTail){
        return 0;
    }
    int32_t retValue = _i2sBuffer[_posTail];
    _posTail++;
    if(_posTail >= _bufferSize)
    _posTail = 0;
    return retValue;
}

uint8_t I2SClass::flush(void)
{
    uint16_t _counter = 0;
    while( _posHead != _posTail ){
        read();
        _counter++;
        if( _counter == _bufferSize) return 1;
    }
    return 0;
}

bool I2SClass::getOverflow(void)
{
    return _overflow;
}

void I2SClass::onReceive(void(*function)(void))
{
  _onReceiveEvent = function;
}

I2SMicrophones_t I2SClass::getSampleInformation()
  {
      return _sampleInformation;
  }

I2SClass I2S = I2SClass();