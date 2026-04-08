#include <fcntl.h>
#include <errno.h>

int isatty (int fd)
{
    if ((fd < 0) || (fd >= _FD_MAX))
    {
		errno = EBADF;
		return -1;
    }
    
    if (_FDTab[fd].handle == 0)
    {
        errno = EBADF;
		return -1;
    }

    return (_FDTab[fd].flags & O_VDP) != 0;
}
