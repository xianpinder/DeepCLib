#include <stdio.h>
#include <fcntl.h>

#undef fopen

FILE *_Fopen (char *filename, char *mode, FILE *fp)
{
    char *p = NULL;
    int fd, iomode = 0, f = 0;
    int bufmode;

    switch (*mode++)
    {
        case 'r':
			f |= _IOREAD;
			break;

		case 'w':
			f |= _IOWRT;
			iomode |= (O_CREAT | O_TRUNC);
			break;

		case 'a':
			f |= _IOWRT | _IOAPND;
			iomode |= (O_CREAT | O_APPEND);
			break;

    	default:
			return NULL;
    }

    if (*mode == '+')
    {
        f |= (_IOREAD | _IOWRT);
		if (*++mode == 'b')
			f |= _IOBIN;
    }
    else
	{
		if (*mode == 'b')
		{
			f |= _IOBIN;
			if (*++mode == '+')
				f |= (_IOREAD | _IOWRT);
		}
    }

    if ((f & (_IOREAD | _IOWRT)) == 0)
        return NULL;

    if ((f & (_IOREAD | _IOWRT)) == (_IOREAD | _IOWRT))
		iomode |= O_RDWR;
    else
	{
		if (f & _IOWRT)
			iomode |= O_WRONLY;
		else
			iomode |= O_RDONLY;
	}

    fd = open (filename, iomode, 0600);
    if (fd < 0)
        return NULL;			/* file open/create error */

    fp->_file = fd;				/* file descriptor */
    fp->_flag = f;				/* file status flags */
    fp->_base = NULL;
    fp->_tmpnam = NULL;

    bufmode = (isatty (fd)) ? _IOLBF : _IOFBF; 
    if (setvbuf (fp, NULL, bufmode, BUFSIZ) != 0)
        return NULL;
    
    return fp;
}


FILE *fopen (char *filename, char *mode)
{
    int i;
    FILE *fp;

    for (i = 0; i < FOPEN_MAX; i++)
        if ((_iob[i]._flag & (_IOREAD | _IOWRT)) == 0)
			break;

    if (i >= FOPEN_MAX)
        return NULL;	    		/* Return if no files left... */

    return _Fopen (filename, mode, &_iob[i]);
}
