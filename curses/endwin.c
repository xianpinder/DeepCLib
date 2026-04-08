#include <agon/vdp.h>
#include <curses.h>

//dump font and reset text mode to bright white on black. NOTE: assumes video mode has at least 16 colours
int endwin(void)
{
	vdp_reset_system_font();
	vdp_set_text_colour(COLOR_WHITE + 8);
	vdp_set_text_colour(COLOR_BLACK + COLOR_BG);
	vdp_cursor_enable(true);
	return OK;
};

