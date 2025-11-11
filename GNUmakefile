# $Id$
BACKEND = x11

CC = gcc
CFLAGS = -I./milsko/include
LDFLAGS = -L./milsko/lib -Wl,-R./milsko/lib
LIBS = -lMw

ifeq ($(BACKEND),x11)
CFLAGS += `pkg-config --cflags x11 gl libxml-2.0`
LIBS += `pkg-config --libs x11 gl libxml-2.0` -lm
endif
ifeq ($(BACKEND),gdi)
LIBS += -lopengl32 -lxml2
endif

.PHONY: all format clean
.SUFFIXES: .c .o

OBJS = src/main.o src/math.o
OBJS += src/gui/master.o src/gui/options.o src/gui/version.o src/gui/opengl.o
OBJS += src/resource/logo.o
OBJS += src/machdep_$(BACKEND).o
OBJS += external/stb_image.o external/stb_ds.o external/font8x8.o

all: ./kleidi$(EXEC)

format:
	clang-format --verbose -i `find src '(' -name "*.c" -or -name "*.h" ')' -and -not -name "res_*.c"`

./kleidi$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./kleidi ./kleidi.exe src/*.o src/*/*.o external/*.o
