#include <stdio.h>

#undef putc

int putc (int ch, FILE *fp)
{
    return fputc (ch, fp);
}

