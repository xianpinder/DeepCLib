#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/agon.h>

typedef struct
{
	unsigned int v;
	unsigned char u;
} WORD32;

int lseek (int fd, int offset, int whence)
{
    unsigned int fh;
    int from;
	WORD32 pos;
	void *fil;
	_FD *fp;

	if ((whence != SEEK_SET) && (whence != SEEK_CUR) && (whence != SEEK_END))
		return -1;

    if ((fd < 0) || (fd >= _FD_MAX))
    {
		errno = EBADF;
		return -1;
    }

	fp = &_FDTab[fd];
	fh = fp->handle;
    if (fh == 0)
    {
        errno = EBADF;
		return -1;
    }
	
	pos.v = 0;
	pos.u = 0;
	
	if (whence == SEEK_CUR)
	{
		fil = _mos_getfil (fh);
		_ffs_ftell (fil, &pos);
		fp->pos = pos.v;
		if (offset == 0)
			return fp->pos;
	}
	else
		if (whence == SEEK_END)
			pos.v = fp->size;

	if ((offset < 0) && (-offset > pos.v))
		pos.v = 0;
	else
		pos.v += offset;

	int rv = _mos_flseek_p (fh, &pos);
	if (rv != 0)
	{
		errno = rv;
		return -1;
	}

	fil = _mos_getfil (fh);
	_ffs_ftell (fil, &pos);
	fp->pos = pos.v;
	if (fp->pos > fp->size)
		fp->size = fp->pos;
		
	return fp->pos;
}

