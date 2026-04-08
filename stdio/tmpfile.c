#include <stdio.h>
#include <stdlib.h>

FILE *tmpfile (void)
{
    FILE *fp;
    char filename[L_tmpnam];
    
    tmpnam (filename);
    fp = fopen (filename, "wb+");
    if (fp != NULL)
    {
        fp->_tmpnam = (char *) malloc (strlen (filename) + 1);
		if (fp->_tmpnam == NULL)
		{
			fclose (fp);
			return NULL;
		}
		strcpy (fp->_tmpnam, filename);
    }

    return fp;
}
