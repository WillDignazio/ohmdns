#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
	OhmSocket* sock;
	Error err;

	sock = ohm_alloc_socket(&err);
	ohm_open_socket(5353, "0.0.0.0", sock, &err);
	/* Do Work */
	ohm_close_socket(sock, &err);
	return 0;
}
