#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "textbloc.h"
#include "errors.fns"

int CTextlockAryFileType( char *name )
{
 FILE *stream ;
 char *buf;
 char ch;
 char *cp;
 int f1 = -1, f2 = -1, f3 = -1, i, len;

 buf = new char[2000];
 if ( buf == NULL ) {
    do_mem_error( 0 );
    return( 0 );
    }
 if ( (stream = fopen( name, "rt" ) ) == NULL ) {
    do_error( name );
    return( 0 );
    }
 do {
    fgets( buf, 1999, stream );
    } while ( *buf != '#' );
 fclose(stream);
 len = strlen( buf );
 for ( i = 0; i < len-1; i++ ) {
     if ( f1 == -1 && buf[i] == ' ' ) {
	while ( buf[++i] == ' ' && i < len-1 );
	f1 = i;
	}
     else if ( f1 != -1 && f2 == -1 && buf[i] == ' ' ) {
	while ( buf[++i] == ' ' && i < len-1 );
	if ( i < len-1 )
	   f2 = i;
	}
     else if ( f2 != -1 && f3 == -1 && buf[i] == ' ' ) {
	while ( buf[++i] == ' ' && i < len-1 );
	if ( i < len-1 )
	   f3 = i;
	}
     }
 free( buf );
 if ( f3 != -1 )
    return( 3 );
 else if ( f2 != -1 )
    return( 2 );
 else
    return( 1 );
}




