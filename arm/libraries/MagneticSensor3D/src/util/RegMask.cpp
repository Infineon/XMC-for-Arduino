#include "RegMask.h"


uint8_t tlv493d::getFromRegs(const RegMask_t *mask, uint8_t *regData)
{
	return (regData[mask->byteAdress] & mask->bitMask) >> mask->shift;
}


uint8_t tlv493d::setToRegs(const RegMask_t *mask, uint8_t *regData, uint8_t toWrite)
{
	if(mask->rw == REGMASK_WRITE)
	{
		uint8_t regValue = regData[mask->byteAdress];
		regValue &= ~(mask->bitMask);
		regValue |= (toWrite << mask->shift) & mask->bitMask;
		regData[mask->byteAdress] = regValue;
	}
}



