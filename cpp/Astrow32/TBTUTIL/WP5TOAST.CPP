#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tbtutil.h>
#include "wp5.h"

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static WPheader header;

static int foreign( FILE *in, FILE *out, int ch );
static int null( FILE *in, FILE *out, int ch );
static int output( FILE *in, FILE *out, int ch );
static int attrib_on( FILE *in, FILE *out, int ch );
static int attrib_off( FILE *in, FILE *out, int ch );
static int stripch( FILE *in, FILE *out, int ch );
static int stripch_ctr( FILE *in, FILE *out, int ch );
static int strip_var_len_output( FILE *in, FILE *out, int ch );
static int strip_var_len( FILE *in, FILE *out, int ch );
static int end_ctr( FILE *in, FILE *out, int ch );
extern void wp5_code_page_update( unsigned short *wpcs );

#define c(s,c) ((s*256)+(c))

static int head;

#define NCHR (sizeof(high_chars)/sizeof(int))

static unsigned short high_chars[] = {
  c(1,28), c(1,61), c(1,41), c(1,29), c(1,31), c(1,33), c(1,35),
  c(1,29), c(1,43), c(1,44), c(1,47), c(1,53), c(1,53), c(1,55),
  c(1,30), c(1,34), c(1,40), c(1,37), c(1,36), c(1,61), c(1,63),
  c(1,64), c(1,68), c(1,72), c(1,74), c(1,63), c(1,70), c(4,19),
  c(4,10), c(4,11), c(1,12), c(1,13), c(1,27), c(1,49), c(1,59),
  c(1,67), c(1,57), c(1,56), 0,       0,       c(4,8),  c(3,10),
  c(3,11), c(4,17), c(4,18), c(4,7),  c(4,9),  c(4,10), c(3,0),
  c(3,1),  c(3,2),  0,       c(3,9),  c(3,16), c(3,40), c(3,44),
  c(3,35), c(3,11), c(3,13), c(3,17), c(3,15), c(3,14), c(3,8),
  c(3,18), c(3,38), c(3,42), c(3,24), c(3,21), c(3,28), c(3,26),
  c(3,25), c(3,19), c(3,29), c(3,45), c(3,41), c(3,43), c(3,39),
  c(3,37), c(3,33), c(3,30), c(3,34), c(3,46), c(3,47), c(3,12),
  c(3,10), c(3,3),  c(3,7),  c(3,4),  c(3,6),  c(3,5) };


typedef int exp_func( FILE *in, FILE *out, int ch );

typedef struct EXP_DATA {
	int len;
	exp_func *func;
	char *output;
	} EXP_DATA;

#define svl strip_var_len

static EXP_DATA ext_asc[128] = { /* start with single byte functions */
/*80*/ 1, null, "", 1, null, "", 1, null, "", 1, end_ctr, "]", 1, null, "",
/*85*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*8a*/ 1, null, "", 1, null, "", 1, output, "\n", 1, null, "", 1, null, "",
/*8f*/ 1, null, "", 1, null, "", 1, null, "", 1, output, " ", 1, null, "",
/*94*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, output, "\n",
/*99*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*9e*/ 1, output, " ", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*a3*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*a8*/ 1, output, "-", 1, output, "-", 1, output, "-", 1, null, "", 1, null, "",
/*ad*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*b2*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*b7*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*bd*/ 1, null, "", 1, null, "", 1, null, "", 3, foreign, "", 9, stripch_ctr, "[",
/*c2*/ 11, stripch, "", 3, attrib_on, "", 3, attrib_off, "", 5, stripch, "", 6, stripch, "",
/*c7*/ 7, stripch, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*cc*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, svl, "",
/*d1*/ 1, svl, "", 1, svl, "", 1, svl, "", 1, svl, "", 1, svl, "",
/*d6*/ 1, svl, "", 1, svl, "", 1, svl, "", 1, svl, "", 1, svl, "",
/*db*/ 1, svl, "", 1, svl, "", 1, svl, "", 4, svl, "", 1, svl, "",
/*e0*/ 1, svl, "", 1, svl, "", 1, svl, "", 1, null, "", 1, null, "",
/*e5*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*ea*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*ef*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*f4*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*f9*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*fe*/ 1, svl, "", 1, null, "" };



static int foreign( FILE *in, FILE *out, int ch )
{
 unsigned fc;
 int i;

 fread( &fc, 2, 1, in );
 getc( in );
 for ( i = 0; i < NCHR; ++i )
     if ( fc == high_chars[i] ) {
	putc( '~', out );
	putc( i+128, out );
     }
 if ( ( fc = fgetc( in ) ) == ' ' ) {
    putc( '~', out );
    putc( ' ', out );
    }
 else
    ungetc( fc, in );
 return( 0 );
}



static int null( FILE *in, FILE *out, int ch )
{
 return( 0 );
}

static int end_ctr( FILE *in, FILE *out, int ch )
{
 if ( head ) {
    head = 0;
    return( fputc( ']', out ) );
    }
 return( 0 );
}



