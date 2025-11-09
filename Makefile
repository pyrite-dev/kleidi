# $Id$
CC = gcc
CFLAGS = -I./milsko/include `pkg-config --cflags gl`
LDFLAGS = -L./milsko/lib -Wl,-R./milsko/lib
LIBS = -lMw `pkg-config --libs gl`

.PHONY: all format clean
.SUFFIXES: .c .o

OBJS = src/main.o src/gui.o src/gui_version.o src/gui_opengl.o src/logo.o src/math.o
OBJS += external/stb_image.o

all: ./kleidi$(EXEC)

format:
	clang-format --verbose -i `find src '(' -name "*.c" -or -name "*.h" ')' -and -not -name "logo.c"`

./kleidi$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./kleidi ./kleidi.exe src/*.o
