#ifndef __bswap__
#define __bswap__

/*
 * Yes, I know there are GNU __builtin craps 
 * that I can use. However, it's easy enough to 
 * write native routines that I think it worth it
 * to just write my own. This is primarily because I can 
 * gaurantee an efficient implementation that I am 
 * in control of.
 */

extern uint64_t	bswap64(uint64_t bin);
extern uint32_t bswap32(uint32_t bin);
extern uint16_t bswap16(uint16_t bin);


#endif
