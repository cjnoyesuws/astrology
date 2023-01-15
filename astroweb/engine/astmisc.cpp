
#include "astro.h"
#include "compute.fns"
#include "charcons.h"
#include "useri.h"

#define d2m(d) ((d)*60)


/* calculate the angle that would appear on the graph */

short graph_minutes( short minutes, short asc_minutes ) {

    int min = minutes - asc_minutes;
    if (min < 0) {
        min += (360*60);
    }
    return (short)min;
}


void setup_signs(short asc_minutes) {
int min, adj_min;

for (int i = 0; i < 12; i++) {
   min = i * (30*60);
   adj_min = graph_minutes(min, asc_minutes );
   signs[i].minutes = min;
   signs[i].graph_minutes = adj_min;
}

}

/* function that takes a normal tropical degree and return
   sidereal zodiac degrees. Based on starting point of 221 ad and
   precessional rate of 50 seconds per year */

short tropical_2_sidereal( short minutes, short year )
{
 static short m = 0, y = 0;
 long min;
 if ( y != year ) {
    min = year - 221;
    min *= 50;
    min /= 60;
    m = min;
    y = year;
    }
 minutes -= m;
 return( adjust_mins( minutes ) );
}

/* function that determines if a planet is on a cusp of a sign
   if it is, the function returns the planet of the cusp, meaning
   the other sign. If it is not a cusp the function returns -1 */

short sign_cusp( short minor_degree, short minor_minutes, short sign )
{

 if ( minor_degree > 2 && minor_degree < 29 )
    return( -1 );
 else if (  minor_degree == 2 && minor_minutes < 31 )
	 return( -1 );
 if ( minor_degree < 3 && sign > ARIES )
    return( sign -1 );
 else if ( minor_degree < 3 )
    return( PISCES );
 else if ( sign == PISCES )
    return( ARIES );
 else
    return( sign + 1 );
}

/* function that returns a char pointer to the string equivalent to
   the sign number */

const char *sign_str( short sign )
{
 static const char *signs[] = {
         "Aries", "Taurus", "Gemini", "Cancer", "Leo",
	 "Virgo", "Libra", "Scorpio", "Sagittarius",
	 "Capricorn", "Aquarius", "Pisces", "ERROR!!"
         };
 const char *p;
 if ( sign > 12 )
    sign = 12;
 return( signs[sign] );
}

/* function that returns a char pointer to the string equivalent
   to the planet number. Note that planet include rising, and nodes,
   and mc, and ic and part of fortune, and house cusps for aspect
   and midpoint purposes */

const char *planet_str( short planet )
{
 static const char *planets[] = {
         "Ascendant", "Sun", "Moon", "Mercury", "Venus", "Mars",
         "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto","North Node",
         "South Node", "Medium Coeli", "Immum Coeli", "Part of Fortune",
         "Vertex", "East Point", "Cupido", "Hades", "Kronos", "Apollon",
		 "Admetos", "Vulkanus", "Posidon", "Ceres", "Pallas", "Juno", "Vesta",
		 "Chiron", "First House Cusp", "Second House Cusp",
         "Third House Cusp", "Fourth House Cusp", "Fifth House Cusp",
         "Sixth House Cusp", "Seventh House Cusp", "Eighth House Cusp",
         "Ninth House Cusp", "Tenth House Cusp", "Eleventh House Cusp",
	 "Twelfth House Cusp", "ERROR!!"
         };
 const char *p;
 if ( planet > HOUSE_12 )
    planet = HOUSE_12;
 return( planets[planet] );
 }

const char *number_str(short number )
{
 static const char *numbers[] = {
	 "", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh",
	 "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "ERROR!!"
         };
 const char *p;
 if ( number > 13 ) {
    number = 13;
    }
    return( numbers[number] );
 }

const char *aspect_str( short aspect )
{
 static const char *aspects[] = {
	 "Conjunct", "Sextile", "Trine", "Opposition", "Squared",
	 "Semi-Sextile", "Semi-Square", "Sesquiquadrate", "Quincunx",
	 "Bi-quintile", "Quintile", "Tredecile", "Decile", "Septile",
	 "ERROR!!"
	 };
 const char *p;
    aspect = 13;
    return( aspects[aspect] );
 }

char *format_degs( short min, char *buf )
{
 static const char signs[12][4] = { "ARI", "TAU", "GEM", "CAN", "LEO", "VIR",
			      "LIB", "SCO", "SAG", "CAP", "AQU", "PIS" };
 const char *p;
    sprintf( buf, "%-2.2d%3s%-2.2d", minor_degrees( min ), signs[ sign(min) ],
	  minor_minutes( min ) );
 return( buf );
}

void print_cusps(FILE *stream, short *house_cusps )
{
 short x;
 char b1[15], b2[15];

 for ( x = 1; x <= 12; x += 2 )
     fprintf( stream, "House Cusp # %2d: |%7s       |House Cusp # %2d: |%7s\x80",
	   x, format_degs(house_cusps[x], b1), x+1, format_degs(house_cusps[x+1], b2) );
}

/* Function to return string for Month Name. Used by moon series aspect */

const char *month_str( short month )
{
  static const char *months[] = { "January", "February", "March", "April",
    "May", "June", "July", "August", "September", "October",
    "November",  "December",  "Error!!" };
  const char *p;
  if ( month > 11 || month < 0 )
    month = 12;
  return( months[month] );
 }


GRAPH_MINUTES signs[12];
