/*
  Mouse.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MOUSE_XMC_h
#define MOUSE_XMC_h

#include <Arduino.h>
#include <utilities/Descriptor.h>



//================================================================================
//================================================================================
//  Mouse

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

#define MS_OS_20_SET_HEADER_DESCRIPTOR 0x00
#define MS_OS_20_SUBSET_HEADER_CONFIGURATION 0x01
#define MS_OS_20_SUBSET_HEADER_FUNCTION 0x02
#define MS_OS_20_FEATURE_COMPATIBLE_ID 0x03
#define MS_OS_20_FEATURE_REG_PROPERTY 0x04
#define MS_OS_20_DESCRIPTOR_LENGTH 0xb2


const uint8_t MS_OS_20_DESCRIPTOR_PREFIX[] PROGMEM = {
// Microsoft OS 2.0 descriptor set header (table 10)
0x0A, 0x00,  // Descriptor size (10 bytes)
MS_OS_20_SET_HEADER_DESCRIPTOR, 0x00,  // MS OS 2.0 descriptor set header
0x00, 0x00, 0x03, 0x06,  // Windows version (8.1) (0x06030000)
MS_OS_20_DESCRIPTOR_LENGTH, 0x00,  // Size, MS OS 2.0 descriptor set

// Microsoft OS 2.0 configuration subset header
0x08, 0x00,  // Descriptor size (8 bytes)
 MS_OS_20_SUBSET_HEADER_CONFIGURATION, 0x00,  // MS OS 2.0 configuration subset header
0x00,        // bConfigurationValue
0x00,        // Reserved
0xA8, 0x00,  // Size, MS OS 2.0 configuration subset

// Microsoft OS 2.0 function subset header
0x08, 0x00,  // Descriptor size (8 bytes)
 MS_OS_20_SUBSET_HEADER_FUNCTION, 0x00,  // MS OS 2.0 function subset header
};

// First interface number (1 byte) sent here.

const uint8_t MS_OS_20_DESCRIPTOR_SUFFIX[] PROGMEM = {
0x00,        // Reserved
0xA0, 0x00,  // Size, MS OS 2.0 function subset

// Microsoft OS 2.0 compatible ID descriptor (table 13)
0x14, 0x00,  // wLength
MS_OS_20_FEATURE_COMPATIBLE_ID, 0x00,  // MS_OS_20_FEATURE_COMPATIBLE_ID
'W',  'I',  'N',  'U',  'S',  'B',  0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const uint8_t MS_OS_20_CUSTOM_PROPERTY[] PROGMEM = {
0x84, 0x00,   //wLength: 
MS_OS_20_FEATURE_REG_PROPERTY, 0x00,   // wDescriptorType: MS_OS_20_FEATURE_REG_PROPERTY: 0x04 (Table 9)
0x07, 0x00,   //wPropertyDataType: REG_MULTI_SZ (Table 15)
0x2a, 0x00,   //wPropertyNameLength: 
//bPropertyName: “DeviceInterfaceGUID”
'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00, 't', 0x00, 'e', 0x00, 
'r', 0x00, 'f', 0x00, 'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00, 'U', 0x00, 'I', 0x00, 'D', 0x00, 's', 0x00, 
0x00, 0x00,
0x50, 0x00,   // wPropertyDataLength
//bPropertyData: “{975F44D9-0D08-43FD-8B3E-127CA8AFFF9D}”.
'{', 0x00, '9', 0x00, '7', 0x00, '5', 0x00, 'F', 0x00, '4', 0x00, '4', 0x00, 'D', 0x00, '9', 0x00, '-', 0x00, 
'0', 0x00, 'D', 0x00, '0', 0x00, '8', 0x00, '-', 0x00, '4', 0x00, '3', 0x00, 'F', 0x00, 'D', 0x00, '-', 0x00, 
'8', 0x00, 'B', 0x00, '3', 0x00, 'E', 0x00, '-', 0x00, '1', 0x00, '2', 0x00, '7', 0x00, 'C', 0x00, 'A', 0x00, 
'8', 0x00, 'A', 0x00, 'F', 0x00, 'F', 0x00, 'F', 0x00, '9', 0x00, 'D', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00
};
class MouseClass
{
	private:
	  uint8_t _buttons;
	  void buttons(uint8_t b);
	  void init();
	  void setupClock();
	  void SendReport(void);


	public:
	  MouseClass(void);
	  void begin(void);
	  void end(void);
	  void click(uint8_t b = MOUSE_LEFT);
	  void move(signed char x,  signed char y, signed char wheel = 0);
	  void press(uint8_t b = MOUSE_LEFT);   // press LEFT by default
	  void release(uint8_t b = MOUSE_LEFT); // release LEFT by default
	  bool isPressed(uint8_t b = MOUSE_LEFT); // check LEFT by default
};
extern int8_t mouse_data[3];
extern MouseClass Mouse;
#endif

