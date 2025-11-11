/* $Id$ */
#include "kleidi.h"

int main(int argc, char** argv) {
	machdep_init();
	gui_init();
	gui_loop();
}
