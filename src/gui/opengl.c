/* $Id$ */
#include "../kleidi.h"

#include "../../external/stb_ds.h"

#include <Mw/Widget/OpenGL.h>

typedef struct widget widget_t;
struct widget {
	MwRect	   rect;
	char	   type[64];
	widget_t** children;
};

static MwPoint	  mouse;
static MwPoint	  first;
static int	  first_set = 0, grid = 16;
static widget_t** rects	   = NULL;
static widget_t*  selected = NULL;

static void gui_opengl_mouse_move(MwWidget handle, void* user, void* client) {
	double x;
	double y;
	char   str[64];

	mouse = *(MwPoint*)client;

	x = mouse.x / (double)grid;
	y = mouse.y / (double)grid;

	mouse.x = k_round(x) * grid;
	mouse.y = k_round(y) * grid;

	if(first_set) {
		sprintf(str, "%dx%d <%s>, Right click to cancel", abs(mouse.x - first.x), abs(mouse.y - first.y), widget_name);
		gui_set_status(str);
	}
}

static void gui_opengl_select(widget_t** rects_list) {
	int i;
	if(rects_list == rects) {
		selected = NULL;
	}
	for(i = 0; i < arrlen(rects_list); i++) {
		if(rects_list[i]->rect.x <= mouse.x && rects_list[i]->rect.y <= mouse.y && mouse.x <= (rects_list[i]->rect.x + rects_list[i]->rect.width) && mouse.y <= (rects_list[i]->rect.y + rects_list[i]->rect.height)) {
			selected = rects_list[i];
		}
		gui_opengl_select(rects_list[i]->children);
	}
}

static void gui_opengl_mouse_down(MwWidget handle, void* user, void* client) {
	MwLLMouse m = *(MwLLMouse*)client;
	if(m.button == MwLLMouseLeft) {
		if(gui_mode == MODE_CREATE) {
			first_set = first_set ? 0 : 1;
			if(first_set) {
				first = mouse;
				if(selected != NULL) {
					if(first.x < selected->rect.x || first.y < selected->rect.y || first.x > (selected->rect.x + selected->rect.width) || first.y > (selected->rect.y + selected->rect.height)) {
						gui_set_status("Widget cannot be placed outside the parent widget");
						first_set = 0;
					}
				} else {
					if(strcmp(widget_name, "Window") != 0) {
						gui_set_status("Toplevel widget must be window");
						first_set = 0;
					}
				}
			} else {
				widget_t* widget;

				if(selected != NULL) {
					if(mouse.x < selected->rect.x || mouse.y < selected->rect.y || mouse.x > (selected->rect.x + selected->rect.width) || mouse.y > (selected->rect.y + selected->rect.height)) {
						gui_set_status("Widget cannot be placed outside the parent widget");
						first_set = 1;
					}
				}

				if(!first_set) {
					widget = malloc(sizeof(*widget));
					strcpy(widget->type, widget_name);
					widget->rect.x	    = first.x < mouse.x ? first.x : mouse.x;
					widget->rect.y	    = first.y < mouse.y ? first.y : mouse.y;
					widget->rect.width  = abs(mouse.x - first.x);
					widget->rect.height = abs(mouse.y - first.y);
					widget->children    = NULL;

					if(selected != NULL) {
						arrput(selected->children, widget);
					} else {
						arrput(rects, widget);
						selected = widget;
					}

					gui_set_status("");

					gui_mode = MODE_SELECT;
				}
			}
		} else if(gui_mode == MODE_SELECT) {
			gui_opengl_select(rects);
		}
	} else if(m.button == MwLLMouseRight) {
		if(gui_mode == MODE_CREATE) {
			gui_mode  = MODE_SELECT;
			first_set = 0;

			gui_set_status("Cancelled creating");
		}
	}
}

static void gui_opengl_draw_widgets(widget_t** rects_list) {
	int i;
	if(rects_list == rects) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(1, 1, 0);
	}
	for(i = 0; i < arrlen(rects_list); i++) {
		if(rects_list[i] == selected) {
			glLineWidth(2);
		} else {
			glLineWidth(1);
		}
		glBegin(GL_QUADS);
		glVertex2f(rects_list[i]->rect.x, rects_list[i]->rect.y);
		glVertex2f(rects_list[i]->rect.x, rects_list[i]->rect.y + rects_list[i]->rect.height);
		glVertex2f(rects_list[i]->rect.x + rects_list[i]->rect.width, rects_list[i]->rect.y + rects_list[i]->rect.height);
		glVertex2f(rects_list[i]->rect.x + rects_list[i]->rect.width, rects_list[i]->rect.y);
		glEnd();
		gui_opengl_draw_widgets(rects_list[i]->children);
	}
	glLineWidth(1);
	if(rects_list == rects) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void gui_opengl_cancel(void) {
	first_set = 0;
}

void gui_opengl_loop(void) {
	int w = MwGetInteger(opengl, MwNwidth);
	int h = MwGetInteger(opengl, MwNheight);
	int x;
	int y;

	glClear(GL_COLOR_BUFFER_BIT);

	gui_opengl_draw_widgets(rects);

	for(y = 0; y < h; y += grid) {
		if(y == mouse.y) {
			glColor3f(1, 1, 0);
			glBegin(GL_LINES);
			glVertex2f(0, y);
			glVertex2f(w, y);
			glEnd();
		}
		for(x = 0; x < w; x += grid) {
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
		glVertex2f(first.x, first.y);
		glVertex2f(mouse.x, first.y);
		glEnd();
	}

	MwOpenGLSwapBuffer(opengl);
}

void gui_opengl_init(void) {
	mouse.x = -grid;
	mouse.y = -grid;

	MwAddUserHandler(opengl, MwNmouseMoveHandler, gui_opengl_mouse_move, NULL);
	MwAddUserHandler(opengl, MwNmouseDownHandler, gui_opengl_mouse_down, NULL);
}

void gui_opengl_set_grid(int size) {
	char str[32];

	grid = size;
	if(grid < 2) grid = 2;

	sprintf(str, "Setting grid size to %d", grid);
	gui_set_status(str);
}

int gui_opengl_get_grid(void) {
	return grid;
}
