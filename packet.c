#include <stdint.h>
#include <stdlib.h>
#include "internal.h"

IPv4Header*
ohm_alloc_header(Error* err)
{
	IPv4Header* header;
	
	header = malloc(sizeof(*header));
	if(header == NULL) {
		error_host(err);
		return NULL;
	}

	return header;
}

void
ohm_free_header(IPv4Header* header)
{
	if(header == NULL)
		return;

	free(header);
}

UDPPacket*
ohm_alloc_udp_packet(Error* err)
{
	UDPPacket* udpp;

	udpp = malloc(sizeof(*udpp));
	if(udpp == NULL) {
		error_host(err);
		return NULL;
	}

	return udpp;
}

void
ohm_free_udp_packet(UDPPacket* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}

MDNSPacket*
ohm_alloc_mdns_packet(Error* err)
{
	MDNSPacket* packet;
	
	packet = malloc(sizeof(*packet));
	if(packet == NULL) {
		error_host(err);
		return NULL;
	}

	return packet;
}

void
ohm_free_mdns_packet(MDNSPacket* packet)
{
	if(packet == NULL)
		return;

	free(packet);
}
