#include <stdio.h>
#include <stdarg.h>

int _doprintf(void *op, void (*put)(int, void *),const char *fmt, va_list ap);

static void _fputc_wrap(int ch, void *op)
{
    fputc(ch, (FILE *)op);
}

int vfprintf(FILE *fp, const char *fmt, va_list ap)
{
    return _doprintf((void *)fp, _fputc_wrap, fmt, ap);
}
