#include <ctype.h>

#undef isdigit

int isdigit (int c)
{
	if ((c < 0) || (c > 255))
		return 0;

    return (_CyTab[c] & _DG) != 0;
}
