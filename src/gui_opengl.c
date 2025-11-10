/* $Id$ */
#include "kleidi.h"

#include "../external/stb_ds.h"

#include <Mw/Widget/OpenGL.h>

typedef struct widget widget_t;
struct widget {
	MwRect	   rect;
	char	   type[64];
	widget_t** children;
};

static MwPoint	  mouse;
static MwPoint	  first;
static int	  first_set = 0;
static widget_t** rects	    = NULL;

static void gui_opengl_mouse_move(MwWidget handle, void* user, void* client) {
	double x;
	double y;
	char   str[64];

	mouse = *(MwPoint*)client;

	x = mouse.x / 15.;
	y = mouse.y / 15.;

	mouse.x = k_round(x) * 15;
	mouse.y = k_round(y) * 15;

	if(first_set) {
		sprintf(str, "%dx%d <%s>, Right click to cancel", abs(mouse.x - first.x), abs(mouse.y - first.y), widget_name);
		gui_set_status(str);
	}
}

static void gui_opengl_mouse_down(MwWidget handle, void* user, void* client) {
	MwLLMouse m = *(MwLLMouse*)client;
	if(m.button == MwLLMouseLeft) {
		if(!first_set && strlen(widget_name) == 0) {
			gui_set_status("Select an widget first");
			return;
		}
		first_set = first_set ? 0 : 1;
		if(first_set) {
			first = mouse;
		} else {
			widget_t* widget = malloc(sizeof(*widget));
			strcpy(widget->type, widget_name);
			widget->rect.x	    = first.x < mouse.x ? first.x : mouse.x;
			widget->rect.y	    = first.y < mouse.y ? first.y : mouse.y;
			widget->rect.width  = abs(mouse.x - first.x);
			widget->rect.height = abs(mouse.y - first.y);
			widget->children    = NULL;

			arrput(rects, widget);

			gui_set_status("");
		}
	} else if(m.button == MwLLMouseRight) {
		first_set = 0;
		gui_set_status("");
	}
}

static void gui_opengl_draw_widgets(widget_t** rects_list) {
	int i, j;
	if(rects_list == rects) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(1, 1, 0);
	}
	for(i = 0; i < arrlen(rects_list); i++) {
		glBegin(GL_QUADS);
		glVertex2f(rects[i]->rect.x, rects[i]->rect.y);
		glVertex2f(rects[i]->rect.x, rects[i]->rect.y + rects[i]->rect.height);
		glVertex2f(rects[i]->rect.x + rects[i]->rect.width, rects[i]->rect.y + rects[i]->rect.height);
		glVertex2f(rects[i]->rect.x + rects[i]->rect.width, rects[i]->rect.y);
		glEnd();
		gui_opengl_draw_widgets(rects_list[i]->children);
	}
	if(rects_list == rects) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void gui_opengl_loop(void) {
	int w = MwGetInteger(opengl, MwNwidth);
	int h = MwGetInteger(opengl, MwNheight);
	int x;
	int y;

	glClear(GL_COLOR_BUFFER_BIT);

	gui_opengl_draw_widgets(rects);

	for(y = 0; y < h; y += 15) {
		if(y == mouse.y) {
			glColor3f(1, 1, 0);
			glBegin(GL_LINES);
			glVertex2f(0, y);
			glVertex2f(w, y);
			glEnd();
		}
		for(x = 0; x < w; x += 15) {
			if(x == mouse.x && y == mouse.y) {
				glColor3f(1, 1, 0);
				glPointSize(5);
			} else if(x == mouse.x) {
				glColor3f(1, 1, 0);
				glBegin(GL_LINES);
				glVertex2f(x, 0);
				glVertex2f(x, h);
				glEnd();
			} else {
				glColor3f(1, 1, 1);
				glPointSize(1);
			}
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
		}
	}

	if(first_set) {
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

void gui_opengl_init(void) {
	mouse.x = -15;
	mouse.y = -15;

	MwAddUserHandler(opengl, MwNmouseMoveHandler, gui_opengl_mouse_move, NULL);
	MwAddUserHandler(opengl, MwNmouseDownHandler, gui_opengl_mouse_down, NULL);
}
