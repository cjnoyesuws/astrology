#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <share.h>
#include <string.h>
#include "freesp.hpp"
#include "errors.fns"

int free_cmp( const void *p1,const void *p2 )
{
 FREE_SP *fp1 = (FREE_SP *) p1, *fp2 =(FREE_SP *) p2;

 return( fp1->len - fp2->len );
}


short FreeBlock::write( char *file )
{
 FILE *stream;

 if ( ( stream = _fsopen( file, "r+b", SH_DENYWR ) ) == NULL ) {
    do_error( file );
    return( 0 );
    }
 if ( fwrite( &nfree, sizeof( short ), 1, stream ) != 1 ) {
    do_error( file );
    fclose( stream );
    return( 0 );
    }
 if ( fwrite( frees, sizeof( FREE_SP ), 20, stream ) != 20 ) {
    do_error( file );
    fclose( stream );
    return( 0 );
    }
 fclose( stream );
 return( 1 );
}

short FreeBlock::read( char *file )
{
 FILE *stream;

 if ( ( stream = _fsopen( file, "rb", SH_DENYWR ) ) == NULL ) {
    do_error( file );
    return( 0 );
    }
 if ( fread( &nfree, sizeof( short ), 1, stream ) != 1 ) {
    do_error( file );
    fclose( stream );
    return( 0 );
    }
 if ( fread( frees, sizeof( FREE_SP ), 20, stream ) != 20 ) {
    do_error( file );
    fclose( stream );
    return( 0 );
    }
 fclose( stream );
 return( 1 );
}

FREE_SP *FreeBlock::find( short len )
{
 short i;
 FREE_SP *fsp;

 for ( i = 0, fsp = frees; i < nfree; ++i, ++fsp ) {
     if ( fsp->len >= len && !fsp->used )
	return( fsp );
     }
 return( NULL );
}

short FreeBlock::getsp( short len, long *ofs)
{
 FREE_SP *fsp;

 if ( ( fsp = find( len ) ) != NULL ) {
    fsp->used = 1;
    *ofs = fsp->ofs;
    if ( fsp == &frees[nfree-1] )
       --nfree;
    return( fsp->len );
    }
 return( 0 );
}

short FreeBlock::add( short len, long ofs )
{
 short i;
 FREE_SP *fsp;

 for ( i = 0, fsp = frees; i < nfree; ++i, ++fsp ) {
     if ( fsp->used ) {
	fsp->used = 0;
	fsp->len = len;
	fsp->ofs = ofs;
	qsort(frees, nfree, sizeof( FREE_SP ), free_cmp );
	return( 1 );
	}
     }
 if ( i < 20 ) {
    fsp = &frees[nfree];
    nfree++;
    fsp->used = 0;
    fsp->len = len;
    fsp->ofs = ofs;
    qsort(frees, nfree, sizeof( FREE_SP ), free_cmp );
    return( 1 );
    }
 return( 0 );
}

long FreeBlock::do_free( short width, short *widthp, short *fail_len, long *fail_rec )
{
 short w = width;
 long rec;

 if ( *fail_rec ) {
    add( *fail_len, *fail_rec );
    *fail_rec = 0L;
    }
 if ( ( w = getsp( width, &rec ) ) )
    *widthp = w;
 else
    rec = -1L;

 return( rec );
}

