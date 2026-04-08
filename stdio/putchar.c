#include <stdio.h>

#undef putchar

int putchar (int ch)
{
    return (fputc (ch, stdout));
}