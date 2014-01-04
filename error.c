#include <errno.h>
#include <string.h>
#include "internal.h"

extern int errno;

int
error_host(Error* err)
{
	int r;

	if(err == NULL)
		return -1;

	err->eid = errno;
	r = strerror_r(errno, err->estr, ERR_STRLEN);

	return r;
}
