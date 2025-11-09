/* $Id$ */
#ifndef __KLEIDI_H__
#define __KLEIDI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Mw/Milsko.h>

#define VERSION "1.0-pre"

/* gui.c */
extern MwWidget	  root, window, menu;
extern MwLLPixmap logo_pixmap;

void gui_init(void);
void gui_loop(void);
void gui_confirm_quit(void);

/* gui_version.c */
void gui_version(void);

/* logo.c */
extern unsigned char logo[];
extern unsigned int  logo_len;

#endif
