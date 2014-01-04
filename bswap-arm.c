#include <stdint.h>
#include "internal.h"

/*
 * XXX: Only for 32 Bit ARM instructions,
 * how will we deal with 64 bit ones?
 */
#pragma arm

uint64_t
bswap64(uint64_t bin)
{
	uint32_t* bptr;

	bptr = (uint32_t*)&bin;
	asm("rbit r0, %[value]" : : [value] "r" (bptr[0]));
	asm("rbit r1, %[value]" : : [value] "r" (bptr[1]));

	/* Swap the registers to finalize the endian change */
	asm("mov %[result], r0" : [result] "=r" (bptr[1]));
	asm("mov %[result], r1" : [result] "=r" (bptr[0]));

	return bin;
}

uint32_t
bswap32(uint32_t bin)
{
	asm("rbit %[result], %[value]" : [result] "=r" (bin) : [value] "r" (bin));
	return  bin;
}

uint16_t
bswap16(uint16_t bin)
{
	uint8_t* bptr;

	bptr = (uint8_t*)&bin;
	/* Promoted to word on use, rev-ed and replaced */
	asm("rbit r0, %[value]" : : [value] "r" (bin));
	asm("rev r0, r0");
	asm("rev16 %[result], r0" : [result] "=r" (bin));

       	return bin;
}
