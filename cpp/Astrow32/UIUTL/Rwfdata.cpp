#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "output.fns"
#include "fptr.h"
#include "errors.fns"

int fdata_rewrite( FILE *istream, FILE *ostream  )
{
 unsigned short d[2];
 int r, c;

 r = fread( d, sizeof( short ), 2, istream );
 if ( ferror(istream) )
    return( 1 );
 fwrite( d, sizeof( short ), 2, ostream );
 for ( r = 0; r < d[1]; r++ ) {
     c = fgetc(istream);
     fputc( c, ostream );
     }
 return( ferror(ostream) );
}


FILE *re_save_header( char *iname, char *oname )
{
 NFP the_nfp;
 FILE *istream, *ostream;

 if ( (istream = freadx_fptr( iname, &the_nfp, 1 ) ) == NULL ) {
    do_error( iname );
    return( NULL );
    }
 if ( (ostream = fwrite_fptr( oname, (NFDB *)&the_nfp.n.fpt, 3 ) ) == NULL ) {
    do_error( oname );
    return( NULL );
    }
 fdata_rewrite( istream, ostream  );
 fclose( istream );
 return( ostream );
}




