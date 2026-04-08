#include <agon/mos.h>
#include <curses.h>

int getcurx(int win)
{
	_ac_vdu_reqtxtpos();
	return _sysvars->cursorX;
}