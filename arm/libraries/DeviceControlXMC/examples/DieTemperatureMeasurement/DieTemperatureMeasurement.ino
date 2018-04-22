
/*
  Simple die temperature measurement for XMC devices
  Demonstrates the measure temperature of die using sensor.
  05 July 2017
 */

#include <DeviceControlXMC.h>
XMCClass xmc;

 uint32_t temperature = 0;
 
//The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{

  delay(1000);

  /*If UC_FAMILY = XMC4 you can also calibrate temperature for finer measurements*/
  temperature = xmc.getTemperature();

  Serial.println();
  Serial.print("Temperature of die is:");
  Serial.print(temperature);

}

