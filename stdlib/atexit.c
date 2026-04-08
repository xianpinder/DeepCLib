#include <stdlib.h>

extern int _Ats_Avail;
extern void (*_At_List[])(void);

int atexit (void (*function)(void))
{
    if (_Ats_Avail == 0)
        return -1;

    --_Ats_Avail;
    _At_List[_Ats_Avail] = function;
    return 0;
}
