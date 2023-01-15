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

#undef ERROR

#define WORD    1
#define WINWORD 2
#define ERROR   -1
#define IDW55 "\x31\xbe"
#define IDWW1 "\x9b\xa5"
#define IDWW2 "\xdb\xa5"

static void copy_doc( FILE *in, FILE *out )
{
 int c;

 while ( (c = fgetc(in)) != EOF )
       fputc(c, out );

 fclose( in );
 fclose( out );
 }

static skip_fld( FILE *stream )
{
 int c;

 while ( (c = fgetc(stream)) != 0x15 );
 return( 1 );
}


static int check_version(FILE *stream, char *version, long *textlen  )
{
 int hln;

 if ( memcmp( IDW55, version, 2) && memcmp( IDWW1, version, 2)
	&& memcmp( IDWW2, version, 2) ) {
    alert_box("MSWTOAST", "Not Microsoft Word or Write File" );
    return( ERROR );
    }
 if ( memcmp( IDW55, version, 2) ) {
    fseek( stream, 28, SEEK_SET );
    fread( textlen, 4, 1, stream );
    fseek( stream, 24, SEEK_SET );
    fread( &hln, 2, 1, stream );
    fseek( stream, hln, SEEK_SET );
    *textlen -= 384;
    return( WINWORD );
    }
 else {
    fseek( stream, 14, SEEK_SET );
    fread( textlen, 4, 1, stream );
    fseek( stream, 128, SEEK_SET );
    *textlen -= 128;
    return( WORD );
    }
  return( 0 );
}

extern "C" {

int __declspec(dllexport) WINAPI _MSWTOAST( int argc, char *argv[] )
{
 long text_len, n;
 char buf[100], *p, version[3];
 FILE *in, *out;
 int c, len, ver;

 if ( argc < 2 ) {
    alert_box("MSWTOAST", "MSWTOAST INFILE OUTFILE\nConvert Microsoft Word, Write Text to Text Source File Format" );
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
 if ( ( in = fopen( argv[1], "rb" ) ) == NULL ) {
    alert_box("MSWTOAST", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wb" ) ) == NULL ) {
    alert_box("MSWTOAST", "Can't Open %s for Writing!", buf );
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
 c = fgetc( in );
 if ( c == '@' || c == '#' ) {
    ungetc( c, in );
    copy_doc( in, out );
    return( 1 );
    }
 ungetc( c, in );
 fread( version, 2, 1, in );
 ver = check_version( in, version, &text_len );
 if ( ver == ERROR ) {
    return( -1 );
    }
 n = 0;
 dllYield();
 while ( ( c = fgetc( in ) ) && n < text_len ) {
       n++;
       switch ( c ) {
	      case '\t' :
		   fputc( '|', out );
		   break;
	      case 0x13 :
		   skip_fld(in);
		   break;
	      case '\n' :
	      case 0x0b :
		   dllYield();
		   fputc( '\n', out );
		   break;
	      case 0x0f :
		   fputc( '-', out );
		   fputc( '-', out );
		   break;
	      case 30:
		   if ( ver == WINWORD )
		      fputc('-', out );
		   break;
	      case 196:
		   if ( ver == WORD )
		      fputc('-', out );
		   break;
	      case 160:
		   if ( ver == WINWORD )
		      fputc(' ', out );
		   break;
	      case 0xff:
		   if ( ver == WORD )
		      fputc(' ', out );
		   break;
	      default :
		   if ( c < ' ' )
		      continue;
		   else if ( c > 126 ) {
			 fputc( '~', out );
			 fputc( c, out );
			 c = fgetc(in);
			 if ( c == ' ' ) {
			    fputc( '~', out );
			    fputc( c, out );
			    }
			 else
			    ungetc(c,in);
			 }
		   else
		      fputc( c, out );
		   break;
	     }
       }

 fclose( in );
 fclose( out );
 return( 0 );
}

}
