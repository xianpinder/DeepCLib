/*
 * sincos.c - Sine and cosine (C89)
 *
 * Provides: sinf, cosf, tanf
 *
 * Uses a parabolic approximation with correction term,
 * giving approximately 0.1% maximum error (~3 decimal
 * digits). Suitable for systems where speed matters
 * more than precision.
 *
 * The core approximation for x in [-pi, pi]:
 *
 *   P = (4/pi)x - (4/pi^2)x|x|
 *   sin(x) = P + 0.225(P|P| - P)
 *
 * cos(x) is computed as sin(x + pi/2).
 */

#include <math.h>

#define PI      3.14159265
#define TWOPI   6.28318530
#define HALFPI  1.57079632

/* Precomputed constants */
#define C1      1.27323954      /* 4 / pi */
#define C2      0.40528473      /* 4 / pi^2 */
#define Q       0.225           /* correction factor */

/* Reduce angle to [-pi, pi] */
static float reduce(float x)
{
    /* Remove full revolutions */
    x = x - (int)(x / TWOPI) * TWOPI;

    /* Bring into [-pi, pi] */
    if (x > PI)
        x -= TWOPI;
    else if (x < -PI)
        x += TWOPI;

    return x;
}

float sinf(float x)
{
    float p, abs_p;

    x = reduce(x);

    /* Parabolic approximation */
    if (x < 0.0)
        p = C1 * x + C2 * x * x;
    else
        p = C1 * x - C2 * x * x;

    /* Correction term */
    abs_p = (p < 0.0) ? -p : p;
    p = Q * (p * abs_p - p) + p;

    return p;
}

float cosf(float x)
{
    return sinf(x + HALFPI);
}

float tanf(float x)
{
    float c = cosf(x);
    if (c == 0.0)
        return HUGE_VAL;
    return sinf(x) / c;
}
