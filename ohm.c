#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "internal.h"

OhmSocket*
ohm_alloc_socket(Error* err)
{
	OhmSocket* sock;
	int r;
	
	r = 0;
	sock = malloc(sizeof(*sock));
	if(sock == NULL) {
		esys(err, "Failed to allocate custom Ohm Socket");
		r = -1;
		goto fail;
	}

	return sock;

fail:
	if(sock)
		free(sock);

	return NULL;
}

void
ohm_free_socket(OhmSocket* sock)
{
	if(sock == NULL)
		return;

	free(sock);
}

int
ohm_open_socket4(int port, OhmSocket* sock, Error* err)
{
	struct sockaddr_in s_in;
	struct ip_mreq mreq;
	int sfd;
	int r;
	unsigned char opt_loop;

	r = 0;
	opt_loop = 1;

	if(sock == NULL) {
		r = -1;
		goto fail;
	}
	
	sfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sfd == 1) {
		esys(err, "Failed to allocate system socket");
		r = -1;
		goto fail;
	}

	memset(&s_in, 0, sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	s_in.sin_port = htons(port);

	r = bind(sfd, (struct sockaddr*)&s_in, sizeof(s_in));
	if(r == -1) {
		esys(err, "Failed to bind system socket");
		r = -1;
		goto fail;
	}

	/* Setup the socket to loopback the data it gets */
	r = setsockopt(sfd, IPPROTO_IP, IP_MULTICAST_LOOP, &opt_loop, sizeof(unsigned char));
	if(r == -1) {
		esys(err, "Failed to set socket option for multicast loop");
		r = -1;
		goto fail;
	}

	/* Enlist the socket in the multicast group */
//	inet_pton(AF_INET, MDNS_ADDR_STR, &addr);
	mreq.imr_multiaddr.s_addr = inet_addr(MDNS_ADDR_STR);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	r = setsockopt(sfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	if(r < 0) {
		esys(err, "Failed to join multicast group");
		r = -1;
		goto fail;
	}

	sock->mreq = mreq;
	sock->s_in = s_in;
	sock->sfd = sfd;

fail:
	if(sock) {
		close(sock->sfd);
		free(sock);
	}
	return r;
}

int
ohm_close_socket4(OhmSocket* sock, Error* err)
{
	int r;

	r = 0;
	if(sock == NULL) {
		strncpy(err->estr, "Invalid OhmSocket", ERR_STRLEN);
		err->eid = ERROR_SOCK;
		r = -1;
		goto fail;
	}

	/* Close actual socket */
	r = close(sock->sfd);
	if(r == -1) {
		esys(err, "Error closing system socket");
		goto fail;
	}

	/* Wipe address info */
	memset(&sock->s_in, 0, sizeof(sock->s_in));
fail:
	return 0;
}

int
ohm_open_socket(int port, OhmSocket* sock, Error* err)
{
	return ohm_open_socket4(port, sock, err);
}

int
ohm_close_socket(OhmSocket* sock, Error* err)
{
	return ohm_close_socket4(sock, err);
}
