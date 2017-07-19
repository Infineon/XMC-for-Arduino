#include "BusInterface2.h"


void tlv493d::initInterface(BusInterface_t *interface, TwoWire *bus, uint8_t adress)
{
	uint8_t i;
	interface->bus = bus;
	interface->adress = adress;
	for(i = 0; i < TLV493D_BUSIF_READSIZE; i++) {
		interface->regReadData[i] = 0x00;;
	}
	for(i = 0; i < TLV493D_BUSIF_WRITESIZE; i++) {
		interface->regWriteData[i] = 0x00;;
	}
}

void tlv493d::readOut(BusInterface_t *interface)
{
	readOut(interface, TLV493D_BUSIF_READSIZE);
}

void tlv493d::readOut(BusInterface_t *interface, uint8_t count)
{
	int i;
	if(count > TLV493D_BUSIF_READSIZE)
	{
		count = TLV493D_BUSIF_READSIZE;
	}
	interface->bus->requestFrom(interface->adress,count);
	for(i = 0; i < count; i++)
	{
		interface->regReadData[i] = interface->bus->read();
	}
}

void tlv493d::writeOut(BusInterface_t *interface)
{
	writeOut(interface, TLV493D_BUSIF_WRITESIZE);
}

void tlv493d::writeOut(BusInterface_t *interface, uint8_t count)
{
	int i;
	if(count > TLV493D_BUSIF_WRITESIZE)
	{
		count = TLV493D_BUSIF_WRITESIZE;
	}
	interface->bus->beginTransmission(interface->adress);
	for(i = 0; i < count; i++)
	{
		interface->bus->write(interface->regWriteData[i]);
	}
	interface->bus->endTransmission();
}

