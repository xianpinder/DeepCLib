double ceil(double x)
{
    double ix = (double)(long)x;

    if (x > 0.0 && ix != x)
        ix += 1.0;

    return ix;
}