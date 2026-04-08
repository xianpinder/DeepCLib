#include <fcntl.h>
#include <stdio.h>

_FD _FDTab[_FD_MAX];		/* Table of Unix file descriptors */
FILE _iob[FOPEN_MAX];		/* Table of std c FILE descriptors */

void _init_fds(void)
{
	int i;
	FILE *fp;
	
	_FDTab[0].handle = 255;
	_FDTab[0].flags = O_RDONLY | O_VDP;		// stdin

	_FDTab[1].handle = 255;
	_FDTab[1].flags = O_WRONLY | O_VDP;		// stdout

	_FDTab[2].handle = 255;
	_FDTab[2].flags = O_WRONLY | O_VDP;		// stderr

	for (i = 3; i < _FD_MAX; ++i)
		_FDTab[i].handle = 0;
	
	fp = stdin;
	fp->_file = 0;
	fp->_flag = _IOREAD;
	fp->_base = NULL;
	setvbuf (fp, NULL, _IOLBF, 256);

	fp = stdout;
	fp->_file = 1;
	fp->_flag = _IOWRT;
	fp->_base = NULL;
	setvbuf (fp, NULL, _IONBF, 0);

	fp = stderr;
	fp->_file = 2;
	fp->_flag = _IOWRT;
	fp->_base = NULL;
	setvbuf (fp, NULL, _IONBF, 0);
}

void _close_fds(void)
{
	int i;
	
	for (i = 0; i < FOPEN_MAX; ++i)
	{
		if ((_iob[i]._flag & (_IOREAD | _IOWRT)) != 0)
			fclose (&_iob[i]);
	}

	for (i = 0; i < _FD_MAX; ++i)
	{
		if (_FDTab[i].handle != 0)
			close (i);
	}
}
