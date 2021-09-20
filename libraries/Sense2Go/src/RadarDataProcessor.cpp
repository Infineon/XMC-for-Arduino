#include <Arduino.h>
#include "RadarDataProcessor.h"


RadarDataProcessorClass::RadarDataProcessorClass( )
{
_fft = FFTAnalyzer( );
_maxMagFreq = { 0, 0 };
_algo = { false, false, false };
_result.speed = 0.0;
_result.max_magnitude = 0;
_result.motion = 0;
}


RadarDataProcessorClass::~RadarDataProcessorClass( )
{
end( );
}


bool RadarDataProcessorClass::available( )
{
return _available;
}


void RadarDataProcessorClass::initHanningWindow( uint8_t windowLength )
{
// w( n ) = 0.5 ( 1-cos( 2*pi*n/( N-1 ) ) ), 0 <= n <= ( N-1 )
float frac = TWO_PI / ( windowLength - 1 );
for( int i = 0; i < windowLength; i++ )
   _hanningWindow[  i ] = round( 32767 * ( 1 - cos( i * frac ) ) ) >> 1;
}


void RadarDataProcessorClass::begin( )
{
// check initialization
if( !_radar )
  return;

_radar->begin( );
_radarFftSize = ( _radar->_config ).fft_size;
if( _radarFftSize > RADAR_MAX_BUFFER_SIZE )
  _radarFftSize = RADAR_MAX_BUFFER_SIZE;

_fftOrder = log2( _radarFftSize );
if( _radarFftSize <= 0 )
  return;

initHanningWindow( _radarFftSize );
_freqWidth = ( _radar->_config ).sampling_rate / _radarFftSize;

// configure task to be executed periodically
_timer = addTask( RadarDataProcessorClass::samplingTask );

if( _timer < 0 || _timer > NUM_TASKS_VARIANT )
  return;         // error: too many tasks

setParam( _timer, _timer );
setInterval( _timer, ( _radar->_config ).cycle_time );
startTask( _timer );
_interruptTimer = addTask( RadarDataProcessorClass::algoTask );

// use as an interrupt
setParam( _interruptTimer, _interruptTimer );
setInterval( _interruptTimer, 1 );
}


void RadarDataProcessorClass::begin( RADAR_t radarType, void ( *cb )( RESULT_t *result ) )
{
// set callback
if( cb )
  _cb = cb;
_radarType = radarType;

switch( _radarType )
    {
    case RADAR_BGT24LTR11:
        _bgt24ltr11 = BGT24LTR11( );
        _radar = &_bgt24ltr11;
        break;
    default:
        // error: wrong data type
        return;
    }
begin( );
}


void RadarDataProcessorClass::end( )
{
deleteTask( RadarDataProcessorClass::samplingTask );
deleteTask( RadarDataProcessorClass::algoTask );
}


void RadarDataProcessorClass::startAcq( void )
{
// check if these functions are necessary for future radars
_radar->startAcq( );
}


void RadarDataProcessorClass::endAcq( void )
{
_radar->endAcq( );

// finished sampling, run the detection algorithm algoTask
startTask( _interruptTimer );
}


void RadarDataProcessorClass::sampleInQ( void )
{
// only need to sum up I data
_radar->sampleInQ( _result.dataI, _result.dataQ );
}


void RadarDataProcessorClass::runAlgorithm( void )
{
// be sure that the time for running all the enabled algorithms plus time for ADC conversion should be shorter than cycle time
if( _algo.fft )
  computeFft( );
if( _algo.detectMotionSimple )
  detectMotionWithRawData( );

// user callback
if( _cb )
  _cb( &_result );

// the interrupt time must be deleted in every cycle!
deleteTask( RadarDataProcessorClass::algoTask );
_available = true;
}


int RadarDataProcessorClass::algoTask( int taskId, int16_t param )
{
RadarDataProcessor.runAlgorithm( );
return 1;
}


