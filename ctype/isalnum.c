#include <ctype.h>
#undef isalnum

int isalnum (int c)
{
    return (_CyTab[c] & _AN);
}
