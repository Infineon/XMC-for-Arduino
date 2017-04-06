#include <MagneticSensor3D.h>


void setup() {
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  magnetic3dSensor.begin();
  digitalWrite(14, HIGH);
}

void loop() {
  digitalWrite(15, LOW);
  magnetic3dSensor.updateData();
  digitalWrite(15, HIGH);

  Serial.print(magnetic3dSensor.getAmount());
  Serial.print(" ; ");
  Serial.print(magnetic3dSensor.getAzimuth());
  Serial.print(" ; ");
  Serial.println(magnetic3dSensor.getPolar());
   
  delay(10);
}

