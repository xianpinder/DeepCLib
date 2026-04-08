#include <stdlib.h>

#undef labs

long labs (long i)
{
    return (i < 0) ? -i : i;
}

