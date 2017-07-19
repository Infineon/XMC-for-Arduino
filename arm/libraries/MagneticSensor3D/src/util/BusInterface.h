#ifndef TLV493D_BUSIF_H_INCLUDED
#define TLV493D_BUSIF_H_INCLUDED

#include <Arduino.h>
#include <Wire.h>

#define TLV493D_BUSIF_READSIZE		10
#define TLV493D_BUSIF_WRITESIZE		4

namespace tlv493d
{

typedef struct 
{
	TwoWire *bus;
	uint8_t adress;
	uint8_t regReadData[TLV493D_BUSIF_READSIZE];
	uint8_t regWriteData[TLV493D_BUSIF_WRITESIZE];
} BusInterface_t;

}

#endif