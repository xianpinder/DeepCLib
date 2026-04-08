#include <stdio.h>

int fputs (char *s, FILE *fp)
{
	if ((s == NULL) || (fp == NULL))
		return EOF;
	
    while (*s)
		if (fputc (*s++, fp) == EOF)
			return EOF;

    return 0;
}
