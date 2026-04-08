#include <stdio.h>

#undef ungetc

int ungetc (int ch, FILE *fp)
{
    unsigned int f;

    if ((fp == NULL) || (ch == EOF))
        return EOF;

    f = fp->_flag;

    if ((f & _IOUCH) || (f & _IOLASTW) || ((f & _IOREAD) == 0))
        return EOF;

    fp->_uch = ch;
    fp->_flag |= _IOUCH;
    fp->_flag &= ~_IOEOF;
    return ch;
}

