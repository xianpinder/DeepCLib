#include <stdio.h>

#undef fflush

static int flush (FILE *fp)
{
    int rv = 0;
    int f = fp->_flag;

    if (f & _IOERR)			/* Has an error occured ? */
		return EOF;

    if (((f & _IOWRT) == 0) ||		/* Is file open for writing ? */
        ((f & _IOLASTW) == 0))		/* Has a write been performed ? */
        return 0;

	if (fp->_cnt > 0)
	{
		unsigned char *base = fp->_base;
		int remaining = fp->_cnt;

		while (remaining > 0)
		{
			int n = write(fp->_file, base, remaining);
			if (n <= 0)
			{
				fp->_flag |= _IOERR;
				rv = EOF;
				break;
			}
			base += n;
			remaining -= n;
		}
	}

    fp->_ptr = fp->_base;
    fp->_cnt = 0;

    return rv;
}


int fflush(FILE *fp)
{
    int i, rv = 0;

    if (fp != NULL)
        return flush(fp);

    for (i = 0; i < FOPEN_MAX; i++)
    {
        if (flush(&_iob[i]) == EOF)
            rv = EOF;
    }

    return rv;
}
