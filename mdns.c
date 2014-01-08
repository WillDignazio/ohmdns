#include <stdint.h>
#include <stdlib.h>
#include "internal.h"

MDNSPacket*
mdns_alloc_packet(Error* err)
{
	MDNSPacket* packet;
	
	packet = malloc(sizeof(*packet));
	if(packet == NULL) {
		esys(err, "Failed to allocate MDNS packet");
		return NULL;
	}

	return packet;
}

void
mdns_free_packet(MDNSPacket* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}
