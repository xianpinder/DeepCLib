/*
 * strtoul.c - String to unsigned long conversion (C89)
 *
 * unsigned long strtoul(const char *nptr, char **endptr, int base);
 *
 * Converts a string to an unsigned long integer.
 * Handles optional leading whitespace, optional sign,
 * base auto-detection (base 0), and overflow detection.
 *
 * Per C89: on overflow, returns ULONG_MAX and sets errno
 * to ERANGE. A leading '-' is permitted and the result
 * is the negation (unsigned wraparound) of the magnitude.
 */

#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>

unsigned long strtoul(const char *nptr, char **endptr, int base)
{
    const char *s = nptr;
    const char *digits_start;
    unsigned long result = 0;
    unsigned long maxdiv;   /* ULONG_MAX / base */
    unsigned long maxrem;   /* ULONG_MAX % base */
    int neg = 0;
    int overflow = 0;
    int digit;

    /* Skip leading whitespace */
    while (isspace((unsigned char)*s))
        s++;

    /* Optional sign */
    if (*s == '-')
    {
        neg = 1;
        s++;
    }
    else if (*s == '+')
    {
        s++;
    }

    /* Base detection / prefix handling */
    if (base < 0 || base == 1 || base > 36)
    {
        /* Invalid base: don't consume anything */
        if (endptr != NULL)
            *endptr = (char *)nptr;
        return 0;
    }

    if (base == 0)
    {
        if (*s == '0')
        {
            s++;
            if (*s == 'x' || *s == 'X')
            {
                /* Tentatively hex: need a valid hex digit */
                if (isxdigit((unsigned char)s[1]))
                {
                    s++;
                    base = 16;
                }
                else
                {
                    /* Just "0" followed by 'x' with no
                     * hex digit: the value is 0 and
                     * endptr points after the '0'. */
                    if (endptr != NULL)
                        *endptr = (char *)s;
                    return 0;
                }
            }
            else
            {
                base = 8;
                /* s already past the '0'; if no octal
                 * digits follow, the value is just 0
                 * and that's fine — digits_start check
                 * below will handle it since we consumed
                 * at least one '0'. We need to back up
                 * so that digits_start captures this. */
                s--;
            }
        }
        else
        {
            base = 10;
        }
    }
    else if (base == 16)
    {
        /* Skip optional 0x/0X prefix for base 16 */
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        {
            if (isxdigit((unsigned char)s[2]))
                s += 2;
        }
    }

    /* Precompute overflow limits */
    maxdiv = ULONG_MAX / (unsigned long)base;
    maxrem = ULONG_MAX % (unsigned long)base;

    /* Parse digits */
    digits_start = s;

    while (*s)
    {
        if (isdigit((unsigned char)*s))
            digit = *s - '0';
        else if (isalpha((unsigned char)*s))
            digit = toupper((unsigned char)*s) - 'A' + 10;
        else
            break;

        if (digit >= base)
            break;

        /* Overflow check:
         * if result > maxdiv, then result*base overflows.
         * if result == maxdiv and digit > maxrem, same. */
        if (result > maxdiv
            || (result == maxdiv
                && (unsigned long)digit > maxrem))
        {
            overflow = 1;
        }

        if (!overflow)
            result = result * (unsigned long)base
                     + (unsigned long)digit;

        s++;
    }

    /* No digits consumed: not a valid number */
    if (s == digits_start)
    {
        if (endptr != NULL)
            *endptr = (char *)nptr;
        return 0;
    }

    if (endptr != NULL)
        *endptr = (char *)s;

    if (overflow)
    {
        errno = ERANGE;
        return ULONG_MAX;
    }

    /* A negative sign causes unsigned wraparound
     * per C89: -(unsigned long)result */
    if (neg)
        result = (unsigned long)(-(long)result);

    return result;
}
