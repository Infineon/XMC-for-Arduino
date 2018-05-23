Ultrasonic Examples based on using common HC-SR04
=================================================

Simple examples that use various timing functions of XMC boards to measure
distances. Uses internal functions without requiring extra libraries.

Based on public domain code from
http://www.pcserviceselectronics.co.uk/arduino/Ultrasonic/simpleecho.php

Paul Carpenter, PC Services
24-Jan-2017

Uses HC-SR04 four pin ultrasonic sensor to continuously output
distances found when in range (every second).

Results output onto serial port at 115,200 baud

Attached hardware
    HC-SR04 5V and GND connected to pins on board
      default Trigger pin connected to pin 5
              Echo pin connected to pin 4

Works on principle sound travels at 343 m/s in dry air at 20 deg C

So time per cm is 29.15452 micro seconds / cm

For round trip (there and back)  58.30904 micro seconds / cm

simple-echo uses PulseIn function with limited error reporting
betterecho  uses micros( ) function and has more error reporting
