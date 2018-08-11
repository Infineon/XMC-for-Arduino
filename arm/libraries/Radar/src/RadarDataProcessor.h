/**
 * @brief 
 * 
 * @file RadarDataProcessor.h
 * @date 2018-07-23
 * 
 * @bug LED1 LOW/HIGH reversed on the sense2gol board
 * @bug Serial print cannot be used in the callback (USIC interrupts possibly mess up Systick interrupts)
 * @bug ADC settling takes unusually long
 */

#ifndef RADAR_DATA_PROCESSOR_H
#define RADAR_DATA_PROCESSOR_H

#include "radars/BGT24LTR11.h"
#include "FixedFFTAnalyzer.h"

#define TWO_PI 6.28318530718

/**
 * @brief Constant for convert Doppler frequency to speed. (10 km/h)/(444.4 Hz) = 0.0225
 * 
 */
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

  // TODO: pre-define all classes, BGT24MTR11 etc.
  BGT24LTR11 _bgt24ltr11;
  BGTRadar *_radar;

  RADAR_t _radarType;

  /**
   * @brief Defines which algorithms are used, such as speed/motion detection
   * 
   */
  ALGORITHM_t _algo;

  /**
   * @brief 
   * 
   */
  RESULT_t _result;

  FFTAnalyzer _fft;

  int _fftOrder;

  int _radarBufferSize;

  float _freqWidth;

  /**
   * @brief Hanning window for pre-FFT processing
   * 
   */
  int16_t _hanningWindow[RADAR_MAX_BUFFER_SIZE];

  int _timer;

  MAX_MAG_FRQ_t _maxMagFreq;

  void (*_cb)(RESULT_t *result);

  void startAcq(void);

  void endAcq(void);

  void sampleInQ(void);

  void initHanningWindow(uint8_t);

  /**
   * @brief Sampling task that runs every cycle time (defined in radar child classes)
   * 
   */
  static void samplingTask(int, int16_t);

  void runAlgorithm(void);

  /**
   * @brief Task to execute algorithms on the sampled data, runs once after every sampling task is finished.
   * 
   */
  static void algoTask(int, int16_t);

  void detectMovingDirection(void);

  void detectSpeed();
  void begin();

public:
  bool _available;

  /**
   * @brief Buffer to store the imaginary parts of the FFT spectrum
   * 
   */
  int16_t _imag[RADAR_MAX_BUFFER_SIZE];

  RadarDataProcessorClass();

  ~RadarDataProcessorClass();

  bool available();

  /**
   * @brief Turns on the radar chip and starts sampling
   * 
   * @param radarType Type of the radar, e.g., RADAR_BGT24LTR11.
   * @param cb Callback function whose argument is the pointer to the computation results (FFT spectrum, object speed, etc) of the raw I/Q data
   */
  void begin(RADAR_t radarType, void (*cb)(RESULT_t *result) = nullptr);

  /**
   * @brief Stops the radar. Needs to be called before reconfigure radar parameters.
   * 
   */
  void end();

  void enableMotionDetection();
  void disableMotionDetection();
  void enableSpeedDetection();
  void disableSpeedDetection();
  void configureRadar(BGT_RADAR_CONFIG_t config);
};

extern RadarDataProcessorClass RadarDataProcessor;

#endif