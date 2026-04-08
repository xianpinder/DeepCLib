/*
 * scanf.c - Formatted input (C89)
 *
 * Provides: scanf, fscanf, sscanf, vscanf, vfscanf, vsscanf
 *
 * Internal engine __scanf() uses function pointers for input,
 * allowing it to work with both strings and FILE streams.
 * The input source is passed as a void * opaque pointer,
 * interpreted only by the get/unget callbacks.
 *
 * Supports: %d, %u, %i, %o, %x, %X, %s, %c, %hh, %[...],
 *           %e, %f, %g, %l and %h length modifiers,
 *           field width, %* suppression.
 *
 * Note: vscanf, vfscanf, vsscanf are C99 additions but
 * are provided here for completeness. The va_list-based
 * wrappers require that va_list is a simple stack pointer,
 * which holds on the eZ80 and most small-system ABIs.
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#undef scanf
#undef fscanf
#undef sscanf
#undef vscanf
#undef vfscanf
#undef vsscanf

/* ================================================================== */
/*  Floating-point state machine tables                                */
/* ================================================================== */

/* fp scan actions */
#define F_NADA  0       /* just change state */
#define F_SIGN  1       /* set sign */
#define F_ESIGN 2       /* set exponent's sign */
#define F_INT   3       /* adjust integer part */
#define F_FRAC  4       /* adjust fraction part */
#define F_EXP   5       /* adjust exponent part */
#define F_QUIT  6

#define NSTATE  8
#define FS_INIT     0   /* initial state */
#define FS_SIGNED   1   /* saw sign */
#define FS_DIGS     2   /* saw digits, no . */
#define FS_DOT      3   /* saw ., no digits */
#define FS_DD       4   /* saw digits and . */
#define FS_E        5   /* saw 'e' */
#define FS_ESIGN    6   /* saw exp's sign */
#define FS_EDIGS    7   /* saw exp's digits */

#define FC_DIG      0
#define FC_DOT      1
#define FC_E        2
#define FC_SIGN     3

/* given transition,state do what action? */
static int fp_do[][NSTATE] =
{
    {F_INT, F_INT, F_INT,
     F_FRAC, F_FRAC,
     F_EXP, F_EXP, F_EXP},        /* see digit */
    {F_NADA, F_NADA, F_NADA,
     F_QUIT, F_QUIT, F_QUIT, F_QUIT, F_QUIT},  /* see '.' */
    {F_QUIT, F_QUIT,
     F_NADA, F_QUIT, F_NADA,
     F_QUIT, F_QUIT, F_QUIT},      /* see e/E */
    {F_SIGN, F_QUIT, F_QUIT, F_QUIT, F_QUIT,
     F_ESIGN, F_QUIT, F_QUIT},     /* see sign */
};

/* given transition,state what is new state? */
static int fp_ns[][NSTATE] =
{
    {FS_DIGS, FS_DIGS, FS_DIGS,
     FS_DD, FS_DD,
     FS_EDIGS, FS_EDIGS, FS_EDIGS},    /* see digit */
    {FS_DOT, FS_DOT, FS_DD,
    },                  /* see '.' */
    {0, 0,
     FS_E, 0, FS_E,
    },                  /* see e/E */
    {FS_SIGNED, 0, 0, 0, 0,
     FS_ESIGN, 0, 0},          /* see sign */
};

/* which states are valid terminators? */
static int fp_sval[NSTATE] =
{
    0, 0, 1, 0, 1, 0, 0, 1
};

/* ================================================================== */
/*  Helper: skip whitespace from input                                 */
/* ================================================================== */

static int skip_ws(int c, void *ip,
                   int (*get)(void *), int *eof)
{
    while (isspace(c))
    {
        c = (*get)(ip);
        if (c < 1) { *eof = 1; break; }
    }
    return c;
}

/* ================================================================== */
/*  Helper: process string/char data (shared by %s, %c, %[...])       */
/* ================================================================== */

static int scan_str(int c, void *ip, int (*get)(void *),
                    const char *delim, int lval,
                    int store, int endnull,
                    int width, char **args,
                    int *cnt, int *done)
{
    unsigned char *p;
    char *q;

    p = ((unsigned char *)*args);

    /* If the first char fails, match fails */
    if (width)
    {
        q = strchr(delim, c);
        if ((c < 1)
            || (lval ? (q == NULL) : (q != NULL)))
        {
            if (endnull)
                *p = '\0';
            *done = 1;
            return c;
        }
    }

    for (;;)
    {
        if (store)
            *p++ = (unsigned char)c;
        c = (*get)(ip);
        if (c < 1 || --width == 0)
            break;

        q = strchr(delim, c);
        if (lval ? (q == NULL) : (q != NULL))
            break;
    }

    if (store)
    {
        if (endnull)
            *p = '\0';
        ++(*cnt);
    }
    return c;
}

