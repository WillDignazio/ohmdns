#ifndef __ohm__
#define __ohm__

#define MDNS_PORT	5353
#define MDNS_ADDR_STR	"224.0.0.251"

typedef struct OhmSocket OhmSocket;

struct OhmSocket
{
	int		sfd;
};

extern OhmSocket*	ohm_alloc_socket(Error* err);
extern int		ohm_open_socket(int port, OhmSocket* sock, Error* err);
extern int		ohm_open_socket4(int port, OhmSocket* sock, Error* err);

#endif
