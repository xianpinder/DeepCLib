#include <stdio.h>
#include <string.h>

#undef fread

size_t fread(void *ptr, size_t size, size_t count, FILE *fp)
{
    unsigned char *p = (unsigned char *)ptr;
    size_t total, done, chunk;

    if (size == 0 || count == 0 || ptr == NULL || fp == NULL)
        return 0;

    if (fp->_flag & (_IOEOF | _IOERR))
        return 0;

    if ((fp->_flag & _IOREAD) == 0)
        return 0;

    if (fp->_flag & _IOLASTW)
    {
        fp->_flag |= _IOERR;
        return 0;
    }

    fp->_flag |= _IOLASTR;
    total = size * count;

    /* Text mode: must go byte-at-a-time for CR stripping */
    if ((fp->_flag & _IOBIN) == 0)
    {
        size_t n, s;
        int c;

        for (n = 0; n < count; ++n)
        {
            for (s = 0; s < size; ++s)
            {
                c = fgetc(fp);
                if (c == EOF)
                    return n;
                *p++ = (unsigned char)c;
            }
        }
        return count;
    }

    /* Binary mode: bulk copy from buffer */

    /* First drain any ungetch character */
    if (fp->_flag & _IOUCH)
    {
        *p++ = (unsigned char)fp->_uch;
        fp->_flag &= ~_IOUCH;
        total--;
        if (total == 0)
            return count;
    }

    done = 0;

	while (done < total)
    {
        /* If buffer has data, copy from it */
        if (fp->_cnt > 0)
        {
            chunk = total - done;
            if (chunk > (size_t)fp->_cnt)
                chunk = (size_t)fp->_cnt;

            memcpy(p, fp->_ptr, chunk);
            p += chunk;
            fp->_ptr += chunk;
            fp->_cnt -= chunk;
            done += chunk;
        }
        else
        {
            /* Buffer empty: read directly into user buffer */
            int n = read(fp->_file, p, total - done);
            if (n <= 0)
            {
                fp->_flag |= (n == 0) ? _IOEOF : _IOERR;
                break;
            }
            p += n;
            done += n;
        }
    }

    return done / size;
}