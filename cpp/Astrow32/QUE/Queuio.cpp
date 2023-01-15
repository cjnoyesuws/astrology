#include "stdafx.h"
#include "afxcoll.h"
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "errors.fns"
#include <assert.h>
#include "paths.hpp"
#include "filelst.hpp"
#include "astrow.h"
#include "filekilldlg.h"
#include "fileeditdlg.h"
#include "direc.hpp"
#include "charcons.h"
#include "filelistset.h"

/* function to get files to delete and ask user if they want to
   delete those files. If they respond yes, then those files are deleted */



void FileListArray::killSelectedFiles( CWnd *pPar, int type, int fld)
{
 int count, cont = 1, index = 0, ret, n;
 XPFILE_DB *ptr;
 CWordArray ar;


 count = selCount(type, fldcheck(fld));
 ar.SetSize(count+2,5);
 if ( !count )
    return;
 getSelection(type, count, ar, fldcheck(fld) );
 AryItem &ptrs= arraygroup.get(type, fldcheck(fld));
 CFileKillDlg fkd;
 index = count-1;
 do {
   if ( index >= ptrs.ar->GetSize() )
	   continue;
   ptr = (XPFILE_DB *)(*ptrs.ar)[ar[index]];
   if ( ptr == NULL )
      continue;
   if ( cont ) {
      fkd.SetData(*ptr);	 
      ret = fkd.DoModal();
      fkd.GetData(cont);
	  }
   if ( ret == IDCANCEL )
      return;
   else if ( ret == IDNO ) {
	  index--;
	  continue;
	  }
   else {
	  if ( (n = findPtr(type, ptr)) != -1 ) {
	     arraygroup.all.get(ptr->folder)->RemoveAt(n);
	     arraygroup.all.count--;
         arraygroup.all.totalcount--;
	     }
	   AryItem &it =arraygroup.get(type,ptr->folder);
	   it.fldp->ar.RemoveAt(ar[index--]);
   	   it.count--;
	   it.totalcount--;
	   it.fldp->count--;
       char buf[200];
       sprintf(buf,"delete from FileList where filename='%s' and folder=%d", ptr->file_name, ptr->folder );
       try {
         CDaoDatabase *pDB = new CDaoDatabase();
	     pDB->Open(GetDatabaseName());
	     if ( pDB->IsOpen() ) {
		    pDB->Execute(buf, dbSQLPassThrough);
		    pDB->Close();
		    }
	     delete pDB;
       }
       catch ( CDaoException *e ) {
         char erbuf[500];
         e->GetErrorMessage(erbuf,500);
         alert_box("Database Error", erbuf );
      }
	  killFile(ptr);
      }
  } while ( index >= 0 );
 dirty(1);
 write();
}


/* function to get file to delete and ask user if they want to
   delete that file. If they respond yes, then file is deleted */

int FileListArray::doKillFile(XPFILE_DB *ptr, CWnd *pPar)
{
 int n;
 if ( ptr == NULL )
    return( 0 );
 CFileKillDlg fkd;
 fkd.SetData(*ptr);	 
 if ( fkd.DoModal() == IDOK ) {
	 char buf[200];
     sprintf(buf,"delete from FileList where filenum=%d and folder=%d", ptr->file_num, ptr->folder );
     try {
        CDaoDatabase *pDB = new CDaoDatabase();
	    pDB->Open(GetDatabaseName());
	    if ( pDB->IsOpen() ) {
		    pDB->Execute(buf, dbSQLPassThrough);
		    pDB->Close();
		    }
	     delete pDB;
       }
       catch ( CDaoException *e ) {
         char erbuf[500];
         e->GetErrorMessage(erbuf,500);
         alert_box("Database Error", erbuf );
      }
	 if ( (n = findPtr(ALL_F, ptr )) != -1 ) {
	   arraygroup.all.get(ptr->folder)->RemoveAt(n);
	   arraygroup.all.fldp->count--;
	   arraygroup.all.totalcount--;
	   }
	if ( (n = findPtr(GRIDFX, ptr )) != -1 ) {
	   arraygroup.grid.get(ptr->folder)->RemoveAt(n);
	   arraygroup.grid.fldp->count--;
	   arraygroup.grid.totalcount--;
	   }
	if ( (n = findPtr(GRA_F, ptr )) != -1 )  {
	   arraygroup.graph.get(ptr->folder)->RemoveAt(n);
	   arraygroup.graph.fldp->count--;
	   arraygroup.graph.totalcount--;
	   }
	if ( (n = findPtr(NON_GRA, ptr )) != -1 ) {
	   arraygroup.text.get(ptr->folder)->RemoveAt(n);   
       arraygroup.text.fldp->count--;
	   arraygroup.text.totalcount--;
	   }
	killFile(ptr);
    }
 dirty(1);
 write();
 keep( 0 );
 return( 0 );
}

void FileListArray::changeEntry( XPFILE_DB *ptr, CWnd *pPar )
{
 char qb[150];
 NFP  nfpt;
 NFP  nfpt2;
 XPFILE_DB fd;
 int ret, fh;

 keep(1);
 check();
 CFileEditDlg fed;
 fed.SetData(*ptr);
 if ( fed.DoModal() == IDCANCEL )
	return;
 fed.GetData( *ptr );
 CFileListSet fls;
 char buf[200];
       sprintf(buf,"select * from FileList where filename='%s' and folder=%d", ptr->file_name, ptr->folder );
       try {
         fls.Open(-1,buf);
		 fls.Edit();
		 fls.m_name = ptr->name;
		 fls.m_comments = ptr->comment;
		 fls.Update();
       }
       catch ( CDaoException *e ) {
         char erbuf[500];
         e->GetErrorMessage(erbuf,500);
         alert_box("Database Error", erbuf );
      }
 strcpy( qb, set_path( ptr->file_name, ptr->folder ) );
 if ( ( fh = readx_fptr( qb, &nfpt, 0 ) ) == -1 ) {
    do_error( qb );
    keep(0);
    return;
    }
 close(fh);
  if ( isafptr3w_file( &nfpt ) ) {
    nfpt.x.fpt = *ptr;
    if ( ( fh = write_fptr( qb, (NFDB *)&nfpt.n.fpt, 7 ) ) == -1 )
       do_error( qb );
    else
       close( fh );
    }
 else if ( isafptr3wx_file( &nfpt ) ) {
    nfpt.x.fpt = *ptr;
    if ( ( fh = write_fptr( qb, (NFDB *)&nfpt.x.fpt, 7 ) ) == -1 )
       do_error( qb );
    else
       close( fh );
    }
 else if ( isafptr3wxg_file( &nfpt ) ) {
    nfpt.x.fpt = *ptr;
    if ( ( fh = write_fptr( qb, (NFDB *)&nfpt.x.fpt, 8 ) ) == -1 )
       do_error( qb );
    else
       close( fh );
    }
 write();
 keep(0);
}

void FileListArray::scanFiles()
{
 check();
 keep(1);
 doFileScan();
 inMem(0);
 dirty(0);
 read();
#ifndef LITE
 sortFiles();
#endif
 keep(0);
}
