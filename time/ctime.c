#include <time.h>
#undef ctime

char *ctime (time_t *tp)
{
    return asctime(localtime(tp));
}

