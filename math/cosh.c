#include <math.h>

double cosh(double x)
{
    double ep = exp(x);
    double em = exp(-x);
    return (ep + em) * 0.5;
}
