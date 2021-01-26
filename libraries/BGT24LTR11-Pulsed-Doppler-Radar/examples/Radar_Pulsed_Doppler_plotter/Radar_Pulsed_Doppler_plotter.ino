#include <IFXRadarPulsedDoppler.h>
#include <LED.h>

// IFX Radar Pulsed Doppler Object
IFXRadarPulsedDoppler radarDev;
LED Led;

void myErrorCallback(uint32_t error)
{
  Serial.print("--- ERROR: 0x");
  Serial.println( error, HEX);
  
  Led.On( LED_GREEN );
  Led.On( LED_RED );
  Led.On( LED_BLUE );
  
  while( 1 )
    ; 
}


void myResultCallback(void)
{
  uint8_t targetDirection = radarDev.getDirection();
  if(targetDirection == 1)
  {
    // turn on Red LED for departing target
    Led.Off( LED_GREEN );
    Led.On( LED_RED );
    Led.Off( LED_BLUE );
  }
  else if(targetDirection == 2)
  {
    // turn on Green LED for approaching target
    Led.On( LED_GREEN );
    Led.Off( LED_RED );
    Led.Off( LED_BLUE );
  }
  else if(radarDev.targetAvailable() == true)
  {
    // turn on Blue LED for just normal motion with no meaningful direction
    Led.Off( LED_GREEN );
    Led.Off( LED_RED );
    Led.On( LED_BLUE );
  }
  else
  {
    // turn off LEDs for no motion
    Led.Off( LED_GREEN );
    Led.Off( LED_RED );
    Led.Off( LED_BLUE );
  }
}


float raw_i[256];
float raw_q[256];


void myRawDataCallback( raw_data_context_t context )
{
    uint32_t frameCnt   = radarDev.getRawDataFrameCount( context );
    uint16_t numSamples = radarDev.getNumRawDataSamples( context );

    radarDev.getRawData( context, raw_i, raw_q, 256 );

    for( uint32_t i = 0; i < numSamples; i++ ) 
    {
        Serial.print( raw_i[i] );
        Serial.print("\t");
        Serial.print( raw_q[i] );
        Serial.println( "" );
    }
}

void setup() {

  Led.Add( LED_RED );
  Led.Add( LED_GREEN );
  Led.Add( LED_BLUE );
  
  Led.Off( LED_RED );
  Led.Off( LED_GREEN );
  Led.Off( LED_BLUE );

  Serial.begin(500000);  //This baudrate is required to show continuous wave on serial plotter, at minimum framerate (continuous sampling!)

  radarDev.registerResultCallback(myResultCallback);
  radarDev.registerErrorCallback(myErrorCallback);
  radarDev.registerRawDataCallback(myRawDataCallback );  // register a handler to receive raw data
  //radarDev.enableAlgoProcessing( false ); // set to false to disables the lib internal radar algo processing

  radarDev.initHW();

  // start the radarDevice, to read the default parameter
  radarDev.begin();
  
  // set minimum Frame period, to get continuous sampling of data, a skip count is required to remove the transient 
  // in analog baseband after frame pause
  // set skip count to zero, in countinuous mode there is not transient that needs to be skipped.
  radarDev.setSkipSamples( 0 );
  
  // read minimum possible Frame period (after setting skip count!)
  uint32_t minFramePeriod = radarDev.getMinFramePeriod();

  // stop the device to change parameters
  radarDev.end();
  radarDev.setFramePeriod( minFramePeriod ); 
    
  // legend for Serial Plotter:
  Serial.print("I-Signal\tQ-Signal-");
  Serial.println(minFramePeriod);

  // Restart the radar device
  radarDev.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  radarDev.run();
}

