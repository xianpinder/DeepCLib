#include <stdio.h>
#include <stdarg.h>

int _doprintf(void *op, void (*put)(int, void *),const char *fmt, va_list ap);

static void _sputc(int ch, void *op)
{
    char **bufp = (char **)op;
    **bufp = (char)ch;
    (*bufp)++;
}

int vsprintf(char *buf, const char *fmt, va_list ap)
{
    char *p = buf;
    int n = _doprintf((void *)&p, _sputc, fmt, ap);
    buf[n] = '\0';
    return n;
}

int sprintf(char *buf, const char *fmt, ...)
{
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsprintf(buf, fmt, ap);
    va_end(ap);
    return n;
}
