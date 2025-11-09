/* $Id$ */
#include "kleidi.h"

#include "../external/stb_image.h"

#include <Mw/Widget/OpenGL.h>

MwWidget   root, window, menu, widgets, logging, opengl;
MwMenu	   menu_file_quit;
MwMenu	   menu_help_version;
MwLLPixmap logo_pixmap;

static void gui_root_tick(MwWidget handle, void* user, void* client) {
	gui_opengl_loop();
}

static void gui_window_close(MwWidget handle, void* user, void* client) {
	gui_confirm_quit();
}

static void gui_window_resize(MwWidget handle, void* user, void* client) {
	int ww = MwGetInteger(window, MwNwidth);
	int wh = MwGetInteger(window, MwNheight);
	int mh = MwGetInteger(menu, MwNheight);

	MwVaApply(widgets,
		  MwNx, 10,
		  MwNy, mh + 10,
		  MwNwidth, 256,
		  MwNheight, wh - mh - 20,
		  NULL);

	MwVaApply(logging,
		  MwNx, 10 + 256 + 10,
		  MwNy, wh - 10 - 128,
		  MwNwidth, ww - 10 - 256 - 10 - 10,
		  MwNheight, 128,
		  NULL);

	MwVaApply(opengl,
		  MwNx, 10 + 256 + 10,
		  MwNy, mh + 10,
		  MwNwidth, ww - 10 - 256 - 10 - 10,
		  MwNheight, wh - mh - 10 - 10 - 128 - 10,
		  NULL);

	glViewport(0, 0, ww - 10 - 256 - 10 - 10, wh - mh - 10 - 10 - 128 - 10);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ww - 10 - 256 - 10 - 10, wh - mh - 10 - 10 - 128 - 10, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void gui_menu_menu(MwWidget handle, void* user, void* client) {
	if(client == menu_file_quit) {
		gui_confirm_quit();
	} else if(client == menu_help_version) {
		gui_version();
	}
}

static void gui_confirm_quit_yes(MwWidget handle, void* user, void* client) {
	MwDestroyWidget(user);
	MwDestroyWidget(root);
}

static void gui_confirm_quit_no(MwWidget handle, void* user, void* client) {
	MwDestroyWidget(user);
}

void gui_confirm_quit(void) {
	MwWidget msg = MwMessageBox(window, "Are you sure you want to quit?", "Confirm", MwMB_ICONWARNING | MwMB_BUTTONYESNO);

	MwAddUserHandler(MwMessageBoxGetChild(msg, MwMB_BUTTONYES), MwNactivateHandler, gui_confirm_quit_yes, msg);
	MwAddUserHandler(MwMessageBoxGetChild(msg, MwMB_BUTTONNO), MwNactivateHandler, gui_confirm_quit_no, msg);
}

void gui_init(void) {
	MwMenu	       m;
	int	       w, h, ch;
	unsigned char* data;
	void*	       p;
	int	       index;

	root	= MwCreateWidget(NULL, "root", NULL, 0, 0, 0, 0);
	window	= MwVaCreateWidget(MwWindowClass, "main", root, MwDEFAULT, MwDEFAULT, 1024, 768,
				   MwNtitle, "Kleidi GUI Builder",
				   NULL);
	menu	= MwCreateWidget(MwMenuClass, "menu", window, 0, 0, 0, 0);
	widgets = MwVaCreateWidget(MwListBoxClass, "widgets", window, 0, 0, 0, 0,
				   MwNhasHeading, 1,
				   NULL);
	logging = MwCreateWidget(MwListBoxClass, "logging", window, 0, 0, 0, 0);
	opengl	= MwCreateWidget(MwOpenGLClass, "opengl", window, 0, 0, 0, 0);

	MwOpenGLMakeCurrent(opengl);

	m	       = MwMenuAdd(menu, NULL, "File");
	menu_file_quit = MwMenuAdd(menu, m, "Quit");

	m		  = MwMenuAdd(menu, NULL, "?Help");
	menu_help_version = MwMenuAdd(menu, m, "Version");

	data	    = stbi_load_from_memory(logo, logo_len, &w, &h, &ch, 4);
	logo_pixmap = MwLoadRaw(window, data, w, h);
	free(data);

	MwVaApply(window,
		  MwNiconPixmap, logo_pixmap,
		  NULL);

	MwAddUserHandler(window, MwNresizeHandler, gui_window_resize, NULL);
	MwAddUserHandler(window, MwNcloseHandler, gui_window_close, NULL);
	MwAddUserHandler(menu, MwNmenuHandler, gui_menu_menu, NULL);

	p     = MwListBoxCreatePacket();
	index = MwListBoxPacketInsert(p, -1);
	MwListBoxPacketSet(p, index, 0, "Widget name");
	MwListBoxInsert(widgets, -1, p);
	MwListBoxDestroyPacket(p);

	MwListBoxSetWidth(widgets, 0, 0);

	gui_window_resize(window, NULL, NULL);
}

void gui_loop(void) {
	MwAddUserHandler(root, MwNtickHandler, gui_root_tick, NULL);
	MwLoop(root);
}
