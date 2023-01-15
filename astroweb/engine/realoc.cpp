#include <assert.h>
#include <stdio.h>
#include <cstring>

/* 09/10/92  Modified for C++ Windows */

/* special realloc function which uses new and delete */

void *reallocx( void *p, unsigned bytes )
{
 void *t;
 assert(bytes < 64000);
 t = new char[bytes];
 if ( t == NULL )
    return( NULL );
 memcpy( t, p, bytes );
 delete p;
 return( t );
}
