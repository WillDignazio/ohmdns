#ifndef __packet__
#define __packet__

#include <stdint.h>
typedef struct IPv4Header IPv4Header;
typedef struct UDPHeader UDPHeader;
typedef struct MDNSPacket MDNSPacket;

#pragma pack(push)
#pragma pack(1) // Aligment to 1 byte boundary

/* MDNS Packet */
struct MDNSPacket
{
	uint16_t	id;		// ID
	uint16_t	flags;		// Flags
	uint16_t	qdcount;	// # of items in Question ection
	uint16_t	ancount;	// # of items in Answer section
	uint16_t	nscount;	// # of items in Authority section
	uint16_t	arcount;	// # of items in additional section
};

#pragma pack(pop)

extern MDNSPacket*	mdns_alloc_packet(Error* err);
extern void		mdns_free_packet(MDNSPacket* packet);

#endif
