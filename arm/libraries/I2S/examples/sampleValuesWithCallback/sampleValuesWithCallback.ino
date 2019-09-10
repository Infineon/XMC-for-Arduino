#include <I2S.h>

/*
 * This example reads audio data from Infineon's IM69D130 Microphone Shield2Go 
 * and prints it on the serial monitor - additionally, it uses a custom callback
 * to show how to distinguish between the peeked values for LOW and HIGH word select.
 * 
 * Open the serial monitor with baudrate of 1000000 to see the results.
 * 
 * Note: as 2 channels are used, the values returned from I2S.read() will be from both channels and thus look noisy
 * In this case, both values need to be separated.
 */

volatile int32_t lastValueLow = 0;
volatile int32_t lastValueHigh = 0; 

void customCallback(){
  if(I2S.getSampleInformation() == NO_MICROPHONE) return;

  if(I2S.getSampleInformation() == MICROPHONE_LOW){
    lastValueLow = I2S.peek();
  }
  if(I2S.getSampleInformation() == MICROPHONE_HIGH){
    lastValueHigh = I2S.peek();
  }
}

void setup()
{
  Serial.begin(1000000);
  Serial.println("Begin of I2S microphone");
  // Disable all microphones
  I2S.disableMicrophones();
  // Enable the microphone in stereo mode
  I2S.enableMicrophoneLow();
  I2S.enableMicrophoneHigh();

  // Register the custom callback function
  I2S.onReceive(customCallback);

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
  // Print the peeked values from the defined callback
  Serial.println("Last peeked value for LOW");
  Serial.println(lastValueLow);
  Serial.println("Last peeked value for HIGH");
  Serial.println(lastValueHigh);
}