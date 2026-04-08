#include <stdlib.h>

#undef atoi

int atoi (char *str)
{
    return (int)strtol(str, NULL, 10);
}
