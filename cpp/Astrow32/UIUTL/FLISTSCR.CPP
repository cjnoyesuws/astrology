#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "charcons.h"
#include "flistscr.hpp"
#include "astromn.h"
#include "asframe.hpp"
#include "menuutl.hpp"
#include "basedcs.h"
#include "helpid.h"
#include "inifile.hpp"
#include "resstr.hpp"

static int BCS flstflds[] = { IDM_FSAVEFLST, IDM_FSAVEASFLST,
  IDM_FEXPORT, IDM_FVIEW, IDM_FEDIT, IDM_FKILL, IDM_FPRINT,
  IDM_EUNDO, IDM_ECUT, IDM_ECOPY, IDM_EPASTE, IDM_FCLOSE,
  IDM_EDEL, IDM_EFIND, IDM_ENEXT, IDM_UPARSE, IDM_UBLDFLST,
  IDM_UCLRSEL, IDM_UEDIT, IDM_USORT, IDM_UARC, IDM_UXARC,
  IDM_FNEWCFL, IDM_FNEWCPG, IDM_FOPENCFL, IDM_FOPENCPG, 0 };

typedef int (zEvH::*KeyProc)(zKeyEvt*);

int FileListPane::update()
{
 updateScroller();
 if (pFla->getCount(type)-nTopItem <= yCnt ) {
    draw(0);
    return( 1 );
    }
 return( 0 );
}

int FileListPane::drawHeader()
{
 zDisplay *cv = canvas();
 zRect r( 0, 0, cxWid, cyDepth );
 cv->pushBrush(pbrNorm);
 cv->textColor(GetSysColor(COLOR_WINDOWTEXT) );
 cv->backColor(GetSysColor(COLOR_WINDOW) );
 cv->text( cxLeft, cyStart, CResStr(_FCS_NAME)/*"Name:"*/ );
 cv->text( cxLeft, cyStart+cyChar, CResStr(_FCS_COMMENT)/*"Comments:"*/ );
#ifdef PRO 
 cv->text( cxWidFlags, cyStart, "P" );
 cv->text( cxWidFlags, cyStart+cyChar, "C" );
#endif
 cv->text( cxWidName, cyStart, CResStr(_FCS_FILENAME)/*"File Name:"*/ );
 cv->text( cxWidName, cyStart+cyChar, CResStr(_FCS_TYPE)/*"Type:"*/ );
 zPen *ppnHead = new zPen(zColor(COLOR_WINDOWTEXT),Solid,3);
 cv->pushPen(ppnHead);
 cv->moveTo( cxStart, cyRule + cyStart);
 cv->lineTo( cxClient-cxStart, cyRule + cyStart);
 cv->popPen();
 delete ppnHead;
 cv->popBrush();
 return(1);
}

int FileListPane::size( zSizeEvt *e)
{
 canvas()->setDirty();
 cxClient=e->width();
 cyClient=e->height();
 yCnt = ( cyClient-(cyStart+cyDepth) )/cyDepth;
 updateScroller();
 return(1);
}

int FileListPane::drawItem( FILE_DB *i, int y, int mrk)
{
 if ( i == NULL )
    return( 0 );
 zDisplay *cv = canvas();
 zRect r(0, y, cxClient, y+cyDepth );
  
 if ( !mrk ) {
    cv->pushBrush(pbrNorm);
    cv->fill(r, pbrNorm);
    cv->textColor(GetSysColor(COLOR_WINDOWTEXT) );
    cv->backColor(GetSysColor(COLOR_WINDOW) );
    }
 else {
    cv->pushBrush(pbrSel);
    cv->fill(r, pbrSel);
    cv->textColor(GetSysColor(COLOR_HIGHLIGHTTEXT) );
    cv->backColor(GetSysColor(COLOR_HIGHLIGHT) );
    }
 cv->text( cxLeft, cyStart+y, i->name );
 cv->text( cxLeft, cyStart+cyChar+y, i->comment );
#ifdef PRO
 cv->text( cxWidFlags, cyStart+y, (i->has_cover?"X":" ") );
 cv->text( cxWidFlags, cyStart+cyChar+y, (i->has_comments?"X":" "));
#endif
 cv->text( cxWidName, cyStart+y, i->file_name );
 cv->text( cxWidName, cyStart+cyChar+y, types(i->type) );
 if ( i->selected )
    cv->bitmap(pbmChk, zPoint(cxStart,cyStart+y) );
 if ( i->type > LAST_NON_GRAPH )
    cv->bitmap(pbmGra, zPoint(cxWid,cyStart+y) );
 else
    cv->bitmap(pbmTxt, zPoint(cxWid,cyStart+y) );
 if ( !mrk )
    cv->pushPen( ppnNorm );
 else
    cv->pushPen( ppnSel );
 cv->moveTo( cxStart, cyRule + y);
 cv->lineTo( cxClient-cxStart, cyRule + y );
 cv->popPen();
 cv->popBrush();
 return(1);
}

