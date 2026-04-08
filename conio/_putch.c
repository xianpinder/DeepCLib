#include <sys/agon.h>

int _putch(int c)
{
	_ac_vdu(c);
	return c;
}
