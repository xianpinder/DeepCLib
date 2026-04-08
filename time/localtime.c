#include <time.h>
#undef localtime

#define SECS_IN_MINUTE	60
#define SECS_IN_HOUR	3600
#define SECS_IN_DAY	86400
#define SECS_IN_YEAR    (365 * SECS_IN_DAY)
#define SECS_IN_LYEAR	(366 * SECS_IN_DAY)
#define SECS_IN_LFEB	(29 * SECS_IN_DAY)


static const int month_secs[] =
{
    31 * SECS_IN_DAY,		/* January	*/
    28 * SECS_IN_DAY,		/* February	*/
    31 * SECS_IN_DAY,		/* March	*/
    30 * SECS_IN_DAY,		/* April	*/
    31 * SECS_IN_DAY,		/* May		*/
    30 * SECS_IN_DAY,		/* June		*/
    31 * SECS_IN_DAY,		/* July		*/
    31 * SECS_IN_DAY,		/* August	*/
    30 * SECS_IN_DAY,		/* September	*/
    31 * SECS_IN_DAY,		/* October	*/
    30 * SECS_IN_DAY,		/* November	*/
    31 * SECS_IN_DAY		/* December	*/
};

static struct tm the_time;

struct tm *localtime (time_t *timeptr)
{
    int secs = *timeptr;
    struct tm *tm = &the_time;
    int year;
    int month;
    int is_leap_year;

    /* Calculate the day of the week...						*/
    /* Modulo 7 to get to the day of the week.  Sunday = 0.	*/
    /* 1-JAN-1970 was a Thursday so need to add on 4.		*/

    tm->tm_wday = ((secs / SECS_IN_DAY) + 4) % 7;

    for (year = 1970;; year++)
    {
        int secs_in_year;

        secs_in_year = (year % 4) ? SECS_IN_YEAR : SECS_IN_LYEAR;
		if (secs < secs_in_year)
			break;
		secs -= secs_in_year;
    }

    tm->tm_year = year - 1900;
    tm->tm_yday = (secs / SECS_IN_DAY);

    is_leap_year = ((year % 4) == 0);
    for (month = 0; ; month++)
    {
        int secs_in_month;
	
		secs_in_month = month_secs[month];
		if (is_leap_year && (month == 1))
			secs_in_month = SECS_IN_LFEB;
	
		if (secs < secs_in_month)
			break;
	
		secs -= secs_in_month;
    }

    tm->tm_mon   = month;
    tm->tm_mday  = (secs / SECS_IN_DAY) + 1;
    tm->tm_hour  = (secs % SECS_IN_DAY) / SECS_IN_HOUR;
    tm->tm_min   = (secs % SECS_IN_HOUR) / SECS_IN_MINUTE;
    tm->tm_sec   = secs % 60;
    tm->tm_isdst = -1;

    return tm;
}
