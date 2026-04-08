#include <sys/agon.h>
#include <stdarg.h>
#include <stddef.h>

int _doprintf(void *op, void (*put)(int, void *), const char *fmt, va_list ap);

static void _putch_wrap(int ch, void *op)
{
	if (ch == 8)
		ch = 127;
    _ac_vdu(ch);
}

int _cprintf(const char *fmt, ...)
{
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = _doprintf(NULL, _putch_wrap, fmt, ap);
    va_end(ap);
    return n;
}
