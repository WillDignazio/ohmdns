#include <stdint.h>
#include <stdlib.h>
#include "internal.h"

IPv4Header*
ohm_alloc_header(Error* err)
{
	IPv4Header* header;
	
	header = malloc(sizeof(*header));
	if(header == NULL) {
		error_host(err);
		return NULL;
	}

	return header;
}
