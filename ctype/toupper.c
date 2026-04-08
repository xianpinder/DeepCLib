#include <ctype.h>
#undef toupper

extern int *_ToUpper;

int toupper (int c)
{
    return _ToUpper[c];
}
