/*
 * strtod.c - String to double conversion (C89)
 *
 * double strtod(const char *nptr, char **endptr);
 *
 * Converts a string to a double-precision floating-point
 * number. Handles optional leading whitespace, optional
 * sign, integer part, fractional part, and optional
 * exponent. Sets errno to ERANGE on overflow or underflow.
 *
 * Accumulates integer part directly into double to avoid
 * overflow on systems with narrow int/long (e.g. eZ80
 * with 24-bit types).
 */

#include <math.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>

double strtod(const char *nptr, char **endptr)
{
    const char *s = nptr;
    const char *end;
    int neg = 0;
    int saw_digits = 0;
    unsigned int frac_digits = 1;
    int exp_val = 0;
    double value = 0.0;
	unsigned int uvalue = 0;
	unsigned int ufrac = 0;

    while (isspace((unsigned char)*s))
        s++;

    if (*s == '-')
    {
        neg = 1;
        s++;
    }
    else if (*s == '+')
    {
        s++;
    }

    while (isdigit((unsigned char)*s))
    {
        uvalue = uvalue * 10 + (*s - '0');
        saw_digits = 1;
        s++;
    }

    if (*s == '.')
    {
        s++;
        while (isdigit((unsigned char)*s))
        {
            ufrac = ufrac * 10 + (*s - '0');
            frac_digits *= 10;
            saw_digits = 1;
            s++;
        }
    }

    if (!saw_digits)
    {
        if (endptr != NULL)
            *endptr = (char *)nptr;
        return 0.0;
    }

    end = s;

    if (*s == 'E' || *s == 'e')
    {
        const char *exp_start = s;
        int exp_neg = 0;

        s++;

        if (*s == '-' || *s == '+')
        {
            if (*s == '-')
                exp_neg = 1;
            s++;
        }

        if (!isdigit((unsigned char)*s))
        {
            s = exp_start;
        }
        else
        {
            exp_val = 0;
            while (isdigit((unsigned char)*s))
            {
                exp_val = exp_val * 10 + (*s - '0');
                if (exp_val > 127)
                    exp_val = 127;
                s++;
            }
            end = s;

            if (exp_neg)
                exp_val = -exp_val;
        }
    }

    /* Combine explicit exponent with fractional
     * digit count into a single power of 10 */
    //exp_val -= frac_digits;
	
	value = (double)uvalue;

	if (ufrac != 0)
		value += (double)ufrac / (double)frac_digits;

    if (neg)
        value = -value;

    if (exp_val > 0)
    {
        while (exp_val >= 10)
        {
            value *= 1.0E10;
            exp_val -= 10;
        }
        while (exp_val > 0)
        {
            value *= 10.0;
            exp_val--;
        }
    }
    else if (exp_val < 0)
    {
        exp_val = -exp_val;
        while (exp_val >= 10)
        {
            value *= 1.0E-10;
            exp_val -= 10;
        }
        while (exp_val > 0)
        {
            value *= 0.1;
            exp_val--;
        }
    }

    if (endptr != NULL)
        *endptr = (char *)end;

    if (value == HUGE_VAL || value == -HUGE_VAL)
        errno = ERANGE;

    return value;
}
