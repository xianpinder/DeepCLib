#include <stdio.h>

#undef rewind

void rewind (FILE *fp)
{
    fseek (fp, 0L, SEEK_SET);
    clearerr (fp);
}
