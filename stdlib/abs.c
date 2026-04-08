#include <stdlib.h>

#undef abs

int abs(int i)
{
	if (i < 0)
		return -i;
	
	return i;
}

