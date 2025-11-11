# $Id$
CC = gcc
CFLAGS = -I./milsko/include `pkg-config --cflags x11 gl`
LDFLAGS = -L./milsko/lib -Wl,-R./milsko/lib
LIBS = -lMw `pkg-config --libs x11 gl` -lm

.PHONY: all format clean
.SUFFIXES: .c .o

OBJS = src/main.o src/gui.o src/gui_version.o src/gui_opengl.o src/math.o
OBJS += src/machdep_x11.o
OBJS += src/res_logo.o
OBJS += external/stb_image.o external/stb_ds.o

all: ./kleidi$(EXEC)

format:
	clang-format --verbose -i `find src '(' -name "*.c" -or -name "*.h" ')' -and -not -name "res_*.c"`

./kleidi$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./kleidi ./kleidi.exe src/*.o
