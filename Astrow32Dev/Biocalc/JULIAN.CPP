#include "stdafx.h"
#include <assert.h>
#include <math.h>
#include <atlcomtime.h>
#include "date.hpp"

extern double trunc_val( double val );

/* function to return raw julian day number from DATES struct.
   These dates are epoch 1900.0 */

double Date::baseJulian()
{
 int m=0, d=0, y=0, a=0;
 double jul = 0.0;

 d = day;
 if ( month < 3 ) {
    y = year -1;
    m = month + 12;
    }
 else {
    y = year;
    m = month;
    }
 if ( year < 0 )
    y++;
 if (( y > 1582 ) || ( y == 1582 && m > 10 ) ||     /* gregorian calendar */
	    ( y == 1582 && m == 10 && d > 15 ) ) {
     a = y / 100;
     jul = (double) (( 2 - a )+(a/4));
     }
 if ( y < 0 ) {
    jul += trunc_val( (365.25 * (double) y)-0.75 ) - 694025;
    }
 else {
    jul += floor( 365.25 * (double) y ) - 694025;
    }
 jul += (double) d;
 jul -= 0.5;
 jul += floor( 30.6001 * (double)(m+1));
 return( jul );
}

/* return full julian date based on date and number of hours. Also subtracts
   julian date of epoch if epoch == 1980. Allows for more epochs if nec.
   Frequently called epochs are added by using constants */


double Date::julian( int epoch )
{
 double jul = 0;

 jul = baseJulian();
 switch( epoch ) {
     case 1980 :
	  return( jul - 29220 );
	  break;
     case 1900 :
	  return( jul );
	  break;
     case 0 :
	  return( jul + 694025 );
	  break;
     case -4713:
	  return( jul + 2415020 );
	  break;
     default :
	  Date t(1,1,epoch);
	  return( jul - t.baseJulian() );
	  break;
     }
}

