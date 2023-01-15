#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include "tbtutil.h"
#include "builder.hpp"
#pragma hdrstop("TBTCVTUT.pch")

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

static int srcAnsi;
static int dstAnsi;

extern "C" {

int __declspec(dllexport) WINAPI _AST2DOC( int argc, char *argv[] )
{
 FILE *in, *out;
 int c;
 char buf[120];
 char gbuf[200];

 if ( argc < 3 ) {
   alert_box( "ASTTODOC", "Usage: ASTTODOC Source Dest" );
   return( -1 );
   }
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "ASTTODOC", "Can't Open %s for Reading!", argv[1] );
    return( 1 );
    }
 if ( ( out = fopen( argv[2], "wt" ) ) == NULL ) {
    alert_box( "ASTTODOC", "Can't Open %s for Writing!", argv[2] );
    fclose( out );
    return( 2 );
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
 while ( fgets(gbuf, 199, in) != NULL ) {
       doConvertText( gbuf, _SRC_T_, _EDT_T_ );
       fputs( gbuf, out );
       }
 fclose( in );
 fclose( out );
 return( 0 );
}

int __declspec(dllexport) WINAPI _AST2MSW( int argc, char *argv[] )
{
 return( _AST2DOC( argc, argv ) );
}

int __declspec(dllexport) WINAPI _DOCTOAST( int argc, char *argv[] )
{
 FILE *in, *out;
 int c;
 char buf[120];
 char gbuf[200];

 if ( argc < 3 ) {
   alert_box( "DOCTOAST", "Usage: DOCTOAST Source Dest" );
   return( -1 );
   }
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "DOCTOAST", "Can't Open %s for Reading!", argv[1] );
    return( 1 );
    }
 if ( ( out = fopen( argv[2], "wt" ) ) == NULL ) {
    alert_box( "DOCTOAST", "Can't Open %s for Writing!", argv[2] );
    fclose( out );
    return( 2 );
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
 while ( fgets(gbuf, 199, in) != NULL ) {
       fputs( gbuf, out );
       }
 fclose( in );
 fclose( out );
 return( 0 );
}

}
