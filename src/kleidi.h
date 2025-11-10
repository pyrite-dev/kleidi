/* $Id$ */
#ifndef __KLEIDI_H__
#define __KLEIDI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Mw/Milsko.h>

#define VERSION "1.0-pre"

/* gui.c */
extern MwWidget	  root, window, menu, widgets, logging, opengl, status, controls;
extern MwLLPixmap logo_pixmap;
extern char	  widget_name[];

void gui_init(void);
void gui_loop(void);
void gui_confirm_quit(void);
void gui_set_status(const char* text);

/* gui_version.c */
void gui_version(void);

/* gui_opengl.c */
void gui_opengl_loop(void);
void gui_opengl_init(void);

/* logo.c */
extern unsigned char logo[];
extern unsigned int  logo_len;

/* math.c */
double k_round(double v);

#endif
