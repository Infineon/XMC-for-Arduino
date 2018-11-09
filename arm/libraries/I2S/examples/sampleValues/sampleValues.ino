#include <I2S.h>

/*
 * This example reads audio data from Infineon's IM69D130 Microphone Shield2Go 
 * and prints it on the serial monitor.
 * 
 * Open the serial monitor with baudrate of 1000000 to see the results.
 * 
 * Note: if 2 channels are used, the values returned from I2S.read() will be from both channels and thus look noisy
 * In this case, both values need to be separated.
 */

void setup()
{
  Serial.begin(1000000);
  Serial.println("Begin of I2S microphone");
  // Disable all microphones
  I2S.disableMicrophones();
  // Enable the microphone when word select is low
  I2S.enableMicrophoneLow();
  // Enable the microphone when word select is high
  // I2S.enableMicrophoneHigh();
  // Get the activated microphones
  // You can compare against NO_MICROPHONE, MICROPHONE_LOW, MICROPHONE_HIGH, MICROPHONE_LOW_HIGH
  // e.g. I2S.getMicrophones() == NO_MICROPHONE
  // I2S.getMicrophones();

  // Start I2S with I2S_PHILIPS_MODE, 11 kHz sampling rate and 20 bits per sample
  // Returns 0 if everything okay, otherwise value > 0
  I2S.begin(I2S_PHILIPS_MODE, 11000, 20);
}

void loop()
{
  // I2S is very demanding in terms of data rate
  // Uncomment the line with I2S.getOverflow() to see whether the internal buffer has an overflow or not
  while (I2S.available() > 0)
  {
    // Read one value from the internal buffer and return it on the serial console
    Serial.println(I2S.read());
    // if(I2S.getOverflow() == true) Serial.println("Overflow");
  }
  // You can always use I2S.peek() to get the latest value
  // With I2S.flush(), you will read once the buffer size (if values are inserted faster, this will not empty the buffer)
}
