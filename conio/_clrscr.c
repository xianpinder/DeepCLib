#include <sys/agon.h>

void _clrscr(void)
{
	_ac_vdu(12);
}
