#include <ctype.h>
#undef isspace

int isspace (int c)
{
    return (_CyTab[c] & _SP);
}
