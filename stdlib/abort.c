#include <stdlib.h>

#undef abort

void abort()
{
    exit (1);
}
