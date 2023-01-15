#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "chartinf.h"
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
     if ( *inptr != '<' && *inptr != '>' && *inptr != '~' ) {
	    if ( fputc( *inptr, outstream ) == EOF )
	       return( -1 );
	    ++count;
	    }
     else if ( *inptr=='~' ) {
	 		 inptr++;
	         if ( fputc( *inptr, outstream ) == EOF )
	            return( -1 );
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
 if ( fflush( outstream ) == EOF )
    return( -1 );
 return( count );
}

