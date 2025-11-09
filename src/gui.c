/* $Id$ */
#include "kleidi.h"

MwWidget root, window;

static void gui_window_close(MwWidget handle, void* user, void* client){
	gui_confirm_quit();
}

void gui_confirm_quit_yes(MwWidget handle, void* user, void* client){
	MwDestroyWidget(user);
	MwDestroyWidget(root);
}

void gui_confirm_quit_no(MwWidget handle, void* user, void* client){
	MwDestroyWidget(user);
}

void gui_confirm_quit(void){
	MwWidget msg = MwMessageBox(window, "Are you sure you want to quit?", "Confirm", MwMB_ICONWARNING | MwMB_BUTTONYESNO);

	MwAddUserHandler(MwMessageBoxGetChild(msg, MwMB_BUTTONYES), MwNactivateHandler, gui_confirm_quit_yes, msg);
	MwAddUserHandler(MwMessageBoxGetChild(msg, MwMB_BUTTONNO), MwNactivateHandler, gui_confirm_quit_no, msg);
}

void gui_init(void){
	root = MwCreateWidget(NULL, "root", NULL, 0, 0, 0, 0);
	window = MwVaCreateWidget(MwWindowClass, "main", root, MwDEFAULT, MwDEFAULT, 1024, 768,
		MwNtitle, "Kleidi GUI Builder",
	NULL);

	MwAddUserHandler(window, MwNcloseHandler, gui_window_close, NULL);
}

void gui_loop(void){
	MwLoop(root);
}
