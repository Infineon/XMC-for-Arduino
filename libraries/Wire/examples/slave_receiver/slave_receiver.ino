// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Serial.begin(115200);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW); 
  delay(500);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) { 
  uint8_t x = Wire.read();    // receive byte
  if(x % 2 == 0)
  {
    digitalWrite(LED2, LOW); 
  }
  else 
  {
    digitalWrite(LED2, HIGH); 
  }
}
