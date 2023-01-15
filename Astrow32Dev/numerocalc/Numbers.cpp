#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <dos.h>
#include "chartinf.h"
#include "numbr.h"
#include "errors.fns"

extern double julian_date( DATES *, short, short, short );
extern short sun_minutes( double );

#define E2 "ERROR!!"

#define EX "ILLEGAL FUNCTION CALL!! -- "

short destiny( DATES *d, short *test )
{
 return( add_ints_reduce( d->month, d->day, d->year, test ) );
}

short life_cycle( DATES *d, short cycle, short *start, short *end, short *test )
{
 short dd, lc, n;

 assert( d != NULL && start != NULL && end != NULL );
 dd = destiny( d, &n );
 switch( cycle ) {
       case 1 :
	    lc = reduce_int( d->month, test );
	    *start = d->year;
	    *end = 36 - dd + d->year + 1;
	    break;
       case 2 :
	    lc = reduce_int( d->day, test );
	    *start = (36 - dd) + d->year + 1;
	    *end = *start + 27;
	    break;
       case 3 :
	    lc = reduce_int( d->year, test );
	    *start = (36 - dd + d->year)+28;
	    *end = *start + 27;
	    break;
       default :
	    alert_box( E2, EX "LIFE CYCLE!!" );
	    break;
       }
 return( lc );
}

short turn_point( DATES *d, short point, short *start, short *end, short *test )
{
 short dd, tp;

 assert( d != NULL && start != NULL && end != NULL );
 dd = destiny( d, &tp );
 switch( point ) {
       case 1 :
	    tp = add_ints_reduce( d->month, d->day, 0, test );
	    *start = d->year;
	    *end = d->year + (36 - dd)+1;
	    break;
       case 2 :
	    tp = add_ints_reduce( d->day, d->year, 0, test );
	    *start = d->year + (36 - dd)+1;
	    *end = *start + 9;
	    break;
       case 3 :
	    tp = add_ints_reduce( turn_point( d, 1, start, end, test ),
		  turn_point( d, 2, start, end, test ), 0, test );
	    *start = d->year + (36 - dd)+10;
	    *end = *start + 9;
	    break;
       case 4 :
	    tp = add_ints_reduce( d->month, d->year, 0, test );
	    *start = d->year + (36 - dd)+19;
	    *end = *start + 9;
	    break;
       default :
	    alert_box( E2, EX "TURNING POINT!!" );
	    break;
       }
 return( tp );
}


short challenge( DATES *d, short ch )
{
 short m1, m2, n;

 assert( d != NULL );
 switch( ch ) {
       case 1 :
	    return( subtract_ints_reduce( d->month, d->day, &n ) );
	    break;
       case 2 :
	    return( subtract_ints_reduce( d->year, d->day, &n  ) );
	    break;
       case 3 :
	    m1 = subtract_ints_reduce( d->month, d->day, &n  );
	    m2 = subtract_ints_reduce( d->year, d->day, &n  );
	    return( subtract_ints_reduce( m1, m2, &n  ) );
	    break;
       default :
	    alert_box( E2, EX "CHALLENGE!!" );
	    break;
       }

return( 0 );
}

short destiny_direction( DATES *d, short sign )
{
 short n;
 short dd = destiny(d, &n);

 assert( d != NULL && sign > 0 && sign <= 12 );
 return( add_ints_reduce( dd, sign, 0, &n ) );
}

CALDATE universal_dates( DATES *at )
{
 CALDATE u;
 short i, *ip, n;

 u.d.year = reduce_int( at->year, &n );
 u.d.month = add_ints_reduce( u.d.year, at->month, 0, &n  );
 u.d.day = add_ints_reduce( u.d.year, at->month, at->day, &n  );
 ip = u.calendar;
 for ( i = 1; i <= 31; ++i, ip++ )
     *ip = add_ints_reduce( u.d.year, at->month, i, &n  );

 return( u );
}

CALDATE personal_dates( DATES *d, DATES *at )
{
 CALDATE p;
 short i, *ip, n;

 assert( d != NULL );

 p.d.year = add_ints_reduce( at->year, d->month, d->day, &n  );
 p.d.month = add_ints_reduce( p.d.year, at->month, 0, &n  );
 p.d.day = add_ints_reduce( p.d.year, at->month, at->day, &n  );
 ip = p.calendar;
 for ( i = 1; i <= 31; ++i, ip++ )
     *ip = add_ints_reduce( p.d.year, at->month, i, &n  );

 return( p );
}

#define nred(x) n->x.red = reduce_int( n->x.raw, &n->x.test )

void calc_numbers( NUMBERS *n, DATES *d )
{
 double j;
 short sign, i, nx;
 time_t t;
 struct tm date;
 
 assert( d != NULL && n != NULL );
 n->destiny.red = destiny(d, &n->destiny.test );
 j = julian_date( d, 0, 0, 1980 );
 if ( !d->month && !d->day && !d->year ) {
    return;
    }
 i = sun_minutes( j );
 assert( i < 21600 );
 i /= 60;
 n->degrees.raw = i;
 nred(degrees);
 n->minor.raw = i % 30;
 nred(minor);
 sign = i / 30;
 n->sign.raw = sign;
 sign++;
 nred(sign);
 n->dest_direct = destiny_direction(d, sign);
 for ( i = 0; i < 3; ++i )
     n->challenges[i] = challenge( d, i+1 );
 for ( i = 0; i < 3; ++i )
     n->life_cycles[i].num = life_cycle( d, i+1, &n->life_cycles[i].start,
	&n->life_cycles[i].end, &n->life_cycles[i].test );
 for ( i = 0; i < 4; ++i )
     n->turn_point[i].num = turn_point( d, i+1, &n->turn_point[i].start,
	&n->turn_point[i].end, &n->turn_point[i].test );
 time(&t);
 date = *gmtime(&t);
 n->universal.year = reduce_int( date.tm_year, &nx );
 n->universal.month = add_ints_reduce( n->universal.year, date.tm_mon, 0, &nx  );
 n->universal.day = add_ints_reduce( n->universal.year, date.tm_mon, date.tm_yday, &nx  );

 n->personal.year = add_ints_reduce( date.tm_year, d->month, d->day, &nx );
 n->personal.month = add_ints_reduce( n->personal.year, date.tm_mon, 0, &nx );
 n->personal.day = add_ints_reduce( n->personal.year, date.tm_mon, date.tm_yday, &nx );
}

