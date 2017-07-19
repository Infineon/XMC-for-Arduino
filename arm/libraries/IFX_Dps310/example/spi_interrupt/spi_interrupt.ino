#include <ifx_dps310.h>

void onFifoFull();

const unsigned char pressureLength = 50;
unsigned char pressureCount = 0;
long int pressure[pressureLength];
unsigned char temperatureCount = 0;
const unsigned char temperatureLength = 50;
long int temperature[temperatureLength];


 

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
  //The third parameter has to be 1 and enables 3-wire SPI interface
  //This is necessary, because SDO will be used to indicate interrupts
  //ATTENTION: Make sure you have connected your MISO and MOSI pins right!
  //  There may NEVER be a direct Connection between MOSI and SDI when 3-wire SPI is enabled
  //  Otherwise, you will cause shortcuts and seriously damage your equipment. 
  //  For three wire interface, MISO has to be connected to SDI and there hase to be a resistor between MISO and MOSI
  //  I successfully tested this with a resistor of 1k, but I won't give you any warranty that this works for your equipment too
  ifxDps310.begin(SPI, pin_cs, 1);
  
    // the function below fixes a hardware problem on some devices
    // you have this bug if you measure around 60°C when temperature is around 20°C
    // call correctTemp() directly after begin() to fix this issue
  //ifxDps310.correctTemp();

  //config Dps310 for Interrupts
  int ret = ifxDps310.setInterruptPolarity(1);
  ret = ifxDps310.setInterruptSources(1, 0, 0);
  //clear interrupt flag by reading
  ifxDps310.getIntStatusFifoFull();

  //initialization of Interrupt for Controller unit
  //SDO pin of Dps310 has to be connected with interrupt pin
  int interruptPin = 2;
  pinMode(interruptPin, INPUT);
  Serial.println(digitalPinToInterrupt(interruptPin));
  attachInterrupt(digitalPinToInterrupt(interruptPin), onFifoFull, RISING);

  //start of a continuous measurement just like before
  int temp_mr = 3;
  int temp_osr = 2;
  int prs_mr = 1;
  int prs_osr = 3;
  ret = ifxDps310.startMeasureBothCont(temp_mr, temp_osr, prs_mr, prs_osr); 
  if(ret!=0)
  {
    Serial.print("Init FAILED! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.println("Init complete!");
  }
}


void loop()
{

  //do other stuff
  Serial.println("loop running");
  delay(500);


  //if result arrays are full
  //This could also be in the interrupt handler, but it would take too much time for an interrupt
  if(pressureCount==pressureLength && temperatureCount==temperatureLength)
  {
    //print results
    Serial.println();
    Serial.println();
    Serial.print(temperatureCount);
    Serial.println(" temperature values found: ");
    for(int i=0; i<temperatureCount; i++)
    {
      Serial.print(temperature[i]);
      Serial.println(" degrees of Celsius");
    }

    Serial.println();
    Serial.print(pressureCount);
    Serial.println(" pressure values found: ");
    for(int i=0; i<pressureCount; i++)
    {
      Serial.print(pressure[i]);
      Serial.println(" Pascal");
    } 
    Serial.println();
    Serial.println();

    //reset result counters
    pressureCount=0;
    temperatureCount=0;
  }
  
}


void onFifoFull() 
{
  //message for debugging
  Serial.println("Interrupt handler called");

  //clear interrupt flag by reading
  ifxDps310.getIntStatusFifoFull();

  //calculate the number of free indexes in the result arrays
  unsigned char prs_freespace = pressureLength - pressureCount;
  unsigned char temp_freespace = temperatureLength - temperatureCount;
  //read the results from Dps310, new results will be added at the end of the arrays
  ifxDps310.getContResults(&temperature[temperatureCount], temp_freespace, &pressure[pressureCount], prs_freespace);
  //after reading the result counters are increased by the amount of new results
  pressureCount+=prs_freespace;
  temperatureCount+=temp_freespace; 


}