static int output( FILE *in, FILE *out, int ch )
{
 return( fputs( ext_asc[ch-0x80].output, out ) );
}

static int attrib_on( FILE *in, FILE *out, int ch )
{
 int at = getc( in ),
     xt = getc( in );

 switch( at ) {
       case 0 :
       case 1 :
       case 2 :
	    if ( !head ) {
	       head = 1;
	       return( fputc( '[', out ) );
	       }
	    break;
       case '\xc':
	    return( fputc( '{', out ) );
	    break;
       case 8 :
       case '\xe':
	    return( fputc( '<', out ) );
	    break;
       default :
	    return( 0 );
	    break;
       }
 }

static int attrib_off( FILE *in, FILE *out, int ch )
{
 int at = getc( in ),
     xt = getc( in );

 switch( at ) {
       case 0 :
       case 1 :
       case 2 :
	    if ( head ) {
	       head = 0;
	       return( fputc( ']', out ) );
	       }
	    break;
       case '\xc':
	    return( fputc( '}', out ) );
	    break;
       case 8 :
       case '\xe':
	    return( fputc( '>', out ) );
	    break;
       default :
	    return( 0 );
	    break;
       }
}


static int stripch( FILE *in, FILE *out, int ch )
{
 int i, len;

 len = ext_asc[ch-0x80].len;
 for ( i = 1; i < len; ++i )
     getc( in );
 return( 0 );
}

static int stripch_ctr( FILE *in, FILE *out, int ch )
{
 int i, len;
 char *output;


 len = ext_asc[ch].len;
 output = ext_asc[ch-0x80].output;
 for ( i = 1; i < len; ++i )
     getc( in );
 if ( !head ) {
    return( fputs( output, out ) );
    head = 1;
    }
 return( 0 );
}


static int strip_var_len_output( FILE *in, FILE *out, int ch )
{
 long offs;
 int i, len;
 char *output;

 output = ext_asc[ch-0x80].output;
 getc( in );
 fread( &len, 2, 1, in );
 for ( i = 0; i < len; ++i )
     getc( in );
 return( fputs( output, out ) );
}

static int strip_var_len( FILE *in, FILE *out, int ch )
{
 int i, len;

 getc( in );
 fread( &len, 2, 1, in );
 for ( i = 0; i < len; ++i )
     getc( in );
 return( 0 );
}

extern "C" {

int __far __pascal __export _WP5TOAST( int argc, char *argv[] )
{
 FILE *instream, *outstream;
 int c;

 if ( argc < 2 ) {
    alert_box( "WP5TOAST", "USAGE: WP5TOAST INFILE.EXT OUTFILE.EXT\n" );
    return( 1 );
    }
 if ( ( instream = fopen( argv[1], "rb" ) ) == NULL ) {
    alert_box( "WP5TOAST", "Can't Open %s For Reading!\n", argv[1] );
    return( 2 );
    }
 if ( ( outstream = fopen( argv[2], "wt" ) ) == NULL ) {
    alert_box( "WP5TOAST", "Can't Open %s For Writing!\n", argv[2] );
    fclose(instream);
    return( 3 );
    }
 wp5_code_page_update( high_chars );
 if ( setvbuf( instream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( instream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( instream, NULL, _IOFBF, 1024 ) )
	  setvbuf( instream, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( outstream, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( outstream, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( outstream, NULL, _IOFBF, 1024 ) )
	  setvbuf( outstream, NULL, _IOFBF, 256 );
       }
    }
 fread( &header, sizeof( WPheader ), 1, instream );
 if ( memcmp( header.id, WPID, 4 ) ) {
    alert_box( "WP5TOAST", "%s Is Not A WordPerfect 5.0+ File!\n", argv[1] );
    fclose(instream);
    fclose(outstream);
    return( 3 );
    }
 dllYield();
 fseek( instream, header.ptr, SEEK_SET );
 while ( ( c = getc( instream ) ) != EOF ) {
       if ( c && strchr( "{}<>~", c ) != NULL ) {
	  if ( putc( '~', outstream ) == EOF)
	     break;
	  if ( putc( c, outstream ) == EOF)
	     break;
	  }
       else if ( c >= 0x20 && c <= 0x7e ) {
	  if ( putc( c, outstream ) == EOF)
	     break;
	  }
       else if ( c < 0x20 ) {
	  switch( c ) {
		case 9 :
		     putc( '|', outstream );
		     break;
		case 0x0a :
		     putc( '\n', outstream );
		     dllYield();
		     break;
		case 0x0b :
		case 0x0c :
		     break;
		case 0x0d :
		     putc( ' ', outstream );
		     break;
		default :
		     break;
		}
	    }
       else
	  if ( ext_asc[c-0x80].func( instream, outstream, c ) == EOF )
	     break;
       }
 fclose(instream);
 fclose(outstream);
 return( 0 );
}

}