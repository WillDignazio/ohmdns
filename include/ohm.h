#ifndef __ohm__
#define __ohm__

#include <netinet/in.h>

#define MDNS_PORT	5353
#define MDNS_ADDR_STR	"224.0.0.251"

typedef struct OhmSocket OhmSocket;

struct OhmSocket
{
	int			sfd;
	struct sockaddr_in	s_in;
	struct ip_mreq		mreq;
};

extern OhmSocket*	ohm_alloc_socket(Error* err);
extern int		ohm_open_socket(int port, char* addrstr, OhmSocket* sock, Error* err);
extern int		ohm_open_socket4(int port, char* addrstr, OhmSocket* sock, Error* err);
extern int		ohm_close_socket(OhmSocket* sock, Error* err);
extern int		ohm_close_socket4(OhmSocket* sock, Error* err);

/*
 * Compile time configuration constants
 */
enum
{
	MAX_BACKLOG	= 10,
};

#endif
