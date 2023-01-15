#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "output.fns"
#include "oututil.h"
#include "outfunc.fns"
#include "assert.h"
#include "report_def.h"

extern const char *nh_pla_str( int planet );

int firstName( FILE *stream, int cap, char *name )
{
 char buf[75], buf2[75], *p;

 assert( strlen(name) < sizeof( buf ) );
 if ( cap )
    strcpy( buf2, xstrupr(enquote_strclip((unsigned char *)name,(unsigned char *)buf)) );
 else
    strcpy( buf2, enquote_strclip((unsigned char *)name,(unsigned char *)buf) );
 assert( strlen(name) < sizeof( buf2 ) );
 if ( !strnicmp( name, "Mr. ", 4 ) || !strnicmp( name, "Ms. ", 4 ) || !strnicmp( name, "Dr. ", 4 ) )
    p = &buf2[4];
 else if ( !strnicmp( name, "Mrs. ", 5 ) || !strnicmp( name, "Mme. ", 5 ) )
    p = &buf2[5];
 else if ( !strnicmp( name, "Sr. ", 4 ) )
    p = &buf2[4];
 else if ( !strnicmp( name, "Sra. ", 5 ) )
    p = &buf2[5];
 else if ( !strnicmp( name, "Srta. ", 6 ) )
    p = &buf2[6];
 else if ( !strnicmp( name+1, ". ", 2 ) )
    p = &buf2[3];
 else
    p = buf2;
 while ( *p && *p != ' ' )
       fputc( *p++, stream );
 return( ferror( stream ) );
}

char *out_bool_query( FILE *stream, int var, char *fmt )
{
 char *pt, dlm;

 pt = fmt;
 dlm = *pt;
 pt++;
 if ( var ) {
    while ( *pt && *pt != dlm )
	  fputc( *pt++, stream );
    pt++;
    while ( *pt && *pt++ != dlm );
    }
 else {
    while ( *pt && *pt != dlm )
		pt++;
	pt++;
	while ( *pt && *pt != dlm )
	    fputc( *pt++, stream );
    pt++;
    }
 return( pt );
}

char *out_mint_query( FILE *stream, short *vars, short *test, int cnt, char *fmt )
{
 char *pt, dlm;
 int i;

 pt = fmt;
 dlm = *pt;
 pt++;

 for ( i = 0; i < cnt; ++i ) {
     if ( vars[i] == test[i] ) {
	while ( *pt && *pt != dlm )
	      fputc( *pt++, stream );
	pt++;
	}
     else {
	while ( *pt && *pt != dlm )
		pt++;
	pt++;
	}
     }
 return( pt );
}


char *next_arg( FILE *stream, char *text )
{
 char *pt = text;

 while ( *pt && *pt != '$' )
       fputc( *pt++, stream );
 if ( *pt )
    pt++;
 return( pt );
}


int output_aspects2( FILE *stream, char *s1, char *s2, int pl, ASPEC *as, char *rpt, int type )
{
 short ar[3], ar2[3], flag = 0;
 char buf[80];
 char *p = rpt;
 int cap = 0;

 if ( pl < 0 ) {
    flag = 1;
    pl = abs( pl );
    if ( pl >= 100 )
       pl %= 100;
    }
 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       putc( '$', stream );
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
	       putc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '0' :
	       opcaps(stream,planet_str( pl ), buf);
	       break;
	  case '1' :
	       opcaps(stream,aspect_str( as->aspect ), buf);
	       break;
	  case '2' :
	       opcaps(stream,planet_str( as->planet ), buf);
	       break;
	  case '3' :
	       opnum(stream, 2, as->orb );
	       break;
          case '4' :
	       opecaps(stream,s1,buf);
	       break;
	  case '5' :
	       out_first_name(stream,cap,s1);
	       cap = 0;
	       break;
	  case '6' :
	       memset( ar, 0, 6 );
	       memset( ar2, 0xff, 6 );
	       if (as->orb < 1) {
		  ar[0] = 1;
		  ar2[0] = 1;
		  }
	       else if ( as->orb > 8 ) {
		  ar[2] = 1;
		  ar2[2] = 1;
		  }
	       else  {
		  ar[1] = 1;
		  ar2[1] = 1;
		  }
	       p = out_mint_query( stream, ar, ar2, 3, p );
	       cap = 0;
	       break;
	  case '7' :
	       p = out_bool_query( stream, flag, p );
	       cap = 0;
	       break;
          case '8' :
	  case 'b' : /* Compromise to fix a bug in table */
	       opecaps(stream,s2,buf);
	       break;
	  case '9' :
	       out_first_name(stream,cap,s2);
	       cap = 0;
	       break;
	  case 'A' :
	  case 'a' :
	  	   switch( type ) {
	  #ifdef PRO
	  		  case ARABP_DI :
	  			opcaps( stream, arabic_part_str( pl ), buf );
	  			break;
	  		  case FIXED_DI :
	  			opcaps( stream, fixed_star_str( pl ), buf );
	  			break;
	  		  case HELIO_DI :
	  			opcaps( stream, nh_pla_str( pl ), buf );
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

int output_aspects( FILE *stream, char *s1, int pl, ASPEC *as, char *rpt, int type )
{
 return( output_aspects2( stream, s1, "", pl, as, rpt, type ) );
}

int output_title( FILE *stream, char *s1, char *s2, char *s3, char *rpt )
{
 int cap = 0;
 char buf[80];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       putc( '$', stream );
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
	       putc( '\x80', stream );
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
	       opecaps(stream, s2, buf );
	       break;
	  case '3' :
	       opecaps(stream, s3, buf );
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

int out_print_cusps( FILE *stream, int i, short *house_cusps, char *rpt )
{
 int cap = 0;
 char b[12];
 char *p = rpt;

 do {
    p = next_arg( stream, p );
    switch( *p++ ) {
	  case '$' :
	       putc( '$', stream );
	       cap = 0;
	       break;
	  case '^' :
	       cap = 1;
	       break;
	  case '\n' :
	  case '\0' :
	       return( 1 );
	       break;
	  case '_' :
	       putc( '\x80', stream );
	       cap = 0;
	       if ( *p+1 == '\n' || *p+1 == '\r' )
		      p++;
		   if ( *p == '\n' )
			   p++;
	       break;
	  case '1' :
	       opnum0( stream, 2, i );
	       break;
	  case '2' :
	       fprintf( stream, "%-7.7s", format_degs(house_cusps[i], b) );
	       cap = 0;
	       break;
	  case '3' :
	       opnum0( stream, 2, i+1 );
	       break;
	  case '4' :
	       fprintf( stream, "%-7.7s", format_degs(house_cusps[i+1], b) );
	       cap = 0;
	       break;
	  default :
	       cap = 0;
	       break;
	  }
    } while ( *p );
 return( 1 );
}

int o_print_cusps(FILE *stream, short *house_cusps, char *rpt )
{
 int x;

 for ( x = 1; x <= 12; x += 2 )
     out_print_cusps( stream, x, house_cusps, rpt );
 return( ferror( stream ) );
}

int out_do_house_cusps(FILE *stream, char *s1, char *s2, char *s3,
			      int table, int global, short *hsc, int tkey )
{
 const char *report;

 if ( ( report = get_report( table, global, tkey ) ) == NULL )
    return(1);
 else
    output_title( stream, s1, s2, s3, (char *)report );
    if ( ( report = get_report( table, global, CH__HOUSE_CS ) ) == NULL ) {
       return( 1 );
       }
    else
       return( o_print_cusps(stream, hsc, (char *)report ) );
}
