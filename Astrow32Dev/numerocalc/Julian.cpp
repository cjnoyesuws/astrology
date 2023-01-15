#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "numbr.h"


/* routines to handle julian dates */


/* function to return raw julian date from DATES struct */

double base_julian_date( DATES *dp )
{
 short m, d, y, a;
 double jul = 0.0;

 d = dp->day;
 if ( dp->month < 3 ) {
    y = dp->year -1;
    m = dp->month + 12;
    }
 else {
    y = dp->year;
    m = dp->month;
    }
 if (( y > 1582 ) || ( y == 1582 && m > 10 ) ||     /* gregorian calendar */
	    ( y == 1582 && m == 10 && d > 15 ) ) {
     a = y / 100;
     jul = (double) (( 2 - a )+(a/4));
     }
 else
     jul = 0.0;
 jul += floor( 365.25 * (double) y );
 jul += floor( 30.6001 * (double)(m+1));
 jul += 1720994.5 + d;

 return( jul );
}

/* return full julian date based on date and number of hours. Also subtracts
   julian date of epoch if epoch == 1980. Allows for more epochs if nec */


double julian_date( DATES *dp, short hours, short minutes, short epoch )
{
 double jul;

 jul = base_julian_date( dp );
 jul += (double)( hours / 24.0 );
 jul += (double)( minutes / 1440.0 );
 switch( epoch ) {
     case 1980 :
	  return( jul - 2444238.5 );
	  break;
     default :
	  return( jul );
	  break;
     }
}

