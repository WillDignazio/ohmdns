#include <stdio.h>
#include <stdint.h>
#include "internal.h"

#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>

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

unsigned short csum(unsigned short *buf, int nwords)
{
        unsigned long sum;
        for(sum=0; nwords>0; nwords--)
                sum += *buf++;
        sum = (sum >> 16) + (sum &0xffff);
        sum += (sum >> 16);
        return (unsigned short)(~sum);
}

int
main(int argc, char* argv[])
{
	Packet p;
	uint16_t val;
	int sd;
	struct sockaddr_in sin;
	
	uint8_t buffer[8192];

	val = 0xaaaa;
	printbn(val, 16);
	
	val = bswap16(val);
	printbn(val, 16);
	

	printf("Packet Size: %d\n", sizeof(Packet));
	printf("TCP Packet Size: %d\n", sizeof(p.tcp));
	printf("UDP Packet Size: %d\n", sizeof(p.udp));

	printf("Beginning Packet Storm....\n");
	sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sd < 0) {
		perror("socket");
		exit(1);
	}

	sin.sin_family = AF_INET;
	sin.sin_port = 2020;
	sin.sin_addr = inet_addr("192.168.1.65");
	
	p.udp.src_port = 1000;
	p.udp.dest_port = 2020;

	return 0;
}
