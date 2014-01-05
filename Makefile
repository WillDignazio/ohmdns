CC= clang
CFLAGS= -O0 -Wall -Werror -g
LIBS=

.PHONY: all clean

CSRC=	packet.c \
	error.c \
	ohm.c

COBJS=$(CSRC:.c=.o)

all: $(COBJS)
	$(CC) $(CFLAGS) $(LIBS) ohmd.c $(COBJS) -o ohmd

.o: internal.h error.h packet.h
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *.o
	@rm -f ohmd
	@rm -rf *.dSYM
