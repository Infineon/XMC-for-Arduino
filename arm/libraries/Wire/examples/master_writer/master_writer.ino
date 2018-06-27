// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW); 
  
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 1;
 
void loop() {
  delay(1000);
  Wire.beginTransmission(8); // transmit to device #8
  //Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  if(x % 2 == 0)
  {
    digitalWrite(LED2, LOW); 
  }
  else 
  {
    digitalWrite(LED2, HIGH); 
  }

  x++;
}
