#ifndef _STRINGS_H
#define _STRINGS_H

#include <stddef.h>
#include <string.h>

int _strcasecmp(const char *s1, const char *s2);
int _strncasecmp(const char *s1, const char *s2, size_t n);

#define strcasecmp  _strcasecmp
#define strncasecmp _strncasecmp
#define strnicmp _strncasecmp
#define stricmp _strcasecmp

#ifdef _OLD_BSD_STRINGS
#define bcopy(src,dst,n)	memmove((dst),(src),(n))
#define bzero(s,n)     		memset((s),0,(n))
#define bcmp(a,b,n)			memcmp((a),(b),(n))
#define index(s,c)			strchr((s),(c))
#define rindex(s,c)			strrchr((s),(c))
#endif

#endif
