#include <ctype.h>
#undef tolower

extern short *_ToLower;

int tolower (int c)
{
    return _ToLower[c];
}
