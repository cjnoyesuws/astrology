#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include <stdlib.h>
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "charcons.h"
#include "flistscr.hpp"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "virttext.hpp"
#include "fview.hpp"
#include "asdrawbs.hpp"
#include "graphdat.hpp"
#include "dib.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "grappane.hpp"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "coverdat.hpp"
#include "astromn.h"
#include "errors.fns"
#include "comment.hpp"
#include "asframe.hpp"
#include "archive.hpp"
#include "flistarc.hpp"
#include "inifile.hpp"
#include "resstr.hpp"

extern int doPrintFile( FILE_DB *ptr, zWindow *pPar );
extern int doSelPrintFiles(zWindow *pPar, FileListArray *fla );
extern int doConvText( zWindow *pPar, FILE_DB *pFd );
extern int doSelConvText(zWindow *pPar, FileListArray *fla );
extern int doPrintSelGraphFile(zWindow *pPar, FileListArray *fla );
extern void do_parse_file(FILE_DB *ptr);
extern int doEdit( zWindow *pPar, FILE_DB *pFd );
extern int doConvertSelGraphFile(zWindow *pPar, FileListArray *fla );
extern int doConvGraph( zWindow *pPar, FILE_DB *pFd );


int FileListPane::doCommand( zCommandEvt *e )
{
 int do_check;
 if ( (HWND)*this != GetFocus() )
    return( 0 );
 do_check =((AstroAppFrame *)app->rootWindow())->getAllCheck();
 FILE_DB *ptr = pFla->topPlus(yCursor, type);   
 if ( ptr == NULL && !pFla->fileCount() )
    ptr = pFla->fileDBptr();
 if ( ptr == NULL ) {
    alert_box("Error!", "Invalid File Selected!" );
    return( 1 );
    }
 switch( (unsigned int)e->cmd() ) {
       case IDM_FVIEW:
	   dofunc(ptr);
	   break;
#ifdef NEW
      case IDM_FCLOSE :
	   //PostMessage((HWND)(*this),WM_CLOSE,0,0L);
	   PostMessage((HWND)(*parent()),WM_CLOSE,0,0L);
	   break;
#endif
       case IDM_FPRINT:
	   if (pFla->selCount(type) && do_check ) {
	      if ( type == ALL_F || type == NON_GRA )
		 doSelPrintFiles(this, pFla );
	      if ( type == ALL_F || type == GRA_F )
		 doPrintSelGraphFile(this, pFla );
	      }
	   else {
	      if ( ptr != NULL ) {
		 if ( ptr->type < LAST_NON_GRAPH ) {
		    doPrintFile( ptr, this );
		    }
		 else {
		    //print graphic
		    AstGraphicsPane *agp = new AstGraphicsPane( ptr->file_name, this, USER_F );
		    agp->doPrint(e);
		    while ( app->tasks()->busy() )
			  app->tasks()->poll();
		    delete agp;
		    }
		 }
	      }
	   break;
#ifdef PRO
      case IDM_FEDIT:
	   {
	   if ( ptr != NULL ) {
	      if ( ptr->type < LAST_NON_GRAPH ) {
		 doEdit( this, pFla->topPlus(yCursor, type) );
		 }
	      else {
		 // save graphics file image.
		 alert_box( _FLC_ONLYTXTF /*"", "Only On Text Files!"*/ );
		 }
	      }
	   }
	   break;
#endif
      case IDM_FEXPORT:
	   if (pFla->selCount(type) && do_check ) {
	      if ( type == ALL_F || type == NON_GRA )
		 doSelConvText(this, pFla );
#ifdef PRO
	      if ( type == ALL_F || type == GRA_F )
		 doConvertSelGraphFile(this, pFla );
#else
	      else
		 alert_box( _FLC_ONLYTXTF /*"", "Only On Text Files!"*/ );
#endif
	      }
	   else {
	      if ( ptr != NULL ) {
		 if ( ptr->type < LAST_NON_GRAPH ) {
		    doConvText( this, ptr );
		    }
		 else {
#ifdef PRO
		    doConvGraph( this, ptr );
#else
		    alert_box( _FLC_ONLYTXTF /*"", "Only On Text Files!"*/ );
#endif
		    }
		 }
	      }
	   break;
      case IDM_ECOPY:
	   {
	   if ( ptr != NULL ) {
	      pClip->clear();
	      pClip->add(ptr,sizeof(FILE_DB),(ptr->type >= LAST_NON_GRAPH?*pxGraph:*pxText));
	      setupEditMenu();
	      cut_at = 0;
	      ins_at = 0;
	      }
	   }
	   break;
      case IDM_ECUT:
	   {
	   if ( ptr != NULL ) {
	      zMessage *mp = new zMessage( this, CResStr(_FLC_QUDEL)/*"Do You Want to Delete The File?"*/,
		     "ASTRO", MB_ICONQUESTION|MB_YESNOCANCEL );
	      if ( mp->isCancel() ) {
		 delete mp;
		 }
	      else if ( mp->isOk() ) {
		 cut_at = 0;
		 ins_at = 0;
		 pFla->doKillFile(ptr, this);
		 updateScroller();
		 canvas()->setDirty();
		 delete mp;
		 setupEditMenu();
		 }
	      else {
		 cut_at = ptr;
		 cut_buf = *cut_at;
		 ins_at = 0;
		 pClip->clear();
		 pClip->add(ptr,sizeof(FILE_DB),(ptr->type >= LAST_NON_GRAPH?*pxGraph:*pxText));
		 pFla->deleteEntry( cut_at );
		 updateScroller();
		 canvas()->setDirty();
		 setupEditMenu();
		 was_cut = 1;
		 delete mp;
		 }
	      }
	   }
	   break;
      case IDM_EDEL :
	   {
	   if ( ptr != NULL ) {
	      zMessage *xmp = new zMessage( this, CResStr(_FLC_QUDEL)/*"Do You Want to Delete The File?"*/,
		     "ASTRO", MB_ICONQUESTION|MB_YESNOCANCEL );
	      if ( xmp->isCancel() ) {
		 delete xmp;
		 }
	      else if ( xmp->isOk() ) {
		 cut_at = 0;
		 ins_at = 0;
		 setupEditMenu();
		 pFla->doKillFile(ptr, this);
		 updateScroller();
		 canvas()->setDirty();
		 delete xmp;
		 }
	      else {
		 cut_at = ptr;
		 ins_at = 0;
		 cut_buf = *cut_at;
		 setupEditMenu();
		 pFla->deleteEntry( ptr );
		 updateScroller();
		 canvas()->setDirty();
		 delete xmp;
		 was_cut = 1;
		 }
	      }
	   }
	   break;
      case IDM_EPASTE:
	   {
	   int do_upd = 0;
	   unsigned int len;
	   if ( cut_at ) {
	      if ( ptr != NULL ) {
		 pFla->addEntry(&cut_buf, ptr);
		 do_upd = 1;
		 }
	      }
	   else if ( ( type == GRA_F || type == ALL_F ) && pClip->isUserDataAvail(*pxGraph) ) {
	      FILE_DB *pg = (FILE_DB *)pClip->getUserData(len,*pxGraph);
	      pFla->addEntry(pg, ptr);
	      do_upd = 1;
	      delete pg;
	      }
	   else if ( ( type == NON_GRA || type == ALL_F ) && pClip->isUserDataAvail(*pxText) ) {
	      FILE_DB *pt = (FILE_DB *)pClip->getUserData(len,*pxText);
	      pFla->addEntry(pt, ptr);
	      do_upd = 1;
	      delete pt;
	      }
	   setupEditMenu();
	   updateScroller();
	   canvas()->setDirty();
	   was_cut = 0;
	   cut_at = 0;
	   ins_at = ptr;
	   break;
	   }
      case IDM_EUNDO:
	   if ( cut_at && was_cut ) {
	      pFla->addEntry(&cut_buf, cut_at);
	      updateScroller();
	      canvas()->setDirty();
	      setupEditMenu();
	      }
	   else if ( ins_at ) {
	      pFla->deleteEntry( ins_at );
	      updateScroller();
	      canvas()->setDirty();
	      setupEditMenu();
	      }
	   break;
      case IDM_FKILL :
	   if (pFla->selCount(type) && do_check ) {
	      pFla->killSelectedFiles(this, type);
	      updateScroller();
	      canvas()->setDirty();
	      }
	   else {
	      if ( ptr != NULL ) {
		 pFla->doKillFile(ptr, this);
		 updateScroller();
		 canvas()->setDirty();
		 }
	      }
	   setupEditMenu();
	   break;
      case IDM_UEDIT :
	   if ( ptr != NULL ) {
	      pFla->changeEntry(ptr, this);
	      canvas()->setDirty();
	      }
	   break;
      case IDM_USORT :
	   pFla->sortFiles();
	   canvas()->setDirty();
	   break;
      case IDM_UBLDFLST :
	   pFla->scanFiles();
	   updateScroller();
	   canvas()->setDirty();
	   break;
      case IDM_UCLRSEL :
	   pFla->clearSel(type);
	   canvas()->setDirty();
	   break;
      case IDM_UPARSE :
	   do_parse_file(ptr);
	   break;
#ifdef PRO
      case IDM_EFIND :
      case IDM_ENEXT :
	   int pos;
	   if ( e->cmd() == IDM_EFIND )
	      pos = pFla->findFirst( this, type );
	   else
	      pos = pFla->findCont( type, yCursor+1 );
	   if ( pos != -1 ) {
	      pos = pFla->iCursor( pos+1, type );
	      if ( pos-nTopItem < yCnt && pos-nTopItem >= 0 ) {
		 hideCursor();
		 yCursor = pos;
		 showCursor();
		 }
	      else {
		 yCursor = pos;
		 scrollBarVert()->pos(yCursor+1);
		 canvas()->setDirty();
		 }
	      }
	   break;
      case IDM_FNEWCFL :
      case IDM_FOPENCFL :
	   {
	   if ( ptr != NULL ) {
	      if ( type != GRA_F && ptr->type < LAST_NON_GRAPH ) {
		 CommentEditor *ce = new CommentEditor(app->rootWindow(), ptr);
		 ce->show();
		 ce->setFocus();
		 }
	      else
		 alert_box("","Only On Text Files!" );
	      }
	   }
	   break;
      case IDM_FNEWCPG :
      case IDM_FOPENCPG :
	   {
	   if ( ptr != NULL ) {
	      if ( type != GRA_F && ptr->type < LAST_NON_GRAPH ) {
		 CoverPageEditor *cpe = new
		     CoverPageEditor( this, ptr );
		 delete cpe;
		 canvas()->setDirty();
		 }
	      else
		 alert_box( _FLC_ONLYTXTF /*"", "Only On Text Files!"*/ );
		 }
	   }
	   break;
      case IDM_UARC :
	   {
	   FileListArchiver *fla = new FileListArchiver(pFla, type, 1);
	   fla->archive(this);
	   delete fla;
	   }
	   break;
      case IDM_UXARC :
	   {
	   FileListArchiver *xfla = new FileListArchiver(pFla, type, 0);
	   xfla->deArchive(this);
	   delete xfla;
	   }
	   break;
#endif
      default :
	   return( 0 );
	   break;
      }
return( 1 );
}

