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

extern void setcrs( unsigned char scr, unsigned char hcr );
extern int text_wrap( char *string, int width );

static char *tbuf;

extern "C" {

int __far __pascal __export _AST2ASC( int argc, char *argv[] )
{
 char buf[100], *p, word[70];
 FILE *in, *out;
 int c, col = 0;

 if ( argc < 2 ) {
    alert_box( "AST2ASC", "AST2ASC INFILE OUTFILE\nConvert ASTRO Text Source file Format to ASCII" );
    return( -1 );
    }
 if ( argc < 3 ) {
    strcpy( buf, argv[1] );
    p = strchr( buf, '.' );
    if ( p == NULL )
       strcat( buf, ".ASC" );
    else
       strcpy( p, ".ASC" );
    }
 else
    strcpy( buf, argv[2] );
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "AST2ASC", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wt" ) ) == NULL ) {
    alert_box( "AST2ASC", "Can't Open %s for Writing!", buf );
    fclose( out );
    return( -1 );
    }
 tbuf = new char[10000];
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
 setcrs( '\n', '\n' );
 while ( ( p = fgets( tbuf, 9998, in ) ) != NULL ) {
       text_wrap( tbuf, 70 );
       fputs( tbuf, out );
       fputs( " \\\n", out );
       dllYield();
       }
 fclose( in );
 fclose( out );
 delete tbuf;
 return( 0 );
}

}