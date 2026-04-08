#include <ctype.h>
#undef islower

int islower (int c)
{
    return (_CyTab[c] & _LO);
}
