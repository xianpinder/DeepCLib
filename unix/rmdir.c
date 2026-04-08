#include <sys/agon.h>

int rmdir(char *filename)
{
	return _mos_del(filename);
}
