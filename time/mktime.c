#include <time.h>
#undef mktime

#define SECS_IN_MIN		60
#define SECS_IN_HOUR	3600
#define SECS_IN_DAY		86400
#define SECS_IN_YEAR	31536000
#define SECS_IN_LYEAR	31622400


static const unsigned short daytab[12] =
{
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

static const unsigned short ldaytab[12] =
{
    0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335
};

time_t mktime(struct tm *tp)
{
    time_t secs = -1;
    int year;
    int dayofyear;
    int month;
    int janfirst;
    int day;

    if (tp != NULL)
    {
        year = tp->tm_year + 1900;
        if (year >= 1970)
        {
			month = tp->tm_mon;
			dayofyear = ((year % 4) ? daytab[month] : ldaytab[month]) + tp->tm_mday - 1;
		
			secs =  tp->tm_sec;
			secs += tp->tm_min * SECS_IN_MIN;
			secs += tp->tm_hour * SECS_IN_HOUR;
			secs += dayofyear * SECS_IN_DAY;
			
			/* Fix up tm_yday and tm_wday elements of tp */
			
			tp->tm_yday = dayofyear;
			day = 4+year+(year+3)/4;
			day -= (year-1701)/100;
			day += (year-1601)/400;
			day += 3;
			tp->tm_wday = (day + dayofyear) % 7;

			while (year-- > 1970)
			{
				secs += ((year % 4) ? SECS_IN_YEAR : SECS_IN_LYEAR);
			}
		}
    }

    return secs;
}
