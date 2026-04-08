#include <agon/mos.h>
#include <curses.h>

// technically we can change colours, but I'm not going to make sure the color provided is valid.
int init_color(short color, short r, short g, short b)
{
	vdp_define_colour(color, 255, r, g, b);
	return OK;
}