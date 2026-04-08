#include <stdio.h>

#undef freopen

FILE *_Fopen (char *filename, char *mode, FILE *fp);

FILE *freopen (char *filename, char *mode, FILE *fp)
{
	if (fp == NULL)
		return NULL;

    if (fclose(fp) == EOF)
        return NULL;

    return _Fopen (filename, mode, fp);
}
