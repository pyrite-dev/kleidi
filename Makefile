# $Id$
CC = gcc
CFLAGS = -I./milsko/include
LDFLAGS = -L./milsko/lib -Wl,-R./milsko/lib
LIBS = -lMw

.PHONY: all clean
.SUFFIXES: .c .o

OBJS =

./kleidi: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./kleidi ./kleidi.exe src/*.o
