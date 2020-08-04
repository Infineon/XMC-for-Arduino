# On Board LED Library Description

| | | |
|:---|:---:|:---|
**Author** | : | Paul Carpenter
 | | | PC Services
 | | | www.pcserviceselectronics.co.uk
**Version** | : | V1.00
**Date** | : | July 2018

Infineon XMC-for-Arduino RTC Library, to assist in making board agnostic examples that
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

| Board | ON state |
| :----  | :---: |
 XMC1100 Boot Kit | Low
 XMC1100 XMC2GO | High
 XMC1100 XMC H Bridge2GO | High
 XMC1300 Boot Kit  | Low
 XMC1300 Sense2GOL | Low
 XMC4700 Relax Kit | Low

[Back to top](#table-of-contents)
### LEDs on Different Boards
Matrix of available on board LED names or LED they map to, known currently.

| LED Macro | XMC1100<BR>Boot Kit | XMC1100<BR>XMC2GO | XMC1100<BR>HBRIDGE2GO | XMC1300<BR>Boot Kit | XMC1300<BR>Sense2GOL | XMC4700<BR>Relax |
| --- | :--: | :--: | :--: | :--: | :--: | :--: |
 LED_BUILTIN | Y | LED1 | LED1 | LED1 | LED1 | LED1
 LED1 | Y | Y | Y | Y | Y | Y 
 LED2 | Y | Y | Y | Y | Y | Y 
 LED3 | Y | - | - | Y | Y | - 
 LED4 | Y | - | - | Y | - | - 
 LED5 | Y | - | - | Y | - | - 
 LED5 | Y | - | - | Y | - | - 

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
This example simply 
- In setup() sets up two LEDs
- In loop()
    - Waits one second 
    - Toggles LED1 
    - Turns Off LED2

[Back to top](#table-of-contents)
