#include <IfxMotorControlShield.h>

int speedvalue=0;
int acceleration = 5;
 
void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Program started");
  if(ifxMcsBiDirectionalMotor.begin())
    Serial.println("Init Fail!");
  Serial.println("Initialising speed");
  ifxMcsBiDirectionalMotor.setBiDirectionalSpeed(speedvalue);
  Serial.println("Starting motor");
  ifxMcsBiDirectionalMotor.start();
}


void loop()
{
   delay(200);

   if(ifxMcsBiDirectionalMotor.getCurrentSense() < IFX_MCS_CRITICALCURRENTSENSE)
   {

      speedvalue += acceleration;
      if(speedvalue > 255 && acceleration > 0)
      {
        acceleration = -acceleration;
        speedvalue = 255;
      }
      if(speedvalue < -255 && acceleration < 0)
      {
        acceleration = -acceleration;
        speedvalue = -255;
      }
      Serial.print("Speed: ");
      Serial.println(speedvalue);
      Serial.print("Acceleration: ");
      Serial.println(acceleration);
      ifxMcsBiDirectionalMotor.setBiDirectionalSpeed(speedvalue);
	  //if speed was set to 0, the motor has to be restarted!
      if(!ifxMcsBiDirectionalMotor.getRunning())
        ifxMcsBiDirectionalMotor.start();
   }
   else
   {
     Serial.println("Error!");
     ifxMcsBiDirectionalMotor.stop();
     speedvalue = 0;
   }
   
}

