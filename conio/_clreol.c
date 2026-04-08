#include <stddef.h>
#include <conio.h>

static unsigned char disable_scroll[] = {23, 16, 0x51, 0};
static unsigned char enable_scroll[] = {23, 16, 0, 0};

void _clreol(void)
{
	_gettextinfo(NULL);
	
	int n = _conio_info.winright - _conio_info.curx;

	_ac_vdp_write (disable_scroll, sizeof(disable_scroll));
	
	while (n--)
		_ac_vdu(' ');

	_gotoxy (_conio_info.curx, _conio_info.cury);

	_ac_vdp_write (enable_scroll, sizeof(enable_scroll));
}