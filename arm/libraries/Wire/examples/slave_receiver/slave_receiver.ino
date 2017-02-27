// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
uint8_t vgl = 1;

void setup() {
  Serial.begin(115200);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, LOW); 
  delay(500);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  delay(100);
  Serial.println(vgl);
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
  
  //while (1 < Wire.available()) { // loop through all but the last
  //  char c = Wire.read(); // receive byte as a character
  //  Serial.print(c);         // print the character
  //}

  if (x == vgl)
  {
    digitalWrite(LED3, HIGH);
  }
  else
  {
    digitalWrite(LED3, LOW);
  }
  vgl++;
}
