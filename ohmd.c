#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
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
	unsigned char buffer[4096];

	sock = ohm_alloc_socket(&err);
	ohm_open_socket(5353, "0.0.0.0", sock, &err);

	MDNSPacket* packet;
	packet = (MDNSPacket*)&buffer;

	for(;;) {
		int rb = read(sock->sfd, buffer, sizeof(buffer));
		printf("read %d bytes\n", rb);
		
		/* Here We Go */
		printf("packet id: %hu\n", ntohs(packet->id));
		printf("packet qdcount: %hu\n", ntohs(packet->qdcount));
		printf("FQDN: %s\n", (char*)&buffer+sizeof(MDNSPacket));
	}

	ohm_close_socket(sock, &err);
	return 0;
}
