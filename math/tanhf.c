#include <math.h>

float tanhf(float x)
{
    float ep, em;

    /* For large |x|, tanh approaches +/-1.
     * Avoid overflow in exp(). */
    if (x > 20.0) return 1.0;
    if (x < -20.0) return -1.0;

    ep = expf(x);
    em = expf(-x);
    return (ep - em) / (ep + em);
}
