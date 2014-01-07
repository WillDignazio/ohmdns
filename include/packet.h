#ifndef __packet__
#define __packet__

#include <stdint.h>
typedef struct IPv4Header IPv4Header;
typedef struct UDPHeader UDPHeader;
typedef struct MDNSPacket MDNSPacket;

#pragma pack(push)
#pragma pack(1) // Aligment to 1 byte boundary

/* IPv4 Header */
struct IPv4Header
{
	uint8_t		version : 4;	// Version
	uint8_t		ihl : 4;	// Internet Header Length
	uint8_t 	dscp : 6;	// Differentiated Services Code Point
	uint8_t		ecn : 2;	// Explicit Congestion Notification

	uint16_t	length;		// Total (Fragment) Size
	uint16_t	ident;		// Identification
	uint8_t		flags : 3;	// Control identification flags
	uint16_t	frag_off : 13;	// Fragment Offset
	uint8_t		ttl;		// Time to live
	uint8_t		prot;	       	// Protocol
	uint16_t	checksum;	// Checksum

	uint32_t	src_addr;	// Source Address
	uint32_t	dst_addr;	// Destination Address
	uint32_t	options;	// Padding (for IHL > 5)
};

/* UDP Header */
struct  UDPHeader
{
	uint16_t	src_port;	// Source Port
	uint16_t	dst_port;	// Destination Port
	uint16_t	length;		// Length
	uint16_t	checksum;	// Checksum
};

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

extern IPv4Header*	packet_alloc_ip4_header(Error* err);
extern UDPHeader*	packet_alloc_udp_header(Error* err);
extern MDNSPacket*	packet_alloc_mdns(Error* err);
extern void		packet_free_ip4_header(IPv4Header* header);
extern void		packet_free_udp_header(UDPHeader* packet);
extern void		packet_free_mdns(MDNSPacket* packet);

#endif
