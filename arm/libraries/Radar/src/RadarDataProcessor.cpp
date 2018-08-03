#include "RadarDataProcessor.h"

RadarDataProcessorClass::RadarDataProcessorClass()
{
    _fft = FFTAnalyzer();
    _maxMagFreq = {0, 0};
    _algo = {false, false};
    _result.speed = 0.0;
    _result.max_magnitude = 0;
    _result.motion = 0;
}

RadarDataProcessorClass::~RadarDataProcessorClass()
{
    end();
}

bool RadarDataProcessorClass::available()
{
    return _available;
}

void RadarDataProcessorClass::initHanningWindow(uint8_t windowLength)
{
    // w(n) = 0.5 (1-cos(2*pi*n/(N-1))), 0<=n<=(N-1)
    float frac = TWO_PI / (windowLength - 1);
    for (int i = 0; i < windowLength; i++)
        _hanningWindow[i] = round(32767 * (1 - cos(i * frac))) >> 1;
}

void RadarDataProcessorClass::begin()
{
    // check initialization
    if (!_radar)
        return;

    _radar->begin();

    // initialize buffer -- not necessary with fixed buffer size
    _radarBufferSize = (_radar->_config).radar_buffersize;
    _fftOrder = log2(_radarBufferSize);
    if (_radarBufferSize <= 0)
        return;

    initHanningWindow(_radarBufferSize);
    _freqWidth = (_radar->_config).sampling_rate / _radarBufferSize;

    // configure task to be executed periodically
    _timer = addTask(RadarDataProcessorClass::samplingTask);

    if (_timer < 0 || _timer > NUM_TASKS_VARIANT)
    {
        // error: too many tasks
        return;
    }

    setParam(_timer, _timer);
    setInterval(_timer, (_radar->_config).cycle_time);
    startTask(_timer);

    _interruptTimer = addTask(RadarDataProcessorClass::algoTask);

    // use as an interrupt
    setParam(_interruptTimer, _interruptTimer);
    setInterval(_interruptTimer, 1);
}

void RadarDataProcessorClass::begin(RADAR_t radarType, void (*cb)(RESULT_t *result))
{
    // set callback
    if (cb)
        _cb = cb;
    _radarType = radarType;

    switch (_radarType)
    {
    case RADAR_BGT24LTR11:
        _bgt24ltr11 = BGT24LTR11();
        _radar = &_bgt24ltr11;
        break;
    default:
        // error: wrong data type
        return;
    }
    begin();
}

void RadarDataProcessorClass::end()
{
    deleteTask(RadarDataProcessorClass::samplingTask);
    deleteTask(RadarDataProcessorClass::algoTask);
}

void RadarDataProcessorClass::startAcq(void)
{
    // check if these functions are necessary for future radars
    _radar->startAcq();
}

void RadarDataProcessorClass::endAcq(void)
{
    _radar->endAcq();

    // finished sampling, run the detection algorithm
    // TODO: make sure this startTask always pairs up with deleteTask in runAlgorithm
    startTask(_interruptTimer);
}

void RadarDataProcessorClass::sampleInQ(void)
{
    // only need to sum up I data
    _radar->sampleInQ(_result.dataI, _result.dataQ);
}

void RadarDataProcessorClass::runAlgorithm(void)
{
    if (_algo.detectSpeed)
        detectSpeed();
    if (_algo.detectMovingDirection)
        detectMovingDirection();

    // user callback
    if (_cb)
    {
        _cb(&_result);
    }

    // this task only runs once, having the effect of an interrupt
    deleteTask(_interruptTimer);

    _available = true;
}

void RadarDataProcessorClass::algoTask(int taskId, int16_t param)
{
    RadarDataProcessor.runAlgorithm();
}

void RadarDataProcessorClass::detectSpeed()
{
    // mean removal
    int sum = 0;
    for (int i = 0; i < _radarBufferSize; i++)
    {
        sum += _result.dataI[i];
    }
    sum = sum >> _fftOrder;
    for (int i = 0; i < _radarBufferSize; i++)
    {
        _result.magnitudes[i] = FIX_MPY((_result.dataI[i] - sum), _hanningWindow[i]);
        _imag[i] = 0;
    }

    // in-place fft, takes about 1.2 ms
    _fft.fix_fft(_result.magnitudes, _imag, _fftOrder, 0);

    //the first half of real fft values replaced by power spectrum
    _maxMagFreq = _fft.compute_magnitude(_result.magnitudes, _imag, _radarBufferSize / 2);

    _result.speed = (RATIO_FREQ_TO_SPEED * _freqWidth * _maxMagFreq.freq);
    _result.max_magnitude = _maxMagFreq.mag;
}

void RadarDataProcessorClass::detectMovingDirection(void)
{
    int8_t motion = 0;

    bool next_is_max = true;

    if (_result.dataI[0] > _result.dataI[1])
    {
        next_is_max = false;
    }

    for (uint16_t i = 0; i < (_radarBufferSize - 1) / 2; i++)
    {
        if ((_result.dataI[i] < (2048 - 200)) ||
            (_result.dataI[i] > (2048 + 200)))
        {
            if (next_is_max)
            {
                if (_result.dataI[i] > _result.dataI[i + 1])
                {
                    if (_result.dataQ[i] > _result.dataQ[i + 1])
                    {
                        motion++;
                    }
                    else if (_result.dataQ[i] < _result.dataQ[i + 1])
                    {
                        motion--;
                    }
                    next_is_max = false;
                }
            }
            else
            {
                if (_result.dataI[i] < _result.dataI[i + 1])
                {
                    if (_result.dataQ[i] > _result.dataQ[i + 1])
                    {
                        motion--;
                    }
                    else if (_result.dataQ[i] < _result.dataQ[i + 1])
                    {
                        motion++;
                    }
                    next_is_max = true;
                }
            }
        }

        if (motion < -2)
        {
            _result.motion = 1;
            return;
        }
        else if (motion > 2)
        {
            _result.motion = 0;
            return;
        }
    }
    _result.motion = 2;
    return;
}

void RadarDataProcessorClass::samplingTask(int taskId, int16_t param)
{
    RadarDataProcessor.startAcq();
    RadarDataProcessor.sampleInQ();
    RadarDataProcessor.endAcq();
}

void RadarDataProcessorClass::enableMotionDetection()
{
    _algo.detectMovingDirection = 1;
}
void RadarDataProcessorClass::disableMotionDetection()
{
    _algo.detectMovingDirection = 0;
}
void RadarDataProcessorClass::enableSpeedDetection()
{
    _algo.detectSpeed = 1;
}
void RadarDataProcessorClass::disableSpeedDetection()
{
    _algo.detectSpeed = 0;
}

void RadarDataProcessorClass::configureRadar(BGT_RADAR_CONFIG_t config)
{
    end();
    _radar->setConfig(config);
    _freqWidth = config.sampling_rate / config.radar_buffersize;
    begin();
}

RadarDataProcessorClass RadarDataProcessor = RadarDataProcessorClass();
