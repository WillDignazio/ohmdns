#include <stdio.h>
#include "internal.h"

#if 0
static void
printbn(uint64_t val, int bits)
{
	int bit;
	
	for(bit=0;bit<bits;bit++) {
		printf("%llu", val & 0x1);
		val >>= 1;
	}
	printf("\n");
}
#endif

int
main(int argc, char* argv[])
{

	return 0;
}
