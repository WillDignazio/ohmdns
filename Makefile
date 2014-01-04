CC= clang
CFLAGS= -O0 -Wall -Werror -g
LIBS=

.PHONY: all clean

CSRC=	packet.c \
	error.c

COBJS=$(CSRC:.c=.o)

all: $(COBJS)
	$(CC) $(CFLAGS) $(LIBS) main.c $(COBJS) -o ohmd

.o: internal.h error.h packet.h
	$(CC) $(CFLAGS) -c $<

clean:
	@rm *.o
	@rm ohmd