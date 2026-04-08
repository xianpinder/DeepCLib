#include <stdio.h>
#include <stdlib.h>

int setvbuf(FILE *fp, char *sbuf, int mode, size_t size)
{
    unsigned char *buf = (unsigned char *)sbuf;
    int mybuf = 0;

    if (fp == NULL)
        return 1;

    if ((size == 0) && (mode != _IONBF))
        return 1;

    if ((mode != _IOFBF) && (mode != _IOLBF) && (mode != _IONBF))
        return 1;

    if (fp->_flag & (_IOLASTR | _IOLASTW))
        return 1;

    if ((buf == NULL) && (mode != _IONBF))
    {
        buf = (unsigned char *)malloc(size);
        if (buf == NULL)
            return 1;
        mybuf = 1;
    }

    if ((fp->_flag & _IOMYBUF) && (fp->_base != NULL))
        free(fp->_base);

    fp->_flag &= ~(_IOFBF | _IOLBF | _IONBF | _IOMYBUF);
    fp->_flag |= mode;
    if (mybuf)
        fp->_flag |= _IOMYBUF;

    fp->_cnt = 0;

    if (mode == _IONBF)
    {
        buf = &fp->_ch;
        size = 1;
    }

    fp->_base = buf;
    fp->_bsiz = size;
    fp->_ptr = fp->_base;

    return 0;
}
