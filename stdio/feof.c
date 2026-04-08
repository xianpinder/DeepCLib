#include <stdio.h>

#undef feof

int feof (FILE *fp)
{
	if (fp == NULL)
		return 1;

    return fp->_flag & _IOEOF;
}

