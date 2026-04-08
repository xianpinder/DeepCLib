#include <stdio.h>

int fclose (FILE *fp)
{
    fflush (fp);

    if ((fp->_flag & _IOMYBUF) && (fp->_base != NULL))
        free (fp->_base);

    fp->_flag = 0;

    if (close (fp->_file) != 0)
        return EOF;

    if (fp->_tmpnam != NULL)
    {
        remove (fp->_tmpnam);
		free (fp->_tmpnam);
		fp->_tmpnam = NULL;
    }

    return 0;
}
