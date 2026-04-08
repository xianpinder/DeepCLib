#include <stdlib.h>

#undef atol

long atol(char *str)
{
    return strtol(str, NULL, 10);
}
