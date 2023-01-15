#include "stdafx.h"
#include "afxcoll.h"
#include <stdlib.h>
#include <search.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "astro.h"
#include "useri.h"
#include "errors.fns"
#include "charcons.h"
#include "paths.hpp"
#include "filelst.hpp"

int fsortcmpi( void const *f1, void const *f2 )
{
 XPFILE_DB const *db1 = (XPFILE_DB *)f1, *db2 = (XPFILE_DB *)f2;
 int r;
 
 r = lstrcmpi( db1->name, db2->name );
 if ( !r )
    r = lstrcmpi( db1->comment, db2->comment );
 else
    return( r );
 if ( db1->type > COMPTR_GRAPH_FILE || db1->type > COMPTR_GRAPH_FILE )
    return( 0 );
 return( db1->type - db2->type );
}

// do a bubble sort on the array.
void FileListArray::SortAnArray(int type)
{
int i, j, max, cmp;
XPFILE_DB *tmp;
AryItem &ar = arraygroup.get(type,DEFAULT_FLD);
max = ar.totalcount;
if ( !max ) {
    alert_box( "", "No Files To sort!" );
    return;
    }
int fldmx = ar.fldcount;
for ( int k = 0; k < fldmx; k++ ) {
	CPtrArray *par = ar.get(k+DEFAULT_FLD);
	max = ar.fldp->count;
	if (!max)
		continue;
	for ( i = max; i > 0; i-- ) {
	    for ( j = 0; j < max-1; j++ )	{
		   cmp = fsortcmpi(par->GetAt(j),par->GetAt(j+1));
	       if ( cmp > 0 ) {
			   tmp = (XPFILE_DB *)par->GetAt(j);
			   par->ElementAt(j) = par->GetAt(j+1);
			   par->ElementAt(j+1) = tmp;
	          }
	       }
	   }
   }
}

void FileListArray::sortFiles()
{
 if ( !inMem() )
    read();
 check();
 SortAnArray(GRA_F);
 FlistDoUpdate(GRA_F);
 SortAnArray(GRIDFX);
 FlistDoUpdate(GRIDFX);
 SortAnArray(NON_GRA);
 FlistDoUpdate(NON_GRA);
 SortAnArray(ALL_F);
 FlistDoUpdate(ALL_F);
 write();
}
