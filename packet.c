#include <stdint.h>
#include <stdlib.h>
#include "internal.h"

IPv4Header*
packet_alloc_header(Error* err)
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
packet_free_header(IPv4Header* header)
{
	if(header == NULL)
		return;

	free(header);
}

UDPPacket*
packet_alloc_udp_packet(Error* err)
{
	UDPPacket* udpp;

	udpp = malloc(sizeof(*udpp));
	if(udpp == NULL) {
		esys(err, "Failed to allocate UDP packet");
		return NULL;
	}

	return udpp;
}

void
packet_free_udp_packet(UDPPacket* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}

MDNSPacket*
packet_alloc_mdns_packet(Error* err)
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
packet_free_mdns_packet(MDNSPacket* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}
