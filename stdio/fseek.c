#include <stdio.h>
#include <unistd.h>

#undef fseek

int fseek (FILE *fp, long offset, int origin)
{
    int rv = 0;

    if (fflush (fp) != 0)
        return EOF;

    fp->_flag &= ~_IOUCH;		/* Clear ungot character */
    
    if ((fp->_flag & _IOLASTR) && (origin == SEEK_CUR))
        offset -= fp->_cnt;

    fp->_flag &= ~(_IOLASTR | _IOLASTW | _IOEOF);
    fp->_cnt = 0;
    fp->_ptr = fp->_base;

    if ((origin == SEEK_SET) && (offset < 0))
        rv = -1;
    else
        rv = lseek (fp->_file, (int)offset, origin);

    if (rv == -1)
    {
        fp->_flag |= _IOERR;
		return EOF;
    }

    return 0;
}
