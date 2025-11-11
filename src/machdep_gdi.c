/* $Id$ */
#include "kleidi.h"

#include <windows.h>

void machdep_init(void) {
}

void machdep_screen_size(int* width, int* height) {
	RECT rc;

	GetClientRect(GetDesktopWindow(), &rc);

	*width	= rc.right - rc.left;
	*height = rc.bottom - rc.top;
}
