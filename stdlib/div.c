#include <stdlib.h>

#undef div

div_t div (int n, int d)
{
    div_t rv;

    rv.quot = n / d;
    rv.rem  = n - d * rv.quot;
    if ((rv.quot < 0) && (rv.rem > 0))
    {
        rv.quot++;
        rv.rem -= d;
    }

    return rv;
} 
