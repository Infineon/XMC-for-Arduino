#include "SPI.h"
char outByte [20] = "Hello from XMC";                           // string to be send and received via SPI port
char inByte;                                                      // variable which stores the value of the byte received from SPI bus
int i = 0;                                                         
void setup() 
{
  pinMode(LED1, OUTPUT);                                           // setting the LED pin as output

  Serial.begin(9600);                                             // initializing the serial port at 9600 baud rate

  SPI.begin();                                                    // initialize the SPI port as master

  delay(100);  
}
void loop() 
{    
  digitalWrite(LED1, HIGH);   
         
    for(i=0;i<16;i++)
    {
    inByte = SPI.transfer(outByte[i]);
    Serial.write(inByte);  
    }
    
  Serial.println();
  delay(100);

  digitalWrite(LED1, LOW); 

  delay(1000);  
}
