#include <agon/mos.h>
#include <curses.h>

int getmaxy(int win)
{
	vdp_get_scr_dims(1);
	return _sysvars->scrRows;
}