void FileListPane::setMetrics()
{
 if ( pbrNorm != NULL ) 
    delete pbrNorm;
 pbrNorm=new zBrush(zColor(GetSysColor(COLOR_WINDOW)) );
    
 if ( pbrSel != NULL ) 
    delete pbrSel;
 pbrSel=new zBrush(zColor(GetSysColor(COLOR_HIGHLIGHT)) );
    
 if ( ppnNorm != NULL ) 
    delete ppnNorm;
 ppnNorm = new zPen(zColor(GetSysColor(COLOR_WINDOWTEXT)),Solid,0);
 if ( ppnSel != NULL ) 
    delete ppnSel;
 ppnSel = new zPen(zColor(GetSysColor(COLOR_HIGHLIGHTTEXT)),Solid,0);
 
 if ( pFnt != NULL ) 
    delete pFnt;
 pFnt = new zFont( zString("Helv"),zPrPoint(0,70), FW_BOLD );
 /* pFnt = new zFont( SystemVariable ); */
 canvas()->lock();
 canvas()->pushFont(pFnt);
 zFontInfo *pFi = new zFontInfo( canvas() );
 cxChar = pFi->width();
 cyChar = pFi->height()+pFi->externLead();
 cxStart = cxChar / 3;
 cxLeft = cxChar * 4;
 cyRule = cyChar + cyChar + (cyChar/3)+1;
 cyDepth = cyRule+1;
 cxWidFlags = ((NAME_WIDTH -2) * cxChar)+cxLeft+cxStart;
 cxWidName = cxWidFlags + (4 * cxChar);
 cxWid = cxWidFlags+(20 * cxChar)+cxStart;
 delete pFi;
 canvas()->popFont();
 canvas()->unlock();
 zRect r;
 getInterior(r);
 cxClient = r.width();
 cyClient = r.height();
 yCnt = ( cyClient-(cyStart+cyDepth) )/cyDepth;
 if ( pbmChk != NULL )
    delete pbmChk;
 pbmChk = new zBitmap(BmpCheck);
 if ( pbmTxt != NULL )
    delete pbmTxt;
 pbmTxt = new zBitmap(zResId("CTEXT") );
 if ( pbmGra != NULL )
    delete pbmGra;
 pbmGra = new zBitmap(zResId("CGLYPH") );
 dblclkTime=GetDoubleClickTime();
 updateScroller();
}

void FileListPane::hideCursor(FILE_DB *fdpx, int ofs)
{
 FILE_DB *fdp;

 if ( fdpx == NULL )
    fdp = pFla->topPlus(yCursor, type);
 else
    fdp = fdpx;
 if ( fdp == NULL )
    return;
 int y = ((yCursor-(scrollBarVert()->pos()-1)+ofs)*cyDepth)+cyStart+cyDepth;
 canvas()->lock();
 canvas()->pushFont(pFnt);
 drawItem( fdp, y, 0 );
 canvas()->popFont();
 canvas()->unlock();
 }

void FileListPane::showCursor(FILE_DB *fdpx, int ofs)
{
 FILE_DB huge *fdp;

 if ( fdpx == NULL )
    fdp = pFla->topPlus(yCursor, type);
 else
    fdp = fdpx;
 if ( fdp == NULL )
    return;
 int y = ((yCursor-(scrollBarVert()->pos()-1)+ofs)*cyDepth)+cyStart+cyDepth;
 canvas()->lock();
 canvas()->pushFont(pFnt);
 drawItem( fdp, y, 1 );
 canvas()->popFont();
 canvas()->unlock();
 }

