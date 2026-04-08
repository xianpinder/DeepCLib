#include <time.h>

typedef struct
{
	unsigned char year_lo;
	unsigned char year_hi;
    unsigned char month;
    unsigned char day;
    unsigned char dayOfWeek;
    unsigned char dayOfYear_lo;
    unsigned char dayOfYear_hi;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} RTCinfo;


time_t time (time_t *tp)
{
	RTCinfo rtc;
	struct tm td;
	time_t cur_secs;
	
	_mos_unpackrtc (&rtc, 1);

	td.tm_year = rtc.year_hi << 8 + rtc.year_lo;
	td.tm_year -= 1900;
	td.tm_yday = rtc.dayOfYear_hi << 8 + rtc.dayOfYear_lo;
	td.tm_mon = rtc.month;
	td.tm_mday = rtc.day;
	td.tm_wday = rtc.dayOfWeek;
	td.tm_hour = rtc.hour;
	td.tm_min = rtc.minute;
	td.tm_sec = rtc.second;
	td.tm_isdst = -1; /* ??? */
	
	cur_secs = mktime(&td);

    if (tp != NULL)
        *tp = (time_t) cur_secs;

    return cur_secs;
}
