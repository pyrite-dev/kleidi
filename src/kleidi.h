/* $Id$ */
#ifndef __KLEIDI_H__
#define __KLEIDI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Mw/Milsko.h>

#define VERSION "1.0-pre"

/* gui/master.c */
extern MwWidget	  root, window, menu, widgets, logging, opengl, status, controls, controls_select, controls_create;
extern MwLLPixmap logo_pixmap;
extern char	  widget_name[];
extern int	  gui_mode, gui_width, gui_height;

enum gui_modes {
	MODE_SELECT = 0,
	MODE_CREATE
};

void gui_init(void);
void gui_loop(void);
void gui_confirm_quit(void);
void gui_set_status(const char* text);

/* gui/options.c */
void gui_options(void);

/* gui/version.c */
void gui_version(void);

/* gui/opengl.c */
void gui_opengl_loop(void);
void gui_opengl_init(void);
void gui_opengl_cancel(void);
void gui_opengl_set_grid(int size);
int  gui_opengl_get_grid(void);

/* resource/logo.c */
extern unsigned char res_logo[];
extern unsigned int  res_logo_len;

/* math.c */
double k_round(double v);

/* machdep.c */
void machdep_init(void);
void machdep_screen_size(int* width, int* height);

#endif
