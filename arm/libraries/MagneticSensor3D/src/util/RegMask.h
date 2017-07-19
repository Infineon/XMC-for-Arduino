#ifndef TLV493D_REGMASK_H_INCLUDED
#define TLV493D_REGMASK_H_INCLUDED

#include <Arduino.h>

#define REGMASK_READ	0
#define REGMASK_WRITE	1

namespace tlv493d
{

typedef struct
{
	uint8_t rw;
	uint8_t byteAdress;
	uint8_t bitMask;
	uint8_t shift;
} RegMask_t;

uint8_t getFromRegs(const RegMask_t *mask, uint8_t *regData);
uint8_t setToRegs(const RegMask_t *mask, uint8_t *regData, uint8_t toWrite);

}

#endif