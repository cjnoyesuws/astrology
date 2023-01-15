#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "misccalc.h"
#include "dataext.h"
#include "flags.h"
#include "charcons.h"
#include "output.fns"
#include "oututil.h"
#include "outfunc.fns"
#include "aspect.h"

int output_scout_planet( FILE *stream, char *s1, char *s2, int sp, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opcaps( stream, planet_str(sp), buf );
	       break;
	  case '4' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_genders( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
	          p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, genders.masculine );
	       break;
	  case '4' :
	       opnum( stream, 2, genders.feminine );
	       break;
	  case '5' :
	       opnum( stream, 2, comp_genders.masculine );
	       break;
	  case '6' :
	       opnum( stream, 2, comp_genders.feminine );
	       break;
	  case '7' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case '8' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_elements( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, elements.fire );
	       break;
	  case '4' :
	       opnum( stream, 2, elements.earth );
	       break;
	  case '5' :
	       opnum( stream, 2, elements.air  );
	       break;
	  case '6' :
	       opnum( stream, 2, elements.water  );
	       break;
	  case '7' :
	       opnum( stream, 2, comp_elements.fire  );
	       break;
	  case '8' :
	       opnum( stream, 2, comp_elements.earth  );
	       break;
	  case '9' :
	       opnum( stream, 2, comp_elements.air  );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, comp_elements.water  );
	       break;
	  case 'B' :
	  case 'b' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_qualities( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, qualities.cardinal );
	       break;
	  case '4' :
	       opnum( stream, 2, qualities.fixed );
	       break;
	  case '5' :
	       opnum( stream, 2, qualities._mutable );
	       break;
	  case '6' :
	       opnum( stream, 2, comp_qualities.cardinal );
	       break;
	  case '7' :
	       opnum( stream, 2, comp_qualities.fixed );
	       break;
	  case '8' :
	       opnum( stream, 2, comp_qualities._mutable );
	       break;
	  case '9' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_hemispheres( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, hemispheres.north );
	       break;
	  case '4' :
	       opnum( stream, 2, hemispheres.south );
	       break;
	  case '5' :
	       opnum( stream, 2, hemispheres.east );
	       break;
	  case '6' :
	       opnum( stream, 2, hemispheres.west );
	       break;
	  case '7' :
	       opnum( stream, 2, comp_hemispheres.north );
	       break;
	  case '8' :
	       opnum( stream, 2, comp_hemispheres.south );
	       break;
	  case '9' :
	       opnum( stream, 2, comp_hemispheres.east );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, comp_hemispheres.west );
	       break;
	  case 'B' :
	  case 'b' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}


