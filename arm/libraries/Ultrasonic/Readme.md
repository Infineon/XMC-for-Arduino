# Ultrasonic Examples based on using common HC-SR04

Simple examples that use various timing functions of XMC boards to measure
distances. Uses internal functions without requiring extra libraries.

## Based on public domain code from
[Simple Echo](http://www.pcserviceselectronics.co.uk/arduino/Ultrasonic/simpleecho.php "Simple echo form for Arduino")
and [Better Echo](http://www.pcserviceselectronics.co.uk/arduino/Ultrasonic/betterecho.php "Better echo form for Arduino")
## Version History

| | | |
|:---|:---:|:---|
**Author** | : | Paul Carpenter
 | | | PC Services
 | | | www.pcserviceselectronics.co.uk
**Version** | : | V1.01
**Date** | : | July 2018

Updated to include better on board LED operation across all boards and Readme file to markdown

| | | |
|:---|:---:|:---|
**Original** | : | V1.00
**Author** | : | Paul Carpenter
 | | | PC Services
 | | | www.pcserviceselectronics.co.uk
**Date** | : | 24-Jan-2017

Uses HC-SR04 four pin ultrasonic sensor to continuously output
distances found when in range (every second).

Results output onto serial port at 115,200 baud

Attached hardware
- HC-SR04 5V and GND connected to pins on board
- Trigger pin connected to pin 5
- Echo pin connected to pin 4

**For 3V3 operated boards find a way to get 5V from USB to HC-SR04 and convert the Echo
pin at 5V down to 3V3.**

Works on principle sound travels at 343 m/s in dry air at 20 deg C

So time per cm is 29.15452 micro seconds / cm

For round trip (there and back)  58.30904 micro seconds / cm

| || |
| --- | :--: | --- |
 simple-echo | - | uses PulseIn function with limited error reporting
 betterecho  | - | uses micros( ) function and has more error reporting
   || | utilises on board LEDs for reading too close or too far away


