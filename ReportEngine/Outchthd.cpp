#include "stdafx.h"
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "flags.h"
#include "charcons.h"
#include "output.fns"
#include "oututil.h"
#include "outfunc.fns"

extern char *angles[];


int output_birth_header( FILE *stream, BITS mode, BIRTH_DB *data,
		 char *s1, int house_mode, DATA_PACKET *dpk, char *rpt  )
{
 int cap = 0;
 char buf1[60];
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
	       opecaps( stream, s1, buf1 );
	       break;
	  case '2' :
	       fputs( make_date( &data->birth_data.birth_date ), stream );
	       cap = 0;
	       break;
	  case '3' :
	       fputs( make_time( &data->birth_data.birth_time, data->am_pm ), stream );
	       cap = 0;
	       break;
	  case '4' :
	       opecaps( stream, data->country, buf1 );
	       break;
	  case '5' :
	       opecaps( stream, data->state, buf1 );
	       break;
	  case '6' :
	       opecaps( stream, data->location, buf1 );
	       break;
	  case '7' :
	       opnum( stream, 2, data->birth_data.latitude.degrees );
	       break;
	  case '8' :
	       cap = 1;
	       opnum0( stream, 2,data->birth_data.latitude.minutes );
	       break;
	  case '9' :
	       fputc( data->birth_data.latitude.dir, stream );
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       p = out_bool_query( stream,
		       data->birth_data.latitude.dir=='N', p );
	       cap = 0;
	       break;
	  case 'B' :
	  case 'b' :
	       opnum( stream, 2, data->birth_data.longitude.degrees );
	       break;
	  case 'C' :
	  case 'c' :
	       cap = 1;
	       opnum0( stream, 2, data->birth_data.longitude.minutes );
	       break;
	  case 'D' :
	  case 'd' :
	       fputc( data->birth_data.longitude.dir, stream );
	       cap = 0;
	       break;
	  case 'E' :
	  case 'e' :
	       p = out_bool_query( stream,
			  data->birth_data.longitude.dir=='W', p );
	       cap = 0;
	       break;
	  case 'F' :
	  case 'f' :
	       {
	       //ResStrBlock tz(SB_TZONE);
	       opcaps( stream, timezones[data->time_zone]/*tz[data->time_zone]*/, buf1 );
	       }
	       break;
	  case 'G' :
	  case 'g' :
	       {
	       //ResStrBlock sc(SB_SPECC);
	       opcaps( stream, speccodes[data->special_code]/*sc[data->special_code]*/, buf1 );
	       }
	       break;
	  case 'H' :
	  case 'h' :
	       opnum( stream, 2, data->birth_data.local_adjust);
	       break;
	  case 'I' :
	  case 'i' :
	       opnum( stream, 2, data->birth_data.local_minutes);
	       break;
	  case 'J' :
	  case 'j' :
	       opnum0( stream, 2, data->birth_data.local_adjust);
	       break;
	  case 'K' :
	  case 'k' :
	       cap = 1;
	       opnum0( stream, 2, data->birth_data.local_minutes);
	       break;
	  case 'L' :
	  case 'l' :
	       fprintf( stream, "%02d:%02d:%02d",
		   data->birth_data.sidereal.hours,
		   data->birth_data.sidereal.minutes,
		   data->birth_data.sidereal.seconds );
	       cap = 0;
	       break;
	  case 'M' :
	  case 'm' :
	       opnum0( stream, 2, data->birth_data.sidereal.hours );
	       break;
	  case 'N' :
	  case 'n' :
	       cap = 1;
	       opnum0( stream, 2, data->birth_data.sidereal.minutes );
	       cap = 0;
	       break;
	  case 'O' :
	  case 'o' :
	       cap = 1;
	       opnum0( stream, 2, data->birth_data.sidereal.seconds );
	       cap = 0;
	       break;
	  case 'P' :
	  case 'p' :
	       opcaps( stream, month_str(data->birth_data.birth_date.month), buf1 );
	       break;
	  case 'Q' :
	  case 'q' :
	       opnum0( stream, 2, data->birth_data.birth_date.month);
	       break;
	  case 'R' :
	  case 'r' :
	       cap = 1;
	       opnum0( stream, 2, data->birth_data.birth_date.day);
	       break;
	  case 'S' :
	  case 's' :
	       cap = 1;
	       opnum0( stream, 4, data->birth_data.birth_date.year);
	       break;
	  case 'T' :
	  case 't' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'U' :
	  case 'u' :
		    opnum( stream, 2, *dpk->harmonic);
			break;
      case 'V' :
      case 'v' :
		   opnum( stream, 2, *dpk->dial);
           break;
   	  default :
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}


