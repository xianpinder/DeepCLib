/*
 * printf.c - Implementation of the printf family for C89
 *
 * Provides:
 *   vsprintf, sprintf
 *   vsnprintf, snprintf
 *   vprintf,  printf
 *   vfprintf, fprintf
 *
 * Supports format specifiers:
 *   %d %i %u %o %x %X      integer conversions
 *   %c %s %p %n %%          char, string, pointer, count, literal %
 *   %e %E %f %F %g %G       floating-point conversions
 *   %b                       unsigned binary (common extension)
 *
 * Supports flags:  - + (space) 0 #
 * Supports width:  number or *
 * Supports precision: .number or .*
 * Supports length modifiers: h l
 */

#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* Maximum significant digits for floating-point */
#define MAXDIG  40

/* Working buffer size */
#define TMPBUFSZ 48

/* ================================================================== */
/*  Internal integer-to-string helpers                                 */
/* ================================================================== */

/*
 * _ultoa: convert unsigned long to string in given radix (2..16).
 * If lower is nonzero, use lowercase hex digits.
 * Writes digits into buf and null-terminates. Returns buf.
 */
static char *_ultoa(unsigned long val, char *buf, int radix,
                    int lower)
{
    char tmp[34];
    char *p = &tmp[sizeof(tmp) - 1];
    char *out = buf;
    int d;

    *p = '\0';
    if (val == 0) {
        *--p = '0';
    } else {
        while (val != 0) {
            d = (int)(val % (unsigned long)radix);
            *--p = (d < 10) ? (char)('0' + d)
                            : (char)((lower ? 'a' : 'A') + d - 10);
            val /= (unsigned long)radix;
        }
    }
    while (*p)
        *out++ = *p++;
    *out = '\0';
    return buf;
}

/*
 * _ltoa: convert signed long to decimal string.
 */
static char *_ltoa(long val, char *buf)
{
    if (val < 0) {
        buf[0] = '-';
        _ultoa(-(unsigned long)val, buf + 1, 10, 0);
    } else {
        _ultoa((unsigned long)val, buf, 10, 0);
    }
    return buf;
}

/* ================================================================== */
/*  Floating-point to string conversion                                */
/* ================================================================== */

static char  ec_buf[MAXDIG + 10];
static int   ec_sign;
static int   ec_exp;

/*
 * fround - round the digit string in ec_buf to n significant digits.
 */
static void fround(int n, int trunc)
{
    char *p;
    int carry;

    if (n < 1)
        n = 1;

    p = &ec_buf[n];
    if (*p >= '5' && !trunc) {
        carry = 1;
        p--;
        while (p >= ec_buf && carry) {
            (*p)++;
            if (*p <= '9') {
                carry = 0;
            } else {
                *p = '0';
                p--;
            }
        }
        if (carry) {
            memmove(ec_buf + 1, ec_buf, (size_t)n);
            ec_buf[0] = '1';
            ec_exp++;
        }
    }
    ec_buf[n] = '\0';
}

/*
 * ec_convert - convert non-negative double to digit string.
 */
