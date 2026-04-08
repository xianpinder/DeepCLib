#include <time.h>
#undef asctime

char *asctime (struct tm *tp)
{
    static char datestr[26];

    strftime (datestr, sizeof(datestr), "%c\n", tp);
    return datestr;
}
