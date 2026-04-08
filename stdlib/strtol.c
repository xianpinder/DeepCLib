/*
 * strtol.c - Convert string to long integer (C89)
 *
 * Provides: strtol
 *
 * Conforms to C89 section 4.10.1.5:
 *   - Skips leading whitespace
 *   - Optional sign (+ or -)
 *   - Base 0 auto-detection (0x for hex, 0 for octal, else decimal)
 *   - Bases 2..36 supported
 *   - Overflow sets errno to ERANGE and returns LONG_MAX or LONG_MIN
 *   - endptr set to first unconverted character
 *   - "0x" prefix only consumed when followed by a valid hex digit
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

long strtol(const char *s, char **endptr, int base)
{
    int sign;
    unsigned long x;
    int toobig;
    unsigned long maxnum;
    unsigned long maxadd;
    unsigned long addon;
    const char *orig;
    const char *saved;
    const char *sd;

    orig = s;
    toobig = 0;

    if (base < 0 || base == 1 || base > 36) {
        if (endptr != NULL)
            *endptr = (char *)s;
        return 0;
    }

    /* Skip leading whitespace */
    while (isspace((unsigned char)*s))
        s++;

    /* Optional sign */
    sign = '+';
    if (*s == '-' || *s == '+')
        sign = *s++;

    /*
     * Handle "0x" / "0X" prefix for hex.
     * Only consume the prefix if a valid hex digit follows.
     * If the input is "0x" or "0xG", the "0" is a valid
     * conversion and the "x" is unconverted.
     */
    if ((base == 0 || base == 16) &&
        s[0] == '0' && (s[1] == 'x' || s[1] == 'X') &&
        memchr(digits, tolower((unsigned char)s[2]), 16) != NULL) {
        base = 16;
        s += 2;
    }

    /* Base 0 auto-detection: octal if leading '0', else decimal */
    if (base == 0)
        base = (*s == '0') ? 8 : 10;

    /* Precompute overflow thresholds */
    maxnum = (unsigned long)ULONG_MAX / (unsigned long)base;
    maxadd = (unsigned long)ULONG_MAX % (unsigned long)base;

    x = 0;

    for (saved = s; *s != '\0'; s++) {
        sd = (const char *)memchr(digits,
                                  tolower((unsigned char)*s),
                                  (size_t)base);
        if (sd == NULL)
            break;
        addon = (unsigned long)(sd - digits);

        if (x > maxnum || (x == maxnum && addon > maxadd))
            toobig = 1;
        else
            x = x * (unsigned long)base + addon;
    }

    /* No valid digits found */
    if (s == saved) {
        if (endptr != NULL)
            *endptr = (char *)orig;
        return 0;
    }

    if (endptr != NULL)
        *endptr = (char *)s;

    /* Check for overflow against signed range */
    if (sign == '+') {
        if (x > (unsigned long)LONG_MAX)
            toobig = 1;
    } else {
        if (x > -(unsigned long)LONG_MIN)
            toobig = 1;
    }

    if (toobig) {
        errno = ERANGE;
        return (sign == '+') ? LONG_MAX : LONG_MIN;
    }

    return (sign == '+') ? (long)x : -(long)x;
}
