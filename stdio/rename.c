#include <stdio.h>
#include <sys/agon.h>

int rename(const char *src, const char *dst)
{
	_mos_ren (src,dst);
	return 0;
}
