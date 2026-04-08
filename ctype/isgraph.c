#include <ctype.h>
#undef isgraph

int isgraph (int c)
{
    return (_CyTab[c] & _GR);
}
