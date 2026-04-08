#include <stdio.h>

#undef tmpnam

static char tmpstr[L_tmpnam];
static unsigned int count = 0;

char *tmpnam(char *tn)
{
    char *tmpptr;

    tmpptr = (tn == NULL) ? tmpstr : tn;
	++count;
    sprintf (tmpptr, "tmpfile%06X.tmp", count);
    return tmpptr;
}
