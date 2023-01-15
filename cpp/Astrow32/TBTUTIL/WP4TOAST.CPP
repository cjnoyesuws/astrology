#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

typedef int exp_func( FILE *in, FILE *out, int ch );

typedef struct EXP_DATA {
	int len;
	exp_func *func;
	char *output;
	} EXP_DATA;

static foreign( FILE *in, FILE *out, int ch );
static int null( FILE *in, FILE *out, int ch );
static int output( FILE *in, FILE *out, int ch );
static int stripftr( FILE *in, FILE *out, int ch );
static int stripclc( FILE *in, FILE *out, int ch );
static int stripeop( FILE *in, FILE *out, int ch );
static int stripftn( FILE *in, FILE *out, int ch );
static int stripnftn( FILE *in, FILE *out, int ch );
static int strip( FILE *in, FILE *out, int ch );
static int stripctr( FILE *in, FILE *out, int ch );
static int strip_var_len( FILE *in, FILE *out, int ch );


static EXP_DATA ext_asc[129] = {
/*80*/ 1, null, "", 1, null, "", 1, null, "", 1, output, "]", 1, null, "",
/*85*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*8a*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*8f*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*94*/ 1, output, "<", 1, output, ">", 1, null, "", 1, null, "", 1, null, "",
/*99*/ 1, null, "", 1, null, "", 1, null, "", 1, output, "}", 1, output, "{",
/*9e*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*a3*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*a8*/ 1, null, "", 1, output, "-", 1, output, "-", 1, output, "-", 1, null, "",
/*ad*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*b2*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*b7*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*bc*/ 1, null, "", 1, null, "", 1, null, "", 1, null, "",
/*c0*/ 6, strip, "", 4, strip, "", 3, strip, "", 5, stripctr, "[", 5, stripctr, "",
/*c5*/ 6, strip, "", 4, strip, "", 6, strip, "", 8, strip, "", 42, strip, "",
/*ca*/ 3, strip, "", 6, strip, "", 4, strip, "", 3, strip, "", 4, strip, "",
/*cf*/ 3, strip, "", 6, strip, "", -1, strip_var_len, "", -1, stripftn, "",
/*d3*/ 4, strip, "", 4, strip, "", 4, strip, "", 6, strip, "", -1, stripclc, "",
/*d8*/ 4, strip, "", 4, strip, "", 4, strip, "", 6, strip, "", -1, strip_var_len, "",
/*dd*/ 24, strip, "", 4, strip, "", -1, strip_var_len, "", 4, strip, "",
/*e1*/ 3, foreign, "", -1, stripnftn, "", 150, strip, "", 6, strip, "",
/*e5*/ 23, strip, "", 11, strip, "", 3, strip, "", 3, strip, "", 8, strip, "",
/*e9*/ -1, strip_var_len, "", 32, strip, "", 4, strip, "", -1, strip_var_len, "",
/*ed*/ -1, strip_var_len, "", -1, strip_var_len, "", -1, strip_var_len, "",
/*f0*/ -1, strip_var_len, "", -1, strip_var_len, "", -1, strip_var_len, "",
/*f3*/ -1, strip_var_len, "", -1, strip_var_len,  "", -1, strip_var_len, "",
/*f6*/ -1, strip_var_len, "", -1, strip_var_len, "", -1, strip_var_len,  "",
/*f9*/ -1, strip_var_len, "", -1, strip_var_len, "", -1, strip_var_len, "",
/*fc*/ -1, strip_var_len, "", -1, strip_var_len, "", -1, strip_var_len, "",
/*ff*/ -1, strip_var_len, "" };



static int foreign( FILE *in, FILE *out, int ch )
{
 unsigned char c;

 putc( '~', out );
 putc( getc( in ), out );
 getc( in );
 c = getc( in );
 if ( c == ' ' ) {
    putc( '~', out );
    putc( ' ', out );
    }
 else
    ungetc( c , in );
 return( 0 );
}


static int null( FILE *in, FILE *out, int ch )
{
 return( 0 );
}

static int output( FILE *in, FILE *out, int ch )
{
 return( fputs( ext_asc[ch-0x80].output, out ) );
}

static int stripftr( FILE *in, FILE *out, int ch )
{
 int i, c;

 for ( i = 1; i < 7; ++i )
     c = getc( in );
 while ( ( c = getc( in ) ) != 0xff );
 for ( i = 0; i < 3; ++i )
     c = getc( in );
 return( 0 );
}

static int stripclc( FILE *in, FILE *out, int ch )
{
 int i, c;

 for ( i = 1; i < 25; ++i )
     c= fgetc( in );
 while ( ( c = getc( in ) ) != 0x0 );
 while ( ( c = getc( in ) ) != 0x0 );
 while ( ( c = getc( in ) ) != 0x0 );
 while ( ( c = getc( in ) ) != 0x0 );
 getc( in );
 for ( i = 1; i < 25; ++i )
     c = getc( in );
 while ( ( c = getc( in ) ) != 0x0 );
 while ( ( c = getc( in ) ) != 0x0 );
 while ( ( c = getc( in ) ) != 0x0 );
 while ( ( c = getc( in ) ) != 0x0 );
 getc( in );
 return( 0 );
}

static int stripeop( FILE *in, FILE *out, int ch )
{
 int i, c;

 for ( i = 1; i < 8; ++i )
     c = getc( in );
 while ( ( c = getc( in ) ) != 0xdc );
 return( 0 );
}

static int stripftn( FILE *in, FILE *out, int ch )
{
 int i, c;

 for ( i = 1; i < 6; ++i )
     c = getc( in );
 while ( ( c = getc( in ) ) != 0xd2 );
 for ( i = 0; i < 3; ++i )
     c = getc( in );
 return( 0 );
}


static int stripnftn( FILE *in, FILE *out, int ch )
{
 int i, c;

 for ( i = 1; i < 14; ++i )
     c = getc( in );
 while ( ( c = getc( in ) ) != 0xe2 );
 for ( i = 0; i < 3; ++i )
     c = getc( in );
 return( 0 );
}

static int strip( FILE *in, FILE *out, int ch )
{
 int i, len, c;

 len = ext_asc[ch-0x80].len;
 for ( i = 1; i < len; ++i )
     c = getc( in );
 return( 0 );
}


static int stripctr( FILE *in, FILE *out, int ch )
{
 int i, c;

 for ( i = 1; i < 5; ++i )
     c = getc( in );
 return( fputs( ext_asc[ch-0x80].output, out ) );
}



static int strip_var_len( FILE *in, FILE *out, int ch )
{
 int c;

 do {
    c = getc( in );
    } while ( c != ch );
 return( 0 );
}

extern "C" {

int __far __pascal __export _WP4TOAST( int argc, char *argv[] )
{
 FILE *instream, *outstream;
 int c;

 if ( argc < 2 ) {
    alert_box( "WP4TOAST","USAGE: WP4TOAST INFILE.EXT OUTFILE.EXT\n" );
    return( 1 );
    }
 if ( ( instream = fopen( argv[1], "rb" ) ) == NULL ) {
    alert_box( "WP4TOAST","Can't Open %s For Reading!\n", argv[1] );
    return( 2 );
    }
 if ( ( outstream = fopen( argv[2], "wt" ) ) == NULL ) {
    alert_box( "WP4TOAST","Can't Open %s For Writing!\n", argv[2] );
    fclose(instream);
    return( 3 );
    }
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
 dllYield();
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
		     dllYield();
		     putc( '\n', outstream );
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