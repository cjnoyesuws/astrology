#include "stdafx.h"
#include "afxcoll.h"
#include <io.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "astro.h"
#include "useri.h"
#include "errors.fns"
#include <assert.h>
#include "paths.hpp"
#include "filelst.hpp"
#include "direc.hpp"
#include "filelistset.h"


/* Function to delete an entry from the list without deleting
   the files underlying it. */

int FileListArray::deleteEntry( XPFILE_DB *ptr )
{
 int x;

 CFileListSet fls;
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
 check();
 keep(1);
 assert( ptr != NULL );
 x = findPtr(ALL_F, ptr );
 FlistDoUpdate(ALL_F);
 if ( x != -1 ) {
	 if ( arraygroup.all.get(ptr->folder)->GetSize() > x) {	
	    arraygroup.all.get(ptr->folder)->RemoveAt(x);
        arraygroup.all.fldp->count--;
	    arraygroup.all.totalcount--;
	   }
     }
 if ( ptr->type < LAST_NON_GRAPH ) {
    x = findPtr(NON_GRA,ptr);
	if ( x != -1 ) {
		if ( arraygroup.text.get(ptr->folder)->GetSize() > x ) {
		   arraygroup.text.get(ptr->folder)->RemoveAt(x);
	       arraygroup.text.totalcount--;
		   arraygroup.text.fldp->count--;
		}
		FlistDoUpdate(NON_GRA);
	   }
	}
 else if ( ptr->type > LAST_GRAPH ) {
     x = findPtr(GRIDFX,ptr);
	if ( x != -1 ) {
		if (arraygroup.grid.get(ptr->folder)->GetSize() > x) {
	      arraygroup.grid.get(ptr->folder)->RemoveAt(x);
	      arraygroup.grid.totalcount--;
	      arraygroup.grid.fldp->count--;
        }
	   FlistDoUpdate(GRIDFX);
	   }
	}
 else {
	x = findPtr(GRA_F,ptr);
	if ( x != -1 ) {
	   if (	arraygroup.graph.get(ptr->folder)->GetSize() > x) {
	     arraygroup.graph.get(ptr->folder)->RemoveAt(x);
         arraygroup.graph.totalcount--;
	     arraygroup.graph.fldp->count--;
	   }
	   FlistDoUpdate(GRA_F);
	   }
	}
 dirty(1);
 return( 0 );
}


XPFILE_DB *FileListArray::addEntry( XPFILE_DB *ptr, int upd, BOOL bAdd)
{
	if ( bAdd ) {
      CFileListSet fls;
	  try {
         fls.Open();
		 fls.AddNew();
		 fls.m_comments = ptr->comment;
		 fls.m_filename = ptr->file_name;
		 fls.m_filenum = ptr->file_num;
		 fls.m_Folder = ptr->folder;
		 fls.m_name = ptr->name;
		 fls.m_FileType = ptr->type;
		 fls.m_IsTextReport = (ptr->type < LAST_NON_GRAPH?TRUE:FALSE);
         if (ptr->type < LAST_NON_GRAPH)
			 fls.m_ListType = "OUT";
		 else if (ptr->type > LAST_GRAPH)
			 fls.m_ListType = "GRD";
		 else
			 fls.m_ListType = "GRA";
		 fls.Update();
		}
      catch (CDaoException *e) {
        char erbuf[500];
        e->GetErrorMessage(erbuf, 500);
        alert_box("Database Error", erbuf );
       }
	}
 if ( ptr->type < LAST_NON_GRAPH ) {
	Add(NON_GRA,ptr);
	Add(ALL_F,ptr);
	if ( upd ) {
       FlistDoUpdate(ALL_F);
 	   FlistDoUpdate(NON_GRA);
	   }
    }
 else if ( ptr->type > LAST_GRAPH ) {
    Add(GRIDFX,ptr);
	Add(ALL_F,ptr);
	if ( upd ) {
	   FlistDoUpdate(ALL_F);
 	   FlistDoUpdate(GRIDFX);
	   }
    }
 else {
	Add(GRA_F,ptr);
	Add(ALL_F,ptr);
	if ( upd ) {
	   FlistDoUpdate(ALL_F);
	   FlistDoUpdate(GRA_F);
	   }
	}
 if ( upd ) {
   keep(1);
   check();
   }
 return( ptr );
}


void FileListArray::Add(int type,XPFILE_DB *p)
{
 AryItem &e = arraygroup.get(type,p->folder);
 if ( !e.fldp )
	 return;
 e.ar->SetAtGrow(e.fldp->count++,p);
 e.count++;
 e.totalcount++;
}

void  FileListArray::UpdatePtr(XPFILE_DB *p)
{
  CFileListSet fls;
  char buf[200];
  sprintf(buf,"select * from FileList where filename='%s' and folder=%d", p->file_name, p->folder );
  try {
     fls.Open(-1,buf);
     fls.Edit();
     fls.m_comments = p->comment;
     fls.m_filename = p->file_name;
	 fls.m_filenum = p->file_num;
	 fls.m_Folder = p->folder;
	 fls.m_name = p->name;
	 fls.m_has_comments = p->has_comments;
	 fls.m_has_cover = p->has_cover;
	 fls.Update();
	}
   catch (CDaoException *e) {
      char erbuf[500];
      e->GetErrorMessage(erbuf, 500);
      alert_box("Database Error", erbuf );
     }
}