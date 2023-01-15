#include "stdafx.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <atlcomtime.h>
#include "date.hpp"

void Date::SetDate(COleDateTime &dt)
{
 int m, d, y;
 m = dt.GetMonth();
 d = dt.GetDay();
 y = dt.GetYear();
 set(m,d,y);
}

/* returns 1 if year is a leap year */

int Date::isLeap()
{
 if ( year % 4 == 0 && year % 100 != 0 )
    return( 1 );
 else if ( year % 400 == 0 )
    return( 1 );
 else
    return( 0 );
}

/* returns number of days to month */

int Date::daysToMonth()
{
  static const short day_to_month[16] = { 31, 28, 31, 30, 31, 30, 31, 31, 30,
                                    31, 30, 31, 31, 28, 31, 30 };
  assert( month>0 && month <= 12 );
  if ( month < 1 )
       month += 12;
  if ( month != 2 )
     return( day_to_month[ month - 1 ] );
  else if ( isLeap() )
     return( 29 );
  else
     return( 28 );
}

/* returns 0 if date is valid, 1 if month is invalid, 2 if day is invalid
   3 if year is invalid */

int Date::badDate()
{
 if ( month < 1 || month > 12 )
    return( 1 );
 if ( year < 1585 ) {
    if ( day < 1 || day > 31 )
       return( 2 );
    else
       return( 0 );
    }
 else if ( day >= 1 && day <= daysToMonth() )
    return( 0 );
 else if ( month == 2 && isLeap() && day == 29 )
    return( 0 );
 else
    return( 2 );
}


/* returns number of days difference from start month for month/day/year
   passes pointer to date structure dp */

int Date::dayNumber(int st_month)
{
 int days=0, total=0;
 static const int v[12] = { 0, 1, -1, 0, 0, 1, 1, 2, 3, 3, 4, 4 };

 days = (( st_month -1 ) * 30 ) + v[st_month-1];
 total = (( month -1 ) * 30 ) + v[month-1] + day;
 if ( isLeap() ) {
    if ( month > 2 )
       ++total;
    else if ( month > 2 )
       ++days;
    }
 return( (total-days) );
}



/* function to test if date rolls over. If date rolls over in any
   part of date structure it is adjusted. if date is greater than
   99 or less than 10 it is reset to max or min val and -1 is returned
   to flag error. Otherwise returns 0  */

int Date::adjust()
{
 int yr = year;
 int flag = 0;

 if ( month < 1 ) {
    year--;
    month += 12;
    }
 else if ( month > 12 ) {
    year++;
    month -= 12;
    }
 if ( day < 1 ) {
    month--;
    day += daysToMonth();
    }
 else if ( day > daysToMonth() ) {
    day -= daysToMonth();
    month++;
    }
 if ( month < 1 ) {
    year--;
    month += 12;
    }
 else if ( month > 12 ) {
    year++;
    month -= 12;
    }
 if ( year < 1585 ) {
    year = 1585;
    flag = -1;
    }
 else if ( year > 2100 ) {
    year = 2100;
    flag = -1;
    }
 return( flag );
}


Date &Date::operator++()
{
 day++;
 adjust();
 return *this;
}

Date &Date::operator+(int i)
{
 day += i;
 adjust();
 return *this;
}

