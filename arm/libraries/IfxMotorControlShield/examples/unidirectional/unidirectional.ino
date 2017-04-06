#include <IfxMotorControlShield.h>


 
void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  if(ifxMcsUniDirectionalMotor1.begin())
    Serial.println("Init fail +++ Init Fail +++ Init Fail");
  Serial.println("Starting motor");
  ifxMcsUniDirectionalMotor1.start();
  Serial.println("Waiting some time");
  delay(30000);
  Serial.println("Stopping motor");
  ifxMcsUniDirectionalMotor1.stop();
  Serial.println("Program has ended");
}


void loop()
{
 
}

