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
	int r;

	sock = ohm_alloc_socket(&err);
	if(sock == NULL) {
		fprintf(stderr, "%s\n", err.estr);
		exit(1);
	}

	r = ohm_open_socket(5555, sock, &err);
	if(r == -1) {
		fprintf(stderr, "%s\n", err.estr);
		exit(1);
        }

	r = ohm_close_socket(sock, &err);
	if(r == -1) {
		fprintf(stderr, "%s\n", err.estr);
		exit(1);
	}

	return 0;
}
