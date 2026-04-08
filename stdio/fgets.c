#include <stdio.h>

#undef fgets

char *fgets (char *str, int n, FILE *fp)
{
    int ch;
    char *ptr;
	
	if ((str == NULL) || (fp == NULL))
		return NULL;

    ptr = str;
    while (--n > 0 && (ch = getc (fp)) != EOF)
    {
		*ptr++ = ch;
		if (ch == '\n')
			break;
    }

    if (ch == EOF && ptr == str)
		return NULL;
	
    *ptr = '\0';
    return str;
}