int FileListPane::scroll( zEvent *e )
{
 switch( e->parm1() ) {
       case SB_TOP:
       case SB_BOTTOM:
       case SB_PAGEUP:
       case SB_PAGEDOWN:
       case SB_THUMBPOSITION:
	    {
	    if ( e->Msg != 0 ) {
	       zScrollInfoVert *pSivx = scrollBarVert();
	       yCursor = pSivx->pos()-1;
	       if ( yCursor < 0 )
		  yCursor = 0;
               }
	    canvas()->setDirty();
	    }
	    break;
       case SB_LINEDOWN:
	    {
            zScrollInfoVert *pSivd = scrollBarVert();
	    if ( pSivd->pos() <= pSivd->limits().hi() ) {
	       if ( e->Msg != 0 ) {
		  hideCursor(NULL,1);
		  yCursor++;
		  }
	       zRect x(0, cyStart+cyDepth, cxClient, cyClient);
	       ScrollWindow( *this, 0, -cyDepth, NULL,(LPRECT) &x );
	       nTopItem++;
	       showCursor();
               }
	    }
	    break;
       case SB_LINEUP:
	    {
	    zScrollInfoVert *pSivu = scrollBarVert();
	    if ( pSivu->pos() > 1 ) {
	       if ( e->Msg != 0 ) {
		  hideCursor(NULL,-1);
		  yCursor--;
		  if ( yCursor==-1)
		     yCursor = 0;
		  }
	       nTopItem--;
	       zRect y(0, cyStart+cyDepth, cxClient, cyClient);
	       ScrollWindow( *this, 0, cyDepth, NULL,(LPRECT) &y );
	       showCursor();
	       }
	    }
            break;
       default :
	    return( 1 );
            break;
	    }
 return( 1 );
}


typedef int (zEvH::*MouseClickProc)(zMouseClickEvt*);

int FileListPane::kbhnd(zKeyEvt *e)
{
 zScrollInfoVert *pSiv = scrollBarVert();
 zEvent ev;
 int p;
 
 if ((HWND)*this != GetFocus())
    return( 0 );
 ev.Msg = 0;
 switch( e->parm1() ) {
       case VK_PRIOR:
	    if ( pSiv->pos() > pSiv->pageDelta()+1 ) {
	       ev.wParam = SB_PAGEUP;
	       pSiv->pos(pSiv->pos()-pSiv->pageDelta());
	       yCursor -= pSiv->pageDelta();
	       if ( yCursor < 0 )
		     yCursor = 0;

	       return( scroll( &ev ) );
	       }
	    break;
       case VK_NEXT:
	    if ( pSiv->pos() + pSiv->pageDelta() <=
		       pSiv->limits().hi() ) {
	       ev.wParam = SB_PAGEDOWN;
	       pSiv->pos(pSiv->pos()+pSiv->pageDelta());
	       yCursor += pSiv->pageDelta();
	       if (yCursor >= pSiv->limits().hi()) 
                  yCursor= pSiv->limits().hi()-1; 
               return( scroll( &ev ) );                        
	       }
	    break;
       case VK_UP:
	    if ( yCursor > nTopItem ) {
	       hideCursor();
	       yCursor--;
	       if ( yCursor==-1)
		  yCursor = 0;
	       showCursor();
	       return( 1 );
	       }
	    else if ( (p=pSiv->pos()) > 1 ) {
	       ev.wParam = SB_LINEUP;
               hideCursor();
	       yCursor--;
	       if ( yCursor==-1)
		  yCursor = 0;
	       pSiv->pos(p-1);
	       return( scroll( &ev ) );
	       }
	    break;
       case VK_DOWN:
	    p=pSiv->pos();
	    if ( p < pSiv->limits().hi()-1 ) {
	       if ( yCursor-nTopItem < yCnt && yCursor <
		     pSiv->limits().hi()-1 ) {
		  hideCursor();
		  yCursor++;
		  showCursor();
		  return( 1 );
		  }
	       else if ( yCursor < pSiv->limits().hi()-1 ) {
		  ev.wParam = SB_LINEDOWN;
		  hideCursor();
		  yCursor++;
		  pSiv->pos(p+1);
		  return( scroll( &ev ) );
		  }
	       }
	    break;
       case VK_DELETE:
	    ev.Msg = WM_COMMAND;
	    ev.wParam = IDM_EDEL;
	    return(doCommand((zCommandEvt *)&ev));
	    break;
       case VK_HOME:
	    yCursor = 0;
	    ev.wParam = SB_TOP;
	    pSiv->pos(1);
	    return( scroll( &ev ) );
	    break;
       case VK_END:
	    ev.wParam = SB_BOTTOM;
	    yCursor= pSiv->limits().hi()-1;
	    pSiv->pos(pSiv->limits().hi()+1);
	    return( scroll( &ev ) );
	    break;
       case VK_SPACE:
	    ev.lParam = MAKELONG(0,cyDepth+cyStart+cyStart+
		    ((yCursor-nTopItem)*cyDepth) );
            ev.wParam=MK_LBUTTON;
            mouseButtonDown((zMouseClickEvt *)&ev);
	    return( 1 );
	    break;
       case VK_RETURN:
	    {
	    FILE_DB *fdp = pFla->topPlus(yCursor, type);
	    if ( fdp != NULL ) {
               dofunc(fdp);
	       }
	    }
	    return( 1 );
            break;
       case VK_F1:
	    WinHelp(*this, set_path("ASTROW.HLP", HELP_F ),
					    HELP_CONTEXT, HELPID_FLIST );
	    break;
       default:
            return( 0 );
            break;
       }
 return(0);
}


