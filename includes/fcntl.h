#ifndef FCNTL_H
#define FCNTL_H

#include <stdint.h>

#define O_RDONLY	(0)
#define O_WRONLY	(1)
#define O_RDWR		(2)
#define O_ACCMODE	(3)
#define O_CREAT		(4)
#define O_TRUNC		(8)
#define O_EXCL		(16)
#define O_APPEND	(32)
#define O_VDP		(64)

#define _FD_MAX		(16)

struct _FileDesc
{
	unsigned int handle;
	unsigned int flags;
	uint32_t pos;
	uint32_t size;
};

typedef struct _FileDesc _FD;

extern _FD _FDTab[_FD_MAX];		/* Table of Unix file descriptors */

int open(const char *, int, ... );
int close (int);
int write (int, void *, unsigned int);
int read (int, void *, unsigned int);

#endif
