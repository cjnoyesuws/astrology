#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <math.h>
#include "astro.h"
#include "julian.h"
#include "utl.h"
#include "plans.h"
#include <assert.h>
#include "planpert.fns"

extern double correct_pluto( JULIAN *j, double lpd, double el);
extern double kepler_eccentric_anomaly( double ma, double ecc);
extern double true_anomaly( double eccen, double kep );
extern double fmodulus( double num, double div );
extern double julian_calc( struct DATES *d, int h, int m, struct JULIAN *j );
extern MINU sun_minutes( JULIAN *j );

extern double sun_longitude;
extern double sun_radius_vector;
extern double sun_mean_anomaly;
extern PLAN_ELE *plan_ptr;


double retrograde( double prv, double pl, double el )
{
 double tmp, p2, s2;

 p2 = pow( prv, 0.5 );
 s2 = pow( sun_radius_vector, 0.5 );
 tmp = ( ( p2 + s2 ) * ( p2 * s2 ) ) /
       ( ( pow( prv, 1.5 ) + pow( sun_radius_vector, 1.5 ) ) );
 tmp -= cos( el - pl );
 return( tmp );
}


/* this structure holds ranges of which the variable ll is compared to
   determine if the planet is in retrograde motion, or is stalled.
   This data has since been invalidated by the above routine. */

/*

struct LL_RANGE {
       double stalled ;
       double retrograde;
       } llvals[] = { 0.850, 0.700, 0.230, 0.211, 0.338, 0.310, 1.01, 0.914,
	     1.170, 1.112, 1.38, 1.21, 1.41, 1.28, 1.48, 1.32 };
*/

double helio_long;


/* function to calculate a planet's position. Note The sun routine must
   be called before calling this function */

MINU planet_minutes( int planet, JULIAN *j, int *retr )
{
 DELTA delta;
 static double earth_long;
 double mean_anomaly, eccentricity, inclination;
 double kepler;
 double true_anomal, ascend_node, xx;
 long double longitude, radius_vector;
 long double lo, sin_lo, cos_lo, psi;
 long double ll, lpd, rpd;

 PLAN_ELE *p;
 int pno;

 pno = planet - MERCURY;

 assert( planet >= MERCURY );
 if ( planet == MERCURY ) {
    if ( !prepare_planetary_data( j ) )
       return( 0 );
    earth_long = sun_longitude + PI;
    if ( earth_long > TWO_PI )
       earth_long -= TWO_PI;
    }
 p = plan_ptr + pno;
 memset( &delta, 0, sizeof( DELTA ) );
 switch( planet ) {
       case MERCURY :
	    p_mercury( plan_ptr, &delta );
	    break;
       case VENUS :
	    p_venus( j, plan_ptr, &delta );
	    break;
       case MARS :
	    p_mars( j, plan_ptr, &delta );
	    break;
       case JUPITER :
	    p_jupiter( j, plan_ptr, &delta );
	    break;
       case SATURN :
	    p_saturn( plan_ptr, &delta );
	    break;
       case URANUS :
	    p_uranus( plan_ptr, &delta, j );
	    break;
       case NEPTUNE :
	    p_neptune( plan_ptr, &delta );
	    break;
       case PLUTO :
	    break;
       default :
	    break;
       }
 eccentricity = p->eccentricity + delta.eccentricity;
 mean_anomaly = p->mean_anomaly + delta.mean_anomaly;
 kepler = kepler_eccentric_anomaly( mean_anomaly, eccentricity );
 true_anomal = true_anomaly( eccentricity, kepler );
 radius_vector = ( p->semi_major + delta.semi_major)
	* ( 1.0 - eccentricity * eccentricity )
	/ ( 1.0 + eccentricity * cosl( true_anomal ) );
 radius_vector += delta.radius_vector;
 longitude = true_anomal + d2r(p->perhelion) +
	 delta.mean_long - delta.mean_anomaly;
 ascend_node = d2r( p->ascend_node );
 lo = longitude - ascend_node;
 cos_lo = cosl( lo );
 sin_lo = sinl( lo );
 inclination = d2r( p->inclination );
 psi = asinl( sin_lo * sinl( inclination ) ) + delta.helio_latitude;
 lpd = atanl( ( sin_lo * cosl( inclination )) / cos_lo ) + ascend_node
  + d2r( delta.longitude );
 if ( cos_lo < 0.0 )
    lpd += PI;
 if ( planet == PLUTO )
    lpd = correct_pluto( j, lpd, earth_long );

 if ( lpd > TWO_PI )
    lpd -= TWO_PI;
 else if ( lpd < 0.0)
    lpd += TWO_PI;
 helio_long = lpd;
 rpd = radius_vector * cosl( psi );
 ll = lpd - earth_long;
 /*
 if ( fabs( ll ) < llvals[pno].retrograde )
    *retr = 1;
 else if ( fabs( ll ) < llvals[pno].stalled )
    *retr = 2;
 else
    *retr = 0;
 */
 xx = retrograde( radius_vector, lpd, earth_long );
 if ( xx < 0.0 )
    *retr = 1;
 else if ( xx == 0.0 )
    *retr = 2;
 else
    *retr = 0;
 if ( planet >= MARS ) {
    longitude = atanl( sun_radius_vector * sinl( ll ) /
	( rpd - sun_radius_vector * cosl( ll ) ) ) + lpd;
    longitude = fmodulus( longitude, TWO_PI );
    }
 else {
    longitude = atanl( -1.0 * rpd * sinl( ll ) /
	( sun_radius_vector - rpd * cosl( ll ) ) ) + earth_long + PI;
    longitude = fmodulus( longitude, TWO_PI );
    }
 if ( planet == PLUTO )
    reset_plan_ptr();
 return( r2m( longitude ) );
}