int FileListPane::mouseButtonDown( zMouseClickEvt *e )
{
 unsigned char sel;
 FILE_DB *fdpx;
 zPoint p;
 int i, y;
 static unsigned long lastClk;
 unsigned long t;

 if ( e->isButtonDown(1) ) {
    t=GetCurrentTime();
    if (lastClk+dblclkTime>=t) {
       FILE_DB *fdpx = pFla->topPlus(yCursor, type);
       if ( fdpx != NULL && fdpx == curMrk ) {
	  if ( curMrk->selected )
	     fdpx->selected = 0;
	  else
	     fdpx->selected = 1;
	  }
       else if ( fdpx == NULL )
	  return( 1 );
       curMrk = fdpx;
       if ( curMrk != NULL ) {
	  dofunc(curMrk);
	  }
       lastClk = t;
       return( 1 );
       }
    else {
       if ( curMrk != NULL )
	  hideCursor(curMrk);
       else {
	  yCursor = nTopItem;
	  curMrk = pFla->topPlus(nTopItem, type);
	  hideCursor(curMrk);
          }
       p = e->pos();
       y = ((p.y()-(cyDepth+cyStart))/cyDepth);
       i = y + nTopItem;
       yCursor = i;
       fdpx = pFla->topPlus(i, type);
       curMrk = fdpx;
       lastClk = t;
       if ( fdpx == NULL ) {
	  yCursor = pFla->iCursor(pFla->iBottom(type),type);
	  if ( yCursor == -1 )
	     yCursor = 0;
	  fdpx = pFla->bottom(type);
	  curMrk = fdpx;
	  }
       if ( fdpx == NULL )
	  return( 1 );
       if ( fdpx->selected )
	  fdpx->selected = 0;
       else
	  fdpx->selected = 1;
       showCursor(curMrk);
       }
    }
   return( 1 );
}

void FileListPane::updateScroller()
{
 zScrollInfoVert *pSiv = scrollBarVert();
 if ( pSiv == NULL )
    return;
 pSiv->limits(zRange(1,pFla->getCount(type)));
 pSiv->moveDelta(1);
 pSiv->pageDelta((cyClient-(cyDepth+cyStart))/cyDepth);
 pSiv->pos(nTopItem+1);
}

int FileListPane::draw( zDrawEvt *e )
{
 zRect r;

 pFla->check();
 if ( e != NULL )
    canvas()->getDirty(r);
 else
    getInterior(r);
 canvas()->lock();
 canvas()->pushFont(pFnt);
 nTopItem = scrollBarVert()->pos()-1;
 if ( nTopItem < 0 ) {
    updateScroller();
    yCursor = 0;
    nTopItem = 0;
    scrollBarVert()->pos(1);
    }
 int y = cyDepth+cyStart;
 if ( r.top() <= y )
    drawHeader();
 int i;
 if ( r.top() < y )
    i = nTopItem;
 else
    i = nTopItem + ( (r.top()-y)/cyDepth );
 y += ((i - nTopItem) * cyDepth);
 FileDBItr fdi(pFla->topPlus(i, type), pFla->iTopPlus(i,type),
	 pFla->getCount());
 FILE_DB *pFd = fdi.at();
 do {
    if ( pFd == NULL )
       break;
    drawItem(pFd,y,i==yCursor?1:0);
    y += cyDepth;
    i++;
    pFd = ++fdi;
    while ( pFd != NULL && isDelFile(pFd) )
	  pFd = ++fdi;
    if ( pFd == NULL )
       break;
    if ( type != ALL_F ) {
       while ( pFd != NULL && type == GRA_F &&
		 ( isTextFile(pFd) || isDelFile(pFd) ) )
	     pFd = ++fdi;
       while ( pFd != NULL && type == NON_GRA &&
		 ( isGraphFile(pFd) || isDelFile(pFd) ) )
	     pFd = ++fdi;
       }
    } while ( y < r.bottom() );
 canvas()->popFont();
 canvas()->unlock();
 return(1);
}


