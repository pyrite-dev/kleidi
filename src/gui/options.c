/* $Id$ */
#include "../kleidi.h"

static void gui_options_close(MwWidget handle, void* user, void* client) {
	MwDestroyWidget(user);
}

void gui_options(void) {
	int	    w = (gui_width < 1000 ? 1000 : gui_width) * 3 / 4, h = w * 3 / 4;
	int	    x = MwGetInteger(window, MwNx) + (MwGetInteger(window, MwNwidth) - w) / 2;
	int	    y = MwGetInteger(window, MwNy) + (MwGetInteger(window, MwNheight) - h) / 2;
	MwSizeHints sh;
	MwWidget    options, list, frame, button;

	sh.min_width = sh.max_width = w;
	sh.min_height = sh.max_height = h;

	options = MwVaCreateWidget(MwWindowClass, "options", root, x, y, w, h,
				   MwNtitle, "Options",
				   MwNsizeHints, &sh,
				   NULL);

	list = MwCreateWidget(MwListBoxClass, "list", options, 10, 10, 160, h - 10 - 10 - 24 - 10);

	frame = MwCreateWidget(MwFrameClass, "frame", options, 10 + 160 + 10, 10, w - 10 - 160 - 10 - 10, h - 10 - 10 - 24 - 10);

	button = MwVaCreateWidget(MwButtonClass, "button", options, w - 10 - 96, h - 10 - 24, 96, 24,
				  MwNtext, "OK",
				  NULL);

	MwAddUserHandler(options, MwNcloseHandler, gui_options_close, options);
	MwAddUserHandler(button, MwNactivateHandler, gui_options_close, options);
}
