#include <stdafx.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dbstruct.h"
#include "freesp.hpp"

LOC_DB loc;
D_LOC_DB dloc;

LOC_DB *cvt_dsk_2_nlocdb( LOC_DB *ldp, D_LOC_DB *dldp )
{
 int cp = 0;

 memcpy( &ldp->longitude, &dldp->longitude,
		 (sizeof(DEG_MIN) * 2) + (4 * sizeof( int )) );
 strcpy( ldp->country, &dldp->buf[cp] );
 assert( sizeof( ldp->country ) > strlen( ldp->country ) );
 cp += strlen(ldp->country)+1;
 strcpy( ldp->state, &dldp->buf[cp] );
 cp += strlen(ldp->state)+1;
 assert( sizeof( ldp->state ) > strlen( ldp->state ) );
 strcpy( ldp->location, &dldp->buf[cp] );
 assert( sizeof( ldp->location ) > strlen( ldp->location ) );
 return( ldp );
}

void export(FILE *stream)
{
 fprintf( stream, "\"%s\",\"%s\",\"%s\",%d,%d,\"%c\",%d,%d,\"%c\",%d,%d,%d,%d\n",
   loc.country, loc.state, loc.location, loc.longitude.degrees,
   loc.longitude.minutes, loc.longitude.dir, loc.latitude.degrees,
   loc.latitude.minutes, loc.latitude.dir, loc.time_zone, loc.special_code,
   loc.hrs_offset, loc.min_offset );
}

void main(int argc, char **argv )
{
 short len;
 FILE *istream;
 FILE *ostream;

 istream = fopen( argv[1], "rb" );
 ostream = fopen( argv[2], "wt" );
 fseek( istream, (20* sizeof(FREE_SP))+2, SEEK_SET );
 do {
     if ( (fread( &len, 2, 1, istream ) != 1) && feof( istream ))
	break;

     if ( (fread( (char *)&dloc.freer, len-2, 1, istream ) != 1)
				    && !feof( istream ) )
	break;
     dloc.len = len;
     if ( dloc.freer == 1 )
	continue;
     cvt_dsk_2_nlocdb( &loc, &dloc );
     export(ostream );
   } while ( !feof( istream ) );
 fclose( istream );
 fclose( ostream );
}
