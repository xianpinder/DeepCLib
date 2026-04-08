#ifndef _STRING_H
#define _STRING_H

#define NULL	0

#ifndef _SIZE_T
#define _SIZE_T
typedef int size_t;
#endif

char *strcat(char *, const char *);
char *strchr(const char *, int);
char *strcpy(char *, const char *);
char *strerror(int);
char *strncat(char *, const char *, size_t);
char *strncpy(char *, const char *, size_t);
char *strpbrk(const char *, const char *);
char *strrchr(const char *, int);
char *strstr(const char *, const char *);
char *strtok(char *, const char *);
int memcmp(const void *, const void *, size_t);
int strcmp(const char *, const char *);
int strcoll(const char *, const char *);
int strncmp(const char *, const char *, size_t);
size_t strcspn(const char *, const char *);
size_t strlen(const char *);
size_t strspn(const char *, const char *);
size_t strxfrm(char *, const char *, size_t);
void *memchr(const void *, int, size_t);
void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);

/* asmcall interfaces for internal use */
__asmcall size_t _ac_strlen(const char *);
__asmcall int _ac_strcmp(const char *, const char *);
__asmcall void _ac_memset(void *, int, size_t);
#endif
