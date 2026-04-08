#include <stdio.h>
#include <stdarg.h>

int _doprintf(void *op, void (*put)(int, void *),const char *fmt, va_list ap);

struct _snbuf { char *pos; char *end; };

static void _snputc(int ch, void *op)
{
    struct _snbuf *sb = (struct _snbuf *)op;
    if (sb->pos < sb->end)
        *sb->pos = (char)ch;
    sb->pos++;
}

int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap)
{
    struct _snbuf sb;
    int n;
    sb.pos = buf;
    sb.end = (size > 0) ? (buf + size - 1) : buf;
    n = _doprintf((void *)&sb, _snputc, fmt, ap);
    if (size > 0)
        *((n < (int)(size - 1)) ? (buf + n) : (buf + size - 1)) = '\0';
    return n;
}

int snprintf(char *buf, size_t size, const char *fmt, ...)
{
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vsnprintf(buf, size, fmt, ap);
    va_end(ap);
    return n;
}
