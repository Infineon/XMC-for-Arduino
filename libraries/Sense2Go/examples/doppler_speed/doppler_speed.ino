#include <RadarDataProcessor.h>

#define SPECTRUM_SIZE ( SENSE2GO_BUFFER_SIZE / 2 )

int16_t magnitudes[ SPECTRUM_SIZE ];
bool available = false;
int max_mag;
float speed;


// this routine shouldn't take too long
void callback( RESULT_t *result )
{
for( int i = 0; i < SPECTRUM_SIZE; i++ )
   magnitudes[ i ] = result->magnitudes[ i ];
max_mag = result->max_magnitude;
speed = result->speed;
available = true;
}


void setup( )
{
Serial.begin( 9600 );
RadarDataProcessor.begin( RADAR_BGT24LTR11, callback );
RadarDataProcessor.enableFft( );
Serial.println( "Init done!" );
}

void loop( )
{
if( available )
  {
  Serial.println( speed );

  // for ( int i = 0; i < SPECTRUM_SIZE; i++ )
  //   Serial.println( magnitudes[ i ] );
  available = false;
  }
}
