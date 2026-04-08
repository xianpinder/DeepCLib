double modf(double x, double *iptr)
{
    double ix;

    if (x < 0.0)
    {
        ix = -(double)(long)(-x);
    }
    else
    {
        ix = (double)(long)x;
    }

    *iptr = ix;
    return x - ix;
}
