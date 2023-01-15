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

static int bold, underscore, head;
static int hi_char, skip = 0;

static int skip_cmd( FILE *stream )
{
 int c;

 do {
   c = fgetc(stream);
   } while ( c != 0x0a && c != 0x8a && c != 0x1d && c!= 0x9d );
 if ( c == 0x1d || c == 0x9d )
    ungetc( c, stream );
 else {
    c = fgetc( stream );
    if ( c == '.' )
       skip_cmd( stream );
    else
       ungetc( c, stream );
    }
 return( 0 );
}


extern "C" {

int __far __pascal __export _WSTOAST( int argc, char *argv[] )
{
 long ofs;
 char buf[100], *p;
 FILE *in, *out;
 int c, len;

 if ( argc < 2 ) {
    alert_box( "WS2AST", "WS2AST INFILE OUTFILE\nConvert WordStar Text to Text Source File Format" );
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
    alert_box( "WSTOAST", "Can't Open %s for Reading!", argv[1] );
    return( -1 );
    }
 if ( ( out = fopen( buf, "wb" ) ) == NULL ) {
    alert_box( "WS2AST", "\aCan't Open %s for Writing!\n", buf );
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
 if ( c == '.' )
    skip_cmd( in );
 else
    ungetc( c, in );
 while ( ( c = fgetc( in ) ) != EOF ) {
       switch ( c ) {
	      case 1 :
		   break;
	      case 2 :
	      case 4 :
		   if ( bold ) {
		      fputc( '}', out );
		      bold = 0;
		      }
		   else {
		      fputc( '{', out );
		      bold = 1;
		      }
		   break;
	      case 5 :
	      case 6 :
	      case 7 :
	      case 8 :
		   break;
	      case 9 :
		   fputc( '|', out );
		   break;
	      case 0x8b :
	      case 0x8c :
		   skip = 1;
		   break;
	      case 0x0b :
	      case 0x0c :
		   skip = 0;
		   break;
	      case 0x0d :
		   if ( !skip )
		      fputc( '\r', out );
		   else
		      skip = 0;
	      case 0x8d :
		   if ( c == 0x8d )
		      skip = 1;
		   c = fgetc( in );
		   if ( c == '.' )
		      skip_cmd( in );
		   else
		      ungetc( c, in );
		   break;
	      case 0x0a :
		   dllYield();
		   if ( !skip )
		      fputc( '\n', out );
		   else
		      skip = 0;
	      case 0x8a :
		   if ( c == 0x8a )
		      skip = 1;
		   c = fgetc( in );
		   if ( c == '.' )
		      skip_cmd( in );
		   else
		      ungetc( c, in );
		   break;
	      case 0x8f :
	      case 0x0f :
		   fputc( ' ', out );
		   break;
	      case 0x10 :
		   break;
	      case 0x11 :
	      case 0x12 :
	      case 0x17 :
		   if ( head ) {
		      fputc( ']', out );
		      head = 0;
		      }
		   else {
		      fputc( '[', out );
		      head = 1;
		      }
		   break;
	      case 0x93 :
	      case 0x99 :
	      case 0x13 :
	      case 0x19 :
		   if ( underscore ) {
		      fputc( '>', out );
		      underscore = 0;
		      }
		   else {
		      fputc( '<', out );
		      underscore = 1;
		      }
		   break;
	      case 0x14 :
	      case 0x15 :
	      case 0x16 :
	      case 0x18 :
	      case 0x1a :
	      case 0x94 :
	      case 0x95 :
	      case 0x96 :
	      case 0x97 :
	      case 0x98 :
	      case 0x9a :
		   break;
	      case 0x9b :
	      case 0x1b :
		   c = fgetc( in );
		   hi_char = 1;
		   fputc( '~', out );
		   fputc( c, out );
		   fgetc( in );
		   break;
	      case 0x9d :
	      case 0x1d :
		   fread( &len, 2, 1, in );
		   ofs = ftell( in );
		   fseek( in, ofs+len, SEEK_SET );
		   c = fgetc( in );
		   if ( c == '.' )
		      skip_cmd( in );
		   else {
		      ungetc( c, in );
		      }
		   break;
	      case 0x1c :
	      case 0x1e :
	      case 0x1f :
	      case 0x9c :
	      case 0x9e :
	      case 0x9f :
	      case 0xa0 :
		   break;
	      case '^' :
	      case '~' :
	      case '{' :
	      case '}' :
	      case '<' :
	      case '>' :
		   fputc( '~', out );
		   fputc( c, out );
		   break;
	      case '~'|0x80 :
	      case '{'|0x80 :
	      case '}'|0x80 :
	      case '<'|0x80 :
	      case '>'|0x80 :
		   fputc( '~', out );
		   fputc( c & 0x80, out );
		   break;
	      case ' ' :
		   if ( hi_char )
		      fputc( '~', out );
		   fputc( ' ', out );
		   break;
	      default :
		   hi_char = 0;
		   if ( c > 0x80 )
		      c ^= 0x80;
		   fputc( c, out );
		   break;
	     }
       }

 return( 1 );
}

}