FileListPane::~FileListPane()
{
 if ( pbrNorm != NULL )
    delete pbrNorm;
 if ( pbrSel != NULL )
    delete pbrSel;
 if ( ppnNorm != NULL )
    delete ppnNorm;
 if ( ppnSel != NULL )
    delete ppnSel;
 if ( pFnt != NULL )
    delete pFnt;
 if ( pbmGra != NULL )
    delete pbmGra;
 if ( pbmTxt != NULL )
    delete pbmTxt;
 if ( pbmChk != NULL )
    delete pbmChk;
 delete pxText;
 delete pxGraph;
 if ( pFla != NULL )
    pFla->release();
 removeHandler(this, (NotifyProc)(KeyProc)&FileListPane::kbhnd, WM_KEYDOWN);
}

FileListPane::FileListPane(FileListArray *a, int t, zWindow *w) : zPane(w,new zSizeWithParent,zSCROLLV|CS_DBLCLKS)
{
 curMrk = 0;
 pFla = a;
 type = t;
 yCursor = 0;
 setMetrics();
 if ( a != NULL )
    a->check();
 pxText = new zExchangeFmt("AST*NON_GRA");
 pxGraph = new zExchangeFmt("AST*GRA_F");
 setHandler(this, (NotifyProc)(KeyProc)&FileListPane::kbhnd, WM_KEYDOWN);
}

void FileListPane::setupEditMenu()
{
 if ( pFla->getCount(type) )
    enableMenuItems(pMenu, flstflds );
 if ( !( cut_at || ins_at ) )
    disableMenuItems(pMenu, IDM_EUNDO );
 if ( (cut_at || ((type==GRA_F||type==ALL_F)&&pClip->isUserDataAvail(*pxGraph) )
      || ((type==NON_GRA||type==ALL_F)&&pClip->isUserDataAvail(*pxText) ) ) )
    enableMenuItems(pMenu, IDM_EPASTE );
#ifndef PRO
 if (type == GRA_F )
    disableMenuItems(pMenu, IDM_FEXPORT );
#endif
}



int FileListFrame::focus(zFocusEvt *focEvt)
{
if ( (focEvt->gainFocus()) && (pane!=0) ) {
    pane->setupEditMenu();
    pane->setFocus();
    pane->pFla->check();
    pane->updateScroller();
    pane->canvas()->setDirty();
    }
/* else if (pane != 0)
    disableMenuItems( pane->pMenu, flstflds ); */
 return 0;
}


int FileListFrame::MDIActivate(zActivateEvt *actEvt)
{
 if ( (actEvt->active()) && (pane!=0) && actEvt->loParam()==(HWND)*this ) {
    pane->setupEditMenu();
    pane->setFocus();
    pane->pFla->check();
    pane->updateScroller();
#ifdef NEW
    ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, CResStr(_FCS_STATUS)/*"Double Click on any Item To View It, or Click to Select." */);
#endif
    }
 else if ( !actEvt->active() && pane!=0 && actEvt->hiParam()==(HWND)*this ) {
    disableMenuItems( pane->pMenu, flstflds );
#ifdef NEW
    ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, "");
#endif
    }
 return 0;
}


FileListFrame::FileListFrame(zFrameWin *pPar, FileListArray *a, int t, char *name)
	: zMDIChildFrame(pPar,new zSizer,zSTDFRAME, name )
{
 if ( GetPrivateProfileInt( "Windows", "ListMax", 0, APPNAME ))
    maximize(1);
 if ( a != NULL )
    a->read();
 if (t == GRA_F)
    setIcon(new zIcon(zResId("GraphList")));
 else if (t == NON_GRA)
    setIcon(new zIcon(zResId("TextList")));
 else
    setIcon(new zIcon(zResId("GraphTextList")));
 if ( a != NULL ) {
    pane=new FileListPane(a, t, this);
    pane->pClip = ((AstroAppFrame *)pPar)->getClipboard();
    pane->addVertScrollBar();
    pane->updateScroller();
    pane->pMenu = pPar->menu();
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_FEXPORT, IDM_FPRINT );
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_EUNDO, IDM_ENEXT );
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_UBLDFLST, IDM_UXARC );
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_UPARSE );
#ifdef NEW
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_FCLOSE );
#endif
#ifdef PRO
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_FNEWCPG, IDM_FNEWCFL );
    pane->pMenu->setCommand(pane,(CommandProc)&FileListPane::doCommand,
      IDM_FOPENCPG, IDM_FOPENCFL );
#endif
    pane->setupEditMenu();
    pane->show();
    }
 deleteOnClose(TRUE);
}

/*
void zApp::main()
{
   debugOn(1);
   theDirectories.getFromIni("TEST.INI");
   myFileList.setName("NASTFIL.LST");
   FileListFrame* pFListFrame=new FileListFrame(&myFileList, NON_GRA);
   pFListFrame->show();
   go();
   delete pFListFrame;
}
*/

