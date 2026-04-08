#include <ctype.h>
#undef ispunct

int ispunct (int c)
{
    return (_CyTab[c] & _PN);
}
