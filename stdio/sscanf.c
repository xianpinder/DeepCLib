#include <stdio.h>
#include <stdarg.h>

#undef sscanf
#undef vsscanf

extern int __scanf(void *ip, int (*get)(void *),int (*unget)(int, void *), const char *fmt, char **args);

static int sgetc(void *vp)
{
    unsigned char **s = (unsigned char **)vp;
    unsigned char c;

    c = *(*s)++;
    return (c == '\0') ? EOF : (int)c;
}

static int sungetc(int c, void *vp)
{
    unsigned char **s = (unsigned char **)vp;

    if (c == EOF)
        c = '\0';
    return *--(*s) = (unsigned char)c;
}

/* ================================================================== */
/*  Public interface: standard C89 functions                           */
/* ================================================================== */

int sscanf(const char *buf, const char *fmt, ...)
{
    va_list ap;
    int ret;
    const char *p = buf;

    va_start(ap, fmt);
    ret = __scanf(&p, sgetc, sungetc, fmt, (char **)ap);
    va_end(ap);
    return ret;
}

int vsscanf(const char *buf, const char *fmt, va_list ap)
{
    const char *p = buf;

    return __scanf(&p, sgetc, sungetc, fmt, (char **)ap);
}

