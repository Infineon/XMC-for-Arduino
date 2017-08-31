#include <ifx_dps310.h>

void setup()
{
  //pin number of your slave select line
  int pin_cs = SS;

  Serial.begin(9600);
  while (!Serial);


  //Call begin to initialize ifxDps310
  //The parameter pin_nr is the number of the CS pin on your Microcontroller
  ifxDps310.begin(SPI, pin_cs);
  
  // IMPORTANT NOTE
  //If you face the issue that the DPS310 indicates a temperature around 60 °C although it should be around 20 °C (room temperature), you might have got an IC with a fuse bit problem
  //Call the following function directly after begin() to resolve this issue (needs only be called once after startup)
  //ifxDps310.correctTemp();

  Serial.println("Init complete!");
}



void loop()
{
  long int temperature;
  long int pressure;
  int oversampling = 7;
  int ret;
  Serial.println();

  //lets the Dps310 perform a Single temperature measurement with the last (or standard) configuration
  //The result will be written to the paramerter temperature
  //ret = ifxDps310.measureTempOnce(temperature);
  //the commented line below does exactly the same as the one above, but you can also config the precision
  //oversampling can be a value from 0 to 7
  //the Dps 310 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
  //measurements with higher precision take more time, consult datasheet for more information
  ret = ifxDps310.measureTempOnce(temperature, oversampling);

  if (ret != 0)
  {
    //Something went wrong.
    //Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees of Celsius");
  }


  //ret = ifxDps310.measurePressureOnce(pressure);
  ret = ifxDps310.measurePressureOnce(pressure, oversampling);
  if (ret != 0)
  {
    //Something went wrong.
    //Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" Pascal");
  }

  //Wait some time
  delay(1000);
}
