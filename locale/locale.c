/*
 * locale.c - Localization (C89)
 *
 * Provides: setlocale, localeconv
 *
 * This implementation supports only the "C" locale,
 * which is the minimum required by the C standard.
 *
 * Per C89 §4.4.1.1, setlocale with "" selects the
 * implementation-defined native locale. On this
 * platform the native locale is "C".
 *
 * Per C89 §4.4.2.1, localeconv returns a pointer to
 * a struct lconv filled in for the current locale.
 * Char members set to CHAR_MAX indicate that the
 * value is not available in the current locale.
 */

#include <limits.h>
#include <string.h>

#include <locale.h>

/* Current locale name for each category */
static char *lc_names[6] =
{
    "C",    /* LC_ALL */
    "C",    /* LC_COLLATE */
    "C",    /* LC_CTYPE */
    "C",    /* LC_MONETARY */
    "C",    /* LC_NUMERIC */
    "C"     /* LC_TIME */
};

/* The "C" locale: only decimal_point is specified;
 * all other values are empty or CHAR_MAX (meaning
 * not available). */
static struct lconv c_locale =
{
    /* Numeric (non-monetary) */
    ".",            /* decimal_point */
    "",             /* thousands_sep */
    "",             /* grouping */

    /* Monetary */
    "",             /* int_curr_symbol */
    "",             /* currency_symbol */
    "",             /* mon_decimal_point */
    "",             /* mon_thousands_sep */
    "",             /* mon_grouping */
    "",             /* positive_sign */
    "",             /* negative_sign */
    CHAR_MAX,       /* int_frac_digits */
    CHAR_MAX,       /* frac_digits */
    CHAR_MAX,       /* p_cs_precedes */
    CHAR_MAX,       /* p_sep_by_space */
    CHAR_MAX,       /* n_cs_precedes */
    CHAR_MAX,       /* n_sep_by_space */
    CHAR_MAX,       /* p_sign_posn */
    CHAR_MAX        /* n_sign_posn */
};

char *setlocale(int category, const char *locale)
{
    /* Validate category */
    if (category < LC_ALL || category > LC_TIME)
        return NULL;

    /* Query: return current locale name */
    if (locale == NULL)
        return lc_names[category];

    /* Only "C" and "" (native) are supported */
    if (locale[0] != '\0' && strcmp(locale, "C") != 0)
        return NULL;

    /* Set the locale name */
    if (category == LC_ALL)
    {
        int i;
        for (i = 0; i < 6; i++)
            lc_names[i] = "C";
    }
    else
    {
        lc_names[category] = "C";
    }

    return "C";
}

struct lconv *localeconv(void)
{
    return &c_locale;
}
