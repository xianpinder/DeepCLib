#include <errno.h> 

float fmodf(float x, float y)
{
    float ay, q;
    int neg = 0;

    /* Domain error: y == 0 */
    if (y == 0.0)
    {
        errno = EDOM;
        return 0.0;
    }

    /* Handle signs: work with positive values,
     * result takes the sign of x per C89. */
    if (x < 0.0)
    {
        neg = 1;
        x = -x;
    }
    if (y < 0.0)
        y = -y;

    /* Quick check */
    if (x < y)
        return neg ? -x : x;

    /* Repeated subtraction of y scaled by powers of 2.
     * This avoids precision loss from x/y truncation
     * and works well on narrow floating-point. */
    ay = y;
    while (ay + ay <= x)
        ay += ay;

    while (ay >= y)
    {
        if (x >= ay)
            x -= ay;
        ay *= 0.5;
    }

    return neg ? -x : x;
}
