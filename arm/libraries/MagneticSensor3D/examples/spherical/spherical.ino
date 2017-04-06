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

  Serial.print("Amount = ");
  Serial.print(magnetic3dSensor.getAmount());
  Serial.print(" mT; Azimuth angle (rad) = ");
  Serial.print(magnetic3dSensor.getAzimuth());
  Serial.print(" ; Polar angle (rad) = ");
  Serial.println(magnetic3dSensor.getPolar());
   
  delay(500);
}

