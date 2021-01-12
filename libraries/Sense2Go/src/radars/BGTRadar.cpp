#include <Arduino.h>
#include "BGTRadar.h"


BGTRadar::BGTRadar( )
{
}


BGTRadar::~BGTRadar( )
{
}


// turn on
void BGTRadar::startAcq( )
{
}


// turn off
void BGTRadar::endAcq( )
{
}


void BGTRadar::setConfig( BGT_RADAR_CONFIG_t config )
{
_config = config;
_samplingTime = int( 1000000 / _config.sampling_rate );
}
