#include "time.h"
#include <time.h>
void GetTime(stTime* now_time)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	(*now_time).iYear = 1900 + p->tm_year;
	(*now_time).iMonth = 1 + p->tm_mon;
	(*now_time).iDay = p->tm_mday;
	(*now_time).iHour = 8 + p->tm_hour;
	(*now_time).iMin = p->tm_min;
}

int CompareTime(stTime* time_a, stTime* time_b)
{
	if (time_a->iYear < time_b->iYear)
	{
		return TIME_OLDER;
	}
	else if(time_a->iYear > time_b->iYear)
	{
		return TIME_NEWER;
	}
	else
	{
		if (time_a->iMonth < time_b->iMonth)
		{
			return TIME_OLDER;
		}
		else if (time_a->iMonth > time_b->iMonth)
		{
			return TIME_NEWER;
		}
		else
		{
			if (time_a->iDay < time_b->iDay)
			{
				return TIME_OLDER;
			}
			else if (time_a->iDay > time_b->iDay)
			{
				return TIME_NEWER;
			}
			else
			{
				return TIME_EQUAL;
			}
		}
	}
}

void AddTime(int span, stTime now_time, stTime* after_time)
{
	int addMonth = 0, addYear = 0;
	after_time->iHour = now_time.iHour;
	after_time->iMin = now_time.iMin;
	after_time->iDay = now_time.iDay;
	after_time->iMonth = now_time.iMonth;
	after_time->iYear = now_time.iYear;
	after_time->iDay += span;
	// 天数大于30加到月份
	if (after_time->iDay > 30)
	{
		addMonth = after_time->iDay % 30;
		after_time->iDay -= addMonth * 30;
	}
	after_time->iMonth += addMonth;
	// 月份大于12加到年数
	if (after_time->iMonth > 12)
	{
		addYear = after_time->iMonth % 12;
		after_time->iMonth -= addYear * 12;
	}
	after_time->iYear += addYear;
}
