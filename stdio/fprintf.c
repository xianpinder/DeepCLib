#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE *fp, const char *fmt, ...)
{
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vfprintf(fp, fmt, ap);
    va_end(ap);
    return n;
}
