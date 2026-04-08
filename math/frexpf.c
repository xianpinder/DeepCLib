float frexpf(float x, int *exp)
{
    int e = 0;

    *exp = 0;

    if (x == 0.0)
        return 0.0;

    if (x < 0.0)
        return -frexpf(-x, exp);

    /* Scale into [0.5, 1.0) */
    while (x >= 1.0)
    {
        x *= 0.5;
        e++;
    }
    while (x < 0.5)
    {
        x += x;
        e--;
    }

    *exp = e;
    return x;
}

