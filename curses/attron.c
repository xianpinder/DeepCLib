#include <agon/vdp.h>
#include <curses.h>

int attron (const chtype attrs)
{
	short color,f,b,bold;

	color = attrs >> 8;
	bold = (color & (A_BOLD >> 8)) >> 2;
	color = (color & COLOR_PAIRS);
	if (color > 0)
	{
		pair_content(color, &f, &b);
		vdp_set_text_colour(f + bold);
	}
	else
	{
		vdp_set_text_colour(COLOR_WHITE + bold);
	}

	return OK;
}

