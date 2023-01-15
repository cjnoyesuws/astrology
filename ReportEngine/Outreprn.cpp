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

int output_return_title( FILE *stream, int chart, char *s1, char *s2, char *rpt )
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
	       p = out_bool_query(stream, !chart, p );
	       break;
	  case '3' :
	       opecaps(stream, s2, buf );
	       break;
	  case '4' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case '5' :
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

#ifdef DELUXE
int output_return_head( FILE *stream, char *s1, BIRTH_DB *data,
    RETURN_DATA *retd, DATA_PACKET *dpk, int house_mode, char *rpt )
{
 short ar[4], ar2[4];
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
	  case '\n' :
	  case '\0' :
	       return( ferror( stream ) );
	       break;
	  case '2' :
	       fputs( make_date( &retd->start ), stream );
	       cap = 0;
	       break;
	  case '3' :
	       fputs( make_date( &retd->end ), stream );
	       cap = 0;
	       break;
	  case '5' :
	       if ( retd->is_prog )
		  opnum(stream, 2, retd->prog.offset.year );
	       break;
	  case '4' :
	  case '6' :
	  case '8' :
	  case 'A' :
	  case 'a' :
	  case 'F' :
	  case 'f' :
	       p = out_bool_query(stream, retd->is_prog, p );
	       cap = 0;
	       break;
	  case '7' :
	       if ( retd->is_prog )
		  opnum( stream, 2, retd->prog.offset.month );
	       break;
	  case '9' :
	       if ( retd->is_prog )
		  opnum( stream, 2, retd->prog.offset.day );
	       break;
	  case 'B' :
	  case 'b' :
	       memset( ar, 0, 8 );
	       memset( ar2, 0xff, 8 );
	       ar[retd->prog.progress_system] = 1;
	       ar2[retd->prog.progress_system] = 1;
	       if ( !retd->is_prog ) {
		  ar[3] = 1;
		  ar2[3] = 1;
		  ar[retd->prog.progress_system] = 0;
		  ar2[retd->prog.progress_system] = 0xff;
		  }
	       p = out_mint_query( stream, ar, ar2, 4, p );
	       cap = 0;
	       break;
	  case 'C' :
	  case 'c' :
	       if ( retd->is_prog ) {
		  opnum0(stream, 2, retd->prog.offset.year );
		  }
	       break;
	  case 'D' :
	  case 'd' :
	       if ( retd->is_prog ) {
		  opnum0( stream, 2, retd->prog.offset.month );
		  }
	       break;
	  case 'E' :
	  case 'e' :
	       if ( retd->is_prog ) {
		  opnum0( stream, 2, retd->prog.offset.day );
		  }
	       break;
	  case 'G' :
	  case 'g' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case 'H' :
	  case 'h' :
	       p = out_bool_query(stream, !retd->planet, p );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( ferror( stream ) );
}


int output_return_entry( FILE *stream, int chart, int reno, DATES *d, TIM *t, int ap, char *s1, char *rpt )
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
	       fputs( make_date( d ), stream );
	       cap = 0;
	       break;
	  case '3' :
	       fputs( make_time( t, ap ), stream );
	       cap = 0;
	       break;
	  case '4' :
	       p = out_bool_query(stream, chart, p );
	       break;
	  case '5' :
	       cap = 1;
	       opnum( stream, 2, reno );
	       break;
	  case '6' :
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
#endif
