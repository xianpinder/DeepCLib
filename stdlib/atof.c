#include <stdlib.h>

#undef atof

double atof (char *str)
{
    return strtod (str, (char **)NULL);
}

