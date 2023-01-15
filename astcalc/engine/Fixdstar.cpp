#include "stdafx.h"
#include "astro.h"
#include "fixstar.h"
#include "flags.h"
#include "output.fns"
#include "compute.fns"
#include "errors.fns"
#include "report.h"
#include "charcons.h"
#include "textptr.h"
#include "datetime.fns"

/* 09/10/92  Modified for C++ Windows */

#define sd2m(s,d,m) (((s)*1800)+((d)*60)+m)

#define N_FIXED_STAR 58
#define N_MESSIER 109
#define FIXED_STAR_WIDTH 30

extern void ProcessFixedStar(double jul, int fix, AS_INF *inf);
#ifdef MESSIER
extern void ProcessMessier(double jul, int mes, AS_INF *inf);
int messier;
#endif

extern int report_table;
/*
char fixed_star_names[N_FIXED_STAR][FIXED_STAR_WIDTH] = { "Alpheratz", "Baten Kaitos",
  "Sharatan", "Algol", "Alcyone", "Aldebaran", "Rigel", "Sirius", "Castor",
  "Pollux", "Procyon", "North Asellus", "South Assellus", "Regullus",
  "Zosma", "Vindemiatrix", "Spica", "Arcturus", "Bungula", "Antares",
  "Wega (Vega)", "Altair", "Deneb Algedi", "Fomalhaut", "Markab", "Scheat"
  };
*/

/*int fixed_star_minutes[N_FIXED_STAR] = {
  sd2m(ARIES, 12, 2), sd2m(ARIES, 21, 40), sd2m(TAURUS, 3, 41),
  sd2m(TAURUS, 25, 53), sd2m(TAURUS, 29, 43), sd2m(GEMINI, 9, 31),
  sd2m(GEMINI, 16, 33), sd2m(CANCER, 13, 38), sd2m(CANCER, 19, 58),
  sd2m(CANCER, 22, 57), sd2m(CANCER, 25, 31), sd2m(LEO, 7, 16),
  sd2m(LEO, 8, 27), sd2m(LEO, 29, 33), sd2m(VIRGO, 11, 02),
  sd2m(LIBRA, 9, 40), sd2m(LIBRA, 23, 34), sd2m(LIBRA, 23, 57),
  sd2m(SCORPIO, 29, 14), sd2m(SAGITARIUS, 9, 29), sd2m(CAPRICORN, 15, 02),
  sd2m(AQUARIUS, 1, 30), sd2m(AQUARIUS, 23, 16),
  sd2m(PISCES, 3, 35), sd2m(PISCES, 23, 12), sd2m(PISCES, 29, 06) };
*/

AS_INF *fixed_stars = NULL;
int fixed_star_count = 0;

AS_INF *getFixedStars()
{
 return( (AS_INF *) fixed_stars );
}

extern int getFixedStarCount()
{
 return( fixed_star_count );
}

void close_fixed_stars( void )
{
 int i;
 AS_INF *p;
 
 if ( fixed_stars == NULL )
    return;
 for ( i = 0, p = fixed_stars; i < fixed_star_count; i++, p++ ) {
     if ( p->aspectr != NULL )
	delete p->aspectr;
     }
 delete fixed_stars;
 fixed_stars = NULL;
 fixed_star_count = 0;
}

const char *fixed_star_str( int f )
{
 int tb;
#ifdef MESSIER
 if ( messier )
    tb = ST__MESSIER;
 else
#endif
    tb = ST__FIXEDN;
 if ( f < 0 || f >= fixed_star_count )
    return( "ERROR!" );
 else
    return( tb_get_text( report_table, tb,f ) );
}


int do_fixed_star( int i, AS_INF *fixed, unsigned short mode, int year, double jul  )
{
 int aspects, maxp;
 ASPEC *asp;
 long m;

 if ( mode & ASTEROID )
	 maxp = CHIRON;
 else if ( mode & VERT_EAST )
    maxp = VERTEX;
 else
    maxp = PART_FORTU;
#ifdef MESSIER
 if ( !messier )
#endif
    ProcessFixedStar(jul, i, fixed);
#ifdef MESSIER
 else
    ProcessMessier(jul, i, fixed);
#endif
 fixed->calced = 1;
 misc_calc(fixed, mode, year);
 if ( mode & ASPECTS ) {
    asp = new ASPEC[30];
    if ( asp == NULL ) {
       errno = ENOMEM;
       fixed->aspectr = NULL;
       fixed->no_aspects = 0;
       return( -1 );
       }
    memset( asp, 0, (30) * sizeof(ASPEC));
    fixed->aspectr = asp;
    aspects = do_arab_aspect( fixed, birth_inf, 0, mode, maxp );
    if ( fixed->aspectr != NULL )
       fixed->aspectr = (ASPEC *)reallocx( fixed->aspectr, aspects * sizeof(ASPEC) );
    }
 else {
    fixed->aspectr = NULL;
    fixed->no_aspects = 0;
    }
 return( 0 );
}


void do_fixed_stars(unsigned short mode, int year, int mess, DATES &birth )
{
 int i, count;
 AS_INF *fixed;
#ifdef MESSIER
 messier = mess;
 if ( mess )
	count = N_MESSIER;
 else
#endif
    count = N_FIXED_STAR; 
 fixed_stars = new AS_INF[count];
 if ( fixed_stars == NULL ) {
    fixed_star_count = 0;
    errno = ENOMEM;
    return;
    }
 double juldate = julian_date( &birth, 0, 0, -4000 );
 for ( i = 0, fixed = fixed_stars; i < count; ++i, ++fixed ) {
     do_fixed_star( i, fixed, mode, year, juldate );
     if ( errno == ENOMEM ) {
	fixed_star_count = i-1;
	return;
	}
     }
 fixed_star_count = count;
 if ( mode & (FULL_MID|HALF_MID)) {
     int mp = SOUTH_NODE;
	 if ( mode & ASTEROID )
		 mp = CHIRON;
	 else if ( mode & VERT_EAST )
		 mp = EAST_POINT;
	 do_main_full_midpoints( fixed_stars, fixed_star_count, birth_inf, mp, mode, 0 );
    }
}
