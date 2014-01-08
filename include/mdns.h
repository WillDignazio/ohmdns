#ifndef __packet__
#define __packet__

#include <stdint.h>
typedef struct IPv4Header IPv4Header;
typedef struct UDPHeader UDPHeader;
typedef struct MDNSPacket MDNSPacket;

#pragma pack(push)
#pragma pack(1) // Aligment to 1 byte boundary


/* MDNS Packet Flag Masks */
enum
{
	MDNS_OPT_RESP	= 1 << 0,
	MDNS_OPT_AUTH	= 1 << 5,
	MDNS_OPT_TRUNC	= 1 << 6,
	MDNS_OPT_RECURD	= 1 << 7,
	MDNS_OPT_RECURA	= 1 << 8,
	MDNS_OPT_VERIFY	= 1 << 10,
	MDNS_OPT_CHECK	= 1 << 11,
};

/* MDNS Packet */
struct MDNSPacket
{
	uint16_t	id;		// ID
	
	union
	{
		uint16_t	flags;	// Flags bitfield
		struct
		{
			uint8_t	qr : 1; // Query Response
			uint8_t op : 4; // Opcode
			uint8_t aa : 1; // Authoritative
			uint8_t	tc : 1; // Truncated
			uint8_t	rd : 1; // Recursion Desired
			uint8_t	ra : 1; // Recursion Accepted
			uint8_t zo : 1; // Zero XXX: Must be zero
			uint8_t ad : 1; // Authentic Data
			uint8_t cd : 1; // Checking Disabled
			uint8_t rc : 4;	// Response Code
		} flag;
	};

	uint16_t	qdcount;	// # of items in Question ection
	uint16_t	ancount;	// # of items in Answer section
	uint16_t	nscount;	// # of items in Authority section
	uint16_t	arcount;	// # of items in additional section
};

#pragma pack(pop)

extern MDNSPacket*	mdns_alloc_packet(Error* err);
extern void		mdns_free_packet(MDNSPacket* packet);

#endif
