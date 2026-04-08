#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/agon.h>

#define FA_OPEN_EXISTING	0x00		// Open file if it exists, fail if it doesn't
#define FA_READ	 	 		0x01		// Open file for reading
#define FA_WRITE		 	0x02		// Open file for writing. Combine with FA_READ for read/write access
#define FA_CREATE_NEW	 	0x04		// Create a new file, fail if it already exists
#define FA_CREATE_ALWAYS 	0x08		// Create a new file. If the file already exists it will be truncated and overwritten
#define FA_OPEN_ALWAYS	 	0x10		// Open file if it exists, create it if it doesn't
#define FA_OPEN_APPEND	 	0x30		// Same as FA_OPEN_ALWAYS, except the read/write pointer will be set to the end of the file


int open(const char *path, int flags, ...)
{
	unsigned int mos_mode = 0;
	int fd;
	unsigned int mos_fh;
	void *fil;
	uint32_t size;

	for (fd = 0; fd < _FD_MAX; fd++)
    {
		if (_FDTab[fd].handle == 0)
			break;
    }

    if (fd >= _FD_MAX)
    {
        errno = EMFILE;
		return -1;
    }

	switch (flags & O_ACCMODE)
	{
		case O_RDONLY:
			mos_mode = FA_READ;
			break;
		
		case O_WRONLY:
			mos_mode = FA_WRITE;
			break;

		case O_RDWR:
			mos_mode = FA_READ | FA_WRITE;
			break;
		
		default:
			return -1;
	}

	if (flags & O_CREAT)
		mos_mode |= FA_OPEN_ALWAYS;
	
	if (flags & O_TRUNC)
		mos_mode |= FA_CREATE_ALWAYS;
	
	if (flags & O_APPEND)
		mos_mode |= FA_OPEN_APPEND;
	
	mos_fh = _mos_fopen(path, mos_mode);
	if (mos_fh == 0)
	{
		//errno = ?
		return -1;
	}

	fil = _mos_getfil (mos_fh);
	_ffs_fsize (fil, &size);

    _FDTab[fd].handle = mos_fh;
    _FDTab[fd].flags = flags;
	_FDTab[fd].pos = 0;
	_FDTab[fd].size = size;
	

	if (flags & O_APPEND)
		lseek (fd, 0, SEEK_END) ;

	return fd;
}

int close (int fd)
{
	_FD *ptr;
	unsigned int mos_fh;

    if ((fd < 0) || (fd > _FD_MAX))
    {
        errno = EBADF;
		return -1;
    }

    ptr = &_FDTab[fd];

    mos_fh = ptr->handle;
    if (mos_fh == 0)
    {
        errno = EBADF;
		return -1;
    }
    
    if ((ptr->flags & O_VDP) == 0)
    {
		_mos_fclose (mos_fh);
		ptr->handle = 0;
		ptr->flags = 0;
    }

    return 0;
}

int write (int fd, void *buf, unsigned int nbytes)
{
	unsigned int mos_fh;		// mos file handle
	unsigned int oflags;
	unsigned int acc;
	int n;
	_FD *fp;
	
	if ((fd < 0) || (fd >= _FD_MAX))
    {
		errno = EBADF;
		return -1;
    }

	fp = &_FDTab[fd];
	mos_fh = fp->handle;
	oflags = fp->flags;
	
	if (mos_fh == 0)
	{
		errno = EBADF;
		return -2;
	}

	acc = oflags & O_ACCMODE;
	
	// check file is open for writing
	if ((acc != O_WRONLY) && (acc != O_RDWR))
	{
		return -3;
	}

	if (oflags & O_VDP)
	{
		_vdp_write (buf, nbytes);
		return nbytes;
	}

	n = _mos_fwrite(mos_fh, buf, nbytes);
	
	if (n > 0)
	{
		fp->pos += n;
		if (fp->pos > fp->size)
			fp->size = fp->pos;
	}
	
	return n;
}


int read (int fd, void *buf, unsigned int nbytes)
{
	unsigned int mos_fh;		// mos file handle
	unsigned int oflags;
	unsigned int acc;
	char *cbuf = (char *)buf;
	int rv, len, n;
	_FD *fp;
	
	if ((fd < 0) || (fd >= _FD_MAX))
    {
		errno = EBADF;
		return -1;
    }

	fp = &_FDTab[fd];
	mos_fh = fp->handle;
	oflags = fp->flags;
	
	if (mos_fh == 0)
	{
		errno = EBADF;
		return -1;
	}

	acc = oflags & O_ACCMODE;
	
	// check file is open for writing
	if ((acc != O_RDONLY) && (acc != O_RDWR))
	{
		return -1;
	}

	if (nbytes == 0)
		return 0;

	if (oflags & O_VDP)
	{
		if (nbytes == 1)
		{
			cbuf[0] = (char)_mos_getkey();
			return 1;
		}

		rv = _mos_editline (cbuf, nbytes, 1);
		len = strlen(cbuf);
		cbuf[len] = '\n';
		return len + 1;
	}

	n = _mos_fread(mos_fh, buf, nbytes);
	if (n > 0)
		fp->pos += n;
	
	return n;
}
