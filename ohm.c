#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "internal.h"

OhmSocket*
ohm_alloc_socket(Error* err)
{
	OhmSocket* sock;
	int r;
	
	r = 0;
	sock = malloc(sizeof(*sock));
	if(sock == NULL) {
		r = error_host(err);
		goto fail;
	}

	return sock;

fail:
	if(sock)
		free(sock);

	return NULL;
}

int
ohm_open_socket4(int port, OhmSocket* sock, Error* err)
{
	int sfd;
	int r;

	r = 0;
	
	if(sock == NULL) {
		r = -1;
		goto fail;
	}
	
	sfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sfd == 1) {
		error_host(err);
		r = -1;
		goto fail;
	}

	sock->sfd = sfd;
fail:
	return r;
}

int
ohm_open_socket(int port, OhmSocket* ohms, Error* err)
{
	return ohm_open_socket4(port, ohms, err);
}
