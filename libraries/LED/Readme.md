# On Board LED Library Description

| | | |
|:---|:---:|:---|
**Author** | : | Paul Carpenter
 | | | PC Services
 | | | www.pcserviceselectronics.co.uk
**Version** | : | V1.0.4
**Updated** | : | March 2023
Date | : | July 2018

Infineon XMC-for-Arduino LED Library, to assist in making board agnostic examples that
will work the same across all boards. This file will be available in the library folder.

Often it is useful to have an example and have LED change state when things happen or
errors occur, so to make this easier it is better to use on board LEDs that will always
be there. Unfortunately if you are writing an example to use across many boards the
XMC boards do not all work the same way. This library enables examples or applications to
use the on board LEDs in the same way across all boards that any example supports. This
is encapsulating the LED drive primarily for easier use of on board LEDs in examples that
work on all or many of the boards.

## Table of Contents
This document consists of these sections
- [Hardware Differences](#hardware-differences-between-the-boards "Differences between the boards")
    - [LEDs on Different Boards](#leds-on-different-boards "What boards have what LEDs on")
- [Requirements for Adding New Boards](#requirements-for-adding-new-boards "How to add support for a new board")
- [Known Limitations](#known-limitations "Known Limitations of Libraries")
- [LED Library](#led-library)
   - [Functions/Methods](#functionsmethods "Functions/methods in the class")
- [Examples](#examples "List of current examples")
   - [Simple LED](#simple-led "Basic LED setup and writing")

## Hardware Differences between the boards
Unfortunately the on-board LEDs on the XMC range of boards work differently between different
models. There is no consistent, on board LED driven by the same state to be ON across all
models of board so we end up with

| Board | Normal LEDs <br>ON state | LED_BUILTIN <br>Separate |  LED_BUILTIN <br>ON state
| :----  | :---: | :---: | :---: |
 KIT_XMC11_BOOT_001 | Low | Yes | High
 KIT_XMC_2GO_XMC1100_V1 | High | No | High
 XMC1100 XMC H Bridge2GO | High| No | High
 KIT_XMC13_BOOT_001  | Low | No | Low
 XMC1300 Sense2GO | Low| No | Low
 KIT_XMC1400_ARDUINO | Low | Yes | High
 KIT_XMC_PLT2GO_XMC4200 | High| No | High
 KIT_XMC_PLT2GO_XMC4400 | High| No | High
 KIT_XMC47_RELAX | High| No | High

** NOTE ** After Version 2.0 of XMC-for-Arduino, some boards were dropped (e.g. XMC1300 Sense2GO) they are still shown here for those using old versions of XMC-for-Arduino, and for history.

[Back to top](#table-of-contents)
### LEDs on Different Boards
Matrix of available on board LED names or LED they map to, known currently.

| LED Macro | XMC1100 <BR>Boot Kit | XMC1100 <BR>XMC2GO | XMC1100 <BR>HBRIDGE2GO | XMC1300 <BR>Boot Kit | XMC1300 <BR>Sense2GO | XMC1400 <br>Arduino Kit | XMC4200 <br>Platform2Go | XMC4400 <br>Platform2Go | XMC4700 <BR>Relax Kit | XMC4700 <BR>Relax Kit Lite |
| --- | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
 LED_BUILTIN | Y | LED1 | LED1 | LED1 | LED1 | Y | LED1 | LED1 | LED1 | LED1
 LED1 | Y | Y | Y | Y | Y | Y | Y | Y | Y | Y
 LED2 | Y | Y | Y | Y | Y | Y | - | Y | Y | Y
 LED3 | Y | - | - | Y | Y | - | - | - | - | -
 LED4 | Y | - | - | Y | - | - | - | - | - | -
 LED5 | Y | - | - | Y | - | - | - | - | - | -
 LED6 | Y | - | - | Y | - | - | - | - | - | -

[Back to top](#table-of-contents)
## Requirements for Adding New Boards
Every board has to have its own pins_arduino.h, then so that this Library can distinguish the
operation this file must include a #define macro based on XMC_LED_ON as below -
~~~
/* On board LED is ON when digital output is 1, HIGH, TRUE, ON */
#define  XMC_LED_ON 1
~~~
**OR**
~~~
/* On board LED is ON when digital output is 0, LOW, False, OFF */
#define  XMC_LED_ON 0
~~~
[Back to top](#table-of-contents)
## Known Limitations
This is meant for controlling hardware on board LEDs on the XMC1 and XMC4 series, if your
additional LEDs operate the **same** way as the on board you can use the same functions but
this may not be portable when adding your hardware to other boards.

See [LEDs on Different Boards](#leds-on-different-boards "Number of LEDs on boards")

[Back to top](#table-of-contents)
## LED Library
All functions have a Arduino Pin reference passed in or a macro that defines it
e.g. LED1 or LED2.

Note at present all boards have **2** LEDs as a minimum some have 3 or 6 LEDs. Obviously only reference
LEDs that actually exist for the boards are supported.

This library uses NO RAM storage it is mainly software encapsulation/wrappers to other functions.

[Back to top](#table-of-contents)
### Functions/Methods
| Function || Description |
:--- | --- | :---
**Add** | - | Configure an On board LED as digital output
**On** | - | Turn on board LED ON
**Off** | - |  Turn on board LED OFF
**Toggle** | - | Toggle on board LED (if was off now on, if was on now off)

[Back to top](#table-of-contents)
#### Class Instantiation and Initialisation
In user application include the LED.h file, instantiate the class, in setup() later add the LEDs to the
class just initialises them to digital outputs.
~~~
/* For on board LEDs */
#include <LED.h>

/* Create an LED object */
LED Led;
~~~
Later in setup()
~~~
void setup( )
{
Led.Add( LED1 );               // Add LED (configure for output)
...
~~~

[Back to top](#table-of-contents)
## Examples
This is here for completeness of Arduino IDE library structure.
### Simple LED
This example works on all currently known boards simply
- In setup() sets up two LEDs
- In loop()
    - Waits one second
    - Toggles LED1
    - Turns Off LED2

If a board like **XMC4200 Platform2Go** with only **ONE** LED is in use **only LED1 function is used**

[Back to top](#table-of-contents)
