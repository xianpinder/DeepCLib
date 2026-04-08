#include <math.h>

double tanh(double x)
{
    double ep, em;

    /* For large |x|, tanh approaches +/-1.
     * Avoid overflow in exp(). */
    if (x > 20.0) return 1.0;
    if (x < -20.0) return -1.0;

    ep = exp(x);
    em = exp(-x);
    return (ep - em) / (ep + em);
}