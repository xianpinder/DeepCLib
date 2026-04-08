/*
 * atan.c - Arctangent functions (C89)
 *
 * Provides: atan, atan2
 *
 * atan uses a polynomial approximation on [0,1] with
 * range reduction via odd symmetry and the reciprocal
 * identity. The core approximation is:
 *
 *   atan(x) = (pi/4)x - x(x-1)(0.2447 + 0.0663x)
 *
 * which is exact at 0 and 1, with approximately 0.1%
 * maximum error (~3-4 decimal digits).
 *
 * atan2 is the standard four-quadrant wrapper.
 */

#include <math.h>
#include <errno.h>

#define PI      3.14159265
#define HALFPI  1.57079632
#define QTR_PI  0.78539816

double atan(double x)
{
    double r;
    int neg = 0;
    int inv = 0;

    if (x < 0.0)
    {
        neg = 1;
        x = -x;
    }

    if (x > 1.0)
    {
        inv = 1;
        x = 1.0 / x;
    }

    /* Polynomial approximation on [0, 1].
     * Exact at endpoints, max error ~0.0015. */
    r = QTR_PI * x - x * (x - 1.0) * (0.2447 + 0.0663 * x);

    if (inv)
        r = HALFPI - r;
    if (neg)
        r = -r;

    return r;
}

double atan2(double y, double x)
{
    if (x > 0.0)
        return atan(y / x);

    if (x < 0.0)
    {
        if (y >= 0.0)
            return atan(y / x) + PI;
        return atan(y / x) - PI;
    }

    /* x == 0 */
    if (y > 0.0)
        return HALFPI;
    if (y < 0.0)
        return -HALFPI;

    /* x == 0, y == 0: undefined */
    errno = EDOM;
    return 0.0;
}
