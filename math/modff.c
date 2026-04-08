float modff(float x, float *iptr)
{
    float ix;

    if (x < 0.0)
    {
        ix = -(float)(long)(-x);
    }
    else
    {
        ix = (float)(long)x;
    }

    *iptr = ix;
    return x - ix;
}
