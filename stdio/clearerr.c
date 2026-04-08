#include <stdio.h>

#undef clearerr

void clearerr (FILE *fp)
{
	if (fp != NULL)
		fp->_flag &= ~(_IOEOF | _IOERR);
}

