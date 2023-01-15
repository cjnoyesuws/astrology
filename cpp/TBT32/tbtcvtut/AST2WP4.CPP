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

char *tbuf;

int wp4_foreign_char( FILE *stream, unsigned char the_char )
{
 if ( putc( '\xe1', stream ) == EOF )
    return( -1 );
 if ( putc( the_char, stream ) == EOF )
    return( -1 );
 if ( putc( '\xe1', stream ) == EOF )
    return( -1 );
 return( 0 );
}


void write_wp4_header( FILE *stream )
{
 char buf[42];
 int i;

 fwrite( "\xc0\0\0\0\x50\xc0", 1, 6, stream );
}


extern "C" {

int __declspec(dllexport) WINAPI _AST2WP4( int argc, char *argv[] )
{
 long l;
 char buf[100], *p, *b;
 FILE *in, *out;
 int c;

 if ( argc < 2 ) {
    alert_box( "AST2WP4", "AST2WP4 INFILE OUTFILE\nConvert ASTRO Text Source file Format to WordPerfect 4.x" );
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
    alert_box( "AST2WP4", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wb" ) ) == NULL ) {
    alert_box( "AST2WP4", "Can't Open %s for Writing!", buf );
    fclose( out );
    return( -1 );
    }
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
 setcrs( 0x0d, 0x0a );
 dllYield();
 write_wp4_header( out );
 while ( ( p = fgets( tbuf, 9998, in ) ) != NULL ) {
       text_wrap( tbuf, 70 );
       doConvertText( tbuf, _SRC_T_, _OEM_T_ );
       dllYield();
       for ( b = p; *b; b++ ) {
	   switch( *b ) {
	      case '{' :
		   putc( '\x9D', out );
		   break;
	      case '}' :
		   putc( '\x9C', out );
		   break;
	      case '<' :
		   putc( '\x94', out );
		   break;
	      case '>' :
		   putc( '\x95', out );
		   break;
	      case '~' :
		   b++;
		   if ( isascii( *b ) )
		      putc( *b, out );
		   else
		      wp4_foreign_char( out, *b );
		   break;
	      default :
		putc( *b, out );
		break;
	      }
	   }
       putc( '\n', out );
       }
 l = ftell(out);
 l--;
 l %= 16;
 if ( l ) {
    while ( l < 16L ) {
	  putc( '\0', out );
	  l++;
	  }
    }
 fclose( in );
 fclose( out );
 delete tbuf;
 return( 0 );
}


}


