#include <stdio.h>

#undef fgetc

static int readchar(FILE *fp)
{
	int count;
    unsigned int f = fp->_flag;

    if (f & _IOUCH)					/* If a character has been put	*/
    {								/* back then use it as the	*/
        fp->_flag &= ~_IOUCH;		/* return character.		*/
        return fp->_uch;
    }

    if (fp->_cnt <= 0)
    {
		count = read (fp->_file, fp->_base, fp->_bsiz);

		if (count < 0)
		{
			fp->_flag |= _IOERR;
			return EOF;
		}

		if (count == 0)
		{
			fp->_flag |= _IOEOF;
			fp->_flag &= ~_IOLASTR;
			return EOF;
		}

		fp->_cnt = count;
		fp->_ptr = fp->_base;
    }

    fp->_cnt--;
    return *fp->_ptr++;
}


int fgetc(FILE *fp)
{
	int c;
    unsigned int f;

	if (fp == NULL)
		return EOF;

	f = fp->_flag;

    if (f & (_IOEOF | _IOERR))		/* EOF or Error has occured */
		return EOF;

    if ((f & _IOREAD) == 0)			/* File not open for read access */
		return EOF;

    if ((f & _IOLASTW) != 0)		/* Cannot read directly after	*/
    {								/* a write.			*/
        fp->_flag |= _IOERR;
		return EOF;
    }

    fp->_flag |= _IOLASTR;			/* Last action a read.		*/

	c = readchar(fp);
	
	if ((c == '\r') && ((fp->_flag & _IOBIN) == 0))
		c = readchar(fp);

	return c;
}
