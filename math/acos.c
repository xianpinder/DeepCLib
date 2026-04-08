#include <math.h>
#include <errno.h>

double acos(double x)
{
    if (x < -1.0 || x > 1.0)
    {
        errno = EDOM;
        return 0.0;
    }

    return atan2(sqrt(1.0 - x * x), x);
}
