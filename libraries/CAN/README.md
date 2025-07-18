This is an Arduino library for XMC boards using CAN bus to send and receive data.

Based on [Arduino CAN library](https://www.arduino.cc/reference/en/libraries/can/)/ [Github Repo](https://github.com/sandeepmistry/arduino-CAN)

# Hardware Setup

XMC boards with CAN support (CAN transceiver on board and CAN controller module): KIT_XMC_PLT2GO_XMC4200, KIT_XMC_PLT2GO_XMC4400, KIT_XMC47_RELAX and KIT_XMC14_2GO.

| Board Name               | Onboard CAN | Termination Resistor |
|--------------------------|-------------|-----------------------|
| KIT_XMC14_2GO           | Yes         | Yes (120 ohm)        |
| KIT_XMC_PLT2GO_XMC4200  | Yes         | No                   |
| KIT_XMC_PLT2GO_XMC4400  | Yes         | Yes (120 ohm)        |
| KIT_XMC47_RELAX         | Yes         | No                   |

All CAN nodes should be connected using the (twisted) pair cable for the CAN_H and CAN_L

# Software Usage

There are [examples](libraries/CAN/examples). See the API definition below for more details.

# CAN API

Here the API definition is based on:

- [:warning: XMC specification](#warning-xmc-specification)
  * [Set device id](#set-device-id)
- [Include Library](#include-library)
- [Setup](#setup)
  * [Begin](#begin)
  * [Set pins](#set-pins)
  * [End](#end)
- [Sending data](#sending-data)
  * [Begin packet](#begin-packet)
  * [Writing](#writing)
  * [End packet](#end-packet)
- [Receiving data](#receiving-data)
  * [Parsing packet](#parsing-packet)
  * [Register callback](#register-callback)
  * [Packet ID](#packet-id)
  * [Packet Extended](#packet-extended)
  * [Packet RTR](#packet-rtr)
  * [Packet DLC](#packet-dlc)
  * [Available](#available)
  * [Peeking](#peeking)
  * [Reading](#reading)
  * [Filtering](#filtering)
- [Other modes](#other-modes)
  * [Loopback mode](#loopback-mode)
  * [Sleep mode](#sleep-mode)
  
## :warning: XMC specification

Due to the different behavior of xmc4000 series and xmc1000 series, the library and provided examples was tested primarily on **KIT_XMC14_2GO**.

The known difference is that the XMC4 is unable to receive CAN messages for all IDs. Therefore, it is necessary to define the device ID using the following function:

### Set device id

```arduino
  CAN.setDeviceId(id);
```
 * `id` - 11 bits standard id of the device. (default: `0xFF`)




## Include Library
```arduino
#include <CAN.h>
```

## Setup

### Begin

Initialize the library with the specified bit rate.

```arduino
CAN.begin(bitrate);
```
 * `bitrate` - bit rate in bits per seconds (bps) (`1000E3`, `500E3`(default), `250E3`, `200E3`, `125E3`, `100E3`, `80E3`, `50E3`, `40E3`, `20E3`, `10E3`, `5E3`)

Returns `1` on success, `0` on failure.

### Set pins

The RX and TX pins are determined. 


### End

Stop the library

```arduino
CAN.end()
```


## Sending data

### Begin packet

Start the sequence of sending a packet.

```arduino
CAN.beginPacket(id);
CAN.beginPacket(id, dlc);
CAN.beginPacket(id, dlc, rtr);

CAN.beginExtendedPacket(id);
CAN.beginExtendedPacket(id, dlc);
CAN.beginExtendedPacket(id, dlc, rtr);
```

 * `id` - 11-bit id (standard packet) or 29-bit packet id (extended packet)
 * `dlc` - (optional) value of Data Length Code (DLC) field of packet, default is size of data written in packet
 * `rtr` - (optional) value of Remote Transmission Request (RTR) field of packet (`false` or `true`), defaults to `false`. RTR packets contain no data, the DLC field of the packet represents the requested length.

Returns `1` on success, `0` on failure.

### Writing

Write data to the packet. Each packet can contain up to 8 bytes.

```arduino
CAN.write(byte);

CAN.write(buffer, length);
```
* `byte` - single byte to write to packet

or

* `buffer` - data to write to packet
* `length` - size of data to write

Returns the number of bytes written.

**Note:** Other Arduino `Print` API's can also be used to write data into the packet

### End packet

End the sequence of sending a packet.

```arduino
CAN.endPacket()
```

Returns `1` on success, `0` on failure.

## Receiving data

### Parsing packet

Check if a packet has been received.

```arduino
int packetSize = CAN.parsePacket(id);
```
 * `id` - 11-bit id (standard packet) or 29-bit packet id (extended packet)

Returns the packet size in bytes or `0` if no packet was received. For RTR packets the size reflects the DLC field of the packet.

### Register callback

Register a callback function for when a packet is received.

```arduino
CAN.onReceive(onReceive);

void onReceive(int packetSize) {
 // ...
}
```

 * `onReceive` - function to call when a packet is received.

### Packet ID

```arduino
long id = CAN.packetId();
```

Returns the id (11-bit or 29 bit) of the received packet. Standard packets have an 11-bit id, extended packets have an 29-bit id.


### Packet Extended

```arduino
bool extended = CAN.packetExtended();
```

Returns `true` if the received packet is extended, `false` otherwise.

### Packet RTR

```arduino
bool rtr = CAN.packetRtr();
```

Returns the value of the Remote Transmission Request (RTR) field of the packet `true`/`false`. RTR packets contain no data, the DLC field is the requested data length.

### Packet DLC

```arduino
int DLC = CAN.packetDlc();
```

Returns the value of the Data Length Code (DLC) field of the packet.


### Available

```arduino
int availableBytes = CAN.available()
```

Returns number of bytes available for reading.

### Peeking

Peek at the next byte in the packet.

```arduino
int b = CAN.peek();
```

Returns the next byte in the packet or `-1` if no bytes are available.

### Reading

Read the next byte from the packet.

```arduino
int b = CAN.read();
```

Returns the next byte in the packet or `-1` if no bytes are available.

**Note:** Other Arduino [`Stream` API's](https://www.arduino.cc/en/Reference/Stream) can also be used to read data from the packet


### Filtering

Filter packets that meet the desired criteria.

```
CAN.filter(id);
CAN.filter(id, mask);

CAN.filterExtended(id);
CAN.filterExtended(id, mask);
```

 * `id` - 11-bit id (standard packet) or 29-bit packet id (extended packet)
 * `mask` - (optional) 11-bit mask (standard packet) or 29-bit mask (extended packet), defaults to `0x7ff` or `0x1fffffff` (extended)

Only packets that meet the following criteria are acknowleged and received, other packets are ignored:

```
if ((packetId & mask) == id) {
  // acknowleged and received
} else {
  // ignored
}
```

Returns `1` on success, `0` on failure.


## Other modes

### Loopback mode

Put the CAN controller in loopback mode, any outgoing packets will also be received.

```arduino
CAN.loopback();
```

### Sleep mode

Put the CAN contoller in sleep mode.

```arduino
CAN.sleep();
```

Wake up the CAN contoller if it was previously in sleep mode.

```arduino
CAN.wakeup();
```
