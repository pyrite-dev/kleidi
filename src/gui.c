/* $Id$ */
#include "kleidi.h"

MwWidget root, window, menu;
MwMenu menu_file_quit;
MwMenu menu_help_version;

static void gui_window_close(MwWidget handle, void* user, void* client){
	gui_confirm_quit();
}

static void gui_menu_menu(MwWidget handle, void* user, void* client){
	if(client == menu_file_quit){
		gui_confirm_quit();
	}else if(client == menu_help_version){
		gui_version();
	}
}

static void gui_confirm_quit_yes(MwWidget handle, void* user, void* client){
	MwDestroyWidget(user);
	MwDestroyWidget(root);
}

static void gui_confirm_quit_no(MwWidget handle, void* user, void* client){
	MwDestroyWidget(user);
}

void gui_confirm_quit(void){
	MwWidget msg = MwMessageBox(window, "Are you sure you want to quit?", "Confirm", MwMB_ICONWARNING | MwMB_BUTTONYESNO);

	MwAddUserHandler(MwMessageBoxGetChild(msg, MwMB_BUTTONYES), MwNactivateHandler, gui_confirm_quit_yes, msg);
	MwAddUserHandler(MwMessageBoxGetChild(msg, MwMB_BUTTONNO), MwNactivateHandler, gui_confirm_quit_no, msg);
}

static void gui_version_close(MwWidget handle, void* user, void* client){
	MwDestroyWidget(handle);
}

void gui_version(void){
	int w = 600, h = 200;
	int x = MwGetInteger(window, MwNx) + (MwGetInteger(window, MwNwidth) - w) / 2;
	int y = MwGetInteger(window, MwNy) + (MwGetInteger(window, MwNheight) - h) / 2;
	MwWidget version = MwVaCreateWidget(MwWindowClass, "version", root, x, y, w, h,
		MwNtitle, "Version information",
	NULL);
	MwWidget image = MwVaCreateWidget(MwImageClass, "image", version, 10, 10, w - 20, h - 20,
	NULL);

	MwAddUserHandler(version, MwNcloseHandler, gui_version_close, NULL);
}

void gui_init(void){
	MwMenu m;

	root = MwCreateWidget(NULL, "root", NULL, 0, 0, 0, 0);
	window = MwVaCreateWidget(MwWindowClass, "main", root, MwDEFAULT, MwDEFAULT, 1024, 768,
		MwNtitle, "Kleidi GUI Builder",
	NULL);
	menu = MwCreateWidget(MwMenuClass, "menu", window, 0, 0, 0, 0);

	m = MwMenuAdd(menu, NULL, "File");
	menu_file_quit = MwMenuAdd(menu, m, "Quit");

	m = MwMenuAdd(menu, NULL, "?Help");
	menu_help_version = MwMenuAdd(menu, m, "Version");

	MwAddUserHandler(window, MwNcloseHandler, gui_window_close, NULL);
	MwAddUserHandler(menu, MwNmenuHandler, gui_menu_menu, NULL);
}

void gui_loop(void){
	MwLoop(root);
}
