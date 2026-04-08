#include <math.h>
#include <errno.h>

#define HALFPI  1.57079632

float asinf(float a)
{
    if (a > 1.0 || a < -1.0)
    {
        errno = EDOM;
        return 0.0;
    }

    return HALFPI - acosf(a);
}
