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

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);

  radarDev.initHW();
  radarDev.registerResultCallback(myResultCallback);
  radarDev.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  radarDev.run();
}
