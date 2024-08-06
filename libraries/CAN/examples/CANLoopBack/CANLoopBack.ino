// Copyright (c) 2024 Infineon Technologies AG. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("CAN Loopback");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

  // set the can in loopback mode
  CAN.loopback();
}

void loop() {

  //
  Serial.print("Sending packet");
  CAN.beginPacket(0x12);
  CAN.write('L');
  CAN.write('O');
  CAN.write('O');
  CAN.write('P');
  CAN.endPacket();


  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    Serial.print(" and length ");
    Serial.println(packetSize);

    while (CAN.available()) {
      Serial.print((char)CAN.read());
    }
    Serial.println();
  }

  delay(1000);
}
