/*
 * exp.c - Exponential function (C89)
 *
 * Provides: exp
 *
 * Uses range reduction: decompose x into
 *
 *   x = n * ln(2) + r
 *
 * where n = round(x / ln(2)) and r is in
 * [-ln(2)/2, ln(2)/2] (approximately [-0.347, 0.347]).
 *
 * Then compute exp(r) via Taylor series:
 *
 *   exp(r) = 1 + r + r^2/2 + r^3/6 + r^4/24
 *            + r^5/120 + r^6/720
 *
 * Six terms give ~5 significant digits on this range,
 * well within the 15-bit mantissa (~4.5 digits).
 *
 * Final result: exp(x) = exp(r) * 2^n
 */

#include <math.h>
#include <errno.h>

#define LN2     0.69314718
#define INV_LN2 1.44269504      /* 1 / ln(2) */

double exp(double x)
{
    int n, i;
    double r, result;

    /* exp(0) == 1 exactly */
    if (x == 0.0)
        return 1.0;

    /* Overflow check */
    if (x > 88.0)
    {
        errno = ERANGE;
        return HUGE_VAL;
    }

    /* Underflow check */
    if (x < -88.0)
    {
        errno = ERANGE;
        return 0.0;
    }

    /* Range reduce: x = n*ln(2) + r */
    if (x >= 0.0)
        n = (int)(x * INV_LN2 + 0.5);
    else
        n = (int)(x * INV_LN2 - 0.5);

    r = x - (double)n * LN2;

    /* Taylor series for exp(r), Horner form:
     * 1 + r(1 + r(1/2 + r(1/6 + r(1/24 + r(1/120 + r/720))))) */
    result = 1.0 + r * (1.0
                 + r * (0.5
                 + r * (0.16666667
                 + r * (0.04166667
                 + r * (0.00833333
                 + r *  0.00138889)))));

    /* Multiply by 2^n */
    if (n >= 0)
    {
        for (i = 0; i < n; i++)
            result *= 2.0;
    }
    else
    {
        for (i = 0; i > n; i--)
            result *= 0.5;
    }

    return result;
}
