#include <stdio.h>

#undef gets

char *gets (char *str)
{
    int ch;
    char *ptr;

	if (str == NULL)
		return NULL;

    ptr = str;
    while ((ch = getc (stdin)) != EOF && ch != '\n')
		*ptr++ = ch;

    if (ch == EOF && ptr == str)
		return NULL;

    *ptr = '\0';
    return str;
}
