/*
 * pow.c - Power function (C89)
 *
 * Provides: pow
 *
 * Uses the identity: pow(x, y) = exp(y * log(x))
 * for positive bases. Negative bases are only valid
 * for integer exponents.
 *
 * Edge cases per C89 §4.5.5.1:
 *   x^0 == 1 for any x (including 0)
 *   0^y == 0 for y > 0
 *   0^y is a domain error for y <= 0
 *   1^y == 1 for any y
 *   negative x with non-integer y is a domain error
 */

#include <math.h>
#include <errno.h>

float powf(float x, float y)
{
    int yi;

    /* x^0 == 1 for any x */
    if (y == 0.0)
        return 1.0;

    /* 0^y */
    if (x == 0.0)
    {
        if (y > 0.0)
            return 0.0;
        /* 0^negative is a domain error */
        errno = EDOM;
        return HUGE_VAL;
    }

    /* 1^y == 1 for any y */
    if (x == 1.0)
        return 1.0;

    /* Positive base: straightforward */
    if (x > 0.0)
        return expf(y * log(x));

    /* Negative base: only valid for integer exponents */
    yi = (int)y;
    if ((float)yi != y)
    {
        errno = EDOM;
        return 0.0;
    }

    /* (-x)^n = x^n if n is even, -(x^n) if n is odd */
    x = expf(y * logf(-x));
    if (yi % 2 != 0)
        x = -x;

    return x;
}
