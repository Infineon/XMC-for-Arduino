#include <SPI.h>

void setup() {
    // Start the SPI bus as a master with default settings: (1 MHz, MSBFIRST, SPI_MODE0)
    SPI.begin();
    Serial.begin(9600);
    pinMode(SS, OUTPUT);

    // Optional: Set SPI settings
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(SS, HIGH);
    Serial.println("SPI Master Started");
}

void loop() {
    uint8_t dataToSend = 99; 
    uint8_t receivedData;

    // Make a transfer and get the response from the slave
    digitalWrite(SS, LOW);
    delayMicroseconds(10);
    receivedData = SPI.transfer(dataToSend);
        delayMicroseconds(10);

    digitalWrite(SS, HIGH);

    Serial.print("Data Sent: ");
    Serial.println(dataToSend);
    Serial.print("Data Received: ");
    Serial.println(receivedData);

    delay(1000); 
}