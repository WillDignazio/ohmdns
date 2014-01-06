#ifndef __error__
#define __error__

#include <stdint.h>
#include <pthread.h>

#define ERR_STRLEN	120
#define BACKTRACE_COUNT	100

typedef struct Error Error;
typedef struct ErrorMonitor ErrorMonitor;

struct Error
{
	char		estr[ERR_STRLEN];
	uint16_t	eid;

	/* Backtrace Fields */
	int		bt_nptrs;
	char**	       	bt_estrs;
	void*		bt_buffer[BACKTRACE_COUNT];
};

struct ErrorMonitor
{
	int		efd;	// Output file descriptor
};
	
extern void	_error(Error* err, int (*efunc)(Error* err), char* estr, ...);
extern int	error_sys(Error* err);

#define esys(__err__, __estr__, ...)	\
	_error(__err__, error_sys, __estr__, ##__VA_ARGS__);

enum
{
	ERROR_SOCK,
};

#endif