/* ================================================================== */
/*  __scanf - core scanning engine                                     */
/*                                                                     */
/*  ip:    opaque pointer passed through to get/unget callbacks        */
/*  get:   function to read one character; returns char or < 1 on EOF  */
/*  unget: function to push back one character                         */
/*  fmt:   format string                                               */
/*  args:  pointer to argument list (treated as array of pointers)     */
/* ================================================================== */

int __scanf(void *ip,
            int (*get)(void *),
            int (*unget)(int, void *),
            const char *fmt, char **args)
{
    long n;
    int c, width, lval, sval, cval, cnt = 0;
    int store, neg, base, wide1, endnull, rngflag, c2;
    unsigned char *p;
    char delim[256];
    char digits[17];
    int eneg, fstate, trans;
    double fx, frac_div;
    long expo;
    int done;

    if (*fmt == '\0')
        return 0;

    done = 0;
    c = (*get)(ip);

    while (c > 0 && !done)
    {
        store = 0;

        if (*fmt == '%')
        {
            n = 0;
            width = -1;
            wide1 = 1;
            base = 10;
            lval = 0;
            sval = 0;
            cval = 0;
            store = 1;
            endnull = 1;
            neg = -1;

            strcpy(delim, "\011\012\013\014\015 ");
            strcpy(digits, "0123456789ABCDEF");

            /* ---- Parse modifiers: *, width, l, h ---- */
            ++fmt;
            while (*fmt)
            {
                if (*fmt == '*')
                {
                    endnull = store = 0;
                    fmt++;
                }
                else if (*fmt == 'l')
                {
                    lval = 1;
                    fmt++;
                }
                else if (*fmt == 'h')
                {
                    fmt++;
                    if (*fmt == 'h')
                    {
                        cval = 1;
                        fmt++;
                    }
                    else
                    {
                        sval = 1;
                    }
                }
                else if (isdigit((unsigned char)*fmt))
                {
                    if (width == -1)
                        width = 0;
                    wide1 = width = (width * 10)
                                    + (*fmt - '0');
                    fmt++;
                }
                else
                {
                    break;
                }
            }

            /* ---- Dispatch on conversion specifier ---- */
            switch (tolower((unsigned char)*fmt))
            {

            /* ---- Integer conversions ---- */
            case 'i':
                base = 0;
                /* fall through */
            case 'o':
                if (tolower((unsigned char)*fmt) == 'o')
                    base = 8;
                /* fall through */
            case 'x':
                if (tolower((unsigned char)*fmt) == 'x')
                    base = 16;
                /* fall through */
            case 'd':
                if (tolower((unsigned char)*fmt) == 'd')
                    neg = 0;
                /* fall through */
            case 'u':

                /* Skip leading whitespace */
                c = skip_ws(c, ip, get, &done);
                if (done) break;

                if (isupper((unsigned char)*fmt))
                    lval = 1;

                /* Auto-detect base for %i */
                if (!base)
                {
                    base = 10;
                    neg = 0;
                    if (c == '0')
                    {
                        c = (*get)(ip);
                        if (c < 1)
                        {
                            /* "0" by itself: n is already 0 */
                            if (store)
                            {
                                p = ((unsigned char *)*args);
                                if (lval)
                                    *((long *)p) = 0;
                                else if (sval)
                                    *((short *)p) = 0;
                                else if (cval)
                                    *((signed char *)p) = 0;
                                else
                                    *((int *)p) = 0;
                                ++cnt;
                            }
                            break;
                        }
                        if (c == 'x' || c == 'X')
                        {
                            base = 16;
                            c = (*get)(ip);
                            if (c < 1) { done = 1; break; }
                        }
                        else
                        {
                            base = 8;
                            digits[8] = '\0';
                        }
                    }
                }

                /* Handle sign for signed decimal formats */
                if (!done && neg == 0 && base == 10
                    && (c == '-' || c == '+'))
                {
                    neg = (c == '-');
                    c = (*get)(ip);
                    if (c < 1) { done = 1; break; }
                }

                /* Parse digit sequence */
                if (!done)
                {
                    digits[base] = '\0';
                    p = ((unsigned char *)
                         strchr(digits, toupper(c)));

                    if ((!c || !p) && width)
                    {
                        done = 1;
                        break;
                    }

                    while (p && width-- && c)
                    {
                        n = (n * base) + (p - (unsigned char *)digits);
                        c = (*get)(ip);
                        p = ((unsigned char *)
                             strchr(digits, toupper(c)));
                    }
                }

                /* Store result */
                if (!done && store)
                {
                    p = ((unsigned char *)*args);
                    if (neg == 1)
                        n = -n;
                    if (lval)
                        *((long *)p) = n;
                    else if (sval)
                        *((short *)p) = n;
                    else if (cval)
                        *((signed char *)p) = (signed char)n;
                    else
                        *((int *)p) = n;
                    ++cnt;
                }
                break;

            /* ---- Floating-point conversions ---- */
            case 'e':
            case 'f':
            case 'g':
                c = skip_ws(c, ip, get, &done);
                if (done) break;

                if (isupper((unsigned char)*fmt))
                    lval = 1;

                fstate = FS_INIT;
                neg = 0;
                eneg = 0;
                fx = 0.0;
                frac_div = 1.0;
                expo = 0;

                while (c && width--)
                {
                    if (c >= '0' && c <= '9')
                        trans = FC_DIG;
                    else if (c == '.')
                        trans = FC_DOT;
                    else if (c == '+' || c == '-')
                        trans = FC_SIGN;
                    else if (tolower(c) == 'e')
                        trans = FC_E;
                    else
                        break;

                    if (fp_do[trans][fstate] == F_QUIT)
                        break;

                    switch (fp_do[trans][fstate])
                    {
                        case F_SIGN:
                            neg = (c == '-');
                            break;
                        case F_ESIGN:
                            eneg = (c == '-');
                            break;
                        case F_INT:
                            fx = 10.0 * fx + (c - '0');
                            break;
                        case F_FRAC:
                            frac_div *= 0.1;
                            fx += (c - '0') * frac_div;
                            break;
                        case F_EXP:
                            expo = 10 * expo + (c - '0');
                            break;
                    }
                    fstate = fp_ns[trans][fstate];
                    c = (*get)(ip);
                }

                if (!fp_sval[fstate])
                {
                    done = 1;
                    break;
                }
                if (store)
                {
                    if (expo != 0)
                    {
                        double scale = 1.0;
                        long ex = expo;
                        while (ex-- > 0)
                            scale *= 10.0;
                        if (eneg)
                            fx /= scale;
                        else
                            fx *= scale;
                    }
                    if (neg)
                        fx = -fx;
                    p = (unsigned char *)*args;
                    if (lval)
                        *((double *)p) = fx;
                    else
                        *((float *)p) = (float)fx;
                    ++cnt;
                }
                break;

            /* ---- Character data ---- */
            case 'c':
                width = wide1;
                endnull = 0;
                delim[0] = '\0';
                c = scan_str(c, ip, get, delim, lval,
                             store, endnull, width,
                             args, &cnt, &done);
                break;

            /* ---- Scanset ---- */
            case '[':
                {
                    char *dp = delim;

                    if (*++fmt == '^')
                        fmt++;
                    else
                        lval = 1;

                    rngflag = 2;
                    if ((*fmt == ']') || (*fmt == '-'))
                    {
                        *dp++ = *fmt++;
                        rngflag = 0;
                    }

                    while (*fmt != ']')
                    {
                        if (*fmt == '\0')
                        {
                            done = 1;
                            break;
                        }
                        switch (rngflag)
                        {
                            case 1:
                                c2 = *(dp - 2);
                                if (c2 <= *fmt)
                                {
                                    dp -= 2;
                                    while (c2 < *fmt)
                                        *dp++ = c2++;
                                    rngflag = 2;
                                    break;
                                }
                                /* fall thru intentional */

                            case 0:
                                rngflag = (*fmt == '-');
                                break;

                            case 2:
                                rngflag = 0;
                        }

                        *dp++ = *fmt++;
                    }

                    if (!done)
                    {
                        *dp = '\0';
                        c = scan_str(c, ip, get, delim, lval,
                                     store, endnull, width,
                                     args, &cnt, &done);
                    }
                }
                break;

            /* ---- String data ---- */
            case 's':
                c = skip_ws(c, ip, get, &done);
                if (!done)
                {
                    c = scan_str(c, ip, get, delim, lval,
                                 store, endnull, width,
                                 args, &cnt, &done);
                }
                break;

            /* ---- End of format or literal match ---- */
            case '\0':
                --fmt;
                store = 0;
                if (c != *fmt)
                    done = 1;
                else
                    c = (*get)(ip);
                break;

            default:
                store = 0;
                if (c != *fmt)
                    done = 1;
                else
                    c = (*get)(ip);
                break;
            }
        }
        else if (isspace((unsigned char)*fmt))
        {
            c = skip_ws(c, ip, get, &done);
        }
        else
        {
            if (c != *fmt)
                break;
            c = (*get)(ip);
        }

        if (done)
            break;

        if (store)
            args++;

        if (!*++fmt)
            break;
    }

    /* End of scan */
    if ((c < 0) && (cnt == 0))
        return EOF;

    (*unget)(c, ip);
    return cnt;
}
