/* $Id$ */
#include "kleidi.h"

static void gui_version_close(MwWidget handle, void* user, void* client) {
	MwDestroyWidget(user);
}

void gui_version(void) {
	int	    w = 600, h = 200;
	int	    x	    = MwGetInteger(window, MwNx) + (MwGetInteger(window, MwNwidth) - w) / 2;
	int	    y	    = MwGetInteger(window, MwNy) + (MwGetInteger(window, MwNheight) - h) / 2;
	int	    t	    = MwTextHeight(window, "M");
	const char* texts[] = {
	    "Kleidi GUI Builder",
	    "Version " VERSION,
	    "",
	    "Milsko version " MwVERSION,
	    NULL};
	int	    i;
	MwSizeHints sh;
	MwWidget    version, image, button;

	sh.min_width = sh.max_width = w;
	sh.min_height = sh.max_height = h;

	version = MwVaCreateWidget(MwWindowClass, "version", root, x, y, w, h,
				   MwNtitle, "Version information",
				   MwNsizeHints, &sh,
				   NULL);
	image	= MwVaCreateWidget(MwImageClass, "image", version, 10, 10, h - 20, h - 20,
				   MwNpixmap, logo_pixmap,
				   NULL);
	button	= MwVaCreateWidget(MwButtonClass, "button", version, w - 96 - 10, h - 24 - 10, 96, 24,
				   MwNtext, "OK",
				   NULL);

	for(i = 0; texts[i] != NULL; i++) {
		if(strlen(texts[i]) == 0) continue;
		(void)MwVaCreateWidget(MwLabelClass, "label", version, h, 10 + ((h - 20) - (t * 4)) / 2 + t * i, w - h, t,
				       MwNtext, texts[i],
				       MwNbold, i == 0 ? 1 : 0,
				       MwNalignment, MwALIGNMENT_BEGINNING,
				       NULL);
	}

	MwAddUserHandler(version, MwNcloseHandler, gui_version_close, version);
	MwAddUserHandler(button, MwNactivateHandler, gui_version_close, version);
}
