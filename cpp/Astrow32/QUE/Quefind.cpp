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


#ifdef PRO
static XPFILE_DB fnd;

int compare( XPFILE_DB *src, XPFILE_DB *lst, int type )
{
 int c, l;

 l = strlen(src->name);
 if ( l ) {
    c = strnicmp( src->name, lst->name, l );
    if ( c )
       return( c );
    }
 l = strlen(src->comment);
 if ( l ) {
    c = strnicmp( src->comment, lst->comment, l );
    if ( c )
       return( c );
    }
 l = strlen(src->file_name);
 if ( l ) {
    c = strnicmp( src->file_name, lst->file_name, l );
    if ( c )
       return( c );
    }
 return c;
}
#endif

int FileListArray::findFirst( CWnd *pPar, int type, int fld )
{
#ifdef PRO
 char *t ;

 if ( type == NON_GRA )
    t = "Text Files";
 else if ( type == GRA_F )
    t = "Graphic Files";
 else if ( type == GRIDFX )
    t = "Grid Files";
 else
    t = "All Files";
 
 CFileNameDlg fndg(pPar);
 fndg.m_bFind=TRUE;
 fndg.SetData(fnd); 
 if ( fndg.DoModal() != IDOK )
 	return( -1 );
 else { 
    fndg.GetData(fnd);
	return( findCont( type, 0, fld ) );
	}
#else
 return( 0 );
#endif
}

int FileListArray::findCont( int type, int start, int fld )
{
#ifdef PRO
 CPtrArray *ar;
 if ( start >= fileCount(type) )
	alert_box("", "No More To Find" );
 ar = arraygroup.get(type, fldcheck(fld)).ar;
 XPFILE_DB *pt =(XPFILE_DB *) (*ar)[start];
 if ( pt == NULL ) {
    alert_box("", "No More To Find" );
    return( -1 );
    }
 if ( compare( &fnd, pt, type )==0 )
    return( start );
 while ( ( pt = (XPFILE_DB *)(*ar)[++start]) != NULL ) {
       if ( !compare( &fnd, pt, type  ) )
	   return( start );
       }
 alert_box("", "No More To Find");
#endif
 return( -1 );
}

