#include <stdafx.h>
/*
#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "dib.hpp"
#include "grappane.hpp"
#include "errors.fns"


int doPrintSelGraphFile(zWindow *pPar, FileListArray *fla )
{
 int n, count, fcount;
 char *fbuf, **flist, nbuf[15];
 FILE_DB **ptr, **pt;

 fla->check();
 count = fla->selCount(GRA_F);
 if ( !count )
    return( 0 );
 ptr = new FILE_DB *[count+2];
 if ( ptr == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 count = fla->getSelection(GRA_F, count, ptr);
 for ( pt = ptr, n = 0; n < count; pt++ ) {
     if ( !*pt )
	break;
     AstGraphicsPane *agp = new AstGraphicsPane( (*pt)->file_name,
		pPar, USER_F);
     agp->doPrint(0);
     delete agp;
     }
 delete ptr;
 return( 1 );
}
*/