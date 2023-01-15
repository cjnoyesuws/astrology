#include "stdafx.h"
#include "flags.h"
#include "astro.h"
#include "aspect.h"
#include "dataext.h"
#include "compute.fns"
#include <stdlib.h>
#include "errors.fns"




ASPEC *firstAspect( ASPEC *pAsp, int cnt, int asp )
{
 int i;
 ASPEC *as;

 if ( pAsp == NULL || !cnt )
    return( NULL );
 for ( i = 0, as = pAsp; i < cnt; ++i, ++as ) {
     if ( as->aspect == asp )
	return( as );
     }
 return( NULL );
}

ASPEC *nextAspect( ASPEC *pAsp, int cnt, int asp, ASPEC *prev )
{
 int i;
 ASPEC *as;

 if ( pAsp == NULL || !cnt || prev == NULL )
    return( NULL );
 for ( i = (int)(prev-pAsp)/sizeof(ASPEC), as = prev+1; i < cnt; ++i, ++as ) {
     if ( as->aspect == asp )
	return( as );
     }
 return( NULL );
}


int teeSquare( AS_INF, *inf, int cnt )
{
 int i;
 ASPEC *fa;
 AS_INF *pi;

 for ( i = 0, pi = inf; i < cnt; i++, pi++ ) {
     if ( ( fa = firstAspect( pi->aspectr, pi->no_aspects, OPPOSITION )) != NULL ) {
	if ( firstAspect( pi->aspectr, pi->no_aspects, SQUARED ) != NULL )
	   return( 1 );
	}
     }
 return( 0 );
}

int grandSquare( AS_INF, *inf, int cnt )
{
 int i;
 ASPEC *fa;
 AS_INF *pi;

 for ( i = 0, pi = inf; i < cnt; i++, pi++ ) {
     if ( ( fa = firstAspect( pi->aspectr, pi->no_aspects, OPPOSITION )) != NULL ) {
	if ( firstAspect( pi->aspectr, pi->no_aspects, SQUARED ) != NULL ) {
	   if ( firstAspect( (inf+second)->aspectr, pi->no_aspects, OPPOSITION ) != NULL ) {
	      return( 1 );
	   }
	}
     }
 return( 0 );
}

