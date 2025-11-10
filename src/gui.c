/* $Id$ */
#include "kleidi.h"

#include "../external/stb_image.h"

#include <Mw/Widget/OpenGL.h>

MwWidget   root, window, menu, widgets, logging, opengl, status, controls, controls_select, controls_create;
MwMenu	   menu_file_quit;
MwMenu	   menu_help_version;
MwLLPixmap logo_pixmap, select_pixmap, create_pixmap;
char	   widget_name[64];

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
	int www, wwh;
	int cww = 48 * 4, cwh = 48;
	int lww, lwh;
	int sww, swh;
	int oww, owh;

	www = cww;
	wwh = wh - mh - 10 - 10 - cwh - 10;
	MwVaApply(widgets,
		  MwNx, 10,
		  MwNy, mh + 10,
		  MwNwidth, www,
		  MwNheight, wwh,
		  NULL);

	MwVaApply(controls,
		  MwNx, 10,
		  MwNy, mh + 10 + wwh + 10,
		  MwNwidth, cww,
		  MwNheight, cwh,
		  NULL);

	MwVaApply(controls_select,
		  MwNx, cwh * 0,
		  MwNy, 0,
		  MwNwidth, cwh,
		  MwNheight, cwh,
		  NULL);

	MwVaApply(controls_create,
		  MwNx, cwh * 1,
		  MwNy, 0,
		  MwNwidth, cwh,
		  MwNheight, cwh,
		  NULL);

	lww = ww - 10 - www - 10 - 10;
	lwh = 128;
	MwVaApply(logging,
		  MwNx, 10 + www + 10,
		  MwNy, wh - 10 - lwh,
		  MwNwidth, lww,
		  MwNheight, lwh,
		  NULL);

	sww = lww;
	swh = 24;
	MwVaApply(status,
		  MwNx, 10 + www + 10,
		  MwNy, wh - 10 - lwh - 10 - swh,
		  MwNwidth, sww,
		  MwNheight, swh,
		  NULL);

	oww = lww;
	owh = wh - mh - 10 - swh - 10 - lwh - 10;
	MwVaApply(opengl,
		  MwNx, 10 + www + 10,
		  MwNy, mh + 10,
		  MwNwidth, oww,
		  MwNheight, owh,
		  NULL);

	glViewport(0, 0, oww, owh);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, oww, owh, 0, -1, 1);

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

static void gui_widgets_activate(MwWidget handle, void* user, void* client) {
	int  n = *(int*)client;
	char str[64];

	strcpy(widget_name, MwListBoxGet(widgets, n));

	sprintf(str, "Selected %s widget", widget_name);

	gui_set_status(str);
}

void gui_init(void) {
	MwMenu	       m;
	int	       w, h, ch;
	unsigned char* data;
	void*	       p;
	int	       index;
	int	       i;
	const char*    widget_names[] = {
	       "Button",
	       "CheckBox",
	       "Entry",
	       "Frame",
	       "Image",
	       "Label",
	       "ListBox",
	       "Menu",
	       "NumberEntry",
	       "ProgressBar",
	       "RadioBox",
	       "ScrollBar",
	       "Viewport",
	       "Window",
	       NULL};

	memset(widget_name, 0, 64);

	root		= MwCreateWidget(NULL, "root", NULL, 0, 0, 0, 0);
	window		= MwVaCreateWidget(MwWindowClass, "main", root, MwDEFAULT, MwDEFAULT, 1024, 768,
					   MwNtitle, "Kleidi GUI Builder",
					   NULL);
	menu		= MwCreateWidget(MwMenuClass, "menu", window, 0, 0, 0, 0);
	controls	= MwCreateWidget(MwFrameClass, "controls", window, 0, 0, 0, 0);
	controls_select = MwCreateWidget(MwButtonClass, "select", controls, 0, 0, 0, 0);
	controls_create = MwCreateWidget(MwButtonClass, "create", controls, 0, 0, 0, 0);
	widgets		= MwVaCreateWidget(MwListBoxClass, "widgets", window, 0, 0, 0, 0,
					   MwNhasHeading, 1,
					   NULL);
	logging		= MwCreateWidget(MwListBoxClass, "logging", window, 0, 0, 0, 0);
	opengl		= MwCreateWidget(MwOpenGLClass, "opengl", window, 0, 0, 0, 0);
	status		= MwVaCreateWidget(MwLabelClass, "status", window, 0, 0, 0, 0,
					   MwNalignment, MwALIGNMENT_BEGINNING,
					   MwNtext, "Welcome to Kleidi GUI Builder",
					   MwNbold, 1,
					   NULL);

	MwOpenGLMakeCurrent(opengl);

	m	       = MwMenuAdd(menu, NULL, "File");
	menu_file_quit = MwMenuAdd(menu, m, "Quit");

	m		  = MwMenuAdd(menu, NULL, "?Help");
	menu_help_version = MwMenuAdd(menu, m, "Version");

	data	    = stbi_load_from_memory(res_logo, res_logo_len, &w, &h, &ch, 4);
	logo_pixmap = MwLoadRaw(window, data, w, h);
	free(data);

	data	      = stbi_load_from_memory(res_select, res_select_len, &w, &h, &ch, 4);
	select_pixmap = MwLoadRaw(window, data, w, h);
	free(data);

	data	      = stbi_load_from_memory(res_create, res_create_len, &w, &h, &ch, 4);
	create_pixmap = MwLoadRaw(window, data, w, h);
	free(data);

	MwVaApply(window,
		  MwNiconPixmap, logo_pixmap,
		  NULL);

	MwAddUserHandler(window, MwNresizeHandler, gui_window_resize, NULL);
	MwAddUserHandler(window, MwNcloseHandler, gui_window_close, NULL);
	MwAddUserHandler(menu, MwNmenuHandler, gui_menu_menu, NULL);
	MwAddUserHandler(widgets, MwNactivateHandler, gui_widgets_activate, NULL);

	p     = MwListBoxCreatePacket();
	index = MwListBoxPacketInsert(p, -1);
	MwListBoxPacketSet(p, index, 0, "Widget name");
	for(i = 0; widget_names[i] != NULL; i++) {
		index = MwListBoxPacketInsert(p, -1);
		MwListBoxPacketSet(p, index, 0, widget_names[i]);
	}
	MwListBoxInsert(widgets, -1, p);
	MwListBoxDestroyPacket(p);

	MwListBoxSetWidth(widgets, 0, 0);

	gui_opengl_init();

	MwVaApply(controls_select,
		  MwNpixmap, select_pixmap,
		  NULL);

	MwVaApply(controls_create,
		  MwNpixmap, create_pixmap,
		  NULL);

	gui_window_resize(window, NULL, NULL);
}

void gui_loop(void) {
	MwAddUserHandler(root, MwNtickHandler, gui_root_tick, NULL);
	MwLoop(root);
}

void gui_set_status(const char* text) {
	MwVaApply(status,
		  MwNtext, text,
		  NULL);
}
