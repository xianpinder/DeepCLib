#include <stdlib.h>

#undef ldiv

ldiv_t ldiv (long n, long d)
{
    ldiv_t rv;

    rv.quot = n / d;
    rv.rem  = n - d * rv.quot;
    if ((rv.quot < 0) && (rv.rem > 0))
    {
        rv.quot++;
        rv.rem -= d;
    }

    return rv;
} 
