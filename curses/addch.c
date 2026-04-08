#include <agon/vdp.h>
#include <curses.h>

int addch(const chtype ch)
{
	short color,f,b,bold;

	color = ch >> 8;
	bold = (color & (A_BOLD >> 8)) >> 2;
	color = (color & COLOR_PAIRS);
	if (color > 0)
	{
		pair_content(color, &f, &b);
		vdp_set_text_colour(f + bold);
	}
	else
	{
		vdp_set_text_colour(COLOR_WHITE + bold );
	}
	putchar(ch);
	return OK;
}