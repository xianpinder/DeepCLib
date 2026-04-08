#ifndef _UNISTD_H
#define _UNISTD_H

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

int close (int);
int isatty (int);
int lseek (int, int, int);
int read (int, void *, unsigned int);
int rmdir (const char *);
int unlink (const char *);
int write (int, void *, unsigned int);

#endif
