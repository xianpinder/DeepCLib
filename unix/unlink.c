#include <sys/agon.h>

int unlink(char *filename)
{
	return _mos_del(filename);
}
