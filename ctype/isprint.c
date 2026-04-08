#include <ctype.h>
#undef isprint

int isprint (int c)
{
    return (_CyTab[c] & _PR);
}