int output_rect_header( FILE *stream, RECT_DATA *rd, char *s1, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 if ( rd->birth_time_known )
    return( 0 );
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
	       {
	       //ResStrBlock rs(SB_RECTM);
	       opcaps( stream, rectstr[rd->rect_system]/*rs[rd->rect_system]*/, buf );
	       }
	       break;
	  case '3' :
	       opcaps( stream, make_time( &rd->trial, rd->am_pm ), buf );
	       break;
	  case '5' :
	       if ( rd->rect_system == KNOWN_ANGL ) {
		      //ResStrBlock ang(SB_ANGLE);
		      opcaps( stream, angles[rd->angle]/*ang[rd->angle]*/, buf );
		      }
	       else
		   cap = 0;
	       break;
	  case '7' :
	       if ( rd->rect_system == KNOWN_ANGL ) {
		  fputs( format_degs( rd->total_minutes, buf ), stream );
		  }
	       else
		  cap = 0;
	       break;
	  case '4' :
	  case '6' :
	  case '8' :
	       p = out_bool_query( stream, rd->rect_system == KNOWN_ANGL, p );
	       cap = 0;
	       break;
	  case '9' :
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

int output_ts_house_mode( FILE *stream, char *s1, int mode, int house_mode, char *rpt )
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
	       opecaps(stream, s1, buf);
	       break;
	  case '2' :
	       p = out_bool_query( stream, ( mode & SIDEREAL ), p );
	       cap = 0;
	       break;
	  case '3' :
	       {
	       //ResStrBlock hm(SB_HOUSE);
	       opcaps(stream, housmod[house_mode]/*hm[house_mode]*/, buf );
	       }
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
#ifdef DELUXE
int output_reloc_header( FILE *stream, char *s1, DATA_PACKET *dpk, char *rpt )
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
	       opecaps(stream,s1,buf);
	       break;
	  case '2' :
	       opecaps(stream,dpk->relocp->country, buf);
	       break;
	  case '3' :
	       opecaps(stream,dpk->relocp->state, buf);
	       break;
	  case '4' :
	       opecaps(stream,dpk->relocp->location,buf);
	       break;
	  case '5' :
	       opnum( stream, 2, dpk->relocp->latitude.degrees );
	       break;
	  case '6' :
	       cap = 1;
	       opnum( stream, 2, dpk->relocp->latitude.minutes );
	       break;
	  case '7' :
	       fputc( dpk->relocp->latitude.dir, stream );
	       cap = 0;
	       break;
	  case '8' :
	       p = out_bool_query( stream, dpk->relocp->latitude.dir=='N', p );
	       cap = 0;
	       break;
	  case '9' :
	       opnum( stream, 2, dpk->relocp->longitude.degrees );
	       break;
	  case 'A' :
	  case 'a' :
	       cap = 1;
	       opnum( stream, 2, dpk->relocp->longitude.minutes );
	       break;
	  case 'B' :
	  case 'b' :
	       fputc( dpk->relocp->longitude.dir, stream );
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       p = out_bool_query( stream, dpk->relocp->longitude.dir=='W', p );
	       cap = 0;
	       break;
	  case 'D' :
	  case 'd' :
	       {
	       //ResStrBlock tz(SB_TZONE);
	       opcaps( stream, timezones[dpk->relocp->time_zone]/*tz[dpk->relocp->time_zone]*/, buf );
	       }
	       break;
	  case 'E' :
	  case 'e' :
	       {
	      // ResStrBlock sc(SB_SPECC);
	       opcaps( stream, speccodes[dpk->relocp->special_code]/*sc[dpk->relocp->special_code]*/, buf );
	       }
	       break;
	       case 'F' :
	  case 'f' :
	       opnum( stream, 2, dpk->relocp->hrs_offset);
	       break;
	  case 'G' :
	  case 'g' :
	       opnum( stream, 2, dpk->relocp->min_offset);
	       break;
	  case 'H' :
	  case 'h' :
	       cap = 1;
	       opnum( stream, 2, dpk->relocp->hrs_offset);
	       break;
	  case 'I' :
	  case 'i' :
	       cap = 1;
	       opnum( stream, 2, dpk->relocp->min_offset);
	       break;
	  case 'J' :
	  case 'j' :
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



int output_prog_header( FILE *stream, char *s1, DATA_PACKET *dpk, char *rpt )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int psys;
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
	       opecaps(stream,s1,buf);
	       break;
	  case '2' :
	       opnum(stream, 2, dpk->pdp->offset.year );
	       break;
	  case '3' :
	       opnum( stream, 2, dpk->pdp->offset.month );
	       break;
	  case '4' :
	       opnum( stream, 2, dpk->pdp->offset.day );
	       break;
	  case '5' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       psys = dpk->pdp->progress_system;
	       if ( psys >= 100 )
		  psys -= 100;
	       ar[psys] = 1;
	       ar2[psys] = 1;
	       p = out_mint_query( stream, ar, ar2, 3, p );
	       cap = 0;
	       break;
	  case '6' :
	       opnum0(stream, 2, dpk->pdp->offset.year );
	       break;
	  case '7' :
	       opnum0( stream, 2, dpk->pdp->offset.month );
	       break;
	  case '8' :
	       opnum0( stream, 2, dpk->pdp->offset.day );
	       break;
	  case '9' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       p = out_bool_query( stream, dpk->pdp->progress_system>=100, p );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

int output_solar_header( FILE *stream, char *s1, DATA_PACKET *dpk, char *rpt )
{
 short ar[3], ar2[3];
 char buf[80];
 char *p = rpt;
 int psys;
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
	       opecaps(stream,s1,buf);
	       break;
	  case '2' :
	       opnum(stream, 2, dpk->ddp->direction.year );
	       break;
	  case '3' :
	       opnum( stream, 2, dpk->ddp->direction.month );
	       break;
	  case '4' :
	       opnum( stream, 2, dpk->ddp->direction.day );
	       break;
	  case '5' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       psys = dpk->ddp->direct_system;
	       if ( psys >= 100 )
		      psys -= 100;
	       ar[psys] = 1;
	       ar2[psys] = 1;
	       p = out_mint_query( stream, ar, ar2, 3, p );
	       cap = 0;
	       break;
	  case '6' :
	       opnum0(stream, 4, dpk->ddp->direction.year );
	       break;
	  case '7' :
	       opnum0( stream, 2, dpk->ddp->direction.month );
	       break;
	  case '8' :
	       opnum0( stream, 2, dpk->ddp->direction.day );
	       break;
	  case '9' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	       p = out_bool_query( stream, dpk->ddp->direct_system>=100, p );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}

#endif
int output_trans_header( FILE *stream, char *s1, DATA_PACKET *dpk, char *rpt )
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
	       opnum( stream, 2, dpk->tdp->num_transits );
	       break;
	  case '2' :
	       opcaps( stream, planet_str( dpk->tdp->start_planet ), buf );
	       break;
	  case '3' :
	       opcaps( stream, planet_str( dpk->tdp->end_planet ), buf );
	       break;
	  case '4' :
	       opnum( stream, 2, dpk->tdp->interval_date.month );
	       break;
	  case '5' :
	       opnum( stream, 2, dpk->tdp->interval_date.day );
	       break;
	  case '6' :
	       opecaps( stream, s1, buf );
	       break;
	  case '7' :
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
