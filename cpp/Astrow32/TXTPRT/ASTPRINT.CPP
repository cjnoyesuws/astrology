#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include <assert.h>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "charcons.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "fdecomp.hpp"
#include "paths.hpp"
#include "fprint.hpp"
#include "asfrmdlg.hpp"
#include "pageopt.hpp"
#include "printopt.hpp"
#include "acombbox.hpp"
#include "coverdat.hpp"
#include "fcovrprt.hpp"
#include "filelst.hpp"
#include "errors.fns"
#include "inifile.hpp"

void zYield( int y = 1 );

int doPrintFile( FILE_DB *ptr, zWindow *pPar )
{
 char path[150], nbuf[15], nbuf2[15];
 char *ar[3];
 PrintData data;
 int n = 0;

 if ( ptr == NULL || pPar == NULL )
    return( 0 );
 data.getFromIni();
 PrintDataDlgf *pdf = new PrintDataDlgf(pPar, &data );
 if ( !pdf->completed() ) {
    delete pdf;
    return( 0 );
    }
 else {
    pdf->getData();
    delete pdf;
    }
 data.saveToIni();
#ifdef PRO
 if ( data.getCpg() && ptr->has_cover
	  && !( data.getRange() && data.getFrom() > 1 ) ) {
    CoverPagePrinter *cpp =
	new CoverPagePrinter(replace_ext(nbuf, ptr->file_name, ".CPG"), ptr);
    cpp->doPrint();
    while ( app->tasks()->busy() )
	  zYield();
    delete cpp;
    }
 if ( data.getCmt() && data.getCmtBefore() && ptr->has_comments ) {
    ar[n] = replace_ext(nbuf2, ptr->file_name, ".CMT");
    n++;
    }
#endif
 ar[n] = ptr->file_name;
 n++;
#ifdef PRO
 if ( data.getCmt() && !data.getCmtBefore() && ptr->has_comments ) {
    ar[n] = replace_ext(nbuf2, ptr->file_name, ".CMT");
    n++;
    }
#endif
 ar[n] = NULL;
 FilePrinter *fp = new FilePrinter(ar, USER_F);
 fp->setRange(data.getRange(), data.getFrom(), data.getTo());
 fp->doPrint();
 while ( app->tasks()->busy() )
       zYield();
 delete fp;
 return( 1 );
}


int doSelPrintFiles(zWindow *pPar, FileListArray *fla )
{
#ifndef _QDTRAN_
 int n, count, fcount;
 char *fbuf, **flist, nbuf[15];
 FILE_DB **ptr, **pt;
 PrintData data;

 fla->check();
 count = fla->selCount(NON_GRA);
 if ( !count )
    return( 0 );
 ptr = new FILE_DB *[count+2];
 if ( ptr == NULL ) {
    do_mem_error(0);
    return( 0 );
    }
 count = fla->getSelection(NON_GRA, count, ptr);
 data.getFromIni();
 PrintDataDlgf *pdf = new PrintDataDlgf(pPar, &data);
 if ( !pdf->completed() ) {
    delete pdf;
    delete ptr;
    return( 0 );
    }
 else {
    pdf->getData();
    delete pdf;
    }
 data.saveToIni();
 fcount = getFileCount( ptr, count, data.getCmt() );
 flist = new char *[fcount+4];
 fbuf = new char[(fcount+4)*15];
 if ( flist == NULL || fbuf == NULL ) {
    do_mem_error(0);
    if ( flist != NULL )
       delete flist;
    if ( fbuf != NULL )
       delete fbuf;
    delete ptr;
    return( 0 );
    }
#ifdef PRO
 if ( data.getCpg() && (*ptr)->has_cover
		 && !( data.getRange() && data.getFrom() > 1 ) ) {
    replace_ext(nbuf, (*ptr)->file_name, ".CPG");
    CoverPagePrinter *cpp = new CoverPagePrinter(nbuf, *ptr);
    cpp->doPrint();
     while ( app->tasks()->busy() )
	   zYield();
    delete cpp;
    }
#endif
 getFileList( ptr, flist, fbuf, count, fcount, data.getCmtBefore(), data.getCmt()  );
 FilePrinter *fp = new FilePrinter(flist, USER_F);
 fp->setRange(data.getRange(), data.getFrom(), data.getTo());
 fp->doPrint();
 while ( app->tasks()->busy() )
       zYield();
 delete fp;
 delete fbuf;
 delete flist;
 delete ptr;
 #endif
 return( 1 );
}

