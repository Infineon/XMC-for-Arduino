#include <I2S.h>

/*
 * This example reads audio data from Infineon's IM69D130 Microphone Shield2Go 
 * and processes it to provide feedback based on the sound pressure level.
 * 
 * Open the serial plotter with baudrate of 1000000 and make noise to see the results.
 *
 * It is based on an example published by Sandeep Mistry (https://github.com/sandeepmistry)
 */

void setup()
{
    // Open serial communication with a baudrate of 1000000
    Serial.begin(1000000);
    // Wait until the serial port is connected
    while (!Serial);

    I2S.disableMicrophones();
    // Enable the microphone when word select is low
    I2S.enableMicrophoneLow();

    // Start I2S at 11 kHz with 20 bits per sample
    if (I2S.begin(I2S_PHILIPS_MODE, 11000, 20) != 0)
    {
        Serial.println("Failed to initialize I2S!");
        // Do nothing and wait
        while (true);
    }
}

void loop()
{
    // Array to store the samples
    int samples[128];
    if (I2S.available() > 128)
    {
        // Read 128 samples into the array
        I2S.read(samples, 128);

        float meanValue = 0;
        for (int i = 0; i < 128; i++)
        {
            meanValue += samples[i];
        }
        meanValue /= 128;

        // Substract it from all samples to normalize output
        for (int i = 0; i < 128; i++)
        {
            samples[i] -= meanValue;
        }

        // Get the peak to peak maximum
        float maxSample, minSample;
        minSample = 100000;
        maxSample = -100000;
        for (int i = 0; i < 128; i++)
        {
            minSample = min(minSample, samples[i]);
            maxSample = max(maxSample, samples[i]);
        }
        Serial.println(maxSample - minSample);
    }
}
