#include <math.h>

double sinh(double x)
{
    double ep = exp(x);
    double em = exp(-x);
    return (ep - em) * 0.5;
}
