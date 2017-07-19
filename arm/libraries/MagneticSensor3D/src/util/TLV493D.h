/*
 *	Arduino library to control Infineon's Magnetic 3D Sensor TLV493D-A1B6
 *
 *	Have a look at the datasheet for more information. 
 */


#ifndef TLV493D_H_INCLUDED
#define TLV493D_H_INCLUDED

namespace tlv493d
{

typedef struct
{
	uint8_t fast;
	uint8_t lp;
	uint8_t lpPeriod;
	uint16_t measurementTime;
} AccessMode_t;

}

#endif		/* MAGNETICSENSOR3D_UTIL_H_INCLUDED */


