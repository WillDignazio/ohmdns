#ifndef __error__
#define __error__

#include <stdint.h>

#define ERR_STRLEN	120

typedef struct Error Error;

struct Error
{
	char		estr[ERR_STRLEN];
	uint16_t	eid;
};

extern int	error_host(Error* err);

#endif
