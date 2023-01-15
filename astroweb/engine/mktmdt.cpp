
#include <string.h>
#include <stdlib.h>
#include "astro.h"



char *make_date( DATES *dp, char *buf )
{

  sprintf(buf,"%d/%d/%d", dp->month, dp->day, dp->year);
  return buf;
}

char *make_time( TIM *tp, int am_pm, char *buf )
{
	static char ampmstr[2][3] = {"AM","PM"};

	sprintf(buf,"%d:%d:%d %s",tp->hours,tp->minutes,tp->seconds,ampmstr[am_pm]);
	return buf;
}
