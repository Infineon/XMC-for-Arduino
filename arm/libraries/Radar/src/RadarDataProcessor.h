/**
 * @brief 
 * 
 * @file RadarDataProcessor.h
 * @date 2018-07-23
 * 
 * @bug LED1 LOW/HIGH reversed
 * @bug Serial print cannot be used in the callback (USIC interrupts possibly mess up Systick interrupts)
 * @bug ADC settling takes unusually long
 */

#ifndef RADAR_DATA_PROCESSOR_H
#define RADAR_DATA_PROCESSOR_H

#include "radars/BGT24LTR11.h"
#include "FixedFFTAnalyzer.h"

#define TWO_PI 6.28318530718

// #define FREQ_WIDTH SENSE2GO_SAMPLING_RATE / SENSE2GO_BUFFER_SIZE
// (km/h) / Hz
#define RATIO_FREQ_TO_SPEED 0.0225
#define RADAR_MAX_BUFFER_SIZE 256

typedef struct
{
  bool detectSpeed;
  bool detectMovingDirection;
} ALGORITHM_t;

typedef struct
{
  int16_t dataI[RADAR_MAX_BUFFER_SIZE];
  int16_t dataQ[RADAR_MAX_BUFFER_SIZE];
  int16_t magnitudes[RADAR_MAX_BUFFER_SIZE]; // power spectrum
  float speed;
  int max_magnitude;
  int motion;
} RESULT_t;

typedef enum
{
  RADAR_BGT24LTR11 = 0, // sense2go
  RADAR_BGT24MTR11 = 1  // distance2go
  // add more types here
} RADAR_t;

typedef enum
{
  APPROACHING = 0,
  DEPARTING = 1,
  NO_MOTION = 2
} MOTION_t;

class RadarDataProcessorClass
{

protected:
  int _interruptTimer;

  // TODO pre-define all classes
  BGT24LTR11 _bgt24ltr11;
  BGTRadar *_radar;

  RADAR_t _radarType;
  ALGORITHM_t _algo;

  RESULT_t _result;

  FFTAnalyzer _fft;

  int _fftOrder;

  int _radarBufferSize;

  float _freqWidth;

  int16_t _hanningWindow[RADAR_MAX_BUFFER_SIZE];

  int _timer;

  MAX_MAG_FRQ_t _maxMagFreq;

  void (*_cb)(RESULT_t *result);

  void startAcq(void);

  void endAcq(void);

  void sampleInQ(void);

  void initHanningWindow(uint8_t);

  static void samplingTask(int, int16_t);

  void runAlgorithm(void);

  static void algoTask(int, int16_t);

  void detectMovingDirection(void);

  void detectSpeed();
  void begin();

public:
  bool _available;

  // FFT buffer
  int16_t _imag[RADAR_MAX_BUFFER_SIZE];

  RadarDataProcessorClass();

  ~RadarDataProcessorClass();

  bool available();

  void begin(RADAR_t radarType, void (*cb)(RESULT_t *result) = nullptr);

  // use serial input to select mode
  void setMode(ALGORITHM_t algorithm);

  void end();

  void enableMotionDetection();
  void disableMotionDetection();
  void enableSpeedDetection();
  void disableSpeedDetection();
  void configureRadar(BGT_RADAR_CONFIG_t config);
};

extern RadarDataProcessorClass RadarDataProcessor;

#endif