static void ec_convert(double x, int ndig, int trunc)
{
    static const double bigpow[] = {1e32, 1e16, 1e8, 1e4, 1e2, 1e1};
    static const double smlpow[] = {1e-31, 1e-15, 1e-7, 1e-3, 1e-1, 1e0};
    static const double bigmul[] = {1e-32, 1e-16, 1e-8, 1e-4, 1e-2, 1e-1};
    static const double smlmul[] = {1e32, 1e16, 1e8, 1e4, 1e2, 1e1};
    static const int    steps[]  = {32, 16, 8, 4, 2, 1};

    int exp = 0;
    int nsig, i, d;

    if (x == 0.0) {
        nsig = (ndig > 0) ? ndig : ((-ndig) + 1);
        if (nsig < 1) nsig = 1;
        if (nsig > MAXDIG) nsig = MAXDIG;
        for (i = 0; i < nsig; i++)
            ec_buf[i] = '0';
        ec_buf[nsig] = '\0';
        ec_exp = 1;
        return;
    }

    /* Normalize x into [1.0, 10.0) */
    if (x >= 1.0) {
        for (i = 0; i < 6; i++) {
            if (x >= bigpow[i]) {
                x *= bigmul[i];
                exp += steps[i];
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (x < smlpow[i]) {
                x *= smlmul[i];
                exp -= steps[i];
            }
        }
    }

    ec_exp = exp + 1;

    if (ndig > 0) {
        nsig = ndig;
    } else {
        nsig = (-ndig) + ec_exp;
        if (nsig < 1)
            nsig = 1;
    }
    if (nsig > MAXDIG)
        nsig = MAXDIG;

    /* Extract digits (one extra for rounding) */
    for (i = 0; i <= nsig && i <= MAXDIG; i++) {
        d = (int)x;
        if (d < 0) d = 0;
        if (d > 9) d = 9;
        ec_buf[i] = (char)('0' + d);
        x = (x - (double)d) * 10.0;
    }
    ec_buf[i] = '\0';

    fround(nsig, trunc);
}

/*
 * ec_pr - front end: handles sign.
 */
static void ec_pr(double x, int ndig, int trunc)
{
    if (x < 0.0) {
        ec_sign = 1;
        x = -x;
    } else {
        ec_sign = 0;
    }
    ec_convert(x, ndig, trunc);
}

/* ------------------------------------------------------------------ */
/*  Format-specific float printers                                     */
/* ------------------------------------------------------------------ */

static int f_upper;

/*
 * e_print - format as [-]d.ddd[eE][+-]dd
 */
static void e_print(double x, int prec, char *out)
{
    int nsig, exp_val;
    char *p;
    char expbuf[12];
    char *ep;

    nsig = (prec < 0) ? 7 : prec + 1;
    ec_pr(x, nsig, 0);

    p = out;
    if (ec_sign)
        *p++ = '-';

    *p++ = ec_buf[0];

    if (nsig > 1 || prec < 0) {
        *p++ = '.';
        if (ec_buf[1] != '\0')
            strcpy(p, &ec_buf[1]);
        else
            *p = '\0';
        p += _ac_strlen(p);
    }

    *p++ = f_upper ? 'E' : 'e';
    exp_val = ec_exp - 1;
    if (exp_val < 0) {
        *p++ = '-';
        exp_val = -exp_val;
    } else {
        *p++ = '+';
    }
    if (exp_val < 10)
        *p++ = '0';

    ep = _ultoa((unsigned long)exp_val, expbuf, 10, 0);
    while (*ep)
        *p++ = *ep++;
    *p = '\0';
}

/*
 * f_print - format as [-]ddd.ddd
 */
static void f_print(double x, int prec, char *out)
{
    int nsig, nz, i;
    char *p;

    nsig = (prec < 0) ? 6 : prec;
    ec_pr(x, -nsig, 0);

    p = out;
    if (ec_sign)
        *p++ = '-';

    /* Integer part */
    if (ec_exp < 1) {
        *p++ = '0';
    } else {
        for (i = 0; i < ec_exp && ec_buf[i] != '\0'; i++)
            *p++ = ec_buf[i];
        for (; i < ec_exp; i++)
            *p++ = '0';
    }

    if (nsig > 0 || prec < 0)
        *p++ = '.';

    if (nsig == 0) {
        *p = '\0';
        return;
    }

    /* Fractional digits */
    if (ec_exp < 0) {
        nz = -ec_exp;
        if (nz > nsig)
            nz = nsig;
        for (i = 0; i < nz; i++)
            *p++ = '0';
        nsig -= nz;
        for (i = 0; i < nsig && ec_buf[i] != '\0'; i++)
            *p++ = ec_buf[i];
        for (; i < nsig; i++)
            *p++ = '0';
        *p = '\0';

        /* Rounding fixup for digits beyond precision */
        if (nsig == 0 && ec_buf[0] >= '5') {
            char *q = p - 1;
            int carry = 1;
            while (q >= out && carry) {
                if (*q == '.' || *q == '-') { q--; continue; }
                (*q)++;
                if (*q <= '9')
                    carry = 0;
                else {
                    *q = '0';
                    q--;
                }
            }
            if (carry) {
                size_t len2 = (size_t)(p - out);
                memmove(out + 1, out, len2 + 1);
                *out = '1';
            }
        }
    } else {
        for (i = 0; i < nsig; i++) {
            if (ec_buf[ec_exp + i] != '\0')
                *p++ = ec_buf[ec_exp + i];
            else
                *p++ = '0';
        }
        *p = '\0';
    }
}

/*
 * strip_trailing_zeros - remove trailing zeros and possibly
 * the decimal point. Used by g_print.
 */
static void strip_trailing_zeros(char *s)
{
    char *dot = NULL;
    char *p = s;
    char *last_nonzero;

    while (*p) {
        if (*p == '.')
            dot = p;
        if (*p == 'e' || *p == 'E')
            break;
        p++;
    }
    if (dot == NULL)
        return;

    last_nonzero = dot;
    {
        char *q = dot + 1;
        while (q < p) {
            if (*q != '0')
                last_nonzero = q;
            q++;
        }
    }

    if (last_nonzero == dot)
        memmove(dot, p, _ac_strlen(p) + 1);
    else
        memmove(last_nonzero + 1, p, _ac_strlen(p) + 1);
}

/*
 * g_print - format using e or f, whichever is shorter.
 */
static void g_print(double x, int prec, int altflag, char *out)
{
    int nsig;

    nsig = (prec < 0) ? 6 : prec;
    if (nsig < 1)
        nsig = 1;

    ec_pr(x, 1, 1);

    if ((ec_exp - 1) < -4 || (ec_exp - 1) >= nsig) {
        e_print(x, nsig - 1, out);
    } else {
        int fprec = nsig - ec_exp;
        if (fprec < 0) fprec = 0;
        f_print(x, fprec, out);
    }

    if (!altflag)
        strip_trailing_zeros(out);
}

/*
 * fp_print - dispatch to e, f, or g.
 */
static void fp_print(double x, int fmtc, int prec, int altflag,
                     char *out)
{
    f_upper = (fmtc == 'E' || fmtc == 'G');

    switch (fmtc) {
    case 'E': case 'e': e_print(x, prec, out); break;
    case 'F': case 'f': f_print(x, prec, out); break;
    case 'G': case 'g': g_print(x, prec, altflag, out); break;
    }
}

/* ================================================================== */
/*  Field output with padding                                          */
/* ================================================================== */

static int _prtfld(void *op, void (*put)(int, void *),
                   char *buf, int ljustf, char sign, char pad,
                   int width, int preci, const char *prefix)
{
    int cnt, len, preflen, total_data, npad;

    len = (int)_ac_strlen(buf);

    if (*buf == '-') {
        sign = '-';
        buf++;
        len--;
    }

    if (preci >= 0 && len > preci)
        len = preci;

    preflen = prefix ? (int)_ac_strlen(prefix) : 0;
    total_data = len + preflen + (sign ? 1 : 0);

    if (width < total_data)
        width = total_data;

    cnt = width;
    npad = width - total_data;

    if (!ljustf) {
        if (pad == '0') {
            if (sign) { put((int)(unsigned char)sign, op); sign = '\0'; }
            if (prefix) {
                while (*prefix)
                    put((int)(unsigned char)*prefix++, op);
                prefix = NULL;
            }
        }
        while (npad-- > 0)
            put((int)(unsigned char)pad, op);
    }

    if (sign)
        put((int)(unsigned char)sign, op);

    if (prefix) {
        while (*prefix)
            put((int)(unsigned char)*prefix++, op);
    }

    {
        int i;
        for (i = 0; i < len; i++)
            put((int)(unsigned char)buf[i], op);
    }

    if (ljustf) {
        while (npad-- > 0)
            put(' ', op);
    }

    return cnt;
}

/* ================================================================== */
/*  Integer precision helper                                           */
/* ================================================================== */

static void _apply_int_preci(char *ptmp, int preci, char *pad)
{
    int dlen;
    char *dp = ptmp;

    if (preci < 0)
        return;

    if (*dp == '-')
        dp++;
    dlen = (int)_ac_strlen(dp);

    if (preci == 0 && dlen == 1 && dp[0] == '0') {
        dp[0] = '\0';
    } else if (preci > dlen) {
        int nz = preci - dlen;
        memmove(dp + nz, dp, (size_t)(dlen + 1));
        _ac_memset(dp, '0', (size_t)nz);
    }

    *pad = ' ';
}

/* ================================================================== */
/*  Core formatting engine                                             */
/* ================================================================== */

int _doprintf(void *op, void (*put)(int, void *),const char *fmt, va_list ap)
{
    int cnt = 0;
    int ljustf, lval, hval;
    int preci, width;
    int altflag;
    char pad, sign;
    char *ptmp;
    char tmp[TMPBUFSZ];
    const char *prefix;
    int do_output, is_int;

    while (*fmt) {
        if (*fmt != '%') {
            put((int)(unsigned char)*fmt++, op);
            cnt++;
            continue;
        }

        fmt++;

        ljustf  = 0;
        sign    = '\0';
        pad     = ' ';
        width   = -1;
        preci   = -1;
        lval    = 0;
        hval    = 0;
        altflag = 0;
        prefix  = NULL;
        ptmp    = tmp;
        do_output = 0;
        is_int    = 0;

        /* Flags */
        for (;;) {
            if      (*fmt == '-') { ljustf = 1; fmt++; }
            else if (*fmt == '+') { sign = '+'; fmt++; }
            else if (*fmt == ' ') { if (sign != '+') sign = ' '; fmt++; }
            else if (*fmt == '0') { pad = '0'; fmt++; }
            else if (*fmt == '#') { altflag = 1; fmt++; }
            else break;
        }

        if (ljustf)
            pad = ' ';

        /* Width */
        if (*fmt == '*') {
            width = va_arg(ap, int);
            if (width < 0) { ljustf = 1; width = -width; pad = ' '; }
            fmt++;
        } else {
            while (*fmt >= '0' && *fmt <= '9') {
                if (width < 0) width = 0;
                width = width * 10 + (*fmt - '0');
                fmt++;
            }
        }

        /* Precision */
        if (*fmt == '.') {
            fmt++;
            preci = 0;
            if (*fmt == '*') {
                preci = va_arg(ap, int);
                if (preci < 0) preci = -1;
                fmt++;
            } else {
                while (*fmt >= '0' && *fmt <= '9') {
                    preci = preci * 10 + (*fmt - '0');
                    fmt++;
                }
            }
        }

        /* Length modifier */
        if (*fmt == 'l') { lval = 1; fmt++; }
        else if (*fmt == 'h') { hval = 1; fmt++; }

        /* Conversion */
        switch (*fmt) {

        case '\0':
            fmt--;
            break;

        case '%':
            put('%', op);
            cnt++;
            break;

        case 'd':
        case 'i': {
            long val;
            if (lval) val = va_arg(ap, long);
            else if (hval) val = (short)va_arg(ap, int);
            else val = (long)va_arg(ap, int);
            _ltoa(val, ptmp);
            do_output = 1;
            is_int = 1;
            break;
        }

        case 'b':
        case 'o':
        case 'x':
        case 'X':
        case 'u': {
            unsigned long uval;
            int radix, lower;

            if (*fmt == 'b')                     radix = 2;
            else if (*fmt == 'o')                radix = 8;
            else if (*fmt == 'x' || *fmt == 'X') radix = 16;
            else                                 radix = 10;

            lower = (*fmt == 'x');

            if (lval) uval = va_arg(ap, unsigned long);
            else if (hval) uval = (unsigned short)va_arg(ap, unsigned int);
            else uval = (unsigned long)va_arg(ap, unsigned int);

            _ultoa(uval, ptmp, radix, lower);

            if (altflag && ptmp[0] != '0') {
                if (radix == 8)
                    prefix = "0";
                else if (radix == 16)
                    prefix = (*fmt == 'X') ? "0X" : "0x";
            }

            sign = '\0';
            do_output = 1;
            is_int = 1;
            break;
        }

        case 'p': {
            unsigned long val;
            val = (unsigned long)(size_t)va_arg(ap, void *);
            _ultoa(val, ptmp, 16, 1);
            prefix = "0x";
            pad = '0';
            sign = '\0';
            if (width < 0)
                width = (int)(sizeof(void *) * 2);
            preci = -1;
            do_output = 1;
            break;
        }

        case 'e': case 'E':
        case 'f': case 'F':
        case 'g': case 'G': {
            double fx = va_arg(ap, double);
            fp_print(fx, *fmt, preci, altflag, ptmp);
            preci = -1;
            do_output = 1;
            break;
        }

        case 'c':
            ptmp[0] = (char)va_arg(ap, int);
            ptmp[1] = '\0';
            sign = '\0';
            pad = ' ';
            preci = -1;
            do_output = 1;
            break;

        case 's':
            ptmp = va_arg(ap, char *);
            if (ptmp == NULL)
                ptmp = "(null)";
            sign = '\0';
            pad = ' ';
            do_output = 1;
            break;

        case 'n':
            if (lval)
                *va_arg(ap, long *) = (long)cnt;
            else if (hval)
                *va_arg(ap, short *) = (short)cnt;
            else
                *va_arg(ap, int *) = cnt;
            break;

        default:
            put('%', op);
            put((int)(unsigned char)*fmt, op);
            cnt += 2;
            break;
        }

        if (is_int) {
            _apply_int_preci(ptmp, preci, &pad);
            preci = -1;
        }
        if (do_output) {
            cnt += _prtfld(op, put, ptmp, ljustf, sign, pad, width, preci, prefix);
        }

        fmt++;
    }

    return cnt;
}

