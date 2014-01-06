#include <stdint.h>
#include <stdlib.h>
#include "internal.h"

IPv4Header*
packet_alloc_ip4_header(Error* err)
{
	IPv4Header* header;
	
	header = malloc(sizeof(*header));
	if(header == NULL) {
		esys(err, "Failed to allocate header");
		return NULL;
	}

	return header;
}

void
packet_free_ip4_header(IPv4Header* header)
{
	if(header == NULL)
		return;

	free(header);
}

UDPHeader*
packet_alloc_udp_header(Error* err)
{
	UDPHeader* udpp;

	udpp = malloc(sizeof(*udpp));
	if(udpp == NULL) {
		esys(err, "Failed to allocate UDP packet");
		return NULL;
	}

	return udpp;
}

void
packet_free_udp_header(UDPHeader* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}

MDNSPacket*
packet_alloc_mdns(Error* err)
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
packet_free_mdns(MDNSPacket* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}
