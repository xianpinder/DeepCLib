#include <stdio.h>

#undef getc

int getc (FILE *fp)
{
    return (fgetc (fp));
}

