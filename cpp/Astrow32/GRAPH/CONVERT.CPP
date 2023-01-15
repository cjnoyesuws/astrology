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
#include "paths.hpp"
#include "filelst.hpp"
#include "dib.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "grappane.hpp"
#include "errors.fns"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "grafilop.hpp"
#include "grconv.hpp"
#include "vicdefs.h"

int doConvertSelGraphFile(zWindow *pPar, FileListArray *fla )
{
 int n, count, fcount, res;
 char *fbuf, **flist, nbuf[15];
 FILE_DB **ptr, **pt;
 GraphicFileConverter *gfc;

 fla->check();
 count = fla->selCount(GRA_F);
 if ( !count )
    return( 0 );
 ptr = new FILE_DB *[count+2];
 if ( ptr == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 gfc = new GraphicFileConverter(pPar);
 if ( !gfc->getSetup() ) {
    delete ptr;
    delete gfc;
    return( 0 );
    }
 count = fla->getSelection(GRA_F, count, ptr);
 for ( pt = ptr, n = 0; n < count; pt++ ) {
     if ( !*pt )
	break;
     if ( !gfc->getFile() ) {
	delete ptr;
	delete gfc;
	return( 0 );
	}
     AstGraphicsPane *agp = new AstGraphicsPane( (*pt)->file_name,
		pPar, USER_F);
     gfc->setPane(agp);
     if ( !(res = gfc->doConvert()) ) {
	delete agp;
	break;
	}
     delete agp;
     }
 delete ptr;
 delete gfc;
 return( res );
}


int doConvGraph( zWindow *pPar, FILE_DB *pFd )
{
 int n=0, res;
 char nbuf[15], *ar[4], nbuf2[15];
 GraphicFileConverter *gfc;

 if ( pFd == NULL )
    return( 0 );
 gfc = new GraphicFileConverter(pPar);
 if ( !gfc->getSetup() ) {
    delete gfc;
    return( 0 );
    }
 if ( !gfc->getFile()  ) {
    delete gfc;
    return( 0 );
    }
 AstGraphicsPane *agp = new AstGraphicsPane( pFd->file_name,
      pPar, USER_F );
 gfc->setPane(agp);
 res = gfc->doConvert();
 delete agp;
 delete gfc;
 return( res );
}

