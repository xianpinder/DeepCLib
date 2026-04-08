#include <stdio.h>
#include <stdarg.h>

#undef fscanf
#undef vscanf
#undef scanf
#undef vscanf

extern int __scanf(void *ip, int (*get)(void *),int (*unget)(int, void *), const char *fmt, char **args);

static int fgetc_cb(void *vp)
{
    return fgetc((FILE *)vp);
}

static int fungetc_cb(int c, void *vp)
{
    return ungetc(c, (FILE *)vp);
}

int fscanf(FILE *stream, const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = __scanf(stream, fgetc_cb, fungetc_cb, fmt, (char **)ap);
    va_end(ap);
    return ret;
}

int scanf(const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = __scanf(stdin, fgetc_cb, fungetc_cb, fmt, (char **)ap);
    va_end(ap);
    return ret;
}

int vfscanf(FILE *stream, const char *fmt, va_list ap)
{
    return __scanf(stream, fgetc_cb, fungetc_cb, fmt, (char **)ap);
}

int vscanf(const char *fmt, va_list ap)
{
    return __scanf(stdin, fgetc_cb, fungetc_cb, fmt, (char **)ap);
}
