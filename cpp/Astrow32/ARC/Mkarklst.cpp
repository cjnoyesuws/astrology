#include "stdafx.h"
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "archive.hpp"
#include "flistarc.hpp"
#include "errors.fns"

extern int getFileCount( CWordArray &war, CPtrArray &par, int n, int cmt, int cvr );
extern int getFileList( CStringArray &sar, CWordArray &war, CPtrArray &par, int n, int sz, int b4, int cmt, int cvr );

// A Function to create An Archive File based on selected files.

char *FileListArchiver::makeArchiveList(int fld)
{
 FILE *stream;
 int n, count, fcount;
 char nbuf[150];
 char fbuf[200];
 CWordArray war;
 CStringArray sar;
 int i;

 pFla->check();
 count = pFla->selCount(type, fld);
 if ( !count )
    return(0);
 war.SetSize(count+2,5);
 count = pFla->getSelection(type, count, war, fld);
 CPtrArray &par = pFla->fileDBArray(type, fld);
 fcount = getFileCount( war, par, count, 1, 1 );
 sar.SetSize(fcount+1,2);
 getFileList( sar, war, par, count, fcount, 0, 1, 1 );
 GetTempFileName( ".", "AST", 0, name );
 if ( ( stream = fopen( name, "wt" ) ) == NULL ) {
    do_error( name );
    return( NULL );
    }
 for ( i = 0; sar[i] != "NULL"; i++ ) {
	 GetShortPathName(set_path((char *)(LPCTSTR)sar[i], pFla->GetCurFolder()), fbuf, 200 );
	 fprintf( stream, "%s\n", fbuf );
     }
 fflush( stream );
 fclose( stream );
 return( name );
}
