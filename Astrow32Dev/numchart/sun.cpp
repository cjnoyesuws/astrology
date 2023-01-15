#include <math.h>
#include "utl.h"

extern double fmodulus( double num, double divisor );
extern double atan2rads( double x, double y );
extern double kepler_eccentric_anomaly( double mean_anomaly, double eccentricity );
extern double true_anomaly( double mean_anomaly, double eccentricity );


double sun_mean_anomaly;
double sun_longitude;

#define PI                3.141515927
#define d2r(d)            ((d)*PI)/180.0
#define FULL_CIRCLE       (2.0*PI)
#define DEGS_MOVED        d2r(360.0)
#define DAYS_USED         365.2422
#define ECL_LONG_EPOCH    d2r(278.833540)
#define ECL_LONG_PERIGEE  d2r(282.596403)
#define ECCENTRICITY      0.016718



/* routine to calculate the position of the sun. Takes julian date
   epoch 1980.0 and returns sun minutes of longitude */

short sun_minutes( double jul_date )
{
 double n, ecx;

 n =  (DEGS_MOVED / DAYS_USED) * jul_date;
 n = fmodulus( n, FULL_CIRCLE );
 sun_mean_anomaly = n + ( ECL_LONG_EPOCH - ECL_LONG_PERIGEE );
 sun_mean_anomaly = fmodulus( sun_mean_anomaly, FULL_CIRCLE );
 sun_longitude = true_anomaly( sun_mean_anomaly, ECCENTRICITY ) + ECL_LONG_PERIGEE;
 sun_longitude = fmodulus( sun_longitude, FULL_CIRCLE );
 return( r2m(sun_longitude) );
}
