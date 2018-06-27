/*
 * IFX9201 H-Bridge Motor Control Example for the H-Bridge 2GO Evaluation Board
 */

#include "SPI.h"
#include "IFX9201.h"

// IFX9201 Object
IFX9201 IFX9201_HBridge = IFX9201();

void setup() {
  // Initialize digital pin LED1 as an output.
  pinMode(LED1, OUTPUT);
  
  Serial.begin(9600);
  
  // Use SPI Mode with H-Bridge 2GO Evaluation Board
  // Change the CSN, DIR, PWM, and DIS pins to custom ones for other boards
  IFX9201_HBridge.begin(SPI, CSN, DIR, PWM, DIS);

  // Use PWM Mode
  // Change the CSN, DIR, PWM, and DIS pins to custom ones for other boards
  // IFX9201_HBridge.begin(CSN, DIR, PWM, DIS);
  
  delay(1000);        
}

void loop() {
  Serial.println("forwards"); 
  IFX9201_HBridge.forwards();
  delay(1000);
  
  Serial.println("stop"); 
  IFX9201_HBridge.stop();
  delay(1000);
  
  Serial.println("backwards"); 
  IFX9201_HBridge.backwards();
  delay(1000);
  
  Serial.println("stop"); 
  IFX9201_HBridge.stop();
  delay(1000);
  
  digitalToggle(LED1);
}
