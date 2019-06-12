/** @file I2S.cpp
 *  @brief The I2S library for XMC to process audio data input
 *	@author Yuxi Sun
 */

#include "I2S.h"

XMCI2SClass::XMCI2SClass(bool isMono, uint8_t bitsPerSample) : _isMono(isMono), _bitsPerSample(bitsPerSample)
{
    _fftUpdateMethod = SYNC;
    channel_config = i2s_config.i2s_ch_config;
    // TODO: options for 16- or 32-bit buffer
    // if (bitsPerSample > 16)
    //     _inputSignalBuffer32 = new int32_t[BUFFER_SIZE];
    // else
    //     _inputSignalBuffer = new int16_t[BUFFER_SIZE];

    _inputSignalBuffer = _i2sBuffer;   
}

void XMCI2SClass::downScaleByTwo()
{
    _downScalingEnabled = true;
}

void XMCI2SClass::begin(uint32_t samplingRate, uint8_t frameLength, uint8_t dataDelay, uint8_t dataBits)
{
    channel_config.baudrate = samplingRate * frameLength * 2; // due to word select; even if only one mic is connected, since it only transmits half of the time
    channel_config.data_bits = dataBits;
    channel_config.frame_length = frameLength;
    channel_config.data_delayed_sclk_periods = dataDelay;
    begin();
}

void XMCI2SClass::begin()
{
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)MASTER_MRST, &(i2s_config.input_config));
    XMC_I2S_CH_Init(MASTER_CHANNEL, &channel_config);
    // system word length = frame length, which is the number of bits sent within a cycle of WA signal
    XMC_I2S_CH_SetSystemWordLength(MASTER_CHANNEL, channel_config.frame_length);
    XMC_I2S_CH_SetInputSource(MASTER_CHANNEL, XMC_I2S_CH_INPUT_DIN0, INPUT_SOURCE);

    XMC_GPIO_Init((XMC_GPIO_PORT_t *)MASTER_SCLK, &(i2s_config.sclk_config));
    XMC_GPIO_Init((XMC_GPIO_PORT_t *)MASTER_WACLK, &(i2s_config.wa_config));

    // configure a FIFO buffer of 2 words; FIFO word size = frame_length/data_bits
    XMC_USIC_CH_RXFIFO_Configure(MASTER_CHANNEL, 0, XMC_USIC_CH_FIFO_SIZE_2WORDS, 1);
    // sets protocol interrupt
    XMC_I2S_CH_SetInterruptNodePointer(MASTER_CHANNEL, i2s_config.protocol_irq_service_request);
    // assign real-time sample reading the highest priority
    NVIC_SetPriority((IRQn_Type)i2s_config.protocol_irq_num, 0);
    NVIC_EnableIRQ((IRQn_Type)i2s_config.protocol_irq_num);

    if (_isMono)
        XMC_I2S_CH_EnableEvent(MASTER_CHANNEL, XMC_I2S_CH_EVENT_WA_RISING_EDGE);
    else
        XMC_I2S_CH_EnableEvent(MASTER_CHANNEL, XMC_I2S_CH_EVENT_WA_FALLING_EDGE | XMC_I2S_CH_EVENT_WA_RISING_EDGE);

    XMC_I2S_CH_Start(MASTER_CHANNEL);
    // Clear master Receive Data
    XMC_I2S_CH_GetReceivedData(MASTER_CHANNEL);
    XMC_I2S_CH_GetReceivedData(MASTER_CHANNEL);
}

#if (UC_FAMILY == XMC4)
bool XMCI2SClass::_dmaInProgress = false;
void XMCI2SClass::configureInterrupt(interrupt_cb_t callback)
{
    _dmaInProgress = 0;
    customCallback = callback;
    // TODO: check _outputBuffer
    dma_module.beginDMA(DMA0);
    dma_module.configDMA_M2M(DMA0, 0, (uint32_t)&_inputSignalBuffer[0], (uint32_t)&_outputBuffer[0], BUFFER_SIZE, TRANSFER_WIDTH_16, BURST_LENGTH_1, true);
    dma_module.attachDMAInterrupt(DMA0, 0, XMCI2SClass::dmaCallback, BLOCK_TRANSFER_COMPLETE);
}

void XMCI2SClass::dmaCallback()
{
    I2S._dmaInProgress = false;
    I2S.customCallback();
}

#endif

void XMCI2SClass::end()
{
    XMC_I2S_CH_Stop(MASTER_CHANNEL);
}

// put read in a loop for data processing; for simple plotting use peek
void XMCI2SClass::read(int16_t *readBuffer, uint16_t readSize)
{
    if (readSize > available())
        readSize = available();
    memcpy(readBuffer, _inputSignalBuffer, readSize * sizeof(int16_t));
    _i2sOffset = 0;
}

// # samples available for read
uint16_t XMCI2SClass::available()
{
    if (_i2sOffset == BUFFER_SIZE - 1)
    {
        return BUFFER_SIZE;
    }
    return _i2sOffset;
}

int XMCI2SClass::peek()
{
    return retval;
}

void XMCI2SClass::enableMasterClock()
{
    XMC_I2S_CH_EnableMasterClock(MASTER_CHANNEL);
}

void XMCI2SClass::onSampleReceived()
{
    // if 2 channels are used the buffer will be filled with samples from both channel one after another

    // for the adafruit mic, 1 data frame = 24 bits, therefore 2 reads of the 16-bit buffer
    // TODO: check if it fits our mic as well
    uint16_t retval1 = XMC_I2S_CH_GetReceivedData(MASTER_CHANNEL);
    uint16_t retval2 = XMC_I2S_CH_GetReceivedData(MASTER_CHANNEL);

    if (_downScalingEnabled)
    {
        _downScalingFlag = !_downScalingFlag;
        if (_downScalingFlag)
            return;
    }

    // reading 24-bit data with 18-bit accuracy -- for adafruit mic
    // int32_t retval = (int)(retval1 << 16);
    // retval |= (retval2 & 0xFF00);
    // retval >>= 14;

    retval = (retval2 >> 14);
    retval |= (retval1 << 2);

    _inputSignalBuffer[_i2sOffset] = retval;

    if (_i2sOffset < BUFFER_SIZE - 1)
    {
        _i2sOffset += 1;
    }

#if (UC_FAMILY == XMC4)
    else
    {
        if (!_dmaInProgress)
        {
            dma_module.configDMA_M2M(DMA0, 0, (uint32_t)&_inputSignalBuffer[0], (uint32_t)&_outputBuffer[0], BUFFER_SIZE, TRANSFER_WIDTH_16, BURST_LENGTH_1, true);
            dma_module.beginDMATransaction(DMA0, 0);
            _i2sOffset = 0;
            _dmaInProgress = true;
        }
    }
#endif
}


extern "C"
{
#if defined(XMC4700_Relax_Kit)
    void USIC2_2_IRQHandler()
    {
        I2S.onSampleReceived();
    }
#elif defined(XMC1100_XMC2GO) || defined(XMC1100_Boot_Kit)
    void USIC0_2_IRQHandler()
    {
        I2S.onSampleReceived();
    }
#endif
}

XMCI2SClass I2S = XMCI2SClass();