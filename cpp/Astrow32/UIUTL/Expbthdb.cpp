#include "..\dumplocs\stdafx.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dbstruct.h"
#include "freesp.hpp"
#include "dataext.h"

BIRTH_DB birth;
RECT_DATA rect;
union DBR dbirth;

BIRTH_DB *cvt_dsk_2_nbirthdb( BIRTH_DB *bdp, DBR *dbdp, RECT_DATA *rdp )
{
 char *buf;
 int cp = 0;

 bdp->birth_data = dbdp->n.birth_data;
 bdp->sex = dbdp->n.sex;
 bdp->time_zone = dbdp->n.time_zone;
 bdp->special_code = dbdp->n.special_code;
 bdp->am_pm = dbdp->n.am_pm;
 memcpy( bdp->tzcodekey, dbdp->n.tzcodekey, 5 );
 if ( dbdp->n.with_rect && rdp != NULL ) {
    *rdp = dbdp->r.rect_data;
    buf = dbdp->r.buf;
    }
 else if ( !dbdp->n.with_rect && rdp != NULL ) {
    rdp->birth_time_known = 1;
    buf = dbdp->n.buf;
    }
 else if ( dbdp->n.with_rect && rdp == NULL )
    buf = dbdp->r.buf;
 else
    buf = dbdp->n.buf;
 strcpy( bdp->name, &buf[cp]);
 cp += strlen(bdp->name)+1;
 assert( sizeof( bdp->name ) > strlen( bdp->name ) );
 strcpy( bdp->country, &buf[cp] );
 cp += strlen(bdp->country)+1;
 assert( sizeof( bdp->country ) > strlen( bdp->country ) );
 strcpy( bdp->state, &buf[cp]);
 cp += strlen(bdp->state)+1;
 assert( sizeof( bdp->state ) > strlen( bdp->state ) );
 strcpy( bdp->location, &buf[cp] );
 assert( sizeof( bdp->location ) > strlen( bdp->location ) );
 return( bdp  );
}


void export(FILE *stream)
{
 fprintf( stream, "\"%s\",\"%c\",%d,%d,%d,%d,%d,\"%s\",", birth.name, (birth.sex?'F':'M'),
   birth.birth_data.birth_date.month, birth.birth_data.birth_date.day,
   birth.birth_data.birth_date.year, birth.birth_data.birth_time.hours,
   birth.birth_data.birth_time.minutes, (birth.am_pm?"PM":"AM") );
 fprintf( stream, "\"%s\",\"%s\",\"%s\",%d,%d,\"%c\",%d,%d,\"%c\",%d,%d,%d,%d\n",
   birth.country, birth.state, birth.location, birth.birth_data.longitude.degrees,
   birth.birth_data.longitude.minutes, birth.birth_data.longitude.dir,
   birth.birth_data.latitude.degrees, birth.birth_data.latitude.minutes,
   birth.birth_data.latitude.dir, birth.time_zone, birth.special_code,
   birth.birth_data.local_adjust, birth.birth_data.local_minutes );
}

void main(int argc, char **argv)
{
 short len;
 FILE *istream;
 FILE *ostream;

 istream = fopen( argv[1], "rb" );
 ostream = fopen( argv[2], "wt" );
 fseek( istream, (20* sizeof(FREE_SP))+2, SEEK_SET );
 do {
     if ( (fread( &len, 2, 1, istream ) != 1) || feof( istream ))
	break;

     if ( (fread( (char *)&dbirth.r.freer, len-2, 1, istream ) != 1)
				    && !feof( istream ) )
	break;
     dbirth.r.len = len;
     if ( dbirth.r.freer == 1 )
	continue;
     cvt_dsk_2_nbirthdb( &birth, &dbirth, &rect );
     export(ostream);
   } while ( !feof( istream ) );
 fclose( istream );
 fclose( ostream );
}
