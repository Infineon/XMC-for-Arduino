#ifndef TLV493D_BUSIF_2_H_INCLUDED
#define TLV493D_BUSIF_2_H_INCLUDED

#include "BusInterface.h"

namespace tlv493d
{
	
void initInterface(BusInterface_t *interface, TwoWire *bus, uint8_t adress);
void readOut(BusInterface_t *interface);
void readOut(BusInterface_t *interface, uint8_t count);
void writeOut(BusInterface_t *interface);
void writeOut(BusInterface_t *interface, uint8_t count);

}

#endif