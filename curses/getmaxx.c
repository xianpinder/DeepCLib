#include <agon/mos.h>
#include <curses.h>

int getmaxx(int win)
{
	vdp_get_scr_dims(1);
	return _sysvars->scrCols;
};