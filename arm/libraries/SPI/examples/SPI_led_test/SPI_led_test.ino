#include <SPI.h>

#define len 19

uint8_t Send_Data[len] = { 0x85, 0xFD, 0x82,
                           0xF0, 0xF0, 0xF0,
                           0x8A, 0x80, 0xF9,
                           0x80, 0x80, 0x80,
                           0x80, 0x80, 0x80,
                           0x80, 0x80, 0x80,
                           0x00
                         };

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(27, OUTPUT);
  digitalWrite(27, LOW);
}

void loop() {
  for (uint8_t a = 0; a < 3; a++)
  {
    uint8_t temp = Send_Data[0];
    for (uint8_t i = 0; i < 17; i++)
    {
      Send_Data[i] = Send_Data[i + 1];
    }
    Send_Data[17] = temp;
  }
  delay(1000);
  SPI.transfer(Send_Data, len);
}


