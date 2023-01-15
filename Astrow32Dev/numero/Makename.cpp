#include <assert.h>
#include <string.h>
#include <stdio.h>

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )


char *replace_ext( char *buf, char *name, char *ext )
{
 char *dot;

 strcpy( buf, name );
 dot = strchr( buf, '.' );
 if ( dot != NULL )
    strcpy( dot, ext );
 else
    strcat( buf, ext );
 return( buf );
}
