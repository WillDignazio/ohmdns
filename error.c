#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <execinfo.h>
#include "internal.h"

extern int errno;

static ErrorMonitor	emon =
{
	.efd = STDERR_FILENO,
};

/*
 * XXX: Assumes errno complies with POSIX compliant thread safety
 *
 * Since there may be some thread sillyness, we want each
 * to be capable of producing it's own 'atomic' Errors.
 * To do this, we're going to set the fields whenever 
 * one of the macros is called to _error
 */

void
_error(Error* err, int(*efunc)(Error* err), char* estr, ...)
{
	int j;
	int r;
	va_list ap;
	char errbuf[ERR_STRLEN]; // estr buffer

	if(err == NULL)
		return;

	va_start(ap, estr);

	/* Call the primary error function given */
	r = efunc(err);

	err->bt_nptrs = backtrace(err->bt_buffer, BACKTRACE_COUNT);
	err->bt_estrs = backtrace_symbols(err->bt_buffer, err->bt_nptrs);

	/* Write out the Error to the log */
	vsnprintf(errbuf, ERR_STRLEN, estr, ap);
	dprintf(emon.efd, "ERROR [%d]: %s, %s\n", err->eid, err->estr, errbuf);

	/* Write out the backtrace */
	for(j=1;j<err->bt_nptrs;j++)
		dprintf(emon.efd, "\t%s\n", err->bt_estrs[j]);
}

int
error_sys(Error* err)
{
	int r;

	err->eid = errno;
	r = strerror_r(errno, err->estr, ERR_STRLEN);

	if(err == NULL)
		return -1;

	return r;
}
