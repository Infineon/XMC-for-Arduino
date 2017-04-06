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
  Serial.begin(9600);
  while(!Serial);
  Wire.begin();
  
    //begin and config Dps310 for interrupts
  ifxDps310.begin(Wire); 
  int ret = ifxDps310.setInterruptPolarity(1);
  ret = ifxDps310.setInterruptSources(1, 0, 0);
    //clear interrupt flag by reading
  ifxDps310.getIntStatusFifoFull();

    //initialization of Interrupt for Controller unit
    //SDO pin of Dps310 has to be connected with interrupt pin
  int interruptPin = 3;
  pinMode(interruptPin, INPUT);
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
    //This could also be in the interrupt handler, but it would take too much time for a proper ISR
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


//interrupt handler
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
