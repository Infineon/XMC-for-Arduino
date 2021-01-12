/**
 * @brief 
 * 
 * @file RadarDataProcessor.h
 * @date 2018-07-23
 * 
 * @bug LED1 LOW/HIGH reversed on the sense2gol board
 * @bug Serial print cannot be used in the callback ( USIC interrupts possibly mess up Systick interrupts )
 * @bug ADC settling takes unusually long
 */

#ifndef RADAR_DATA_PROCESSOR_H
#define RADAR_DATA_PROCESSOR_H

#include <Arduino.h>
#include "radars/BGT24LTR11.h"
#include "FixedFFTAnalyzer.h"

/** Constant for convert Doppler frequency to speed. ( 10 km/h )/( 444.4 Hz ) = 0.0225 */
#define RATIO_FREQ_TO_SPEED 0.0225
#define RADAR_MAX_BUFFER_SIZE 256

typedef struct
  {
  // two versions of motion detection are implemented
  bool detectMotionSimple;
  bool detectMotionFft;
  bool fft;
  } ALGORITHM_t;

typedef enum
  {
  APPROACHING = 0,
  DEPARTING = 1,
  NO_MOTION = 2
  } MOTION_t;


/**
 * @struct Results passed back to the user callback
 * 
 */
typedef struct
  {
  int16_t dataI[ RADAR_MAX_BUFFER_SIZE ];
  int16_t dataQ[ RADAR_MAX_BUFFER_SIZE ];
  /** real parts of I data's FFT spectrum*/
  int16_t realI[ RADAR_MAX_BUFFER_SIZE ];
  /** imaginary parts of I data's FFT spectrum*/
  int16_t imagI[ RADAR_MAX_BUFFER_SIZE ];
  int16_t realQ[ RADAR_MAX_BUFFER_SIZE ];
  int16_t imagQ[ RADAR_MAX_BUFFER_SIZE ];
  /** power spectrum*/
  int16_t magnitudes[ RADAR_MAX_BUFFER_SIZE ]; 
  float speed;
  float phase_shift;
  int max_magnitude;
  int motion;
  } RESULT_t;

/**
 * @enum Radar types
 * 
 */
typedef enum
  {
  /** Sense2GoL*/
  RADAR_BGT24LTR11 = 0, 
  /** Distance2Go*/
  RADAR_BGT24MTR11 = 1  
  // add more types here
  } RADAR_t;

class RadarDataProcessorClass
{
protected:
  /**
   * @brief A dummy timer used only to generate an interrupt
   * 
   */
  int _interruptTimer;

  // TODO: pre-define all classes, BGT24MTR11 etc.
  BGT24LTR11 _bgt24ltr11;
  BGTRadar *_radar;
  RADAR_t _radarType;
  ALGORITHM_t _algo;
  RESULT_t _result;
  FFTAnalyzer _fft;
  int _fftOrder;
  int _radarFftSize;
  float _freqWidth;

  /**
   * @brief Hanning window for pre-FFT processing
   * 
   */
  int16_t _hanningWindow[ RADAR_MAX_BUFFER_SIZE ];

  int _timer;

  /**
   * @brief Magnitude and frequency pair at the frequency peak.
   * 
   */
  MAX_MAG_FRQ_t _maxMagFreq;

  void ( *_cb )( RESULT_t *result );
  void startAcq( void );
  void endAcq( void );
  void sampleInQ( void );
  void initHanningWindow( uint8_t );

  /**
   * @brief Sampling task that runs every cycle time ( defined in radar child classes )
   * 
   */
  static int samplingTask( int, int16_t );

  void runAlgorithm( void );

  /**
   * @brief Task to execute algorithms on the sampled data, runs once after every sampling task is finished.
   * 
   */
  static int algoTask( int, int16_t );

  /**
   * @brief This algorithm works by comparing the phase shifts of I and Q data
   * 
   */
  void detectMotionWithRawData( void );

  void computeFft( );
  void begin( );

public:
  bool _available;
  RadarDataProcessorClass( );
  ~RadarDataProcessorClass( );
  bool available( );

  /**
   * @brief Turns on the radar chip and starts sampling
   * 
   * @param radarType Type of the radar, e.g., RADAR_BGT24LTR11.
   * @param cb Callback function whose argument is the pointer to the computation results
   */
  void begin( RADAR_t radarType, void ( *cb )( RESULT_t *result ) = nullptr );

  /**
   * @brief Stops the radar. Needs to be called before reconfigure radar parameters.
   * 
   */
  void end( );

  /**
   * @brief Enables the motion detection algorithm, which is called in runAlgorithm
   * 
   */
  void enableSimpleMotionDetection( );
  void enableFftMotionDetection( );
  void disableMotionDetection( );
  void enableFft( );
  void disableFft( );
  void configureRadar( BGT_RADAR_CONFIG_t config );
};

extern RadarDataProcessorClass RadarDataProcessor;
#endif