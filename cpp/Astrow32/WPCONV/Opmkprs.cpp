#include "stdafx.h"
#include <stdlib.h>
#include <ctype.h>
#include "astro.h"
#include "useri.h"
#include "output.fns"
#include "attrib.h"
#include "charcons.h"

int op_make_printer_string( char *instring, FILE *outstream )
{
 char *inptr;
 int  val, count;

 if ( outstream == NULL )
    return( -1 );
 count = 0;
 if ( *instring == '\0' ) {
    return( count );
    }
 for ( inptr = instring; *inptr; inptr++ ) {
     if ( *inptr == '~' ) {
	inptr++;
	if ( fputc( *inptr, outstream ) == EOF )
	   return( -1 );
	}
     else if ( *inptr != '<' && *inptr != '>' ) {
	if ( fputc( *inptr, outstream ) == EOF )
	   return( -1 );
	++count;
	}
     else if ( *inptr != '>' ) {
	val = atoi( inptr+1 );
	if ( fputc( (char) val, outstream ) == EOF )
	   return( -1 );
	++inptr;
	++count;
	while ( *inptr && isdigit( *inptr ) )
	      ++inptr;
	}
     }
 return( count );
}

#ifdef _UNICODEVER
int wc_op_make_printer_string( char *instring, FILE *outstream )
{
 char *inptr, buf[5];
 int  val, count;
 wchar_t wchar[5];

 if ( outstream == NULL )
    return( -1 );
 count = 0;
 if ( *instring == '\0' ) {
    return( count );
    }
 for ( inptr = instring; *inptr; inptr++ ) {
     if ( *inptr == '~' ) {
	inptr++;
	mbtowc(wchar,(const char *)instring,1);
	wchar[1] = 0;
	if ( fputwc( wchar[0], outstream ) == EOF )
	   return( -1 );
	}
    else if ( *inptr != '<' && *inptr != '>' ) {
	   mbtowc(wchar,(const char *)instring,1);
	   wchar[1] = 0;
	   if ( fputwc( wchar[0], outstream ) == EOF )
	     return( -1 );
	   ++count;
	   }
    else if ( *inptr != '>' ) {
	   val = atoi( inptr+1 );
	   buf[0] = (char)val;
	   buf[1] = '\0';
	   mbtowc(wchar,(const char *)instring,1);
	   wchar[1] = 0;
	   if ( fputwc( wchar[0], outstream ) == EOF )
	      return( -1 );
	   ++inptr;
	   ++count;
	   while ( *inptr && isdigit( *inptr ) )
	        ++inptr;
	   }
     }
 return( count );
}

void OutputUnichar( char *b, FILE *out )
{
 wchar_t ub[10];

 mbtowc(ub,b,1);
 fwrite(ub,2,1,out);
}

#endif