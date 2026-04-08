#include <math.h>

float sinhf(float x)
{
    float ep = exp(x);
    float em = exp(-x);
    return (ep - em) * 0.5;
}