void FileListPane::dofunc( FILE_DB *p )
{
 static int runs;
 if ( p == NULL )
    return;
 if ( p->type < LAST_NON_GRAPH ) {
    FileViewFrame *fv = new FileViewFrame(app->rootWindow(),
		       p->file_name, USER_F);
    fv->show();
    fv->setFocus();
    }
 else {
    AstGraphicsFrame *agf = new AstGraphicsFrame(app->rootWindow(), p->file_name, USER_F);
    agf->show();
    agf->setFocus();
    }
#ifdef DEMO
#ifdef DELUXE 
 runs++;
 if (runs > 6 )
    alert_box("","How About Buying ASTRO For Windows?" );
#endif
#endif

}

int FileListFrame::kill( zEvent *e )
{                                     
 zMessage *mp = new zMessage(this, CResStr(_FLC_QUCLOSE)/*"Are You Sure You Want To Close This Window..."
    "If You Choose \'Yes\' You Won't Be Able to View/Print/Export charts."
    " If you Choose \'Yes\' You Can Find This Window in the Windows Menu"*/,
	CResStr(pane->getType() == GRA_F?_GRAPHSCRNAME:_TEXTSCRNAME)/*"Graphic Files List":"Text Reports List"*/, 
	MB_OK|MB_ICONINFORMATION|MB_YESNOCANCEL );
    if ( mp->isNo() || mp->isCancel() ) {
       delete mp;
       return( 1 );
       }
 delete mp;          
    
 
 zMenu *pm = ((zMDIAppFrame *)app->rootWindow())->MDImenu();
 if ( pane->getType() == GRA_F ) {
    pm->insertItem(IDM_WGRAPLST, 3, CResStr(_FLC_WGFILES)/*"&Graphic Files"*/ );
    pm->update();
    ((AstroAppFrame *)app->rootWindow())->pGraphFrame = 0;
    }
 else if ( pane->getType() == NON_GRA ) {
    pm->insertItem(IDM_WTEXTLST, 3, CResStr(_FLC_WTFILES)/*"T&ext Reports"*/ );
    pm->update();
    ((AstroAppFrame *)app->rootWindow())->pTextFrame = 0;
    }
 pane->pMenu->removeCommand(pane,(CommandProc)&FileListPane::doCommand);
 return( 0 );
}




