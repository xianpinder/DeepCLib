float ldexpf(float x, int exp)
{
    if (x == 0.0)
        return 0.0;

    while (exp > 0)
    {
        x += x;
        --exp;
    }
    while (exp < 0)
    {
        x *= 0.5;
        ++exp;
    }

    return x;
}
