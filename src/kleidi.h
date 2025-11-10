/* $Id$ */
#ifndef __KLEIDI_H__
#define __KLEIDI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Mw/Milsko.h>

#define VERSION "1.0-pre"

/* gui.c */
extern MwWidget	  root, window, menu, widgets, logging, opengl, status, controls, controls_select, controls_create;
extern MwLLPixmap logo_pixmap, select_pixmap, create_pixmap;
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

/* res_logo.c */
extern unsigned char res_logo[];
extern unsigned int  res_logo_len;

/* res_select.c */
extern unsigned char res_select[];
extern unsigned int  res_select_len;

/* res_create.c */
extern unsigned char res_create[];
extern unsigned int  res_create_len;

/* math.c */
double k_round(double v);

#endif
