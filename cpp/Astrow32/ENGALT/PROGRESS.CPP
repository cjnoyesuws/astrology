#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "astro.h"
#include "flags.h"
#include "julian.h"
#include "compute.fns" 
#include "datetime.fns"
#include "dataext.h"
#include "errors.fns"

/* 09/10/92  Modified for C++ Windows */

#define d2m(d) ((d)*60)

static int step;

AS_INF near * moon_series = NULL, near * prog = NULL,
       near * prog_moon_series = NULL; /* for progression moon analysis
       for each month, and for progressed to progressed aspects, and
       for aspects of moon versus progressed planets */

/* function to progress a date. Function implements Secondary, Tertiary,
   minor progressions. Once date is progressed, then date is adjusted
   to normal limits. If an error exists in date function returns 1
   otherwise it returns 0 indicating no error */


/* Function to produce a moon series for a progressed moon. A separate 
   moon calculation is calculated for each month four prior to the
   month and one year afterward. Presently moon is stepped 1 degree, 4min
   for each month. */

void make_moon_series( MINU moon, BITS mode, short year )
{
 COUNT i;
 MINU md;
 AS_INF m;

 for ( i = 4, md = moon; i >= 0; --i, md -= step )
     (moon_series + i)->minutes_total = adjust_mins( md );
 for ( i = 5, md = moon + step; i <= 15; ++i, md += step )
     (moon_series + i)->minutes_total = adjust_mins( md );
 for ( i = 0; i <= 15; ++i ) {
     misc_calc( (moon_series + i), mode, year );
     }
}

/* function to process aspects For Progressions. Space is allocated
   intitially for 15 aspects as starting point. Then aspects are
   calculated. When total number of aspects is known, then space
   is resized to fit with realoc. This process is followed for
   all members of the array that main points to. If mode is set
   then we have no birthtime so we have to skip those planets
   which depend on birth time. maxx determines the maximum number
   of elements that are indexed. This is necessary and different
   from the variable maxp in that a moon series only has 16 enries,
   where a normal AS_INF array has 18 max. */

void prog_process_aspects( AS_INF near *planet, AS_INF near *sub,
						      BITS mode, NUM maxx )
{
 ASPEC *asp;
 AS_INF near *pl;
 NUM    maxp;
 COUNT  pno, aspects;
 MINU   maxorb;
 BITS   hm = mode & HOUSES;

 maxorb = d2m(2);
 if ( mode & VERT_EAST && !(mode & NOBIRTHTIM) )
    maxp = VERTEX;
 else if ( !(mode & NOBIRTHTIM) )
    maxp = IM_COELI;
 else
   maxp = NORTH_NODE;
 if ( maxx == -1 )
    maxx = maxp;
 mode &= NOBIRTHTIM;

 for ( pno = SUN, pl = planet; pno <= maxx; ++pl, ++pno ) {
     if ( !mode || ( pno != ASCEND ) ) {
	asp = new ASPEC[15];
	if ( asp == NULL ) {
	   errno = ENOMEM;
	   pl->aspectr = NULL;
	   pl->no_aspects = 0;
	   return;
	   }
	pl->aspectr = asp;
	aspects = do_aspect( pl, 0, sub, maxorb, mode,
				       ( ( hm ) ? -maxp : maxp), 0 );
	pl->aspectr = (ASPEC *) reallocx( asp, aspects * sizeof(ASPEC) );
	}
      else {
	pl->aspectr = NULL;
	pl->no_aspects = 0;
	}
    }
}


/* Function to to full Series Progressions including moon Series and
   aspects for Moon Series. Variable begining with P refer to progresed
   and b refer to birth*/

void do_full_progr( AS_DATA *bdata, AS_INF near *binf, AS_INF near *pinf,
		   BITS bmode, BITS pmode, NUM house_proc, DATA_PACKET *dpk )
{
 BITS mask = ( 0xffff ^ ( BASE_MID | FULL_MID | MID_ASPECT | ASPECTS  ) );

 int hc[13];
 int cc;
 short i, m1, m2;
 JULIAN j1;
 AS_INF *ptr;
 bmode &= mask;
 pmode &= mask;

 moon_series =(AS_INF near *) LocalAlloc( LPTR, 17 * sizeof( AS_INF ) );
 prog = (AS_INF near *)LocalAlloc( LPTR, 19 * sizeof( AS_INF ) );
 prog_moon_series = (AS_INF near *)LocalAlloc( LPTR, 17 * sizeof( AS_INF ) );
 if ( moon_series == NULL || prog == NULL || prog_moon_series == NULL ) {
    errno = ENOMEM;
    return;     
    }
 if ( bmode & NOBIRTHTIM )
    pmode |= NOBIRTHTIM;
 else if ( pmode & NOBIRTHTIM )
    bmode |= NOBIRTHTIM;
 cc = dpk->chart_code;
 dpk->chart_code |= PRGCS_CH;
 do_calc( pinf, bdata, pmode, house_proc, dpk );
 julian_calc( &bdata->noon_date, bdata->hour_adjust,
       bdata->birth_time.minutes, &j1 );
 memcpy( alt_cusps, house_cusps, 13 * sizeof( int ) );
 dpk->chart_code = NATAL_CH;
 do_calc( binf, bdata, bmode, house_proc, dpk );
 dpk->chart_code = cc;
 if ( bmode & HOUSES ) {
    for ( ptr = pinf, i = 0; i < 18; i++, ptr++ ) {
	ptr->house = house_number( ptr->minutes_total );
	ptr->house_cusp = house_cusp_intercept( ptr->minutes_total,
	      ptr->house );
	ptr->intercepted = is_sign_intercept( ptr->sign );
	}
    }
 prog_process_aspects( pinf, binf, bmode, -1 );
 if ( errno == ENOMEM )
    return;
 m1 = moon_minutes( &j1, &i );
 j1.jd_1900 += 1.0;
 julian_update( &j1 );
 m2 = moon_minutes( &j1, &i );
 if ( m2 - m1 < 0 )
    m2 += (360*60);
 step = (m2-m1)/12;
 make_moon_series( ( pinf+ MOON )->minutes_total,
               bmode, bdata->birth_date.year );
 memcpy( prog_moon_series, moon_series, (16 * sizeof(AS_INF)) );
 prog_process_aspects( moon_series, binf, bmode, 16 );
 if ( errno == ENOMEM )
    return;
 prog_process_aspects( prog_moon_series, pinf, bmode, 16 );
 memcpy( prog, pinf, (18 * sizeof(AS_INF)) );
 process_aspects( pinf, pinf, bmode, dpk->chart_code );
}
