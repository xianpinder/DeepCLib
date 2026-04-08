#include <ctype.h>
#undef isupper

int isupper (int c)
{
    return (_CyTab[c] & _UP);
}
