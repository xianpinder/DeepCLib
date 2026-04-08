#include <sys/agon.h>

int _getch(void)
{
	return _mos_getkey();
}
