#include "stdafx.h"
#include "afxcoll.h"
#include "astro.h"
#include "useri.h"
#include <assert.h>
#include "errors.fns"
#include "paths.hpp"
#include "filelst.hpp"
#include "astrow.h"
#include "filenamedlg.h"
#include "charcons.h"



/* function to check status of que. If the que is not in memory, the
   function calls the necessary code to read it into memory. Locks
   memory block and makes sure memory is ok */

void FileListArray::check( void )
{
 if ( !strlen( name ) )
    return;
 if ( !inMem() )
	read();
 keep(1);
}

/*  If memory is locked, unlock, make discardable */

void FileListArray::release( void )
{
 keep(0);
}

/* function to add files to que and create file names. Type is the
   basic type for the file. The function will adjust for the graph
   name information. but will have a different type, name and
   extension. Name is the name of the individual in question from the
   date screen. The file names are returned through the two char
   pointers tfile for the text file and, if graph then a file is
   returned through gfile. If !graph then you should set gfile to NULL
   tfile and gfile should point to a string of not less than 13 wide
   returns 0 for ok 1 for error */

int FileListArray::doAddFile( CWnd *pPar, int type, int graph, char *name, int dogrid,
   char *cmt, char *tfile, char *gfile, char *grdfile, XPFILE_DB **gptr, XPFILE_DB **tptr,
   XPFILE_DB **grdptr, int folder, BOOL &bAuto )
{
 XPFILE_DB fdb, *ptr, hold;
 char *p;

 memset( &fdb, 0, sizeof(XPFILE_DB) );
 assert( name != NULL && cmt != NULL && tfile != NULL && gfile != NULL && grdfile != NULL );
 assert( gptr != NULL && tptr != NULL && grdptr != NULL );
 name[NAME_WIDTH]='\0';
 strcpy( fdb.name, name );
 assert( strlen( fdb.name ) < sizeof( fdb.name ) );
 cmt[COMMENT_WIDTH]='\0';
 strcpy( fdb.comment, cmt );
 assert( strlen( fdb.comment ) < sizeof( fdb.comment ) );
 fdb.type = type;
 if ( folder == -1 )
    fdb.folder = GetCurFolder();
 else
    fdb.folder = folder;
 if ( folder == -1 )
 {
   makeFileName( type, &fdb );
   hold = fdb;
   CFileNameDlg fn(pPar);
   fn.SetData(fdb);
   if ( fn.DoModal() == IDOK ) {
	    bAuto = fn.m_auto;
    	fn.GetData(fdb);
   }
   else
	    return( 1 );
   if ( hold.folder != fdb.folder )
      makeFileName( type, &fdb );
 }
 else 
    makeFileName( type, &fdb );
 ptr = addFile( &fdb, type);
 if ( ptr == NULL )
    return( 1 );
 if ( tptr != NULL )
    *tptr = ptr;
 strcpy( tfile, ptr->file_name );
 if ( graph ) {
 	p = strrchr(fdb.file_name, '.' );
	if ( p != NULL )
	   strcpy( p, ".ASGRA" );
	fdb.type += LAST_NON_GRAPH;
	ptr = addFile( &fdb, type + LAST_NON_GRAPH);
    if ( ptr == NULL )
       return( 1 );
    if ( gptr != NULL )
       *gptr = ptr;
    strcpy( gfile, ptr->file_name );
    }
 if ( dogrid ) {
 	p = strrchr(fdb.file_name, '.' );
	if ( p != NULL )
	   strcpy( p, ".ASGRD" );
	fdb.type = type + LAST_GRAPH;
	ptr = addFile( &fdb, type + LAST_GRAPH);
    if ( ptr == NULL )
       return( 1 );
    if ( grdptr != NULL )
       *grdptr = ptr;
    strcpy( grdfile, ptr->file_name );
    }

 last_no++;
 dirty(1);
 return( 0 );
}
