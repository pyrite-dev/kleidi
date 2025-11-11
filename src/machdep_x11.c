#include "kleidi.h"

#include <X11/Xlib.h>

static Display* display;

void machdep_init(void) {
	display = XOpenDisplay(NULL);
}

void machdep_screen_size(int* width, int* height) {
	XWindowAttributes xwa;

	XGetWindowAttributes(display, RootWindow(display, DefaultScreen(display)), &xwa);

	*width	= xwa.width;
	*height = xwa.height;
}
