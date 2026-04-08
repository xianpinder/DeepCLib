#ifndef _ERRNO_H
#define _ERRNO_H

#define ESDACC		1		// Error accessing the SD card
#define EINTERR		2		// Internal error
#define ESDFAIL		3		// SD card failure
#define	ENOENT		4		// No such file or directory
#define ENOPATH		5		// The path could not be found
#define EINVPATH	6		// Invalid path
#define	EPERM		7		// Access denied or directory full
#define EACCES 		8		// Access denied 
#define	EBADF		9		// Bad file descriptor
#define	EROFS		10		// File system is read-only
#define	ENODEV		11		// Logical drive number is invalid
#define EIO			12		// Volume has no work area
#define	ENOTBLK		13		// No valid FAT volume
#define EMKFS		14		// Error occurred during mkfs
#define ETIME		15		// Volume timeout
#define EBUSY		16		// Volume locked
#define ENOBUFS		17		// LFN working buffer could not be allocated
#define	ENFILE		18		// Too many open files
#define	EMFILE		18		// Too many open files
#define	EINVAL		19		// Invalid parameter
#define EBADCMD		20		// Invalid command
#define	ENOEXEC		21		// Invalid executable
#define	ENOMEM		22		// Out of memory
#define ENOSYS		23		// Not implemented

#define	EDOM		33		// Numerical argument out of domain
#define	ERANGE		34		// Numerical result out of range
#define EILSEQ		35		// Invalid or incomplete multibyte or wide character

extern int errno;

#endif
