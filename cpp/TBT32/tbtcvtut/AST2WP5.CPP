#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#include <ctype.h>


// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

extern void setcrs( unsigned char scr, unsigned char hcr );
extern int text_wrap( char *string, int width );
static char *tbuf;
extern void wp5_code_page_update( unsigned short *wpcs );

#pragma pack( 1 )

struct WPheader {
       char id[4];
       long ptr;
       char product;
       char type;
       char maj_v;
       char min_v;
       int  key;
       int  res;
       } WPheader;

struct WPmargin {
       unsigned char fnc;
       unsigned char sub;
       unsigned len;
       unsigned ol;
       unsigned or;
       unsigned nl;
       unsigned nr;
       unsigned len2;
       unsigned char sub2;
       unsigned char fnc2;
       } WPmargin;


#pragma pack()

struct WPheader wph = {'\xff','W','P','C', 76L, 1, 10, 0, 0, 0, 0 };
unsigned char ext_data[60] = { 0xfb, 0xff, 5, 0, 0x32, 0, 0, 0,
	0, 0, 6, 0, 8, 0, 0, 0, 0x42, 0, 0, 0, 8, 0, 2, 0, 0, 0, 0x4a,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 8, 0, 0x7c, 0, 0x78, 0, 0, 0, 0, 0 };

struct WPmargin margin = { 0xd0, 1, 12, 0, 0, 0, 0, 12, 1, 0xd0 };


#define c(s,c) ((s*256)+(c))

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



static int wordperf_foreign( FILE *stream, unsigned char c )
{
 int i;

 if ( c < ' ' )
    return( c );
 if ( c >= NCHR + 128 )
    return( c );
 i =  high_chars[c-128];
 if ( i == 0 )
    return( c );
 if (!( i & 0xff00 )) {
    putc( i & 0xff, stream );
    return ( 0 );
    }
 if ( putc( '\xc0', stream ) == EOF ||
      putc( i & 0xff, stream ) == EOF ||
      putc( i/256, stream ) == EOF ||
      putc( '\xc0', stream ) == EOF )
    return( EOF );
 return( 0 );
}




static int write_word_perf_header(FILE *stream)
{
 int e;

 e = fwrite( &wph, sizeof( struct WPheader ), 1, stream );
 if ( e )
    e = fwrite( &ext_data, 60, 1, stream );
 if ( e )
    e = fwrite( &margin, sizeof( struct WPmargin ), 1, stream );
 return( e );
}


extern "C" {

int __declspec(dllexport) WINAPI _AST2WP5( int argc, char *argv[] )
{
 char buf[100], *p, *b;
 FILE *in, *out;
 int c;

 if ( argc < 2 ) {
    alert_box( "AST2WP5", "AST2WP5 INFILE OUTFILE\nConvert ASTRO Text Source file Format to WordPefect 5.x" );
    return( -1 );
    }
 if ( argc < 3 ) {
    strcpy( buf, argv[1] );
    p = strchr( buf, '.' );
    if ( p == NULL )
       strcat( buf, ".DOC" );
    else
       strcpy( p, ".DOC" );
    }
 else
    strcpy( buf, argv[2] );
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "AST2WP5", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wb" ) ) == NULL ) {
    alert_box( "AST2WP5", "Can't Open %s for Writing!", buf );
    return( -1 );
    }
 wp5_code_page_update( high_chars );
 if ( setvbuf( in, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( in, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( in, NULL, _IOFBF, 1024 ) )
	  setvbuf( in, NULL, _IOFBF, 256 );
       }
    }
 if ( setvbuf( out, NULL, _IOFBF, 4096 ) ) {
    if ( setvbuf( out, NULL, _IOFBF, 2048 ) ) {
       if ( setvbuf( out, NULL, _IOFBF, 1024 ) )
	  setvbuf( out, NULL, _IOFBF, 256 );
       }
    }
 tbuf = new char[10000];
 setcrs( '\r', '\n' );
 dllYield();
 write_word_perf_header( out );
 while ( ( p = fgets( tbuf, 9998, in ) ) != NULL ) {
       text_wrap( tbuf, 70 );
       doConvertText( tbuf, _SRC_T_, _OEM_T_ );
       dllYield();
       for ( b = p; *b; b++ ) {
	   switch( *b ) {
	      case '{' :
		   fwrite( "\xc3\x0c\xc3", 1, 3, out );
		   break;
	      case '}' :
		   fwrite( "\xc4\x0c\xc4", 1, 3, out );
		   break;
	      case '<' :
		   fwrite( "\xc3\x0e\xc3", 1, 3, out );
		   break;
	      case '>' :
		   fwrite( "\xc4\x0e\xc4", 1, 3, out );
		   break;
	      case '~' :
		   b++;
		   if ( isascii( *b ) )
		      putc( *b, out );
		   else
		      wordperf_foreign( out, *b );
		   break;
	      default :
		putc( *b, out );
		break;
	      }
	   }
       putc( '\n', out );
       }
 fclose( in );
 fclose( out );
 delete tbuf;
 return( 0 );
}

}



