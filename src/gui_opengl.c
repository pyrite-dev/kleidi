/* $Id$ */
#include "kleidi.h"

#include <Mw/Widget/OpenGL.h>

static MwPoint mouse;
static MwPoint first;
static int first_set = 0;

static void gui_opengl_mouse_move(MwWidget handle, void* user, void* client){
	double x;
	double y;

	mouse = *(MwPoint*)client;

	x = mouse.x / 15.;
	y = mouse.y / 15.;

	mouse.x = k_round(x) * 15;
	mouse.y = k_round(y) * 15;
}

static void gui_opengl_mouse_down(MwWidget handle, void* user, void* client){
	MwLLMouse m = *(MwLLMouse*)client;
	if(m.button == MwLLMouseLeft){
		first_set = first_set ? 0 : 1;
		if(first_set){
			first = mouse;
		}else{
		}
	}
}

void gui_opengl_loop(void) {
	int w = MwGetInteger(opengl, MwNwidth);
	int h = MwGetInteger(opengl, MwNheight);
	int x;
	int y;

	glClear(GL_COLOR_BUFFER_BIT);

	for(y = 0; y < h; y += 15){
		if(y == mouse.y){
			glColor3f(1, 1, 0);
			glBegin(GL_LINES);
			glVertex2f(0, y);
			glVertex2f(w, y);
			glEnd();
		}
		for(x = 0; x < w; x += 15){
			if(x == mouse.x && y == mouse.y){
				glColor3f(1, 1, 0);
				glPointSize(5);
			}else if(x == mouse.x){
				glColor3f(1, 1, 0);
				glBegin(GL_LINES);
				glVertex2f(x, 0);
				glVertex2f(x, h);
				glEnd();
			}else{
				glColor3f(1, 1, 1);
				glPointSize(1);
			}
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
		}
	}

	if(first_set){
		glColor3f(1, 1, 0);
		glBegin(GL_LINES);
			glVertex2f(first.x, first.y);
			glVertex2f(first.x, mouse.y);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(first.x, first.y);
			glVertex2f(mouse.x, first.y);
		glEnd();
	}

	MwOpenGLSwapBuffer(opengl);
}

void gui_opengl_init(void){
	mouse.x = -15;
	mouse.y = -15;

	MwAddUserHandler(opengl, MwNmouseMoveHandler, gui_opengl_mouse_move, NULL);
	MwAddUserHandler(opengl, MwNmouseDownHandler, gui_opengl_mouse_down, NULL);
}
