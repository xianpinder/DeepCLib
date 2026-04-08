#include <ctype.h>
#undef isxdigit

int isxdigit (int c)
{
    return (_CyTab[c] & _HX);
}
