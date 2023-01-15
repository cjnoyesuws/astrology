#include <string.h>

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

char *strclip( char *pStr )
{
 int l = strlen( pStr );

 for ( char *s = (pStr+l)-1; l; l--, s-- ) {
     if ( *s != ' ' )
	break;
     }
 if ( *(s+1) == ' ' )
    *(s+1) = '\0';
 return( pStr );
}


char *xstrcpy( char *dest, char* src )
{
 char *d, *s;

 d=dest;
 s=src;

 while ( *s != '\0' )
	 *d++ = *s++;

 return(dest);

}