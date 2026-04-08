#include <stdio.h>

static void addchar (char ch, FILE *fp)
{
    *fp->_ptr++ = ch;			/* Insert character into buffer. */
    fp->_cnt++;

	/* if the buffer is full write the data */
    if (fp->_cnt >= fp->_bsiz)
		fflush (fp);
}

int fputc (int ch, FILE *fp)
{
	unsigned int f;
	
	if (fp == NULL)
		return EOF;
	
    f = fp->_flag;

    if ((f & _IOERR) ||			/* If file has an error or	*/
        (f & _IOLASTR) ||		/* last action was a read or	*/
	((f & _IOWRT) == 0))		/* file not open for writing	*/
    {
        fp->_flag |= _IOERR;	/* then set error flag and	*/
        return EOF;				/* return EOF.			*/
    }

    fp->_flag |= _IOLASTW;		/* Last action was a write.	*/

	if ((ch == '\n') && ((f & _IOBIN) == 0))
		addchar ('\r', fp);
	
	addchar (ch, fp);

    if ((f & _IOLBF) && (ch == '\n'))
		fflush (fp);
 
	if (fp->_flag & _IOERR)
		return EOF;

    return ch;
}
