// Demonstrates how to change radar configuration. Be aware that some config might not work.

#include <RadarDataProcessor.h>

#define DETECTING_MAG_THRESH 100

#define SPECTRUM_SIZE SENSE2GO_BUFFER_SIZE / 2

int16_t magnitudes[SPECTRUM_SIZE ];
bool available = false;

BGT_RADAR_CONFIG_t user_config = 
  {
  fft_size : 128,
  fft_threshold : DETECTING_MAG_THRESH,
  cycle_time : 100,
  sampling_rate : 3000
  };

  
// this routine shouldn't take too long
void callback( RESULT_t *result )
{
for( int i = 0; i < SPECTRUM_SIZE; i++ )
   magnitudes[ i ] = result->magnitudes[ i ];
available = true;
}


void setup( )
{
Serial.begin( 9600 );
RadarDataProcessor.begin( RADAR_BGT24LTR11, callback );
RadarDataProcessor.enableFft( );
RadarDataProcessor.configureRadar( user_config );
Serial.println( "Init done!" );
}


void loop( )
{
if( available )
  {
  for( int i = 0; i < SPECTRUM_SIZE; i++ )
     Serial.println( magnitudes[ i ] );
  available = false;
  }
}