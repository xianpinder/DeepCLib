#include <ctype.h>
#undef iscntrl

int iscntrl (int c)
{
    return (_CyTab[c] & _CT);
}
