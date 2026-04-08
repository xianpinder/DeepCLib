/*
 * multibyte.c - Multibyte/wide character conversion (C89)
 *
 * Provides: mblen, mbtowc, wctomb, mbstowcs, wcstombs
 *
 * This implementation supports only the "C" locale,
 * where every multibyte character is a single byte and
 * the wide character value equals the byte value. There
 * is no state-dependent encoding.
 *
 * Per C89 §4.10.7, when the s argument is NULL, the
 * single-character functions return 0 to indicate that
 * the encoding is not state-dependent.
 */

#include <stdlib.h>
#include <stddef.h>

int mblen(const char *s, size_t n)
{
    /* NULL: query whether encoding is state-dependent.
     * Return 0 = not state-dependent. */
    if (s == NULL)
        return 0;

    /* Zero length or null byte: no complete character */
    if (n == 0)
        return -1;

    /* Null terminator is a valid character of length 0 */
    if (*s == '\0')
        return 0;

    /* In the C locale, every character is one byte */
    return 1;
}

int mbtowc(wchar_t *pwc, const char *s, size_t n)
{
    /* NULL: query whether encoding is state-dependent.
     * Return 0 = not state-dependent. */
    if (s == NULL)
        return 0;

    /* Zero length: cannot examine any bytes */
    if (n == 0)
        return -1;

    /* Store the wide character if requested */
    if (pwc != NULL)
        *pwc = (wchar_t)(unsigned char)*s;

    /* Return 0 for null byte, 1 for any other character */
    return (*s != '\0') ? 1 : 0;
}

int wctomb(char *s, wchar_t wc)
{
    /* NULL: query whether encoding is state-dependent.
     * Return 0 = not state-dependent. */
    if (s == NULL)
        return 0;

    /* In the C locale, the wide character value is the
     * byte value. Values outside 0-255 cannot be
     * represented, but C89 does not require an error
     * return for this case; we truncate. */
    *s = (char)(unsigned char)wc;
    return 1;
}

size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n)
{
    size_t count = 0;

    if (n == 0)
        return 0;

    while (count < n)
    {
        wchar_t wc = (wchar_t)(unsigned char)*s;

        if (pwcs != NULL)
            pwcs[count] = wc;

        if (*s == '\0')
            return count;

        s++;
        count++;
    }

    return count;
}

size_t wcstombs(char *s, const wchar_t *pwcs, size_t n)
{
    size_t count = 0;

    if (n == 0)
        return 0;

    while (count < n)
    {
        wchar_t wc = pwcs[count];

        /* C89 says return (size_t)-1 if a wide character
         * cannot be represented as a multibyte character.
         * In the C locale, values 0-255 are valid. */
        if (wc < 0 || wc > 255)
            return (size_t)-1;

        if (s != NULL)
            s[count] = (char)(unsigned char)wc;

        if (wc == 0)
            return count;

        count++;
    }

    return count;
}
