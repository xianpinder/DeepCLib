#include <ctype.h>
#undef isalpha

int isalpha (int c)
{
    return (_CyTab[c] & _AL);
}
