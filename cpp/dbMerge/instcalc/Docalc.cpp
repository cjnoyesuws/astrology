#include "stdafx.h"
#include <float.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "compute.fns"
#include "datetime.fns"
#include "errors.fns"
#include "ascend.h"
#include "julian.h"
#include "dataext.h"
#include "utlduad.h"
#include <setjmp.h>
#include <float.h>


extern void GetPlanetData( int plan, AS_INF *inf, double jul );

/* 09/10/92  Modified for C++ Windows */

jmp_buf j;
extern double sun_longitude;
#define RESET_ENGINE 999

int cdecl _matherr( struct _exception *e )
{
 static char *errs[] = { "", "Domain", "Singularity", "Overflow",
   "Underflow", "Total Loss of Significance", "Partial Loss of Significance" };

 if ( (!strcmpi(e->name, "acos" ) || !strcmpi(e->name, "asin" )) && e->type == DOMAIN ) {
    alert_box( "MATH ERROR!!", "Too High Latitude for Ascendant, "
		 "or Too Low Latitude for Vertex!!" );
    e->retval = 0.0;
    errno = EDOM;
    }
 else {
    if ( e->type && e->type <= _PLOSS ) {
       alert_box( "MATH ERROR!!", "%s Error in %s--Args are: %lf and %lf, retval = %lf--"
		  "Call Technical Support with These Details!!\n",
		  errs[e->type], e->name, e->arg1, e->arg2, e->retval );
       e->retval = 0.0;
       errno = EDOM;
       }
    else
       return( 0 );
    }
 _fpreset();
 longjmp( j, 3 );
 return( 1 );
}

typedef void (*sigtype)(int sig);

void fpehnd(int sig, int num )
{
 static char *errs[] = {"", "Invalid", "Denormal", "Divide By Zero",
      "Overflow", "Underflow", "Inexact", "UnEmulated Instruction",
      "Negative Square Root", "", "Stack Overflow", "Stack Underflow", "" };
 if ( num >= _FPE_INVALID || num <= _FPE_EXPLICITGEN ) {
    num %= 0x80;
    alert_box( "Math Error!!", "Error: %s--Call Technical Support and "
       "Report this Error!!", errs[num] );
    }
 else
    return;
 errno = EDOM;
 _fpreset();
 longjmp( j, 2 );
 return;
}

/* module to do do calcualtions and call other modules */



/* function to call other modules and do calculations.
   enter with pointer to array of AS_INF type of structure
   and pointer to AS_DATA type of structure. Also supply
   operating code which selects various options and house_proc
   code which calls house processing routines */

void do_calc( DATES &birth, TIM &btime, DEG_MIN &longitude, DEG_MIN &latitude, int gmt_hrs, int gmt_min, short *mins )
{
 COUNT i;
 LMIN min;
 DEGR degrees, d = 0;
 JULIAN jul;
 AS_INF info;
 short retr;
 TIM sidereal, noon_time;
 DATES tnoon_date;

 memset(&tnoon_date,0,sizeof(DATES)); 
 memset(&noon_time,0,sizeof(TIM));
 memset(&sidereal,0,sizeof(TIM));
 if ( setjmp( j ) ) {        /* Math Error Occurred */
    return;
    }
 if ( signal( SIGFPE, (sigtype)fpehnd ) == SIG_ERR ) {
    return;
    }
 if ( !longitude.dir || !latitude.dir ) {
    alert_box( "", "Longitude or Latitutde Are Not Set!" );
    return;
    }
 short hour_adjust = noon_date( &birth, &tnoon_date, &noon_time, &btime,
	   gmt_hrs, gmt_min );
 sidereal_time( &tnoon_date, hour_adjust, noon_time.minutes,
	    &longitude, &sidereal, latitude.dir );
 julian_calc( &tnoon_date, hour_adjust, noon_time.minutes, &jul);
 setup_obliquity(&jul );
 mins[MED_COELI] = comp_med_coeli( &sidereal );
 mins[IM_COELI] = adjust_mins( flip_mins(mins[MED_COELI] + 
	  d2m(180), latitude.dir ) );
 mins[ASCEND] = calc_ascendant( &latitude );
 mins[SUN] = sun_minutes( &jul );
 GetPlanetData( SUN, &info, jul.jd_4000bc );
 mins[SUN] = info.minutes_total;
 mins[MOON] = moon_minutes( &jul, mins+NORTH_NODE );
 GetPlanetData( MOON, &info, jul.jd_4000bc );
 mins[MOON] = info.minutes_total;
 mins[NORTH_NODE] = -mins[NORTH_NODE];
 mins[SOUTH_NODE] = -adjust_mins( flip_mins( mins[NORTH_NODE]+d2m(180),
	 latitude.dir ) );
 for ( i = MERCURY; i <= PLUTO; ++i  ) {
     mins[i] = planet_minutes( i, &jul, &retr );
	 GetPlanetData( i, &info, jul.jd_4000bc );
	 if ( retr == 1 )
		 mins[i] = - info.minutes_total;
	 else
		 mins[i] = info.minutes_total;
     }
  min = mins[ASCEND];
  min += mins[MOON];
  min -= mins[SUN];
  if ( min < 0L )
     min += d2m(360L);
  min %= d2m(360L);
  mins[PART_FORTU]= (short) min;
}
