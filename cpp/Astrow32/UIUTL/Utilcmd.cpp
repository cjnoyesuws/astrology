#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "asframe.hpp"
#include "msg.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "database.hpp"
#include "filelst.hpp"
#include "astromn.h"

extern void index_db( char * );
extern void make_pop( char * );
extern void merge_index_db( char * );


AstroAppFrame::utilCmd( zCommandEvt *e )
{
 switch( e->cmd() ) {
       case IDM_UIBIRTH :
	    index_db( "BIRTH" );
	    break;
       case IDM_UILOCAT :
	    index_db( "LOC" );
	    break;
       case IDM_UIALLD :
	    index_db( "ALL" );
	    break;
       case IDM_UPBIRTH :
	    make_pop( "BIRTH" );
	    break;
       case IDM_UPLOCAT :
	    make_pop( "LOC" );
	    break;
       case IDM_UPALLD :
	    make_pop( "ALL" );
	    break;
       case IDM_UMBIRTH :
	    merge_index_db( "BIRTH" );
	    break;
       case IDM_UMLOCAT :
	    merge_index_db( "LOC" );
	    break;
#ifndef _QDTRAN_
       case IDM_USORT :
	    AstFileList.sortFiles();
	    if ( pTextFrame != NULL )
	       pTextFrame->setDirty();
	    if ( pGraphFrame != NULL )
	       pGraphFrame->setDirty();
	    break;
       case IDM_UBLDFLST :
	    AstFileList.scanFiles();
	    break;
#endif
       default :
	    return( 0 );
	    break;
       }
 return( 1 );
}
