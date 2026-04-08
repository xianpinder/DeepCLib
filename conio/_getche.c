#include <sys/agon.h>

int _getche(void)
{
	int c = _mos_getkey();
	_ac_vdu(c);
	return c;
}
