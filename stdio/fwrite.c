#include <stdio.h>

size_t fwrite(const void *ptr, size_t size, size_t count, FILE *fp)
{
    const unsigned char *p = (const unsigned char *)ptr;
    size_t total, done, chunk, avail;

    if (size == 0 || count == 0 || ptr == NULL || fp == NULL)
        return 0;

    if (fp->_flag & _IOERR)
        return 0;

    if ((fp->_flag & _IOWRT) == 0 || (fp->_flag & _IOLASTR))
    {
        fp->_flag |= _IOERR;
        return 0;
    }

    fp->_flag |= _IOLASTW;
    total = size * count;

    /* Text mode: byte-at-a-time for CR insertion */
    if ((fp->_flag & _IOBIN) == 0)
    {
        size_t n, s;
        int c;

        for (n = 0; n < count; ++n)
        {
            for (s = 0; s < size; ++s)
            {
                c = fputc(*p++, fp);
                if (c == EOF)
                    return n;
            }
        }
        return count;
    }

	/* Binary mode: flush buffer then write directly */
    done = 0;

    if (fp->_cnt > 0)
    {
        fflush(fp);
        if (fp->_flag & _IOERR)
            return 0;
    }

    while (done < total)
    {
        int n = write(fp->_file, p, total - done);
        if (n <= 0)
        {
            fp->_flag |= _IOERR;
            break;
        }
        p += n;
        done += n;
    }

    return done / size;
}