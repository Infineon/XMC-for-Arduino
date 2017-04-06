#include <ifx_dps310.h>

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  Wire.begin();


    //Call begin to initialize ifxDps310
    //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given. 
  ifxDps310.begin(Wire, 0x76);
    //Use the commented line below instead of the one above to use the default I2C address. 
    //if you are using the Pressure 3 click Board, you need 0x76
  //ifxDps310.begin(&Wire);
  
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
   
  if(ret!=0)
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

    //Pressure measurement behaves like temperature measurement
  //ret = ifxDps310.measurePressureOnce(pressure);
  ret = ifxDps310.measurePressureOnce(pressure, oversampling); 
  if(ret!=0)
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
  delay(500);
}
