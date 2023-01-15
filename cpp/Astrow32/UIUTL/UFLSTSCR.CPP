#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#ifdef PRO
#include <intpack\zip.hpp>
#endif
#endif
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "charcons.h"
#include "flistscr.hpp"
#include "uflstscr.hpp"
#include "astromn.h"
#include "asframe.hpp"
#include "menuutl.hpp"
#include "resstr.hpp"


UserFileListPane::~UserFileListPane()
{
 pFla->release();
 delete pFla;
 pFla = NULL;
}

UserFileListPane::UserFileListPane(zWindow *w, char *name) : FileListPane(new FileListArray(10), ALL_F, w)
{
 strcpy( fname, name );
 pFla->setName(name, -1 );
 if ( strlen( name ) ) {
    pFla->inMem(0);
    pFla->read();
    }
 pFla->inMem(1);
}

void UserFileListPane::setupEditMenu()
{
 FileListPane::setupEditMenu();
}

int UserFileListFrame::MDIActivate(zActivateEvt *actEvt)
{
 static int uflitm[] = {IDM_FSAVEFLST, IDM_FSAVEASFLST, 0 };
 if ( (actEvt->active()) && (pane!=0) )
    enableMenuItems(pane->pMenu, uflitm);
 else if ( (!actEvt->active()) && (pane!=0) )
    disableMenuItems(pane->pMenu, uflitm);

 return( FileListFrame::MDIActivate(actEvt) );
}


UserFileListFrame::UserFileListFrame(zFrameWin *pPar, char *name)
	: FileListFrame(pPar, NULL, -1, (!strlen(name)?"UNTITLED":name))
{
 pane=new UserFileListPane(this, name);
 pane->pClip = ((AstroAppFrame *)pPar)->getClipboard();
 pane->addVertScrollBar();
 pane->updateScroller();
 pane->pMenu = pPar->menu();
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FVIEW, IDM_FPRINT );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_EUNDO, IDM_ENEXT );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_UBLDFLST, IDM_USORT );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FOPENFLST );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_UPARSE );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FNEWCPG, IDM_FNEWCFL );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FOPENCPG, IDM_FOPENCFL );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FSAVEFLST );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FSAVEASFLST );
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FEXPORT );
#ifdef NEW
 pane->pMenu->setCommand(pane,(CommandProc)&UserFileListPane::doCommand,
   IDM_FCLOSE );
#endif
 pane->setupEditMenu();
 pane->show();
}


int UserFileListPane::doCommand( zCommandEvt *e )
{
 static char *types[] = { "Astro File Lists (*.AFL)","*.AFL",
		       "All Files (*.*)", "*.*", 0, 0 };

 if ( (HWND)*this != GetFocus() )
    return( 0 );
 FILE_DB *ptr = pFla->topPlus(yCursor, ALL_F);
 switch( e->cmd() ) {
      case IDM_FOPENFLST :
	   {
	   if ( !strlen( fname ) )
	      strcpy( fname, "USER.AFL" );
	   zFileOpenForm *fof = new zFileOpenForm( this,
		 CResStr(_UFL_OAFL)/*"Open Astro File List."*/, fname, types );
	      if ( !fof->completed() ) {
		 delete fof;
		 return( 1 );
		 }
	   strcpy( fname, fof->name() );
	   delete fof;
	   ((zFrameWin *)parent())->caption(fname);
	   pFla->setName( fname, -1 );
	   pFla->inMem(0);
	   pFla->read();
	   canvas()->setDirty();
	   }
	   break;
      case IDM_FSAVEFLST :
      case IDM_FSAVEASFLST :
	   {
	   if ( e->cmd() == IDM_FSAVEASFLST || !strlen( fname )
		  || !strcmpi(fname, "UNTITLED") ) {
	      if ( !strlen( fname ) )
		 strcpy( fname, "USER.AFL" );
	      zFileSaveAsForm *fsaf = new zFileSaveAsForm( this,
		 CResStr(_UFL_SAFLA)/*"Save Astro File List As."*/, fname, types );
	      if ( !fsaf->completed() ) {
		 delete fsaf;
		 return( 1 );
		 }
	      strcpy( fname, fsaf->name() );
	      delete fsaf;
	      ((zFrameWin *)parent())->caption(fname);
	      pFla->setName( fname, -1 );
	      }
	   pFla->write();
	   }
	   break;
      default :
	   return( FileListPane::doCommand( e ) );
	   break;
      }
 return( 1 );
}


int UserFileListFrame::kill( zEvent *e )
{
 if ( pane->pFla->dirty() ) {
    zMessage *mp = new zMessage(this, CResStr(_UFL_FLQUCL)/*"File List Has Changed, Ok to Close?"*/,
	CResStr(_UFL_UFLT)/*"User File List"*/, MB_OK|MB_ICONINFORMATION|MB_YESNOCANCEL );
    if ( mp->isNo() || mp->isCancel() ) {
       delete mp;
       return( 1 );
       }
    if ( mp->isYes() ) {
       pane->pMenu->removeCommand(pane,(CommandProc)&UserFileListPane::doCommand );
       delete mp;
       return( 0 );
       }
    }
 pane->pMenu->removeCommand(pane,(CommandProc)&UserFileListPane::doCommand );
 return( 0 );
}

