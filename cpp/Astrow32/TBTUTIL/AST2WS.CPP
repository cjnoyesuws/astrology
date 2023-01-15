#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")
#include <ctype.h>


// 7/8/94  CJN   complete Conversion
// 10/24/94 CJN  setup for 1 DLL

extern void setcrs( unsigned char scr, unsigned char hcr );
extern int text_wrap( char *string, int width );

static char *tbuf;

static int ws_foreign_char( FILE *stream, unsigned char the_char )
{
 if ( putc( '\x1b', stream ) == EOF )
    return( -1 );
 if ( putc( the_char, stream ) == EOF )
    return( -1 );
 if ( putc( '\x1c', stream ) == EOF )
    return( -1 );
 return( 0 );
}


static void write_ws_header( FILE *stream )
{
 char buf[42];
 int i;

 fputs( ".MT 6\r\n.MB 6\r\n.PL 66\r\n", stream );
 fputs( ".PO 0\r\n..\r", stream );
 fputs( ".RR \r", stream );
 fputs( "L----!", stream );
 for ( i = 6; i < 78; ++i )
     putc( '-', stream );
 fputs( "R\r\n", stream );
}


extern "C" {

int __far __pascal __export _AST2WS( int argc, char *argv[] )
{
 char buf[100], *p, *b;
 FILE *in, *out;
 int c, col = 0;

 if ( argc < 2 ) {
    alert_box( "AST2WS", "AST2WS INFILE OUTFILE\nConvert ASTRO Text Source file Format to WordStar" );
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
    alert_box( "AST2WS", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wb" ) ) == NULL ) {
    alert_box( "AST2WS", "Can't Open %s for Writing!", buf );
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
 setcrs( '\x8d', '\x0d' );
 write_ws_header( out );
 dllYield();
 while ( ( p = fgets( tbuf, 9998, in ) ) != NULL ) {
       text_wrap( tbuf, 70 );
       doConvertText( tbuf, _SRC_T_, _OEM_T_ );
       dllYield();
       for ( b = p; *b; b++ ) {
	   switch( *b ) {
	      case '{' :
	      case '}' :
		   putc( 2, out );
		   break;
	      case '<' :
	      case '>' :
		   putc( 0x13, out );
		   break;
	      case '\x8d' :
		   fputs( " \x8d\n", out );
		   break;
	      case '~' :
		   b++;
		   if ( isascii( *b ) )
		      putc( *b, out );
		   else
		      ws_foreign_char( out, *b );
		   break;
	      default :
		putc( *b, out );
		break;
	      }
	   }
       fputs( "\r\n", out );
       }
 fclose( in );
 fclose( out );
 delete tbuf;
 return( 0 );
}

}



