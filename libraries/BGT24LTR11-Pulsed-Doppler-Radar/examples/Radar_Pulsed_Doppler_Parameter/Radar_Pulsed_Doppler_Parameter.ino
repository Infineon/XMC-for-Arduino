#include <IFXRadarPulsedDoppler.h>

// IFX Radar Pulsed Doppler Object
IFXRadarPulsedDoppler radarDev;

void myResultCallback()
{
  uint8_t targetDirection = radarDev.getDirection();
  if(targetDirection == 1)
  {
    // turn on Red LED for departing target
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
  }
  else if(targetDirection == 2)
  {
    // turn on Green LED for approaching target
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);      
  }
  else if(radarDev.targetAvailable() == true)
  {
    // turn on Blue LED for just normal motion with no meaningful direction
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
  else
  {
    // turn off LEDs for no motion
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
  }
}

void myErrorCallback(uint32_t error)
{
  Serial.print("--- ERROR: 0x");
  Serial.println( error, HEX);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);

  Serial.begin(115200);

  radarDev.registerResultCallback(myResultCallback);
  radarDev.registerErrorCallback(myErrorCallback);
  
  radarDev.initHW();
  
  radarDev.begin();
  // dump default settings to serial port
  radarDev.parameterDump(&Serial);

  
  
  Serial.println("---------------------");
  radarDev.end();
  
  // apply very insensitive setting
  if( radarDev.setMotionSensitivity(200) ) {
     // Error occured, tell user
     Serial.println("Error, motion sensitivity out of range!");
  }
  
  if( radarDev.setDopplerSensitivity(400) ) {
     // Error occured, tell user
     Serial.println("Error, doppler sensitivity out of range!");
  }

  radarDev.parameterDump(&Serial);


  Serial.println("---------------------");
  radarDev.begin();
  radarDev.parameterDump(&Serial);

}

void loop() {
  // put your main code here, to run repeatedly:
  radarDev.run();
}