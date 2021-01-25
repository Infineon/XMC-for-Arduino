#include <IFXRadarPulsedDoppler.h>

// IFX Radar Pulsed Doppler Object
IFXRadarPulsedDoppler radarDev;

void myErrorCallback( uint32_t error ) 
{
  Serial.print("--- ERROR: 0x");
  Serial.println( error, HEX);
  
  // turn on LEDs for error
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  
  while( 1 )
    ; 
}


void myResultCallback(void)
{
  uint8_t targetDirection = radarDev.getDirection();
  if(targetDirection == 1)
  {
    // turn on Red LED for departing target
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
    Serial.println("departing");
  }
  else if(targetDirection == 2)
  {
    // turn on Green LED for approaching target
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);      
    Serial.println("approaching");
  }
  else if(radarDev.targetAvailable() == true)
  {
    // turn on Blue LED for just normal motion with no meaningful direction
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    Serial.println("motion");
  }
  else
  {
    // turn off LEDs for no motion
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
  }
}



float raw_i[256];
float raw_q[256];


void setup() {

  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);

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