void RadarDataProcessorClass::computeFft( )
{
// mean removal
int sum = 0;
for( int i = 0; i < _radarFftSize; i++ )
   sum += _result.dataI[ i ];
sum = sum >> _fftOrder;

// windowing -> move to fft analyzer
for( int i = 0; i < _radarFftSize; i++ )
   {
   _result.realI[ i ] = FIX_MPY( ( _result.dataI[ i ] - sum ), _hanningWindow[ i ] );
   _result.imagI[ i ] = 0;
   }
// in-place fft
_fft.fix_fft( _result.realI, _result.imagI, _fftOrder, 0 );

// the first half of real fft values replaced by power spectrum
_maxMagFreq = _fft.compute_magnitude( _result.realI, _result.imagI, _result.magnitudes, _radarFftSize / 2 );
bool detected = _maxMagFreq.mag > ( _radar->_config ).fft_threshold;
if( _algo.detectMotionFft )
  {
  float maxImagI = ( float ) _result.imagI[ _maxMagFreq.freq ];
  float maxRealI = ( float ) _result.realI[ _maxMagFreq.freq ];

  for( int i = 0; i < _radarFftSize; i++ )
     {
     _result.realQ[ i ] = FIX_MPY( ( _result.dataQ[ i ] - sum ), _hanningWindow[ i ] );
     _result.imagQ[ i ] = 0;
     }

  // TODO: only one-point fft needed for the Q data
  _fft.fix_fft( _result.realQ, _result.imagQ, _fftOrder, 0 );

  float maxImagQ = ( float ) _result.imagQ[ _maxMagFreq.freq ];
  float maxRealQ = ( float ) _result.realQ[ _maxMagFreq.freq ];

  // TODO use integer atan2, e.g. CORDIC version from xmc_math
  if( maxRealQ && maxRealI && detected )
    {
    float phase_shift = atan2( maxImagI, maxRealI ) - atan2( maxImagQ, maxRealQ );
    if( phase_shift < -3.14 )
      phase_shift += 6.28;
    else 
      if( phase_shift > 3.14 )
        phase_shift -= 6.28;

    if( phase_shift > 0 )
      _result.motion = 1;
    else
      if( phase_shift < 0 )
        _result.motion = 0;
      else
        _result.motion = 2;

    _result.phase_shift = phase_shift;
    }
  else
    {
    _result.phase_shift = 0;
    _result.motion = 2;
    }
  }
if( detected )
  _result.speed = ( RATIO_FREQ_TO_SPEED * _freqWidth * _maxMagFreq.freq );
else
  _result.speed = 0;

_result.max_magnitude = _maxMagFreq.mag;
}


void RadarDataProcessorClass::detectMotionWithRawData( void )
{
int8_t motion = 0;

bool next_is_max = true;

if( _result.dataI[ 0 ] > _result.dataI[ 1 ] )
  next_is_max = false;

for( uint16_t i = 0; i < ( _radarFftSize - 1 ) / 2; i++ )
   {
   if( ( _result.dataI[ i ] < ( 2048 - 200 ) ) ||
          ( _result.dataI[ i ] > ( 2048 + 200 ) ) )
     {
     if( next_is_max )
       if( _result.dataI[ i ] > _result.dataI[ i + 1 ] )
         {
         if( _result.dataQ[ i ] > _result.dataQ[ i + 1 ] )
           motion++;
         else
           if( _result.dataQ[ i ] < _result.dataQ[ i + 1 ] )
             motion--;
         next_is_max = false;
         }
     else
       if( _result.dataI[ i ] < _result.dataI[ i + 1 ] )
         {
         if( _result.dataQ[ i ] > _result.dataQ[ i + 1 ] )
           motion--;
         else
           if( _result.dataQ[ i ] < _result.dataQ[ i + 1 ] )
             motion++;
         next_is_max = true;
         }
     }
   if( motion < -2 )
     {
     _result.motion = 1;
     return;
     }
   else
     if( motion > 2 )
       {
       _result.motion = 0;
       return;
       }
   }
_result.motion = 2;
return;
}


int RadarDataProcessorClass::samplingTask( int taskId, int16_t param )
{
RadarDataProcessor.startAcq( );
RadarDataProcessor.sampleInQ( );
RadarDataProcessor.endAcq( );
return 1;
}


void RadarDataProcessorClass::enableSimpleMotionDetection( )
{
_algo.detectMotionSimple = 1;
_algo.detectMotionFft = 0;
}


void RadarDataProcessorClass::enableFftMotionDetection( )
{
if( !_algo.fft )
  _algo.fft = 1;
_algo.detectMotionFft = 1;
_algo.detectMotionSimple = 0;
}


void RadarDataProcessorClass::disableMotionDetection( )
{
_algo.detectMotionSimple = 0;
_algo.detectMotionFft = 0;
}


void RadarDataProcessorClass::enableFft( )
{
_algo.fft = 1;
}


void RadarDataProcessorClass::disableFft( )
{
_algo.fft = 0;
}


void RadarDataProcessorClass::configureRadar( BGT_RADAR_CONFIG_t config )
{
end( );
_radar->setConfig( config );
_freqWidth = config.sampling_rate / config.fft_size;
begin( );
}

RadarDataProcessorClass RadarDataProcessor = RadarDataProcessorClass( );
