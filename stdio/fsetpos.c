#include <stdio.h>

int fsetpos (FILE *fp, fpos_t *pos)
{
    int rv;

    if (pos != NULL)
    {
		rv = fseek (fp, *pos, SEEK_SET);
		if (rv >= 0)
		{
			clearerr (fp);
			return 0;
		}
    }
    return 1;
}
