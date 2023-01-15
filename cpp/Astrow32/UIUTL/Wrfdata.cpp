#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "output.fns"


unsigned short fdata_size( unsigned short type )
{
 unsigned short sz = sizeof( BIRTH_DB ) + sizeof( RECT_DATA ) + 4;

 if ( type & RELOC_CH )
    sz += sizeof( LOC_DB ) + 2;
 if ( type & PROGR_CH )
    sz += sizeof( PROGR_DATA ) + 2;
 if ( type & (COMPO_CH|COMPA_CH) )
    sz += sizeof( BIRTH_DB ) + sizeof( RECT_DATA ) + 4;
 if ( type & TRANS_CH )
    sz += sizeof( BIRTH_DB ) + sizeof( TRANS_DATA ) + 4;
 if ( type & RETUR_CH )
    sz += sizeof( RETURN_DATA ) + 2;
 if ( type & SOLAR_CH )
    sz += sizeof( DIREC_DATA ) + 2;
 return( sz );
}

unsigned short fdata_write_item( FILE *stream, void *data, short sz )
{
 short j;

 j = fwrite( &sz, sizeof( short ), 1, stream );
 j += fwrite( data, sz, 1, stream );
 return( j );
}

short fdata_write( FILE *stream, unsigned short type )
{
 unsigned short d[2], r;

 d[0] = type;
 d[1] = fdata_size( type );
 r = fwrite( d, sizeof( short ), 2, stream );
 r += fdata_write_item( stream, &birth_rec, sizeof( BIRTH_DB ) );
 r += fdata_write_item( stream, &birth_rectd, sizeof( RECT_DATA ) );
 if ( type & RELOC_CH )
    r += fdata_write_item( stream, &reloc_data, sizeof( LOC_DB ) );
 if ( type & PROGR_CH )
    r += fdata_write_item( stream, &progress_data, sizeof( PROGR_DATA ) );
 if ( type & (COMPO_CH|COMPA_CH) ) {
    r += fdata_write_item( stream, &comp_rec, sizeof( BIRTH_DB ) );
    r += fdata_write_item( stream, &comp_rectd, sizeof( RECT_DATA ) );
    }
 if ( type & TRANS_CH ) {
    r += fdata_write_item( stream, &trans_rec,  sizeof( BIRTH_DB ) );
    r += fdata_write_item( stream, &transit_data,  sizeof( TRANS_DATA ) );
    }
 if ( type & RETUR_CH )
    r += fdata_write_item( stream, &return_data,  sizeof( RETURN_DATA ) );
 if ( type & SOLAR_CH )
    r += fdata_write_item( stream, &solar_data,  sizeof( DIREC_DATA ) );
 return( r );
}

unsigned short fdata_read_item( FILE *stream, void *data, short sz )
{
 short j, l;

 j = fread( &l, sizeof( short ), 1, stream );
 if ( l == sz )
    l += fread( data, sz, 1, stream );
 else if ( l < sz )
    j += fread( data, l, 1, stream );
 else {
    j += fread( data, sz, 1, stream );
    fseek( stream, l - sz, SEEK_CUR );
    }
 return( j );
}

short fdata_read( FILE *stream )
{
 unsigned short d[2], r, type;

 r = fread( d, sizeof( short ), 2, stream );
 type = d[0];
 r = fdata_read_item( stream, &birth_rec, sizeof( BIRTH_DB ) );
 r += fdata_read_item( stream, &birth_rectd, sizeof( RECT_DATA ) );
 if ( type & RELOC_CH )
    r += fdata_read_item( stream, &reloc_data, sizeof( LOC_DB ) );
 if ( type & PROGR_CH )
    r += fdata_read_item( stream, &progress_data, sizeof( PROGR_DATA ) );
 if ( type & (COMPO_CH|COMPA_CH) ) {
    r += fdata_read_item( stream, &comp_rec, sizeof( BIRTH_DB ) );
    r += fdata_read_item( stream, &comp_rectd, sizeof( RECT_DATA ) );
    }
 if ( type & TRANS_CH )
    r += fdata_read_item( stream, &trans_rec,  sizeof( BIRTH_DB ) );
 if ( type & RETUR_CH )
    r += fdata_read_item( stream, &return_data,  sizeof( RETURN_DATA ) );
 if ( type & SOLAR_CH )
    r += fdata_read_item( stream, &solar_data,  sizeof( DIREC_DATA ) );

 return( r );
}
