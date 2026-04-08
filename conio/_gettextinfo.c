#include <stddef.h>
#include <sys/agon.h>
#include <conio.h>

void _gettextinfo (struct text_info *r)
{
	_ac_vdu_reqtxtpos();
	
	_conio_info.curx = _sysvars->cursorX + 1;
	_conio_info.cury = _sysvars->cursorY + 1;
	
	if (r != NULL)
		*r = _conio_info;
}