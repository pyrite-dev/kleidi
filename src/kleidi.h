/* $Id$ */
#ifndef __KLEIDI_H__
#define __KLEIDI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Mw/Milsko.h>

/* gui.c */
extern MwWidget root, window;

void gui_init(void);
void gui_loop(void);
void gui_confirm_quit(void);

#endif
