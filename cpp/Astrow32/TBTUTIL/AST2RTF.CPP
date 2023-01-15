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

int win;
int toWin;

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static char *rtf_soft_line = "\n";
static char *rtf_hard_line = "\\par}\n{";

static int rtf_foreign( FILE *stream, unsigned char c )
{
 char buf[10];
 char cbf[5];

 if ( win && !toWin ) {
    cbf[0] = c;
    cbf[1] = '\0';
    AnsiToOem(cbf,cbf);
    c = cbf[0];
    }
 else if ( !win && toWin ) {
    cbf[0] = c;
    cbf[1] = '\0';
    OemToAnsi(cbf,cbf);
    c = cbf[0];
    }
 sprintf( buf, "\\\'%2x", c );
 return( fputs( buf, stream ) );
}

static int write_rtf_header(FILE *stream )
{
 fprintf( stream, "{\\rtf0\\%s{\\fonttbl\\f0\\fnil default;}", (toWin?"ansi":"pc") );
 fprintf( stream, "{\\stylesheet {\\s0\\f0\\fi0\\marginl0\\marginr12160"
     "\\ql Normal;}}\r\n{\\pard\\ql " );
 return( 0 );
}

extern "C" {

int __far __pascal __export _AST2RTF( int argc, char *argv[] )
{
 char buf[100], *p;
 FILE *in, *out;
 int c, s, e, d;

 getConvertTextSettings( s, e, d, c );
 win = s;
 toWin = e;
 if ( argc < 2 ) {
    alert_box( "AST2RTF", "AST2RTF INFILE OUTFILE\nConvert ASTRO Text Source file Format to MS Word RTF" );
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
    alert_box( "AST2RTF", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wt" ) ) == NULL ) {
    alert_box( "AST2RTF", "Can't Open %s for Writing!", buf );
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
 dllYield();
 write_rtf_header( out );
 while ( ( c = getc( in ) ) != EOF ) {
       switch( c ) {
	     case '\\' :
		  fputs( "\\\\", out );
		  break;
	     case '\n' :
		  fputs( rtf_hard_line, out );
		  dllYield();
		  break;
	     case '<' :
		  fputs( "\\ul ", out );
		  break;
	     case '>' :
		  fputs( "\\ul0 " , out );
		  break;
	     case '{' :
		  fputs( "\\b ", out );
		  break;
	     case '}' :
		  fputs( "\\b0 ", out );
		  break;
	     case '~' :
		  c = getc( in );
		  if ( isascii( c ) && strchr( "\\{}", c ) != NULL ) {
		     putc( '\\', out );
		     putc( c, out );
		     }
		  else if ( strchr( "~^[]", c ) != NULL ) {
		     putc( '~', out );
		     putc( c, out );
		     }
		  else if ( isascii( c ) )
		     putc( c, out );
		  else
		     rtf_foreign( out, c );
		  break;
	     default :
		  putc( c, out );
		  break;
	     }
       }
 fputs( "\\par } }\n", out );
 fclose( in );
 fclose( out );
 return( 0 );
}

}



