#include <agon/mos.h>
#include <curses.h>

int getcury(int win)
{
	_ac_vdu_reqtxtpos();
	return _sysvars->cursorY;
}