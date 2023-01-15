#include "stdafx.h"
#include <io.h>
#include "astro.h"
#include "useri.h"
#include "flags.h"
#include "dataext.h"
#include "charcons.h"
#include "utlduad.h"
#include "oututil.h"
#include "outfunc.fns"
#include "output.fns"

extern void do_house_sign( DEGR minutes, int *minor, int *sign, int *cusp );
extern const char *nh_pla_str( int planet );
#ifdef DELUXE
int output_midpoint_sign( FILE *stream, NUM planet, MIDPT *ptr,
						     char *s1, char *rpt, int type )
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
	       opcaps( stream, planet_str( planet ), buf );
	       break;
	  case '2' :
	       opcaps( stream, planet_str( ptr->second_planet ), buf );
	       break;
	  case '3' :
	       opnum( stream, 2, ptr->minor_degrees );
	       break;
	  case '4' :
	       opnum0( stream, 0, ptr->minor_minutes );
	       break;
	  case '5' :
	       opcaps( stream, sign_str( ptr->sign ), buf );
	       break;
	  case '6' :
	  case '7' :
	  case '8' :
	       p = out_bool_query( stream, ptr->cusp!=-1, p );
	       cap = 0;
	       break;
	  case '9' :
	       if ( ptr->cusp != -1 )
		  opcaps( stream, sign_str( ptr->cusp ), buf );
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       fputs( format_degs( ptr->total_minutes, buf ), stream );
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	       opecaps( stream, s1, buf );
	       break;
	  case 'C' :
	  case 'c' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'D' :
	  	  case 'd' :
	  	       switch( type ) {

	  #ifdef PRO
	  		     case ARABP_DI :
	  			  opcaps( stream, arabic_part_str( planet ), buf );
	  			  break;
	  		     case FIXED_DI :
	  			  opcaps( stream, fixed_star_str( planet ), buf );
	  			  break;
	  		     case HELIO_DI :
	  			  opcaps( stream, nh_pla_str( planet ), buf );
	  			  break;
	  #endif
	  		     default :
	  			  cap = 0;
	  			  break;
		     }
		  case 'E' :
		  case 'e' :
		  	switch( type ) {

		  	  #ifdef PRO
		  	  	  case ARABP_DI :
		  	  	    opcaps( stream, arabic_part_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case FIXED_DI :
		  	  	    opcaps( stream, fixed_star_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case HELIO_DI :
		  	  	    opcaps( stream, nh_pla_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  #endif
		  	  	  default :
		  	  		 cap = 0;
		  	  	     break;
		  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_midpoint_house( FILE *stream, NUM planet, MIDPT *ptr,
						    char *s1, char *rpt, int type )
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
	       opcaps( stream, planet_str( planet ), buf );
	       break;
	  case '2' :
	       opcaps( stream, planet_str( ptr->second_planet ), buf );
	       break;
	  case '3' :
	       opnum( stream, 2, ptr->house );
	       break;
	  case '4' :
	       opcaps( stream, number_str( ptr->house ), buf );
	       break;
	  case '5' :
	  case '6' :
	       p = out_bool_query( stream, ptr->house_cusp, p );
	       break;
	  case '7' :
	  case '8' :
	       p = out_bool_query( stream, ptr->intercepted, p );
	       break;
	  case '9' :
	       opecaps( stream, s1, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	  	       switch( type ) {

	  #ifdef PRO
	  		     case ARABP_DI :
	  			  opcaps( stream, arabic_part_str( planet ), buf );
	  			  break;
	  		     case FIXED_DI :
	  			  opcaps( stream, fixed_star_str( planet ), buf );
	  			  break;
	  		     case HELIO_DI :
	  			  opcaps( stream, nh_pla_str( planet ), buf );
	  			  break;
	  #endif
	  		     default :
	  			  cap = 0;
	  			  break;
		     }
		case 'C' :
		case 'c' :
		  	switch( type ) {

		  	  #ifdef PRO
		  	  	  case ARABP_DI :
		  	  	    opcaps( stream, arabic_part_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case FIXED_DI :
		  	  	    opcaps( stream, fixed_star_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  	  case HELIO_DI :
		  	  	    opcaps( stream, nh_pla_str( ptr->second_planet ), buf );
		  	  	    break;
		  	  #endif
		  	  	  default :
		  	  		 cap = 0;
		  	  	     break;
		  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}
#endif

int output_planet_house( FILE *stream, NUM planet, AS_INF *ptr,
					    char *s1, char *s2, char *rpt, int type )
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
	       opcaps( stream, planet_str( planet ), buf );
	       break;
	  case '2' :
	       opnum( stream, 2, ptr->house );
	       break;
	  case '3' :
	       opcaps( stream, number_str( ptr->house ), buf );
	       break;
	  case '4' :
	  case '5' :
	       p = out_bool_query( stream, ptr->house_cusp, p );
	       break;
	  case '6' :
	  case '7' :
	       p = out_bool_query( stream, ptr->intercepted, p );
	       break;
	  case '8' :
	       opecaps( stream, s1, buf );
	       break;
	  case '9' :
	       opecaps( stream, s2, buf );
	       break;
	  case 'A' :
	  case 'a' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	  	  switch( type ) {

	  	  #ifdef PRO
	  	  		     case ARABP_DI :
	  	  			  opcaps( stream, arabic_part_str( planet ), buf );
	  	  			  break;
	  	  		     case FIXED_DI :
	  	  			  opcaps( stream, fixed_star_str( planet ), buf );
	  	  			  break;
	  	  		     case HELIO_DI :
	  	  			  opcaps( stream, nh_pla_str( planet ), buf );
	  	  			  break;
	  	  #endif
	  	  		     default :
	  	  			  cap = 0;
	  	  			  break;
	  		     }
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

int output_planet_sign( FILE *stream, NUM planet, AS_INF *ptr,
	    int type, void *data, BITS mode, char *s1, char *s2, char *rpt )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int cap = 0;
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
		   fputc('\n',stream);
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
	       opcaps( stream, planet_str( planet ), buf );
	       break;
	  case '2' :
	       opnum( stream, 2, ptr->degree_minor );
	       break;
	  case '3' :
	       opnum0( stream, 0, ptr->minutes_minor );
	       break;
	  case '4' :
	       opcaps( stream, sign_str( ptr->sign ), buf );
	       break;
	  case '5' :
	  case '6' :
	  case '7' :
	       p = out_bool_query( stream, ptr->cusp!=-1, p );
	       break;
	  case '8' :
	       if ( ptr->cusp != -1 )
		  opcaps( stream, sign_str( ptr->cusp ), buf );
	       break;
	  case '9' :
	       fputs( format_degs( ptr->minutes_total, buf ), stream );
	       break;
	  case 'A' :
	  case 'a' :
	       opcaps( stream, motion_str( ptr->retrograde ), buf );
	       break;
	  case 'B' :
	  case 'b' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       ar[ptr->retrograde] = 1;
	       ar2[ptr->retrograde] = 1;
	       p = out_mint_query( stream, ar, ar2, 3, p );
	       break;
	  case 'C' :
	  case 'c' :
	  case 'D' :
	  case 'd' :
	       p = out_bool_query( stream, mode & MISCELL, p );
	       break;
	  case 'E' :
	  case 'e' :
	       if ( mode & MISCELL )
		  opcaps( stream, number_str( ptr->misc_code & 3 ), buf );
	       break;
	  case 'F' :
	  case 'f' :
	  case 'G' :
	  case 'g' :
	       p = out_bool_query( stream, mode & MISCELL &&
					     ptr->misc_code & CRITICAL, p );
	       break;
	  case 'H' :
	  case 'h' :
	  case 'I' :
	  case 'i' :
	       p = out_bool_query( stream, mode & MISCELL &&
					     ptr->misc_code & ANARET_DEG, p );
	       break;
	  case 'J' :
	  case 'j' :
	       opecaps( stream, s1, buf );
	       break;
	  case 'K' :
	  case 'k' :
	       switch( type ) {
		     case MONTH_DI :
			  opcaps( stream, month_str( (int)data ), buf );
			  break;
		     case DATES_DP :
			  fputs(make_date((struct DATES *)data), stream );
			  cap = 0;
			  break;
#ifdef PRO
		     case ARABP_DI :
			  opcaps( stream, arabic_part_str( (int)data ), buf );
			  break;
		     case FIXED_DI :
			  opcaps( stream, fixed_star_str( (int)data ), buf );
			  break;
		     case HELIO_DI :
			  opcaps( stream, nh_pla_str( (int)data ), buf );
			  break;
#endif
		     default :
			  cap = 0;
			  break;
		     }
	       break;
	  case 'L' :
	  case 'l' :
	       if ( type == DATES_DP ) {
		  opnum( stream, 2, ((struct DATES *)data)->month );
		  }
	       else
		  cap = 0;
	       break;
	  case 'M' :
	  case 'm' :
	       if ( type == DATES_DP ) {
		  opnum0( stream, 2, ((struct DATES *)data)->day );
		  }
	       else
		  cap = 0;
	       break;
	  case 'N' :
	  case 'n' :
	       if ( type == DATES_DP ) {
		  opnum0( stream, 4, ((struct DATES *)data)->year );
		  }
	       else
		  cap = 0;
	       break;
	  case 'O' :
	  case 'o' :
	       if ( type == DATES_DP ) {
		  opcaps( stream,
			 month_str( ((struct DATES *)data)->month ), buf );
		  }
	       else
		  cap = 0;
	       break;
	  case 'P' :
	  case 'p' :
	       opecaps( stream, s2, buf );
	       break;
          case 'Q' :
	  case 'q' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'R' :
	  case 'r' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
/*

	  case 'S' :
	  case 's' :
	       p = out_bool_query( stream, mode & MISCELL &&
			   ptr->misc_code & VOID_CRSE, p );
	       cap = 0;
	       break;

*/
	  case 'T' :
	  case 't' :
		  opnum0( stream, 2, planet );
		  break;
	  case 'U' :
	  case 'u' :
		  opnum0( stream, 2, ptr->sign );
		  break;
	  case 'V' :
	  case 'v' :
		  opnum( stream, 2, (short)ptr->longitude );
		  break;
	  case 'W' :
	  case 'w' :
		  opnum0( stream, 3, ptr->dec_degrees );
		  break;
	  case 'X' :
	  case 'x' :
		  opnum( stream, 3, ptr->dec_degrees );
		  break;
	  case 'Y' :
	  case 'y' :
		  opnum( stream, 2, ptr->dec_minutes_minor );
		  break;
	  case 'Z' :
	  case 'z' :
		  opnum0( stream, 2, ptr->dec_minutes_minor );
		  break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}



int output_planet_sign_ext( FILE *stream, NUM planet, AS_INF_EXT *aie,
						     char *s1,  char *rpt, int type )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int cap = 0;
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
	       opnum( stream, 1, aie->decan );
	       break;
	  case '2' :
	       opcaps( stream, number_str( aie->decan ), buf );
	       break;
	  case '3' :
	       opcaps( stream, planet_str( aie->decan_ruler ), buf );
	       break;
	  case '4' :
	  case '5' :
	       p = out_bool_query( stream, aie->decan_ruler2 != -1, p );
	       break;
	  case '6' :
	       if ( aie->decan_ruler2 != -1 )
		  opcaps( stream, planet_str( aie->decan_ruler2 ), buf );
	       break;
	  case '7' :
	       opnum( stream, 2, aie->navasma );
	       break;
	  case '8' :
	       opcaps( stream, number_str( aie->navasma ), buf );
	       break;
	  case '9' :
	       opcaps( stream, sign_str( aie->navasma_sign ), buf );
	       break;
	  case 'A' :
	  case 'a' :
	       opnum( stream, 2, aie->duad );
	       break;
	  case 'B' :
	  case 'b' :
	       opcaps( stream, number_str( aie->duad ), buf );
	       break;
	  case 'C' :
	  case 'c' :
	       opcaps( stream, planet_str( aie->duad_ruler ), buf );
	       break;
	  case 'D' :
	  case 'd' :
	  case 'E' :
	  case 'e' :
	       p = out_bool_query( stream, aie->duad_ruler2 != -1, p );
	       break;
	  case 'F' :
	  case 'f' :
	       if ( aie->duad_ruler2 != -1 )
		  opcaps( stream, planet_str( aie->duad_ruler2 ), buf );
	       break;
	  case 'G' :
	  case 'g' :
	  case 'H' :
	  case 'h' :
	       p = out_bool_query( stream, aie->flags & IS_COMBUST, p );
	       break;
	  case 'I' :
	  case 'i' :
	  case 'J' :
	  case 'j' :
	       p = out_bool_query( stream, aie->flags & IS_HOME, p );
	       break;
	  case 'K' :
	  case 'k' :
	  case 'L' :
	  case 'l' :
	       p = out_bool_query( stream, aie->flags & IS_DETRIMENT, p );
	       break;
	  case 'M' :
	  case 'm' :
	  case 'N' :
	  case 'n' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if ( aie->flags & IS_EXACT && aie->flags & IS_EXALTED ) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( aie->flags & IS_EXALTED ) {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       else {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       p = out_mint_query( stream, ar, ar2, 3, p );
	       break;
	  case 'O' :
	  case 'o' :
	  case 'P' :
	  case 'p' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if ( aie->flags & IS_EXACT && aie->flags & IS_FALL ) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( aie->flags & IS_FALL ) {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       else {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       p = out_mint_query( stream, ar, ar2, 3, p );
	       break;
	  case 'Q' :
	  case 'q' :
	  case 'R' :
	  case 'r' :
	       p = out_bool_query( stream, aie->flags & IS_RULER, p );
	       break;
	  case 'S' :
	  case 's' :
	       if ( aie->flags & IS_RULER )
		  opcaps( stream, planet_str( planet ), buf );
	       break;
	  case 'T' :
	  case 't' :
	       opecaps( stream, s1, buf );
	       break;
	  case 'U' :
	  case 'u' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'V' :
	  case 'v' :
	  	   switch( type ) {

	  	  #ifdef PRO
	  	  		     case ARABP_DI :
	  	  			  opcaps( stream, arabic_part_str( planet ), buf );
	  	  			  break;
	  	  		     case FIXED_DI :
	  	  			  opcaps( stream, fixed_star_str( planet ), buf );
	  	  			  break;
	  	  		     case HELIO_DI :
	  	  			  opcaps( stream, nh_pla_str( planet ), buf );
	  	  			  break;
	  	  #endif
	  	  		     default :
	  	  			  cap = 0;
	  	  			  break;
	  		     }

	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}



int output_house_sign( FILE *stream, NUM house, DEGR minutes, int *pcusp, int *psign, char *s1, char *rpt )
{
 int cap = 0, sign, cusp, minor;
 char buf[80];
 char *p = rpt;

 do_house_sign( minutes, &minor, &sign, &cusp );
 *pcusp = cusp;
 *psign = sign;
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
	       opnum( stream, 2, house );
	       break;
	  case '2' :
	       opnum( stream, 2, minor );
	       break;
	  case '3' :
	       opcaps( stream, sign_str( sign ), buf );
	       break;
	  case '4' :
	  case '5' :
	  case '6' :
	       p = out_bool_query( stream, cusp!=-1, p );
	       break;
	  case '7' :
	       if ( cusp != -1 )
		 opcaps( stream, sign_str( cusp ), buf );
	       break;
	  case '8' :
	       opcaps( stream, number_str( house ), buf );
	       break;
	  case '9' :
	       opecaps( stream, s1, buf );
	       break;
	  case 'A' :
	  case 'a' :
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

int output_trans_id( FILE *stream, int transit, DATES *d,
				       char *s1, char *s2, char *rpt )
{
 int cap = 0, ar[3], ar2[3];
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
	       opnum( stream, 2, transit );
	       break;
	  case '2' :
	       opcaps( stream, make_date( d ), buf );
	       break;
	  case '3' :
	       opnum( stream, 2, d->month );
	       break;
	  case '4' :
	       opnum0( stream, 2, d->day );
	       break;
	  case '5' :
	       opnum0( stream, 4, d->year );
	       break;
	  case '6' :
	       opcaps( stream, month_str( d->month ), buf );
	       break;
	  case '7' :
	       opecaps( stream, s1, buf );
	       break;
	  case '8' :
	       opecaps( stream, s2, buf );
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
