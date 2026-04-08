#ifndef _STDDEF_H
#define _STDDEF_H

#define NULL	0

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

typedef int ptrdiff_t;

#ifndef _WCHAR_T
#define _WCHAR_T
typedef int wchar_t;
#endif

#define offsetof(T, member)	((size_t)&((T *)0)->member)

#endif
