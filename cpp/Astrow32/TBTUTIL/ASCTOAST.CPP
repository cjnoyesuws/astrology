#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <search.H>
#include <string.h>
#include <io.h>
#include <tbtutil.h>
#include <builder.hpp>
#pragma hdrstop("TBTCVTUT.pch")

static int isImport;

// 7/8/94   CJN  complete Conversion
// 10/24/94 CJN  setup for 1 DLL

/* program to read text and concat text together, so that when text is read
   then text can be text-wrapped properly. It places \n's only on lines
   marked with \ for hard breaks */

static char *inbuf;
static char *outbuf;

static FILE *out;

static void trim(char *buf)
{
 int i;

 i = strlen( buf )-1;
 while ( *(buf+i) == ' ' || *(buf+i) == '\n' ) {
       *(buf+i) = '\0';
       --i;
       }
}

static void append_text()
{
 static int outpoint = 0;
 static int len = 0;
 char ch;

 trim(inbuf);
 len = strlen( inbuf );
 ch = inbuf[len-1];
 if ( ch == '\\' )
    inbuf[len-1] = '\n';
 else if ( ch != ' ' && ch != '-' ) {
    inbuf[len] = ' ';
    ++len;
    inbuf[len] = '\0';
    }
 if ( inbuf[0] == '-'&& outbuf[outpoint-1] != '\n' )
    --outpoint;
 if ( len + outpoint > 11998 ) {
    fwrite( outbuf, 1, outpoint, out );
    outpoint = 0;
    outbuf[0] = '\0';
    }
 strcpy( &outbuf[outpoint], inbuf );
 outpoint += len;
}

extern "C" {

int __far __export __pascal _ASCTOAST( int argc, char *argv[] )
{
 char buf[100], *p, word[70];
 FILE *in;
 int c, col;

 if ( argc < 2 ) {
    alert_box( "ASCTOAST", "ASCTOAST INFILE OUTFILE\nConvert ASTRO ASCII Text Source file Format to ASTRO Format\n" );
    return( -1 );
    }
 if ( argc < 3 ) {
    strcpy( buf, argv[1] );
    p = strchr( buf, '.' );
    if ( p == NULL )
       strcat( buf, ".AST" );
    else
       strcpy( p, ".AST" );
    }
 else
    strcpy( buf, argv[2] );
 if ( ( in = fopen( argv[1], "rt" ) ) == NULL ) {
    alert_box( "ASCTOAST", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wt" ) ) == NULL ) {
    alert_box( "ASCTOAST", "Can't Open %s for Writing!", buf );
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
 inbuf = new char[300];
 outbuf = new char[12000];
 while ( ( p = fgets(inbuf,290,in) ) != NULL ) {
       append_text();
       dllYield();
       if ( isImport )
	  doConvertText( outbuf, _OEM_T_, _SRC_T_ );
       }
 fputs( outbuf, out );
 fclose( in );
 fclose( out );
 delete inbuf;
 delete outbuf;
 return( 0 );
}

}

extern "C" {

int __far __export __pascal _ASCTOASTI( int argc, char *argv[] )
{
 int x;
 isImport = 1;
 x = _ASCTOAST( argc, argv );
 isImport = 0;
 return x;
}

}
