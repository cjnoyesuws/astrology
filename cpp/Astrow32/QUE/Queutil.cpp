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
#include "filelistset.h"
#include "direc.hpp"

/* function to kill one file in que. deletes file itself and marks type
   with DELETED_FILE, write_que should be called afterwards to refresh
   que file */

int FileListArray::killFile( XPFILE_DB *ptr )
{
 char *p;
 char *file_name;
 int x;

 check();
 keep(1);
 assert( ptr != NULL );
 if ( !isDelFile(ptr) ) {
	file_name = (char *)set_path( ptr->file_name, ptr->folder );
    unlink( file_name );
    p = strchr( file_name, '.' );        /* Support for future Comment file */
    if ( p != NULL && ptr->has_comments  ) {       /* and Cover Page files. */
       strcpy( p, ".CMT" );
       unlink( file_name );
       }
    if ( p != NULL && ptr->has_cover  ) {
       strcpy( p, ".CPG" );
       unlink( file_name );
       }
	}
 delete ptr;   
 dirty(1);
 return(0);
}

/* function to kill whole que. Erases que file, and then erases each file
   in que calling FileListArray::killFile().

   Use with Caution. Kills entire file listing, deleting files.
   */

void FileListArray::killWholeFileList()
{
 
 CFileListSet fls;
 try {
    CDaoDatabase *pDB = new CDaoDatabase();
	pDB->Open(GetDatabaseName());
	if ( pDB->IsOpen() ) {
		pDB->Execute("delete from FileList", dbSQLPassThrough);
		pDB->Close();
		}
	delete pDB;
 }
 catch ( CDaoException *e ) {
   char erbuf[500];
   e->GetErrorMessage(erbuf,500);
   alert_box("Database Error", erbuf );
 }	
 XPFILE_DB *ptr;	 
 int i, x =arraygroup.all.fldcount;
 for ( i = 0; i < x; x++ ) {
	 AryFldItem *par= (AryFldItem *)arraygroup.all.fldAr[i];
	 for ( int j = 0; j < par->ar.GetSize(); i++ )
		 killFile( (XPFILE_DB *)par->ar[j] );
     }
 unlink( name );
 free();
}


/* function to free up memory and cause file to be written to disk
   also sets the in_mem variable to 0 signifying that the file
   needs to be read in, as well as setting fileDBptr() to null */

void FileListArray::free(void)
{
void *p; 
int i, x =arraygroup.all.fldcount;
 
 for ( i = 0; i < x; i++ ) {
	 AryFldItem *par = (AryFldItem *)arraygroup.all.fldAr[i];
	 for ( int j = 0; j < par->ar.GetSize(); j++ ) {
	    p = par->ar[j];
	    if ( p != NULL ) {
		   delete p;
           par->ar[j] = NULL;
	       }
	    }
    }
 arraygroup.all.free();
 arraygroup.all.totalcount = 0;
 arraygroup.text.free();;
 arraygroup.text.totalcount=0;
 arraygroup.graph.free();
 arraygroup.graph.totalcount=0;
}
