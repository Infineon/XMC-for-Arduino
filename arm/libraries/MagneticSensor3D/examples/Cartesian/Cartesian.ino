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
  delay(100);
  digitalWrite(15, HIGH);

  Serial.print("X = ");
  Serial.print(magnetic3dSensor.getX());
  Serial.print(" mT; Y = ");
  Serial.print(magnetic3dSensor.getY());
  Serial.print(" mT; Z = ");
  Serial.print(magnetic3dSensor.getZ());
  Serial.println(" mT");
   
  delay(500);
}

