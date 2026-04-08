#include <stdio.h>

#undef ftell

long ftell (FILE *fp)
{
    return fgetpos(fp, NULL);
}

