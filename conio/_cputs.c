#include <sys/agon.h>

int _cputs(const char *str)
{
	_ac_vdp_write (str, 0);
	return 0;
}
