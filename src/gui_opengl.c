/* $Id$ */
#include "kleidi.h"

#include <Mw/Widget/OpenGL.h>

void gui_opengl_loop(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	MwOpenGLSwapBuffer(opengl);
}
