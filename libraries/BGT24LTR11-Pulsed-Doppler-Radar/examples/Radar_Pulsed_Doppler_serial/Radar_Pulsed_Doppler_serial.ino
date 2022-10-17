#include <IFXRadarPulsedDoppler.h>
#include <LED.h>

// IFX Radar Pulsed Doppler Object
IFXRadarPulsedDoppler radarDev;
LED Led;

void myErrorCallback( uint32_t error ) 
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
    Serial.println("departing");
  }
  else if(targetDirection == 2)
  {
    // turn on Green LED for approaching target
    Led.On( LED_GREEN );
    Led.Off( LED_RED );
    Led.Off( LED_BLUE );
    Serial.println("approaching");
  }
  else if(radarDev.targetAvailable() == true)
  {
    // turn on Blue LED for just normal motion with no meaningful direction
    Led.Off( LED_GREEN );
    Led.Off( LED_RED );
    Led.On( LED_BLUE );
    Serial.println("motion");
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


void setup() {

  Led.Add( LED_RED );
  Led.Add( LED_GREEN );
  Led.Add( LED_BLUE );
  
  Led.Off( LED_RED );
  Led.Off( LED_GREEN );
  Led.Off( LED_BLUE );

  Serial.begin(115200);  

  radarDev.registerResultCallback(myResultCallback);
  radarDev.registerErrorCallback(myErrorCallback);

  radarDev.initHW();

  // start the radarDevice, to read the default parameter
  radarDev.begin();
  // dump default settings to serial port
  radarDev.parameterDump(&Serial);

  
  
  Serial.println("---------------------");
  // stop the device to change parameters
  radarDev.end();
  
  // apply very insensitive setting
  
  radarDev.setMotionSensitivity(300);
  radarDev.setDopplerSensitivity(500);

  radarDev.parameterDump(&Serial);


  Serial.println("---------------------");
  // Restart the radar device
  radarDev.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  radarDev.run();
}

