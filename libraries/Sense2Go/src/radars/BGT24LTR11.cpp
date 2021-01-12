#include <Arduino.h>
#include "BGT24LTR11.h"

BGT_RADAR_CONFIG_t BGT24LTR11::default_config = { fft_size : SENSE2GO_BUFFER_SIZE,
												 fft_threshold : SENSE2GO_MAG_THRESH,
												 cycle_time : SENSE2GO_CYCLE_TIME,
												 sampling_rate : SENSE2GO_SAMPLING_RATE,
												 settle_time : SENSE2GO_SETTLE_TIME };


BGT24LTR11::BGT24LTR11( BGT_RADAR_CONFIG_t radarConfig )
{
_config = radarConfig;

// sampling time ( us ) needs to be computed from sampling rate.
_samplingTime = int( 1000000 / _config.sampling_rate );
}


BGT24LTR11::~BGT24LTR11( )
{
}


void BGT24LTR11::begin( )
{
// turn on radar
#ifdef XMC1300_Sense2GoL
pinMode( SENSE2GO_ON_PIN, OUTPUT );
digitalWrite( SENSE2GO_ON_PIN, LOW );
#endif
analogReadResolution( 12u );
}


void BGT24LTR11::startAcq( void )
{
#ifdef XMC1300_Sense2GoL
digitalWrite( SENSE2GO_ON_PIN, LOW );
// timing of this delay reveals that the actual delay is much less than specified
delayMicroseconds( SENSE2GO_SETTLE_TIME );
#endif
}


void BGT24LTR11::endAcq( void )
{
#ifdef XMC1300_Sense2GoL
digitalWrite( SENSE2GO_ON_PIN, HIGH );
#endif
}


void BGT24LTR11::sampleInQ( int16_t *bufferI, int16_t *bufferQ )
{
for( uint16_t i = 0; i < _config.fft_size; i++ )
   {
   bufferI[i] = analogRead( CH_I );
   bufferQ[i] = analogRead( CH_Q );
   delayMicroseconds( _samplingTime );
   }
}