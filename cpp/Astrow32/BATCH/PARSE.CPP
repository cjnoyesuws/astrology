#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <ctype.h>
#include <stdarg.h>
#include "batch.hpp"

char *parseStr( char *sbuf, char *fmt, char *del, char *var  )
{
 char *fd;

 sscanf( sbuf, fmt, var );
 fd = strstr( sbuf, del );
 if ( fd == NULL )
    return( NULL );
 fd += strlen( del );
 while ( *fd && isspace( *fd ) )
       fd++;
 return( fd );
}

char *parseInt( char *sbuf, char *fmt, char *del int *var )
{
 char *fd;

 sscanf( sbuf, fmt, var );
 fd = strstr( sbuf, del );
 if ( fd == NULL )
    return( NULL );
 fd += strlen( del );
 while ( *fd && isspace( *fd ) )
       fd++;
 return( fd );
}

char *parsef( char *sbuf, char *fmt, char *del, ... )
{
 va_list argptr;
 char *fd;

 va_start(argptr, del );
 vsscanf( sbuf, fmt, argptr );
 fd = strstr( sbuf, del );
 if ( fd == NULL )
    return( NULL );
 fd += strlen( del );
 while ( *fd && isspace( *fd ) )
       fd++;
 return( fd );
}