int output_functionals( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, functionals.individual );
	       break;
	  case '4' :
	       opnum( stream, 2, functionals.relative );
	       break;
	  case '5' :
	       opnum( stream, 2, functionals.temporal );
	       break;
	  case '6' :
	       opnum( stream, 2, functionals.terminal );
	       break;
	  case '7' :
	       opnum( stream, 2, comp_functionals.individual );
	       break;
	  case '8' :
	       opnum( stream, 2, comp_functionals.relative );
	       break;
	  case '9' :
	       opnum( stream, 2, comp_functionals.temporal );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, comp_functionals.terminal );
	       break;
	  case 'B' :
	  case 'b' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_modals( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, modals.cadent );
	       break;
	  case '4' :
	       opnum( stream, 2, modals.angular );
	       break;
	  case '5' :
	       opnum( stream, 2, modals.succedent );
	       break;
	  case '6' :
	       opnum( stream, 2, comp_modals.cadent );
	       break;
	  case '7' :
	       opnum( stream, 2, comp_modals.angular );
	       break;
	  case '8' :
	       opnum( stream, 2, comp_modals.succedent );
	       break;
	  case '9' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_aspect_count( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, aspect_count[CONJUNCT] );
	       break;
	  case '4' :
	       opnum( stream, 2, aspect_count[SEXTILE] );
	       break;
	  case '5' :
	       opnum( stream, 2, aspect_count[TRINE] );
	       break;
	  case '6' :
	       opnum( stream, 2, aspect_count[OPPOSITION] );
	       break;
	  case '7' :
	       opnum( stream, 2, aspect_count[SQUARED] );
	       break;
	  case '8' :
	       opnum( stream, 2, aspect_count[SEMISEXT] );
	       break;
	  case '9' :
	       opnum( stream, 2, aspect_count[SEMISESQUAD] );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, aspect_count[SEMISQUARE] );
	       break;
	  case 'B' :
	  case 'b' :
	       opnum( stream, 2, aspect_count[QUINCUNX] );
	       break;
	  case 'C' :
	  case 'c' :
	       opnum( stream, 2, aspect_count[BIQUINTILE] );
	       break;
	  case 'D' :
	  case 'd' :
	       opnum( stream, 2, aspect_count[QUINTILE] );
	       break;
	  case 'E' :
	  case 'e' :
	       opnum( stream, 2, aspect_count[TREDECILE] );
	       break;
	  case 'F' :
	  case 'f' :
	       opnum( stream, 2, aspect_count[DECILE] );
	       break;
	  case 'G' :
	  case 'g' :
	       opnum( stream, 2, aspect_count[SEPTILE] );
	       break;
	  case 'H' :
	  case 'h' :
	       opnum( stream, 2, comp_aspect_count[CONJUNCT] );
	       break;
	  case 'I' :
	  case 'i' :
	       opnum( stream, 2, comp_aspect_count[SEXTILE] );
	       break;
	  case 'J' :
	  case 'j' :
	       opnum( stream, 2, comp_aspect_count[TRINE] );
	       break;
	  case 'K' :
	  case 'k' :
	       opnum( stream, 2, comp_aspect_count[OPPOSITION] );
	       break;
	  case 'L' :
	  case 'l' :
	       opnum( stream, 2, comp_aspect_count[SQUARED] );
	       break;
	  case 'M' :
	  case 'm' :
	       opnum( stream, 2, comp_aspect_count[SEMISEXT] );
	       break;
	  case 'N' :
	  case 'n' :
	       opnum( stream, 2, comp_aspect_count[SEMISESQUAD] );
	       break;
	  case 'O' :
	  case 'o' :
	       opnum( stream, 2, comp_aspect_count[SEMISQUARE] );
	       break;
	  case 'P' :
	  case 'p' :
	       opnum( stream, 2, comp_aspect_count[QUINCUNX] );
	       break;
	  case 'Q' :
	  case 'q' :
	       opnum( stream, 2, comp_aspect_count[BIQUINTILE] );
	       break;
	  case 'R' :
	  case 'r' :
	       opnum( stream, 2, comp_aspect_count[QUINTILE] );
	       break;
	  case 'S' :
	  case 's' :
	       opnum( stream, 2, comp_aspect_count[TREDECILE] );
	       break;
	  case 'T' :
	  case 't' :
	       opnum( stream, 2, comp_aspect_count[DECILE] );
	       break;
	  case 'U' :
	  case 'u' :
	       opnum( stream, 2, comp_aspect_count[SEPTILE] );
	       break;
	  case 'V' :
	  case 'v' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'W' :
	  case 'w' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_sign_count( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, sign_count[ARIES] );
	       break;
	  case '4' :
	       opnum( stream, 2, sign_count[TAURUS] );
	       break;
	  case '5' :
	       opnum( stream, 2, sign_count[GEMINI] );
	       break;
	  case '6' :
	       opnum( stream, 2, sign_count[CANCER] );
	       break;
	  case '7' :
	       opnum( stream, 2, sign_count[LEO] );
	       break;
	  case '8' :
	       opnum( stream, 2, sign_count[VIRGO] );
	       break;
	  case '9' :
	       opnum( stream, 2, sign_count[LIBRA] );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, sign_count[SCORPIO] );
	       break;
	  case 'B' :
	  case 'b' :
	       opnum( stream, 2, sign_count[SAGITARIUS] );
	       break;
	  case 'C' :
	  case 'c' :
	       opnum( stream, 2, sign_count[CAPRICORN] );
	       break;
	  case 'D' :
	  case 'd' :
	       opnum( stream, 2, sign_count[AQUARIUS] );
	       break;
	  case 'E' :
	  case 'e' :
	       opnum( stream, 2, sign_count[PISCES] );
	       break;
	  case 'F' :
	  case 'f' :
	       opnum( stream, 2, comp_sign_count[ARIES] );
	       break;
	  case 'G' :
	  case 'g' :
	       opnum( stream, 2, comp_sign_count[TAURUS] );
	       break;
	  case 'H' :
	  case 'h' :
	       opnum( stream, 2, comp_sign_count[GEMINI] );
	       break;
	  case 'I' :
	  case 'i' :
	       opnum( stream, 2, comp_sign_count[CANCER] );
	       break;
	  case 'J' :
	  case 'j' :
	       opnum( stream, 2, comp_sign_count[LEO] );
	       break;
	  case 'K' :
	  case 'k' :
	       opnum( stream, 2, comp_sign_count[VIRGO] );
	       break;
	  case 'L' :
	  case 'l' :
	       opnum( stream, 2, comp_sign_count[LIBRA] );
	       break;
	  case 'M' :
	  case 'm' :
	       opnum( stream, 2, comp_sign_count[SCORPIO] );
	       break;
	  case 'N' :
	  case 'n' :
	       opnum( stream, 2, comp_sign_count[SAGITARIUS] );
	       break;
	  case 'O' :
	  case 'o' :
	       opnum( stream, 2, comp_sign_count[CAPRICORN] );
	       break;
	  case 'P' :
	  case 'p' :
	       opnum( stream, 2, comp_sign_count[AQUARIUS] );
	       break;
	  case 'Q' :
	  case 'q' :
	       opnum( stream, 2, comp_sign_count[PISCES] );
	       break;
	  case 'R' :
	  case 'r' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'S' :
	  case 's' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_house_count( FILE *stream, char *s1, char *s2, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       fputc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
		  fputc('\n', stream );
		   break;
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '_' :
	       fputc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opecaps( stream, s1, buf );
	       break;
	  case '2' :
	       opecaps( stream, s2, buf );
	       break;
	  case '3' :
	       opnum( stream, 2, house_count[1] );
	       break;
	  case '4' :
	       opnum( stream, 2, house_count[2] );
	       break;
	  case '5' :
	       opnum( stream, 2, house_count[3] );
	       break;
	  case '6' :
	       opnum( stream, 2, house_count[4] );
	       break;
	  case '7' :
	       opnum( stream, 2, house_count[5] );
	       break;
	  case '8' :
	       opnum( stream, 2, house_count[6] );
	       break;
	  case '9' :
	       opnum( stream, 2, house_count[7] );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, house_count[8] );
	       break;
	  case 'B' :
	  case 'b' :
	       opnum( stream, 2, house_count[9] );
	       break;
	  case 'C' :
	  case 'c' :
	       opnum( stream, 2, house_count[10] );
	       break;
	  case 'D' :
	  case 'd' :
	       opnum( stream, 2, house_count[11] );
	       break;
	  case 'E' :
	  case 'e' :
	       opnum( stream, 2, house_count[12] );
	       break;
	  case 'F' :
	  case 'f' :
	       opnum( stream, 2, comp_house_count[1] );
	       break;
	  case 'G' :
	  case 'g' :
	       opnum( stream, 2, comp_house_count[2] );
	       break;
	  case 'H' :
	  case 'h' :
	       opnum( stream, 2, comp_house_count[3] );
	       break;
	  case 'I' :
	  case 'i' :
	       opnum( stream, 2, comp_house_count[4] );
	       break;
	  case 'J' :
	  case 'j' :
	       opnum( stream, 2, comp_house_count[5] );
	       break;
	  case 'K' :
	  case 'k' :
	       opnum( stream, 2, comp_house_count[6] );
	       break;
	  case 'L' :
	  case 'l' :
	       opnum( stream, 2, comp_house_count[7] );
	       break;
	  case 'M' :
	  case 'm' :
	       opnum( stream, 2, comp_house_count[8] );
	       break;
	  case 'N' :
	  case 'n' :
	       opnum( stream, 2, comp_house_count[9] );
	       break;
	  case 'O' :
	  case 'o' :
	       opnum( stream, 2, comp_house_count[10] );
	       break;
	  case 'P' :
	  case 'p' :
	       opnum( stream, 2, comp_house_count[11] );
	       break;
	  case 'Q' :
	  case 'q' :
	       opnum( stream, 2, comp_house_count[12] );
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}
