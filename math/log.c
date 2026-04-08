/*
 * log.c - Natural and base-10 logarithm (C89)
 *
 * Provides: log, log10
 *
 * Uses range reduction: decompose x into m * 2^e
 * where 1 <= m < 2, then compute ln(m) using the
 * substitution t = (m-1)/(m+1) and the series:
 *
 *   ln(m) = 2(t + t^3/3 + t^5/5 + t^7/7)
 *
 * Since m is in [1,2), t is in [0, 1/3), so the
 * series converges rapidly. Four terms give ~5
 * significant digits, well within the 15-bit
 * mantissa (~4.5 digits).
 *
 * Final result: ln(x) = ln(m) + e * ln(2)
 *
 * log10 uses: log10(x) = ln(x) * log10(e)
 */

#include <math.h>
#include <errno.h>

#define LN2     0.69314718
#define LOG10E  0.43429448      /* 1 / ln(10) */

double log(double x)
{
    int e;
    double m, t, t2, r;

    /* Domain errors */
    if (x < 0.0)
    {
        errno = EDOM;
        return -HUGE_VAL;
    }

    if (x == 0.0)
    {
        errno = ERANGE;
        return -HUGE_VAL;
    }

    /* Exact result for 1.0 */
    if (x == 1.0)
        return 0.0;

    /* Range reduce: find e and m such that
     * x = m * 2^e, with 1 <= m < 2 */
    e = 0;
    m = x;

    while (m >= 2.0)
    {
        m *= 0.5;
        e++;
    }

    while (m < 1.0)
    {
        m += m;
        e--;
    }

    /* Substitution: t = (m-1)/(m+1), t in [0, 1/3) */
    t = (m - 1.0) / (m + 1.0);
    t2 = t * t;

    /* Series: ln(m) = 2(t + t^3/3 + t^5/5 + t^7/7) */
    r = t * (2.0
           + t2 * (2.0 / 3.0
           + t2 * (2.0 / 5.0
           + t2 * (2.0 / 7.0))));

    /* ln(x) = ln(m) + e * ln(2) */
    return r + (double)e * LN2;
}

double log10(double x)
{
    return log(x) * LOG10E;
}
