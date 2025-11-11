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

OBJS = src/main.o src/gui.o src/gui_version.o src/gui_opengl.o src/math.o
OBJS += src/machdep_$(BACKEND).o
OBJS += src/res_logo.o
OBJS += external/stb_image.o external/stb_ds.o external/font8x8.o

all: ./kleidi$(EXEC)

format:
	clang-format --verbose -i `find src '(' -name "*.c" -or -name "*.h" ')' -and -not -name "res_*.c"`

./kleidi$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ./kleidi ./kleidi.exe src/*.o external/*.o
