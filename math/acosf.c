#include <math.h>
#include <errno.h>

float acosf(float x)
{
    if (x < -1.0 || x > 1.0)
    {
        errno = EDOM;
        return 0.0;
    }

    return atan2f(sqrtf(1.0 - x * x), x);
}
