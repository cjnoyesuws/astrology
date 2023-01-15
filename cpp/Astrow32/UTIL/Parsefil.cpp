#include "stdafx.h"
#include <io.h>
#include <fcntl.h>
#include <assert.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "charcons.h"
#include "dataext.h"
#include "paths.hpp"
#include "errors.fns"

void do_parse_file( XPFILE_DB *pFd )
{
 char fn[75];
 FILE *stream;
 NFP fp;

 if ( pFd == NULL )
    return;
 strcpy( fn, set_path( pFd->file_name, TEMP_F ) );
 if ( ( stream = freadx_fptr( fn, &fp, 1 ) ) == NULL ) {
    do_error( fn );
    return;
    }
 if ( ferror( stream ) || feof( stream ) ) {
    do_error( fn );
    fclose( stream );
    return;
    }
 if ( !isafptr3_file(&fp) && !isafptr2_file(&fp) && !isafptr3w_file(&fp) && !isafptr3wx_file(&fp) ) {
    alert_box( "", "Can't Get Info From Earlier ASTRO .OUT Files." );
    fclose( stream );
    return;
    }
 fdata_read( stream );
 if ( ferror( stream ) ) {
    do_error( fn );
    }
 fclose( stream );
}
