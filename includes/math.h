#ifndef _MATH_H
#define _MATH_H

#define HUGE_VAL        1.7013859e+38
#define HUGE_VALF        1.7013859e+38

typedef float float_t;
typedef double double_t;

double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double cos(double);
double cosh(double);
double exp(double);
double fabs(double);
double floor(double);
double fmod(double, double);
double frexp(double, int *);
double ldexp(double, int);
double log(double);
double log10(double);
double modf(double, double *);
double pow(double, double);
double sin(double);
double sinh(double);
double sqrt(double);
double tan(double);
double tanh(double);
double copysign(double, double);

float acosf(float);
float asinf(float);
float atanf(float);
float atan2f(float, float);
float ceilf(float);
float cosf(float);
float coshf(float);
float expf(float);
float fabsf(float);
float floorf(float);
float fmodf(float, float);
float frexpf(float, int *);
float ldexpf(float, int);
float logf(float);
float log10f(float);
float modff(float, float *);
float powf(float, float);
float sinf(float);
float sinhf(float);
float sqrtf(float);
float tanf(float);
float tanhf(float);
float copysignf(float,float);

#endif
