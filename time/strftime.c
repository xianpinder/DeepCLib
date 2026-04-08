#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

static const char *short_days[] =
{
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char *long_days[] =
{
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

static const char *short_months[] =
{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char *long_months[] =
{
    "January",   "February", "March",    "April",
    "May",       "June",     "July",     "August",
    "September", "October",  "November", "December"
};

#define ADDSTR(src) addstr (&maxsize, &s, (src))

static int addstr (size_t *maxsize, char **dst, const char *src)
{
    int len;

    len = strlen (src);
    if (len >= *maxsize)
        return 1;

    *maxsize -= len;
        
    while (len > 0)
    {
        **dst = *src++;
		len--;
		++*dst;
    }
	
    return 0;
}


static char *dec2str (char *buf, int num, int width)
{
    buf += width;
    *buf = '\0';
    while (width-- > 0)
    {
        *--buf = num % 10 + '0';
		num /= 10;
    }

    return buf;
}


static int sun_week (int wday, int yday)
{
    int day;

    day = (wday + 7) % 7;
    return (yday - day + 12) / 7 - 1;
}

static int mon_week (int wday, int yday)
{
    int day;

    day = (wday + 6) % 7;
    return (yday - day + 12) / 7 - 1;
}


size_t strftime (char *s, size_t maxsize, const char *fmt, const struct tm *tm)
{
    int rv;
    size_t actsize = maxsize;
    char buf[32];
	int h;

    rv = 0;

    for (; *fmt; fmt++)
    {
		if (*fmt != '%')
		{
			if (maxsize < 2)
				return 0;

			*s++ = *fmt;
			maxsize--;
			continue;
		}

		switch (*++fmt)
		{
			case '%':
				if (maxsize < 2)
				return 0;

				*s++ = '%';
				maxsize--;
				break;

			case 'a':
				rv = ADDSTR (short_days[tm->tm_wday]);
				break;

			case 'A':
				rv = ADDSTR (long_days[tm->tm_wday]);
				break;

			case 'b':
				rv = ADDSTR (short_months[tm->tm_mon]);
				break;

			case 'B':
				rv = ADDSTR (long_months[tm->tm_mon]);
				break;

			case 'c':
				rv  = ADDSTR (short_days[tm->tm_wday]);
				rv |= ADDSTR (" ");
				rv |= ADDSTR (short_months[tm->tm_mon]);
				rv |= ADDSTR (" ");
				rv |= ADDSTR (dec2str (buf, tm->tm_mday, 2));
				rv |= ADDSTR (" ");
				rv |= ADDSTR (dec2str (buf, tm->tm_hour, 2));
				rv |= ADDSTR (":");
				rv |= ADDSTR (dec2str (buf, tm->tm_min, 2));
				rv |= ADDSTR (":");
					rv |= ADDSTR (dec2str (buf, tm->tm_sec, 2));
				rv |= ADDSTR (" ");
					rv |= ADDSTR (dec2str (buf, tm->tm_year + 1900, 4));
				break;
			
			case 'd':
				rv = ADDSTR (dec2str (buf, tm->tm_mday, 2));
				break;

			case 'H':
				rv = ADDSTR (dec2str (buf, tm->tm_hour, 2));
				break;

			case 'I':
				h = tm->tm_hour % 12;
				if (h == 0) h = 12;
					rv = ADDSTR(dec2str(buf, h, 2));
				break;

			case 'j':
				rv = ADDSTR (dec2str (buf, tm->tm_yday + 1, 3));
				break;

			case 'm':
				rv = ADDSTR (dec2str (buf, tm->tm_mon + 1, 2));
				break;

			case 'M':
				rv = ADDSTR (dec2str (buf, tm->tm_min, 2));
				break;

			case 'p':
				rv = ADDSTR (tm->tm_hour < 12 ? "AM" : "PM");
				break;

			case 'S':
				rv = ADDSTR (dec2str (buf, tm->tm_sec, 2));
				break;

			case 'U':
				rv = ADDSTR (dec2str (buf,
				sun_week (tm->tm_wday, tm->tm_yday), 2));
				break;

			case 'w':
				rv = ADDSTR (dec2str (buf, tm->tm_wday, 1));
				break;

			case 'W':
				rv = ADDSTR (dec2str (buf,
				mon_week (tm->tm_wday, tm->tm_yday), 2));
				break;

			case 'x':
				rv  = ADDSTR (short_days[tm->tm_wday]);
				rv |= ADDSTR (" ");
				rv |= ADDSTR (short_months[tm->tm_mon]);
				rv |= ADDSTR (" ");
				rv |= ADDSTR (dec2str (buf, tm->tm_mday, 2));
				rv |= ADDSTR (", ");
				rv |= ADDSTR (dec2str (buf, tm->tm_year + 1900, 4));
				break;

			case 'X':
				rv  = ADDSTR (dec2str (buf, tm->tm_hour, 2));
				rv |= ADDSTR (":");
				rv |= ADDSTR (dec2str (buf, tm->tm_min, 2));
				rv |= ADDSTR (":");
				rv |= ADDSTR (dec2str (buf, tm->tm_sec, 2));
				break;

			case 'y':
				rv = ADDSTR (dec2str (buf, tm->tm_year % 100, 2));
				break;

			case 'Y':
				rv = ADDSTR (dec2str (buf, tm->tm_year + 1900, 4));
				break;

			case 'Z':
				rv = ADDSTR ("UTC");
				break;

			default:
				if (maxsize < 3)
					return 0;

				*s++ = '%';
				*s++ = *fmt;
				maxsize -= 2;
				break;
		}

		if (rv != 0)
			return 0;
    }

    *s = '\0';
    return actsize - maxsize;
}

