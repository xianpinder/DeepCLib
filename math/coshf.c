#include <math.h>

float coshf(float x)
{
    float ep = expf(x);
    float em = expf(-x);
    return (ep + em) * 0.5;
}
