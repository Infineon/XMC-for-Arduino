# The Radar Library for Infineon's 24GHz Radar Series 

This library offers support for Infineon's [24GHz Radar Series](https://www.infineon.com/cms/en/product/sensor/radar-sensor-ics/24ghz-radar/).  

## Status
- [x] Sense2GoL
- [ ] Distance2Go
- [ ] Position2Go

## Interfaces
- [x] RadarDataProcessor<br/>
  Several algorithms are implemented to process raw data from the radar. The following functions can be called to enable/disable these algorithms:
  ```
  void enableSimpleMotionDetection();
  void enableFftMotionDetection();
  void disableMotionDetection();
  void enableFft();
  void disableFft();
  ```
  - [x] motion detection<br/>
    Motion detection (approaching & departing) is implemented based on the phase shift. `enableSimpleMotionDetection` runs the algorithm based on comparing wav shapes of I and Q data, whereas `enableFftMotionDetection` is based on the phase difference of the FFT peaks of I and Q data.
  - [x] speed detection<br/>
    FFT peak frequency is proportional to the doppler speed.
- [x] BGTRadar<br/>
  Defines radar configurations and parameters for algorithms (different radars might have different data formats)
  - [x] BGT24LTR11 (Sense2GoL)
- [ ] Communication Library

## Usage
The examples can be either compiled on the original board, or redirected to another board via the **IF_I_HG** and **IF_Q_HG** pins.

![Pin Layout](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Sense2GoL.png)

If you want to do this, please follow these steps:
- Flash the following sketch to Sense2GoL board
  ```
  // Turn on the radar chip; select board to be XMC1300 Sense2GoL
  void setup()
  {
    pinMode(BGT_ON, OUTPUT);
    digitalWrite(BGT_ON, LOW);
  }
  
  void loop()
  {
  }
  ```
- Power off the radar board and connect it with the XMC4700 relax kit (the one I used for testing). 
   Relax Kit needs to output 5V (find **IOREF** on the board and put the bridge over **VDD5**). In addition to **GND** & **VCCIN**, also connect **IF_I_HG** to **P14.0** and **IF_Q_HG** to **P14.1**. **P14.0** and **P14.1** are analog input 1 and 2, see also the following definitions in the file `BGT24LTR11.h`.
  ```
  #define CH_I A0
  #define CH_Q A1
  ```
- Flash the relax kit with the examples.

## Known Issues
- XMC1300 board has limitations when doing floating-point calculation.

## Additional Information
See also our [Wiki](https://github.com/Infineon/XMC-for-Arduino/wiki/Core-Libraries) and doxygen-generated [documentation page](https://github.com/Infineon/InfineonDoxyGenerator).