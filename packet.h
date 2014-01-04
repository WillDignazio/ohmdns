#ifndef __packet__
#define __packet__

#include <stdint.h>
typedef union Packet Packet;

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
 * TCP/UDP Packet Structures 
 */
union Packet
{
	struct
	{
		uint16_t	src_port;	// Source Port
		uint16_t	dest_port;	// Destination Port
		uint32_t	seq_num;	// Sequence Number
		uint32_t	ack_num;	// Acknowledgement Number
		
		uint8_t		dat_offset : 4;	// Data Offset
		uint8_t		resv : 3;	// Reserved
		
		union
		{
			struct
			{
				uint8_t	ns : 1;		// ECN-nonce concealment protection
				uint8_t cwr : 1;	// Congestion Window Reduced 
				uint8_t ece : 1;	// Echo
				uint8_t urg : 1;	// Urgent
				uint8_t ack : 1;	// ACK
				uint8_t psh : 1;	// Push Function
				uint8_t rst : 1;	// Reset
				uint8_t syn : 1;	// Synchronize Sequence Numbers
				uint8_t fin : 1;	// Finished/Final
			} tcp_flags;
			
			uint16_t	tcp_field;
		} flags;
		
		uint32_t	windowsz;	// Window Size
		uint32_t	checksum;	// Checksum
		uint32_t	urg_ptr;	// Urgent Pointer
		
		uint64_t	options;	// Options, if data offset > 5, is 0 padded
	} tcp;

	struct
	{
		uint16_t	src_port;	// Source Port
		uint16_t	dest_port;	// Destination Port
		uint16_t	length;		// Length
		uint16_t	checksum;	// Checksum
	} udp;
};
#pragma pack(pop)
	


#endif
