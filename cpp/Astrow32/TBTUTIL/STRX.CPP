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

#define START '['
#define END   ']'

extern int hval( char c );
int translate_string_chrs( char *instring, unsigned char *outstring )
{
 unsigned char *inptr, *outptr;
 int  val, count;

 count = 0;
 if ( *instring == '\0' ) {
    strcpy( (char *)outstring, "" );
    return( 0 );
    }
 for ( inptr = (unsigned char *)instring, outptr = outstring; *inptr;  ) {
     if ( *inptr == '\\' ) {
	++inptr;
	*outptr = *inptr;
	++outptr;
	++count;
	if ( *inptr )
	   ++inptr;
	}
     else if ( *inptr == '#' ) {
	++inptr;
	if ( *inptr != '#' ) {
	   *outptr = ' ';
	   ++outptr;
	   ++count;
	   }
	else {
	   *outptr = '#';
	   ++outptr;
	   ++count;
	   ++inptr;
	   }
	}
     else if ( *inptr != START && *inptr != END && *inptr != '\0' ) {
	*outptr = *inptr++;
	++outptr;
	++count;
	}
     else if ( *inptr != END ) {
	if ( !strcmpi( "0x", (char *)inptr+1 ) )
	   
	   val = (hval(*inptr+3)*16)+hval(*inptr+4);
	else
	   val = atoi( (char *)inptr+1 );
	*outptr = (char) val;
	++inptr;
	++outptr;
	++count;
	while ( *inptr && (isxdigit( *inptr ) || *inptr == 'x' || *inptr == 'X' ) )
	      ++inptr;
	if ( *inptr )
	   ++inptr;
	}
     }
 *outptr = '\0';
 return( count );
}




