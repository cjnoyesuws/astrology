#include "stdafx.h"
#include "astro.h"
#include "compute.fns"
#include "output.fns"
#include "charcons.h"
#include "report.h"
#include "textptr.h"

extern int global_table;

#define get_text( k, i) tb_get_text( global_table, (k), (i) )

#define SIGN_START      ST__SIGN
#define PLANET_START    ST__PLANET
#define NUMBER_START    ST__NUMBERS
#define ASPECT_START    ST__ASPECTS
#define SIGN3_START     ST__SIGN3

#define d2m(d) ((d)*60)

/* Functions below commented out are in ASTXMISC.ASM */

/* function that takes a normal tropical degree and return
   sidereal zodiac degrees. Based on starting point of 221 ad and
   precessional rate of 50 seconds per year */

MINU tropical_2_sidereal( MINU minutes, short year )
{
 static short near m = 0, near y = 0;
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

NUM sign_cusp( DEGR minor_degree, DEGR minor_minutes, NUM sign )
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

const char *sign_str( NUM sign )
{
 static const char *signs[] = {
         "Aries", "Taurus", "Gemini", "Cancer", "Leo", 
	 "Virgo", "Libra", "Scorpio", "Sagittarius",
	 "Capricorn", "Aquarius", "Pisces", "ERROR!!"
         };
 const char *p;
 if ( sign > 12 )
    sign = 12;
if ( global_table == -1 )
   return( signs[sign] );
else {
   p = get_text( SIGN_START, sign);
   if ( p == NULL )
      return( signs[sign] );
   else
      return( p );
   }
}

/* function that returns a char pointer to the string equivalent
   to the planet number. Note that planet include rising, and nodes,
   and mc, and ic and part of fortune, and house cusps for aspect
   and midpoint purposes */      

const char *planet_str( NUM planet )
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
 if ( global_table == -1 )
    return( planets[planet] );
 else {
   p = get_text( PLANET_START, planet);
   if ( p == NULL )
      return( planets[planet] );
   else
      return( p );
   }
}

const char *number_str( NUM number )
{
 static const char *numbers[] = {
	 "", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh",
	 "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "ERROR!!"
         };
 const char *p;
 if ( number > 13 )
    number = 13;
 if ( global_table == -1 )
    return( numbers[number] );
 else {
   p = get_text( NUMBER_START-1, number);
   if ( p == NULL )
      return( numbers[number] );
   else
      return( p );
   }
}

const char *aspect_str( NUM aspect )
{
 static const char *aspects[] = {
	 "Conjunct", "Sextile", "Trine", "Opposition", "Squared",
	 "Semi-Sextile", "Semi-Square", "Sesquiquadrate", "Quincunx",
	 "Bi-quintile", "Quintile", "Tredecile", "Decile", "Septile",
	 "ERROR!!"
	 };
 const char *p;
 if ( aspect > 13 )
    aspect = 13;
 if ( global_table == -1 )
    return( aspects[aspect] );
 else {
   p = get_text(ASPECT_START, aspect);
   if ( p == NULL )
      return( aspects[aspect] );
   else
      return( p );
   }
}

char *format_degs( MINU min, char *buf )
{
 static char signs[12][4] = { "ARI", "TAU", "GEM", "CAN", "LEO", "VIR",
			      "LIB", "SCO", "SAG", "CAP", "AQU", "PIS" };
 const char *p;
 if ( global_table == -1 )
    sprintf( buf, "%-2.2d%3s%-2.2d", minor_degrees( min ), signs[ sign(min) ],
	  minor_minutes( min ) );
 else {
    p = get_text(SIGN3_START,sign(min));
    if ( p == NULL )
       p = signs[ sign(min) ];
    sprintf( buf, "%-2.2d%3s%-2.2d", minor_degrees( min ), p,
	 minor_minutes( min ) );
    }
 return( buf );
}

void print_cusps(FILE *stream, MINU *house_cusps )
{
 COUNT x;
 char b1[15], b2[15];

 for ( x = 1; x <= 12; x += 2 )
     fprintf( stream, "House Cusp # %2d: |%7s       |House Cusp # %2d: |%7s\x80",
	   x, format_degs(house_cusps[x], b1), x+1, format_degs(house_cusps[x+1], b2) );
}

/* Function to return string for Month Name. Used by moon series aspect */

const char *month_str( short month )
{
 static char *months[] = { "January", "February", "March", "April",
    "May", "June", "July", "August", "September", "October",
    "November",  "December",  "Error!!" };
 const char *p;
 if ( month > 11 || month < 0 )
    month = 12;
 if ( global_table == -1 ) {
    return( months[month] );
    }
 else {
    p = tb_get_text( global_table, ST__MONTH, month );
    if ( p == NULL )
       return( months[month] );
    else
       return( p );
    }
}


