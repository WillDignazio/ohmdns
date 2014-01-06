#ifndef __packet__
#define __packet__

#include <stdint.h>
typedef struct IPv4Header IPv4Header;
typedef struct UDPPacket UDPPacket;
typedef struct MDNSPacket MDNSPacket;

#pragma pack(push)
#pragma pack(1) // Aligment to 1 byte boundary

/* IPv4 Header */
struct IPv4Header
{
	uint8_t		version : 4;	// Version
	uint8_t		ihl : 4;	// Internet Header Length
	uint8_t 	dscp : 6;	// Differentiated Services Code Point
	
	uint16_t	length;		// Total (Fragment) Size
	uint16_t	ident;		// Identification
	uint8_t		flags : 3;	// Control identification flags
	uint32_t	frag_off : 20;	// Fragment Offset
	uint8_t		ttl;		// Time to live
	uint8_t		prot;	       	// Protocol
	uint16_t	checksum;	// Checksum
	
	uint32_t	src_addr;	// Source Address
	uint32_t	dst_addr;	// Destination Address
	
	uint32_t	options;	// Padding (for IHL > 5)
};

/*
 * UDP Packet Structures 
 */
struct  UDPPacket
{
	uint16_t	src_port;	// Source Port
	uint16_t	dest_port;	// Destination Port
	uint16_t	length;		// Length
	uint16_t	checksum;	// Checksum
};

struct MDNSPacket
{
	uint16_t	id;		// ID

	union
	{
		uint16_t field;
		struct
		{
			uint8_t	qr;		// Query Response
			uint8_t	opcode : 4; 	// Request operation type
			uint8_t	aa : 1;		// Authoritative Answer;
			uint8_t	tc : 1;		// Truncation
			uint8_t rd : 1; 	// Recursion Desired
			uint8_t rcode : 4;	// Response Type
		} flag;
	} flags;

	uint16_t	qdcount;	// # of items in Question ection
	uint16_t	ancount;	// # of items in Answer section
	uint16_t	nscount;	// # of items in Authority section
	uint16_t	arcount;	// # of items in additional section
};

#pragma pack(pop)

extern IPv4Header*	packet_alloc_header(Error* err);
extern UDPPacket*	packet_alloc_udp_packet(Error* err);
extern MDNSPacket*	packet_alloc_mdns_packet(Error* err);
extern void		packet_free_header(IPv4Header* header);
extern void		packet_free_udp_packet(UDPPacket* packet);
extern void		packet_free_mdns_packet(MDNSPacket* packet);

#endif
