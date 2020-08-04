# Multiple Serial Ports Examples

Simple examples that use multiple serial ports of XMC boards. Uses internal functions without requiring extra libraries.

| | | |
|:---|:---:|:---|
**Author** | : | Paul Carpenter
 | | | PC Services
 | | | www.pcserviceselectronics.co.uk

## Examples
<table width="50%" align=center border=0>
 <tr>
   <td><b>Name</B></td>
   <td><b>Version</B></td>
   <td><b>Ports</B></td>
 </tr>
 <tr>
   <td>TwoPort</td>
   <td>V1.00</td>
   <td>Serial and Serial1</td>
 </tr>
</table> 
<br>

## Version History

| | | |
|:---|:---:|:---|
**Original** | : | V1.00
**Author** | : | Paul Carpenter
 | | | PC Services
 | | | www.pcserviceselectronics.co.uk
**Date** | : | February 2020
## Operation
All serial ports at 115,200 baud

If connecting other devices to serial ports it is your responsibility to make sure voltages match
### TwoPort Example
Receives from the main serial port (Serial), sends to serial port 1 (Serial1).

Receives from serial port 1 (Serial1), sends to the main serial port (Serial).

This example works only with boards with more than one serial like XMC4700 or others as 2 serial ports.

The circuit:
- Loopback RX to TX on Serial port 1 or another device
- Serial Monitor open on Serial port 0

In Loopback anything sent from Serial monitor or terminal window is echoed back after going via Serial 1. 
LEDs flash as data is received
- LED1 for Serial1
- LED2 for Serial (0)

LEDs toggle on each byte received on that port so two bytes for a flash.
