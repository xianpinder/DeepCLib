#include <stdlib.h>
#include <string.h>

void *calloc(size_t nelem, size_t elsize)
{
    size_t total = nelem * elsize;
    void *ptr = malloc(total);

    if (ptr != NULL)
        _ac_memset(ptr, 0, total);

    return ptr;
}

