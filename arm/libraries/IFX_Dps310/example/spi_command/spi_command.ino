#include <ifx_dps310.h>

void setup() 
{
  //pin number of your slave select line
  int pin_cs=3;
  
  Serial.begin(9600);
  while(!Serial);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  pinMode(pin_cs, OUTPUT);
  digitalWrite(pin_cs, HIGH);


    //Call begin to initialize ifxDps310
    //The parameter pin_nr is the number of the CS pin on your Microcontroller
  ifxDps310.begin(SPI, pin_cs);
  
    // the function below fixes a hardware problem on some devices
    // you have this bug if you measure around 60°C when temperature is around 20°C
    // call correctTemp() directly after begin() to fix this issue
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
  delay(1000);
}
