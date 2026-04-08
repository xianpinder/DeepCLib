#ifndef _STDIO_H
#define _STDIO_H

#define NULL 0
#define FOPEN_MAX	(16)
#define FILENAME_MAX (128)

#ifndef _FPOS_T
#define _FPOS_T
typedef int fpos_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef _VA_LIST
#define _VA_LIST
typedef char *va_list;
#endif

#define _IOREAD		(1)
#define _IOWRT		(2)
#define _IOAPND		(4)
#define _IOBIN		(8)
#define _IOERR		(16)
#define _IOLASTR	(32)
#define _IOLASTW	(64)
#define _IOLBF		(128)
#define _IOFBF		(256)
#define _IONBF		(512)
#define _IOMYBUF	(1024)
#define _IOUCH		(2048)
#define _IOEOF		(4096)

#define BUFSIZ	(512)
#define EOF		(-1)
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

typedef struct
{
	unsigned int _flag;		/* flags */
	unsigned char *_ptr;	/* current position in buffer */
	unsigned char *_base;	/* pointer to start of buffer */
	int _cnt;				/* number of unread/unwritten bytes in buffer */
	int _file;				/* unix file descriptor */
	int _bsiz;				/* size of buffer */
	char *_tmpnam;			/* name of file if temporary */
	unsigned char _ch;		/* single char buffer for unbuffered files */
	unsigned char _uch;		/* char put back */
} FILE;

extern FILE _iob[FOPEN_MAX];

#define stdin		(&_iob[0])
#define stdout		(&_iob[1])
#define stderr		(&_iob[2])

#define L_tmpnam	(32)

void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE *, fpos_t *);
char *fgets(char *, int, FILE *);
FILE *fopen(const char *, const char *);
int fprintf(FILE *, const char *, ...);
int fputc(int, FILE *);
int fputs(const char *, FILE *);
size_t fread(void *, size_t, size_t, FILE *);
FILE *freopen(const char *, const char *, FILE *);
int fscanf(FILE *, const char *, ...);
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
int getc(FILE *);
int getchar(void);
char *gets(char *);
void perror(const char *);
int printf(const char *, ...);
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);
int scanf(const char *, ...);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);
int sprintf(char *, const char *, ...);
int sscanf(const char *, const char *, ...);
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE *, const char *, va_list);
int vfscanf(FILE *, const char *, va_list);
int vprintf(const char *, va_list);
int vscanf(const char *, va_list);
int vsprintf(char *, const char *, va_list);
int vsscanf(const char *, const char *, va_list);

#endif
