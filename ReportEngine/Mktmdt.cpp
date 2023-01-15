#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "astro.h"
#include "output.fns"

char *make_date( DATES *dp )
{
 static char buf[30];
 char date_fmt[25], *df, *bp = buf;

 GetProfileString("intl", "sShortDate", "M/d/yy", date_fmt, 14 );
 for ( df = date_fmt; *df; df++ ) {
     switch( *df ) {
	   case 'M' :
		if ( *(df+1) == 'M' ) {
		   df++;
		   bp += sprintf( bp, "%02d", dp->month );
		   }
		else
		   bp += sprintf( bp, "%d", dp->month );
		break;
	   case 'd' :
		if ( *(df+1) == 'd' ) {
		   df++;
		   bp += sprintf( bp, "%02d", dp->day );
		   }
		else
		   bp += sprintf( bp, "%d", dp->day );
		break;
	   case 'y' :
		while (*(df+1) == 'y')
		      df++;
		   bp += sprintf( bp, "%04d", dp->year );
		break;
	   default :
		*bp++ = *df;
		break;
	   }

     }
 return( buf );
}

char *make_time( TIM *tp, int am_pm )
{
 static char buf[40];
 char time_sep[20], am[25], pm[25], *bp;
 int zl, h24;

 GetProfileString("intl", "sTime", ":", time_sep, 4 );
 GetProfileString("intl", "s1159", "AM", am, 14 );
 GetProfileString("intl", "s2359", "PM", pm, 14 );
 h24 = GetProfileInt("intl", "iTime", 0 );
 zl = GetProfileInt("intl", "iTLZero", 0 );
 bp = buf;

 if ( h24 ) {
    if ( zl )
       bp+= sprintf( bp, "%02d", tp->hours );
    else
       bp+= sprintf( bp, "%d", tp->hours );
    }
 else {
    int hr;
    hr = ( am_pm && tp->hours > 12 ) ? tp->hours - 12 : tp->hours;
    if ( !hr && !am_pm )
       hr = 12;
    if ( zl )
       bp+= sprintf( bp, "%02d", hr );
    else
       bp+= sprintf( bp, "%d", hr );
    }
 strcpy( bp, time_sep );
 bp += strlen( time_sep );
 if ( h24 ) {
    bp+= sprintf( bp, "%02d %s", tp->minutes, pm );
    }
 else {
    if ( am_pm )
       bp+= sprintf( bp, "%02d %s", tp->minutes, pm );
    else
       bp+= sprintf( bp, "%02d %s", tp->minutes, am );
    }
 return( buf );
}
