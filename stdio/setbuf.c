#include <stdio.h>

#undef setbuf

void setbuf (FILE *fp, char *buf)
{
    setvbuf (fp, buf, (buf == NULL) ? _IONBF : _IOFBF, BUFSIZ);
}
