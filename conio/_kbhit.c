#include <sys/agon.h>

int _kbhit(void)
{
	return _inkey(0) != 0;
}
