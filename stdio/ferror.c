#include <stdio.h>

#undef ferror

int ferror (FILE *fp)
{
	if (fp == NULL)
		return 1;

    return fp->_flag & _IOERR;
}

