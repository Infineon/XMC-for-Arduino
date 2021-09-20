#include <RadarDataProcessor.h>

bool available = false;
int motion;


// this routine shouldn't take too long
void callback( RESULT_t *result )
{
motion = result->motion;
available = true;
}


void setup( )
{
Serial.begin( 9600 );
RadarDataProcessor.begin( RADAR_BGT24LTR11, callback );
// you can try out both versions of motion detection algorithms

// RadarDataProcessor.enableSimpleMotionDetection( );
RadarDataProcessor.enableFftMotionDetection( );
Serial.println( "Init done!" );
}


void loop( )
{
if( available )
  {
  if( motion == APPROACHING )
    Serial.println( "approching" );
  else
    if( motion == DEPARTING )
      Serial.println( "departing" );
  available = false;
  }
}