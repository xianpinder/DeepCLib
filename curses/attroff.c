#include <agon/vdp.h>
#include <curses.h>

// I'm currently turning EVERYTHING off, which is not correct, but will do for now.
int attroff (int attrs)
{
	vdp_set_text_colour(COLOR_WHITE);
	vdp_set_text_colour(COLOR_BLACK + COLOR_BG);
	return OK;
}
