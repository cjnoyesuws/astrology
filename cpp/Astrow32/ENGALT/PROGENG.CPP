#include "astro.h"
#include "flags.h"
#include "julian.h"
#include "compute.fns" 
#include "datetime.fns"
#include "dataext.h"
#include "errors.fns"

/* 09/10/92  Modified for C++ Windows */

/* function to progress a date. Function implements Secondary, Tertiary,
   minor progressions. Once date is progressed, then date is adjusted
   to normal limits. If an error exists in date function returns 1
   otherwise it returns 0 indicating no error */

int __export progress_date( AS_DATA *data, PROGR_DATA *pdata )
{
 LONG_DOUBLE jd, jdx, dv;
 DATES d, dx, t;
 COUNT days, hours, minutes, x;

 switch( pdata->progress_system ) {
       case SECONDARY_PR :
       case SECONDARY_PR +100 :
	    t = pdata->offset;
	    if ( pdata->progress_system >= 100 ) {
	       jd = base_julian_date( &t );
	       jdx = base_julian_date( &data->noon_date );
	       jd -= jdx;
	       t.year  = (int) (jd/365.25);
	       t.month = 0;
	       t.day = 0;
	       }
	    days = t.year;
	    hours = t.month * 2;
	    minutes = t.day * 2;
	    break;
       case MINOR_PR :
       case MINOR_PR + 100 :
       case TERTIARY_PR:
       case TERTIARY_PR + 100:
	    if ( pdata->progress_system >= 100 ) {
	       jdx = base_julian_date( &pdata->offset );
	       }
	    else {
	       dx = data->noon_date;
	       dx.year += t.year;
	       dx.month += t.month;
	       dx.day += t.day;
	       adj_date( &dx );
	       jdx = base_julian_date( &dx );
	       }
	    jd = base_julian_date( &data->noon_date );
	    jdx -= jd;
	    switch( pdata->progress_system ) {
		  case MINOR_PR :
		  case MINOR_PR + 100 :
		       jdx *= 27.32;
		       jdx /= 365.2422;
		       break;
		  case TERTIARY_PR:
		  case TERTIARY_PR+100:
		       jdx /= 27.32;
		       break;
		  }
	    days = (COUNT) jdx;
	    jdx -= (double) days;
	    jdx *= 24.0;
	    hours = (COUNT)jdx;
	    jdx -= (double) hours;
	    jdx *= 60.0;
	    minutes = (COUNT)jdx;
	    break;
       default :
	    break;
       }
 data->minutes_adjust += minutes;
 if ( data->minutes_adjust > 59 ) {
    ++hours;
    data->minutes_adjust %= 60;
    }
 data->hour_adjust += hours;
 if ( data->hour_adjust > 23 ) {
    ++days;
    data->hour_adjust %= 24;
    }
 data->noon_date.day += days;
 x = adj_date( &data->noon_date );
 return( x );
}

