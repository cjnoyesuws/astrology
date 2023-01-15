// astroflistView.cpp : implementation of the CAstroflistView class
//

#include "stdafx.h"
#include "astrow.h"
#include "afxcoll.h"
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "charcons.h"
#include "filelst.hpp"
#include "astroflistDoc.h"
#include "astroflistView.h"
#include "direc.hpp"
#include "directories.h"
#include "errors.fns"
#include <io.h>
#include "archive.hpp"
#include "flistarc.hpp"

#ifdef PRO
#include "rtffuncs.h"
#include "Coverdat.hpp"
#include "CoverPage.h"
#include "CommentEd.h"
#include "chartsearch.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int fAllChecked;

extern int doConvText( CWnd *pPar, XPFILE_DB *pFd );
extern int doSelConvText(CWnd *pPar, FileListArray *fla, int type );
extern int doEdit( CWnd *pPar, XPFILE_DB *pFd );
extern int doEdit( CWnd *pPar, FileListArray *fla, int type );
extern void do_parse_file( XPFILE_DB *pFd );
/////////////////////////////////////////////////////////////////////////////
// CAstroflistView

IMPLEMENT_DYNCREATE(CAstroflistView, CView)

BEGIN_MESSAGE_MAP(CAstroflistView, CView)
	//{{AFX_MSG_MAP(CAstroflistView)
	ON_COMMAND(ID_FILE_VIEW, OnFileView)
	ON_UPDATE_COMMAND_UI(ID_FILE_VIEW, OnUpdateFileView)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(ID_FILE_KILL, OnFileKill)
	ON_UPDATE_COMMAND_UI(ID_FILE_KILL, OnUpdateFileKill)
	ON_COMMAND(ID_OPTIONS_ALLCHECK, OnOptionsAllcheck)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALLCHECK, OnUpdateOptionsAllcheck)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_UTILITIES_CLEARSELECTION, OnUtilitiesClearselection)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_CLEARSELECTION, OnUpdateUtilitiesClearselection)
	ON_COMMAND(ID_UTILITIES_EDITENTRY, OnUtilitiesEditentry)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_EDITENTRY, OnUpdateUtilitiesEditentry)
	ON_COMMAND(ID_UTILITIES_SORT, OnUtilitiesSort)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_SORT, OnUpdateUtilitiesSort)
	ON_COMMAND(ID_UTILITIESREADFILEDATA, OnUtilitiesreadfiledata)
	ON_UPDATE_COMMAND_UI(ID_UTILITIESREADFILEDATA, OnUpdateUtilitiesreadfiledata)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_WM_SIZE()
	ON_COMMAND(ID_OPTIONS_DIRECTORIES, OnOptionsDirectories)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DIRECTORIES, OnUpdateOptionsDirectories)
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_UTILITIES_REBUILDFLIST, OnUtilitiesRebuildflist)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_REBUILDFLIST, OnUpdateUtilitiesRebuildflist)
	ON_COMMAND(ID_FILE_NEW_COMMENTFILE, OnFileNewCommentfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW_COMMENTFILE, OnUpdateFileNewCommentfile)
	ON_COMMAND(ID_FILE_NEW_COVERPAGE, OnFileNewCoverpage)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW_COVERPAGE, OnUpdateFileNewCoverpage)
	ON_COMMAND(ID_FILE_OPEN_COMMENTFILE, OnFileOpenCommentfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_COMMENTFILE, OnUpdateFileOpenCommentfile)
	ON_COMMAND(ID_FILE_OPEN_COVERPAGE, OnFileNewCoverpage)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN_COVERPAGE, OnUpdateFileNewCoverpage)
	ON_COMMAND(ID_UTILITIES_ARCHIVECHARTS, OnUtilitiesArchivecharts)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_ARCHIVECHARTS, OnUpdateUtilitiesArchivecharts)
	ON_COMMAND(ID_UTILITIES_UNARCHIVECHARTS, OnUtilitiesUnarchivecharts)
	ON_UPDATE_COMMAND_UI(ID_UTILITIES_UNARCHIVECHARTS, OnUpdateUtilitiesUnarchivecharts)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SEARCH,OnUpdateEditSearch)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SEARCHCONTINUE,OnUpdateEditSearch)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdatePaste )
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_FILE_EDIT, OnUpdateFileEdit )
	ON_COMMAND(ID_FILE_EDIT, OnFileEdit)
	ON_COMMAND(ID_EDIT_SEARCH,OnEditSearch)
	ON_COMMAND(ID_EDIT_SEARCHCONTINUE,OnEditSearchCont)
	ON_UPDATE_COMMAND_UI(ID_SELECTALL, OnUpdateSelectAll )
	ON_COMMAND(ID_SELECTALL, OnSelectAll)
	//}}AFX_MSG_MAP
	ON_WM_MOUSEWHEEL()
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroflistView construction/destruction

CAstroflistView::CAstroflistView()
{
	// TODO: add construction code here
editptr = NULL;
was_cut = 0;
was_copy = 0;
was_delete = 0;
edit_at = 0;
can_undo = 0;
can_paste = 0;
pLogFont = NULL;
pFnt = NULL;
ppnNorm = NULL;
ppnSel = NULL;
pbrSel  = NULL;
pbrNorm = NULL;
pbmGra = NULL;
pbmTxt = NULL;
pbmChk = NULL;
pbmGrid = NULL;
cyDepth = 20;
nTopItem = 0;
nCursor = 0;
#ifdef Pro
clipFmt = RegisterClipboardFormat("ASTFILEDB");
#endif
}

CAstroflistView::~CAstroflistView()
{
if ( pFnt != NULL )
   delete pFnt;
if ( pLogFont != NULL )
   delete pLogFont;
if ( ppnNorm != NULL )
   delete ppnNorm;
if ( ppnSel != NULL )
   delete ppnSel;
if ( pbrSel != NULL )
   delete pbrSel;
if ( pbrNorm != NULL )
   delete pbrNorm;
if ( pbmGra != NULL )
   delete pbmGra;
if ( pbmTxt != NULL )
   delete pbmTxt;
if ( pbmGrid != NULL )
   delete pbmGrid;
if ( pbmChk != NULL )
   delete pbmChk;
}

BOOL CAstroflistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= (WS_VSCROLL|CS_DBLCLKS);
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAstroflistView drawing

void CAstroflistView::OnDraw(CDC* pDC)
{
	CAstroflistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
CRect rx;
pDC->GetClipBox(&rx);
CFont *old = pDC->SelectObject(pFnt);
pDC->SetTextAlign(TA_LEFT|TA_TOP);
drawHeader(pDC);
if ( pDoc->GetFileList() == NULL ) {
	pDC->SelectObject(old);
   return;
	}
AryItem &ar = pDoc->flary->arraygroup.get(pDoc->type,pDoc->flary->GetCurFolder());
CPtrArray *par = ar.ar;
if ( !par || !par->GetSize() )
   return;
if ( nTopItem < 0 )
   nTopItem = 0;
if ( !par->GetSize() ) {
    pDC->SelectObject(old);
    return;
	}
for ( int i = nTopItem, y = cyDepth; i < yCnt+nTopItem; i++, y+= cyDepth ) {
    if ( par->GetSize() == 0 || i >= par->GetSize() )
		break;
	XPFILE_DB *ptr = (XPFILE_DB *)(*par)[i];
	if ( ptr == NULL )
	   break;
    drawItem( pDC, ptr, y, (i==nCursor?1:0));
	}
pDC->SelectObject(old);
}

/////////////////////////////////////////////////////////////////////////////
// CAstroflistView diagnostics

#ifdef _DEBUG
void CAstroflistView::AssertValid() const
{
	CView::AssertValid();
}

void CAstroflistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAstroflistDoc* CAstroflistView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstroflistDoc)));
	return (CAstroflistDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstroflistView message handlers

int CAstroflistView::drawHeader(CDC *pDC)
{
 CRect r( 0, 0, cxWid, cyDepth );
 CBrush *oldb = pDC->SelectObject(pbrNorm);
 pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT) );
 pDC->SetBkColor(GetSysColor(COLOR_WINDOW) );
 pDC->TextOut( cxLeft, cyStart, "Name:" );
 pDC->TextOut( cxLeft, cyStart+cyChar, "Comments:" );
#ifdef PRO 
 pDC->TextOut( cxWidFlags, cyStart, "P" );
 pDC->TextOut( cxWidFlags, cyStart+cyChar, "C" );
#endif
 pDC->TextOut( cxWidName, cyStart, "File Name:" );
 pDC->TextOut( cxWidName, cyStart+cyChar, "Type:" );
 CPen *ppnHead = new CPen(GetSysColor(COLOR_WINDOWTEXT),PS_SOLID,3);
 CPen *oldp=pDC->SelectObject(ppnHead);
 pDC->MoveTo( cxStart, cyRule + cyStart);
 pDC->LineTo( cxClient-cxStart, cyRule + cyStart);
 pDC->SelectObject(oldp);
 delete ppnHead;
 pDC->SelectObject(oldb);
 return(1);
}

int CAstroflistView::drawItem( CDC *pDC, XPFILE_DB *i, int y, int mrk)
{
 CPen *oldp;
 CBrush *oldb;
	
 if ( i == NULL )
    return( 0 );
  CRect r(0, y, cxClient, y+cyDepth );
  if ( !mrk ) {
    oldb = pDC->SelectObject(pbrNorm);
    pDC->FillRect(&r, pbrNorm);
    pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT) );
    pDC->SetBkColor(GetSysColor(COLOR_WINDOW) );
    }
 else {
    oldb = pDC->SelectObject(pbrSel);
    pDC->FillRect(&r, pbrSel);
    pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT) );
    pDC->SetBkColor(GetSysColor(COLOR_HIGHLIGHT) );
    }
 pDC->TextOut( cxLeft, cyStart+y, i->name );
 pDC->TextOut( cxLeft, cyStart+cyChar+y, i->comment );
#ifdef PRO
 pDC->TextOut( cxWidFlags, cyStart+y, (i->has_cover?"X":" ") );
 pDC->TextOut( cxWidFlags, cyStart+cyChar+y, (i->has_comments?"X":" "));
#endif
 pDC->TextOut( cxWidName, cyStart+y, i->file_name );
 if (i->type <= 75 && i->type >= 0)
    pDC->TextOut( cxWidName, cyStart+cyChar+y, types[i->type] );
 if ( i->selected )
	bitmap(pDC, pbmChk, cxStart, cyStart+y, (mrk?MERGEPAINT:SRCCOPY) );
 if ( i->type > LAST_NON_GRAPH && i->type <= LAST_GRAPH )
    bitmap(pDC,pbmGra, cxWid, cyStart+y);
 else if ( i->type > LAST_GRAPH )
    bitmap(pDC,pbmGrid, cxWid, cyStart+y);
 else
    bitmap(pDC,pbmTxt, cxWid, cyStart+y );
 if ( !mrk )
    oldp = pDC->SelectObject( ppnNorm );
 else
    oldp = pDC->SelectObject( ppnSel );
 pDC->MoveTo( cxStart, cyRule + y);
 pDC->LineTo( cxClient-cxStart, cyRule + y );
 pDC->SelectObject(oldp);
 pDC->SelectObject(oldb);
 return(1);
}


void CAstroflistView::OnSize(UINT nType, int cx, int cy) 
{
    CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    cxClient = cx;
    cyClient = cy;
    yCnt = ( cyClient-(cyStart+cyDepth) )/cyDepth;
	Invalidate(TRUE);
}


BOOL CAstroflistView::bitmap( CDC *pdc, CBitmap *pb, int x, int y, DWORD rop )
{
    BOOL ret;
	CDC *tmp = new CDC();
	tmp->CreateCompatibleDC(pdc);
	BITMAP b;
	
	tmp->SelectObject(pb);
	tmp->SetMapMode(pdc->GetMapMode());
	
	pb->GetObject(sizeof(BITMAP),(LPSTR)&b);
	CPoint si(b.bmWidth,b.bmHeight);
	CPoint org(0,0);

	pdc->DPtoLP(&si,1);
	tmp->DPtoLP(&org,1);
	
	ret = pdc->BitBlt(x,y,si.x,si.y,tmp,org.x,org.y,rop);
	delete tmp;
	return ret;
}

void CAstroflistView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class	
 CView::OnPrepareDC(pDC, pInfo);

 if ( pbrNorm != NULL ) 
    delete pbrNorm;
 pbrNorm=new CBrush(GetSysColor(COLOR_WINDOW));
    
 if ( pbrSel != NULL ) 
    delete pbrSel;
 pbrSel=new CBrush(GetSysColor(COLOR_HIGHLIGHT));
    
 if ( ppnNorm != NULL ) 
    delete ppnNorm;
 ppnNorm = new CPen(PS_SOLID,1,GetSysColor(COLOR_WINDOWTEXT));
 if ( ppnSel != NULL ) 
    delete ppnSel;
 ppnSel = new CPen(PS_SOLID,1,GetSysColor(COLOR_HIGHLIGHTTEXT));
 if ( pFnt != NULL ) 
    delete pFnt;
 pFnt = new CFont();
 if ( pLogFont != NULL )
    delete pLogFont;
 pLogFont =(LPLOGFONT) new char[sizeof(LOGFONT)+100];
 pLogFont->lfHeight= (int)((100.0 *(float) pDC->GetDeviceCaps(LOGPIXELSY))/720.0);
 pLogFont->lfWidth=0;
 pLogFont->lfEscapement=0;
 pLogFont->lfOrientation=0;
 pLogFont->lfWeight=FW_BOLD;
 pLogFont->lfItalic=FALSE;
 pLogFont->lfUnderline=FALSE;
 pLogFont->lfStrikeOut=FALSE;
 pLogFont->lfCharSet=ANSI_CHARSET;
 pLogFont->lfOutPrecision=OUT_DEFAULT_PRECIS;
 pLogFont->lfClipPrecision=CLIP_DEFAULT_PRECIS;
 pLogFont->lfQuality=DEFAULT_QUALITY;
 pLogFont->lfPitchAndFamily=FF_SWISS|VARIABLE_PITCH;
 strcpy( pLogFont->lfFaceName,"MS SANS SERIF");
 pFnt->CreateFontIndirect(pLogFont);	 
 CFont *oldf = pDC->SelectObject(pFnt);
 TEXTMETRIC tm;
 pDC->GetTextMetrics(&tm);
 cxChar = tm.tmAveCharWidth;
 cyChar = tm.tmHeight+tm.tmExternalLeading;
 cxStart = cxChar / 3;
 cyStart = 0;
 cxLeft = cxChar * 4;
 cyRule = cyChar + cyChar + (cyChar/3)+1;
 cyDepth = cyRule+1;
 cxWidFlags = ((NAME_WIDTH -2) * cxChar)+cxLeft+cxStart;
 cxWid = cxWidFlags + (3 * cxChar);
 cxWidName = cxWid+32;
 pDC->SelectObject(oldf);
 CRect r; 
 GetClientRect(&r);
 cxClient = r.Width();
 cyClient = r.Height();
 yCnt = ( cyClient-(cyStart+cyDepth) )/cyDepth;
 if ( pbmChk != NULL )
    delete pbmChk;
 pbmChk = new CBitmap();
 pbmChk->LoadBitmap(IDB_CHECK);	 
 if ( pbmTxt != NULL )
    delete pbmTxt;
 pbmTxt = new CBitmap();
 pbmTxt->LoadBitmap(IDB_TEXT);
 if ( pbmGrid != NULL )
    delete pbmGrid;
 pbmGrid = new CBitmap();
 pbmGrid->LoadBitmap(IDB_GRID);
 if ( pbmGra != NULL )
    delete pbmGra;
 pbmGra = new CBitmap();
 pbmGra->LoadBitmap(IDB_GLYPH);
 CAstroflistDoc *pdoc = GetDocument();
 if ( pdoc->GetFileList() != NULL )
    SetScrollRange( SB_VERT, 0, pdoc->GetFileList()->fileCount(pdoc->GetType())-yCnt, TRUE );
 }

void CAstroflistView::OnOptionsDirectories() 
{
	// TODO: Add your command handler code here
	CDirectories cd;
	cd.SetData(theDirectories);
	if ( cd.DoModal() == IDOK )	{
	   cd.GetData(theDirectories);
	   theDirectories.saveToIni();
	
	   }

}

void CAstroflistView::OnUpdateOptionsDirectories(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate(TRUE);
	
}

void CAstroflistView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int down;
	CAstroflistDoc *pdoc = GetDocument();
 	
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
	switch( nSBCode ) {
       case SB_TOP:		 
		down = nCursor - nTopItem;
		nTopItem = 0;
		nCursor = down;
		SetScrollPos(SB_VERT,0,TRUE);
		Invalidate(TRUE);
		break;
       case SB_BOTTOM:
	    down = nCursor - nTopItem;
		nCursor = nTopItem + down;   
		nTopItem =pdoc->GetFileList()->fileCount(pdoc->GetType())-yCnt;
		SetScrollPos(SB_VERT,nTopItem,TRUE);
		Invalidate(TRUE);
		break;
       case SB_PAGEUP:
		down = nCursor - nTopItem;
		nTopItem -= yCnt;
		if ( nTopItem < 0 )
		   nTopItem = 0;
		nCursor = nTopItem + down;   
		SetScrollPos(SB_VERT,nTopItem,TRUE);
		Invalidate(TRUE);
		break;
       case SB_PAGEDOWN:
	    down = nCursor - nTopItem;
		nTopItem += yCnt;
		if ( nTopItem > pdoc->GetFileList()->fileCount(pdoc->GetType())-yCnt )
		   nTopItem = pdoc->GetFileList()->fileCount(pdoc->GetType())-yCnt;
		if ( nTopItem < 0 )
		   nTopItem = 0;
		SetScrollPos(SB_VERT,nTopItem,TRUE);
		nCursor = nTopItem + down;   
        Invalidate(TRUE);
		break;
       case SB_THUMBPOSITION:
	    down = nCursor - nTopItem;
		nTopItem = nPos;
		if ( nTopItem < 0 )
           nTopItem = 0;
		nCursor = nPos + down;
		SetScrollPos(SB_VERT,nPos,TRUE);
		Invalidate(TRUE);
		break;
       case SB_LINEDOWN:
	    {
	    down = nCursor - nTopItem;
		if ( down < yCnt-1 )
		   nCursor++;
		else {
		   nCursor++;
		   nTopItem++;
		   if ( nTopItem > pdoc->GetFileList()->fileCount(pdoc->GetType())-yCnt )	{
		      nTopItem = pdoc->GetFileList()->fileCount(pdoc->GetType())-yCnt;
		      if ( nTopItem < 0 )
				 nTopItem = 0;
			  nCursor = nTopItem;
		      }
		   SetScrollPos(SB_VERT,nTopItem,TRUE);
		   }
		Invalidate(TRUE);
		}
		break;
       case SB_LINEUP:
		{
        down = nCursor - nTopItem;
	    if ( down > 0 )
		   nCursor--;
		else {
		   nTopItem--;
		   if ( nTopItem < 0 )
		      nTopItem = 0;
		   nCursor = nTopItem + down;   
		   SetScrollPos(SB_VERT,nTopItem,TRUE);
		   }
		Invalidate(TRUE);
		}
		break;
       default :
	    break;
       }

}

void CAstroflistView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	 switch( nChar ) {
          case VK_PRIOR:
			OnVScroll(SB_PAGEUP, 0, NULL );
		    break;
          case VK_NEXT:
	       	OnVScroll(SB_PAGEDOWN, 0, NULL );
			break;
          case VK_UP:
	        OnVScroll(SB_LINEUP, 0, NULL );
			break;
          case VK_DOWN:
	       	OnVScroll(SB_LINEDOWN, 0, NULL );
			break;
          case VK_HOME:
	        OnVScroll(SB_TOP, 0, NULL );
	        break;
          case VK_END:
	        OnVScroll(SB_BOTTOM, 0, NULL );
	       break;
          case VK_SPACE:
			{
		    CAstroflistDoc *pdoc = GetDocument();  
			AryItem &xar = pdoc->flary->arraygroup.get(pdoc->type,
				pdoc->flary->GetCurFolder());
			CPtrArray *ar = xar.ar;
	        if ( !ar || !ar->GetSize() )
				break;
			if ((*ar).GetSize() <= nCursor)
				break;
			XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	        if ( p != NULL ) {
	           if ( p->selected )
		          p->selected = 0;
	           else
		          p->selected = 1;
	           }
	        Invalidate(TRUE);
			}
			break;
		  default :
	       break;
	       }

}

void CAstroflistView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int i, y;
	CView::OnLButtonDown(nFlags, point);
	y = ((point.y-(cyDepth+cyStart))/cyDepth);
    i = y + nTopItem;
    nCursor = i;
    CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->type,
				pdoc->flary->GetCurFolder());
    CPtrArray *ar = xar.ar;
	if ( !ar || !ar->GetSize() )
		return;
	if ( nCursor >= ar->GetSize() )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
	   if ( p->selected )
		  p->selected = 0;
	   else
		  p->selected = 1;
	   }
	Invalidate(TRUE);
}

void CAstroflistView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	
	// TODO: Add your message handler code here and/or call default
	int i, y;
	char buf[250];

	y = ((point.y-(cyDepth+cyStart))/cyDepth);
    i = y + nTopItem;
    nCursor = i;
    CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->type,
				pdoc->flary->GetCurFolder());
	if ( xar.count == 0 )
		return;
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
	   strcpy( buf, set_path( p->file_name, p->folder ) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
}
											  
BOOL CAstroflistView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
  return CView::DestroyWindow();
 }


LRESULT CAstroflistView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::DefWindowProc(message, wParam, lParam);
}
void CAstroflistView::OnFileView() 
{
	// TODO: Add your command handler code here
	
	char buf[350];
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->type,
				pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || !ar->GetSize() || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
		strcpy( buf, set_path( p->file_name, p->folder ) );
       AfxGetApp()->OpenDocumentFile(buf);
	   }
}

void CAstroflistView::OnUpdateFileView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}


void CAstroflistView::DoBatchOfFiles(enum filetype ftype, UINT cmd, FileListArray *fla, int type)
{
 int count, fcount;
 CWordArray war;
 CStringArray sar; 

 fla->check();
 count = fla->selCount(type,fla->GetCurFolder());
 if ( !count ) {
	 count = 1;
	 war.SetSize(count+2,5);
	 war[0] = nCursor;
	}
 else {
	war.SetSize(count+2,5);
	count = fla->getSelection(type, count, war, fla->GetCurFolder());
	}
 CPtrArray &par = fla->fileDBArray(type,fla->GetCurFolder());
#ifdef PRO
 fcount = getFileCount( war, par, count, 1, 1 );
 sar.SetSize(fcount+1,2);
 getFileList( sar, war, par, count, fcount, 1, 1, 1 );
#else
 fcount = getFileCount( war, par, count, 0, 0 );
 sar.SetSize(fcount+1,2);
 getFileList( sar, war, par, count, fcount, 0, 0, 0 );
#endif
 
 CWinApp *app = AfxGetApp();
 ((CAstrowApp *)app)->OpenDocBatchSendCmdWait(ftype, sar[0], cmd, &sar, fcount );

}


int GetListType(FileListArray *fla)
{
#ifdef PRO
 int count, type, type2;
 CWordArray war;
	 
 fla->check();
 count = fla->selCount(ALL_F, fla->GetCurFolder());
 if ( !count )
    return(0);
 war.SetSize(count+2,5);
 count = fla->getSelection(ALL_F, count, war, fla->GetCurFolder());
 CPtrArray &par = fla->fileDBArray(ALL_F, fla->GetCurFolder());
 XPFILE_DB *ptr;
 ptr = (XPFILE_DB *)par[war[0]];
 if ( ptr->type < LAST_NON_GRAPH )
    type = 0;
 else if ( ptr->type > LAST_GRAPH )
    type = 2;
 else
    type = 1;
 for ( int i = 1; i < war.GetSize(); i++ ) {
     ptr = (XPFILE_DB *)par[war[i]];
     if ( ptr->type < LAST_NON_GRAPH )
        type2 = 0;
	 else if ( ptr->type > LAST_GRAPH )
	    type2 = 2;
     else
        type2 = 1;
	 if ( type != type2 ) {
		alert_box("", "Selections of Files for Print, Convert, Edit Purposes Must All Be Either Graphics or Text, Not Mixed!" );
		return( -1 );
		} 
     else
        type = type2;
 	}
 return( type );
#else
return( 0 );
#endif
}

void CAstroflistView::OnFileExport() 
{
 char buf[200];
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
    AryItem &xar = pdoc->flary->arraygroup.get(pdoc->type,
				pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;     
	if ( !ar || !ar->GetSize() )
		return;
	if ( pdoc->GetFileList()->selCount(pdoc->GetType(),pdoc->flary->GetCurFolder())>1) {
		if ( fAllChecked ) {
			if ( pdoc->GetType() == NON_GRA || pdoc->GetType() == GRIDFX )
			   doSelConvText(this, pdoc->GetFileList(), pdoc->GetType() ); 
			else if (pdoc->GetType() == ALL_F) {
			   int type = GetListType(pdoc->GetFileList());
               if ( !type )
			      doSelConvText(this, pdoc->GetFileList(), pdoc->GetType() ); 
			   else if ( type == 1 )
   			      DoBatchOfFiles(GraphTypeFile, ID_FILE_EXPORT, pdoc->GetFileList(), pdoc->GetType());				
				}
			else {
                // convert a bunch of graphics			
			DoBatchOfFiles(GraphTypeFile, ID_FILE_EXPORT, pdoc->GetFileList(), pdoc->GetType());	
			}		
		} // fAllChecked
	   else { // !fAllChecked
          if ( ar->GetSize() <= nCursor )
			  return;
	      XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	      if ( p != NULL ) {
			  strcpy( buf, set_path( p->file_name, p->folder ) );
		  if ( p->type < LAST_NON_GRAPH || p->type > LAST_GRAPH)
		     doConvText( this, p );
			 
#ifdef PRO	      
		  else
			  ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(GraphTypeFile, buf, ID_FILE_EXPORT ); 	 
	
#endif
		
		} // p != NULL

		} // else !fAllChecked	   
	} // SelCount > 1
    else { // SelCount == 1
	   if ( ar->GetSize() <= nCursor )
		   return;
	   XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	   if ( p != NULL ) {
		   strcpy( buf, set_path( p->file_name, p->folder ) );
		  if ( p->type < LAST_NON_GRAPH || p->type > LAST_GRAPH )
		     doConvText( this, p ); 
#ifdef PRO	      
			else
				 ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(GraphTypeFile, buf, ID_FILE_EXPORT ); 	 
#endif	   
			} // p != NULL
	   } // else SelCount == 1
}

void CAstroflistView::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
	pCmdUI->Enable(TRUE);
#else
    CAstroflistDoc *pdoc = GetDocument();  
    if ( pdoc->GetType() == GRA_F )
       pCmdUI->Enable(FALSE);
    else
       pCmdUI->Enable(TRUE);
#endif
}

void CAstroflistView::OnFileKill() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	pdoc->GetFileList()->killSelectedFiles(this, pdoc->GetType(),pdoc->flary->GetCurFolder());
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdateFileKill(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnOptionsAllcheck() 
{
	// TODO: Add your command handler code here
	fAllChecked ^= 1;
}

void CAstroflistView::OnUpdateOptionsAllcheck(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(fAllChecked);
	pCmdUI->Enable(TRUE);
}


void CAstroflistView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	char buf[150];
	CAstroflistDoc *pdoc = GetDocument();  
    AryItem &xar = pdoc->flary->arraygroup.get(pdoc->type,
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;     
	if ( !ar || !ar->GetSize() )
		return;
	if ( pdoc->GetFileList()->selCount(pdoc->GetType(), pdoc->flary->GetCurFolder())>1) {
		if ( fAllChecked ) {
			// print a bunch of files
			if (pdoc->GetType() == GRA_F)
			   DoBatchOfFiles(GraphTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());
			else if (pdoc->GetType() == NON_GRA || pdoc->GetType() == GRIDFX )
			   DoBatchOfFiles(TextTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());
			else {
			   int type = GetListType(pdoc->GetFileList());
               if ( !type )
			      DoBatchOfFiles(GraphTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());      
			   else if ( type == 1 )
				  DoBatchOfFiles(TextTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());	   			      
		       else if ( type == 2 )
				  DoBatchOfFiles(GridTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());	   			      
			}	
		   }
		
		else { // !fAllChecked
		if ( ar->GetSize() <= nCursor )
			return;
		XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	    if ( p != NULL ) {
			strcpy( buf, set_path( p->file_name, p->folder ) );
		   if ( p->type > LAST_NON_GRAPH )
		      ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(GraphTypeFile, buf, ID_FILE_PRINT ); 	
           if ( p->type > LAST_GRAPH )
		      ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(GridTypeFile, buf, ID_FILE_PRINT ); 	
		   else
#ifdef PRO
			  DoBatchOfFiles(TextTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());
#else
			  ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(TextTypeFile, buf, ID_FILE_PRINT ); 	 	
#endif
	          
			} // p!= NULL
		} // else !fAllChecked
	
		} // selCount > 1
    else { // selCount = 1
       if ( ar->GetSize() <= nCursor )
		   return;
	   XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	   if ( p != NULL ) {
		   strcpy( buf, set_path( p->file_name, p->folder ) );
		  if ( p->type > LAST_NON_GRAPH )
		     ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(GraphTypeFile, buf, ID_FILE_PRINT ); 	
	      else if ( p->type > LAST_GRAPH )
#ifdef PRO
			  DoBatchOfFiles(GridTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());
#else
			  ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(GridTypeFile, buf, ID_FILE_PRINT ); 	 	
#endif

		  else
#ifdef PRO
			  DoBatchOfFiles(TextTypeFile, ID_FILE_PRINT, pdoc->GetFileList(), pdoc->GetType());
#else
			  ((CAstrowApp *)AfxGetApp())->OpenDocSendCmdWait(TextTypeFile, buf, ID_FILE_PRINT ); 	 	
#endif

	   }  // p != NULL
	} // else SelCount = 1
}	

void CAstroflistView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnUtilitiesClearselection() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	pdoc->GetFileList()->clearSel( pdoc->GetType(), pdoc->flary->GetCurFolder() );
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdateUtilitiesClearselection(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnUtilitiesEditentry() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->GetType(),pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || !ar->GetSize() || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
	   pdoc->GetFileList()->changeEntry( p, this );
	   }
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdateUtilitiesEditentry(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnUtilitiesSort() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	pdoc->GetFileList()->sortFiles();
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdateUtilitiesSort(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnUtilitiesreadfiledata() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
	   if ( p->type < LAST_NON_GRAPH )
		  do_parse_file( p );
	   else
		  alert_box("", "No Data To Read In File!" );
	   }
}

void CAstroflistView::OnUpdateUtilitiesreadfiledata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	if ( pdoc->GetType() != GRA_F )
	   pCmdUI->Enable(TRUE);
	else
	   pCmdUI->Enable(FALSE);
}

void CAstroflistView::OnEditCopy() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	int count;
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
	   edit_at = nCursor;
	   editptr = p;
	   was_copy = 1;
	   can_undo = 0;
	   can_paste = 1;
	   }
	if ( fAllChecked && pdoc->GetFileList()->selCount(pdoc->GetType(),
		pdoc->flary->GetCurFolder()) > 1 ) {
	CWordArray war;
	count = pdoc->GetFileList()->selCount(pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	if ( !count )
		return;
	war.SetSize(count+2,5);
	count = pdoc->GetFileList()->getSelection(pdoc->GetType(), count, war,
		pdoc->flary->GetCurFolder());
	CPtrArray &par = pdoc->GetFileList()->fileDBArray(pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	HANDLE hMem = GlobalAlloc( GMEM_DDESHARE,4 + (count *sizeof(XPFILE_DB)));
	if ( hMem == NULL ) 
		do_mem_error(0);
	else {
		LPSTR pMem = (char *)GlobalLock(hMem);
		if ( pMem == NULL )
			do_mem_error(0);
		else {
			memcpy((LPVOID)pMem,(LPVOID)&count,4);
			XPFILE_DB *ptr = (XPFILE_DB *)(pMem+4);
			for ( int i = 0; i < count; i++, ptr++ )
			    memcpy(ptr,par[war[i]],sizeof(XPFILE_DB) );
			GlobalUnlock(hMem);
			if ( OpenClipboard() ) {
				if (EmptyClipboard() )
			       SetClipboardData(clipFmt,hMem);
				CloseClipboard();
				}	
			}
		}
	
	}
	else {
	HANDLE hMem = GlobalAlloc( GMEM_DDESHARE,4 + sizeof(XPFILE_DB));
	if ( hMem == NULL ) 
		do_mem_error(0);
	else {
		LPSTR pMem = (char *)GlobalLock(hMem);
		if ( pMem == NULL )
			do_mem_error(0);
		else {
			count = 1;
			memcpy((LPVOID)pMem,(LPVOID)&count,4);
			memcpy((LPVOID)(pMem+4),p,sizeof(XPFILE_DB) );
			GlobalUnlock(hMem);
			if ( OpenClipboard() ) {
				if (EmptyClipboard() )
				   SetClipboardData(clipFmt,hMem);
				CloseClipboard();	
				}
			}
		}
	
	}
	Invalidate(TRUE);
#endif
}

void CAstroflistView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CAstroflistView::OnEditCut() 
{
	// TODO: Add your command handler code here
#ifdef PRO
	OnEditCopy();
	CAstroflistDoc *pdoc = GetDocument();
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	if ( !xar.count )
		return;
	if (!fAllChecked || pdoc->GetFileList()->selCount(pdoc->GetType(),
		   pdoc->flary->GetCurFolder()) == 1) {
			   XPFILE_DB *p =(XPFILE_DB *)(*xar.ar)[nCursor];
		if ( p != NULL ) {
		   edit_at = nCursor;
		   editptr = p;
		   was_cut = 1;
		   can_undo = 1;
		   can_paste = 1;
		   pdoc->GetFileList()->deleteEntry(p);
		}
		else {
		CWordArray war;
		int count = pdoc->GetFileList()->selCount(pdoc->GetType(),
			pdoc->flary->GetCurFolder());
		if ( !count )
			return;
		war.SetSize(count+2,5);
		count = pdoc->GetFileList()->getSelection(pdoc->GetType(), 
			count, war, pdoc->flary->GetCurFolder());
		CPtrArray &par = pdoc->GetFileList()->fileDBArray(pdoc->GetType(),
			pdoc->flary->GetCurFolder());
		for ( int i = 0; i < count; i++ ) {
			XPFILE_DB *ptr = (XPFILE_DB *)par[war[i]];
			if ( ptr != NULL )
				pdoc->GetFileList()->deleteEntry(ptr);	
			}
		}
	}
	Invalidate(TRUE);
#endif
}

void CAstroflistView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
	pCmdUI->Enable(TRUE);
#endif
}

void CAstroflistView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	int r;
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get(pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar->GetSize() )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
	   edit_at = nCursor;
	   editptr = p;
	   was_delete = 1;
	   can_undo = 1;
	   can_paste = 1;
	   }
	pdoc->GetFileList()->deleteEntry(p);
	r = MessageBox("Do You Want to Delete (Yes) the File or just this Entry (No)","Delete", MB_ICONQUESTION|MB_YESNOCANCEL);
	if ( r == IDYES ) {
	   can_undo = 0;
	   can_paste = 0;
	   pdoc->GetFileList()->killFile(p);
	   editptr = NULL;
	   }
Invalidate(TRUE);
}

void CAstroflistView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar->GetSize() )
		return;
	ar->InsertAt(edit_at, editptr, 1 );
	xar.count++;
	xar.totalcount++;
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( can_undo )
	   pCmdUI->Enable(TRUE);
	else
	   pCmdUI->Enable(FALSE);
}

void CAstroflistView::OnUtilitiesRebuildflist() 
{
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	pdoc->GetFileList()->scanFiles();
	Invalidate(TRUE);
}

void CAstroflistView::OnUpdateUtilitiesRebuildflist(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}


void CAstroflistView::OnFileNewCommentfile() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    char buf[250];
    char name[250];	 

	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor)
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
       CCommentEd cced;
	   strcpy( name, p->file_name );
       char *dot = strrchr( name, '.' );
       if ( dot == NULL )
          strcat( name, ".CMT" );
       else
          strcpy( dot, ".CMT" );
	   strcpy( buf,  set_path( name, p->folder ) );   
       cced.SetFileNameFdb(buf,p);
	   cced.DoModal();
	   p->has_comments = 1;  
       pdoc->flary->UpdatePtr(p);
	}
#endif
}

void CAstroflistView::OnUpdateFileNewCommentfile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) 
       pCmdUI->Enable(TRUE);
	else   
#endif       
	   pCmdUI->Enable(FALSE);
}

void CAstroflistView::OnFileNewCoverpage() 
{
#ifdef PRO
    char buf[250];
    char name[250];	 

	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
    AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) {
       CCoverPage ccp;
	   CoverPageData cpd;
       strcpy( name, p->file_name );
       char *dot = strrchr( name, '.' );
       if ( dot == NULL )
          strcat( name, ".CPG" );
       else
          strcpy( dot, ".CPG" );
	   strcpy( buf,  set_path( name, p->folder ) );   
       if ( access( buf, 6 ) == -1 )
          cpd.create(p);
       else {
          if ( !cpd.load(buf) )
             cpd.create(p);
	      }
	   ccp.SetData( cpd );
	   if ( ccp.DoModal() == IDOK ) {
          ccp.GetData(cpd);
	      p->has_cover = 1;
          cpd.save(buf);
		  pdoc->flary->UpdatePtr(p);
	      }
	   }
	
#endif
}

void CAstroflistView::OnUpdateFileNewCoverpage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize() <= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) 
       pCmdUI->Enable(TRUE);
	else   
#endif       
	   pCmdUI->Enable(FALSE);
	
}

void CAstroflistView::OnFileOpenCommentfile() 
{
	// TODO: Add your command handler code here
	OnFileNewCommentfile(); 
}

void CAstroflistView::OnUpdateFileOpenCommentfile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar || ar->GetSize()<= nCursor )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) 
       pCmdUI->Enable(TRUE);
	else   
#endif       
	   pCmdUI->Enable(FALSE);
	
}

void CAstroflistView::OnUtilitiesArchivecharts() 
{
	// TODO: Add your command handler code here
#ifdef PRO
    CAstroflistDoc *pdoc = GetDocument();  
    FileListArchiver fla(pdoc->GetFileList(), pdoc->GetType(), 1);
	fla.archive(this, pdoc->GetFileList()->GetCurFolder());
#endif	
	
}

void CAstroflistView::OnUpdateUtilitiesArchivecharts(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
	CAstroflistDoc *pdoc = GetDocument();  
	AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar->GetSize() )
		return;
	XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	if ( p != NULL ) 
       pCmdUI->Enable(TRUE);
	else   
#endif       
	   pCmdUI->Enable(FALSE);
}

void CAstroflistView::OnUtilitiesUnarchivecharts() 
{
	// TODO: Add your command handler code here
#ifdef PRO
   CAstroflistDoc *pdoc = GetDocument();  
   FileListArchiver xfla(pdoc->GetFileList(), pdoc->GetType(), 0 );
   xfla.deArchive(this, pdoc->flary->GetCurFolder());
#endif	
}

void CAstroflistView::OnUpdateUtilitiesUnarchivecharts(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
       pCmdUI->Enable(TRUE);
#endif       
	
}


void CAstroflistView::OnUpdateEditSearch(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
       pCmdUI->Enable(TRUE);
#endif       
	
}

void CAstroflistView::OnUpdatePaste(CCmdUI* pCmdUI) 
{
#ifdef PRO	
    if ( IsClipboardFormatAvailable(clipFmt) )   
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
#endif       

}
void CAstroflistView::OnEditPaste() 
{
#ifdef PRO
int count;
CAstroflistDoc *pdoc = GetDocument();  
FileListArray *fla = pdoc->GetFileList();
if ( OpenClipboard() ) {
    HANDLE hMem = GetClipboardData(clipFmt);
	if ( hMem != NULL ) {
	   LPSTR pdata = (char *)GlobalLock(hMem);
	   if (pdata != NULL ) {
	    	memcpy((LPVOID)&count,(LPVOID)pdata,4);
		    pdata += 4;
		    for ( int i = 0; i < count; i++ ) {
			    XPFILE_DB *ptr = new XPFILE_DB;
			    memcpy((LPVOID)ptr,pdata,sizeof(XPFILE_DB));
			    pdata+= sizeof(XPFILE_DB);
			    fla->addEntry(ptr);		
				}
	
			}
		}	
	CloseClipboard();
	}
Invalidate(TRUE);
#endif
}

extern int doEdit( CWnd *pPar, XPFILE_DB *pFd );

void CAstroflistView::OnFileEdit() 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
 char buf[200];
	// TODO: Add your command handler code here
	CAstroflistDoc *pdoc = GetDocument();  
    AryItem &xar = pdoc->flary->arraygroup.get( pdoc->GetType(),
		pdoc->flary->GetCurFolder());
	CPtrArray *ar = xar.ar;
	if ( !ar->GetSize() )
		return;
	if ( pdoc->GetFileList()->selCount(pdoc->GetType(), 
		   pdoc->flary->GetCurFolder())>1) {
		if ( fAllChecked ) {
		   if ( pdoc->GetType() == NON_GRA )
			   doEdit(this, pdoc->GetFileList(), pdoc->GetType()); 
		   else {
   			   int type = GetListType(pdoc->GetFileList() );
               if ( !type )
			      doEdit(this, pdoc->GetFileList(), pdoc->GetType() ); 
			   else if ( type == 1 )
   			      alert_box("", "Can\'t Edit Graphic Files!" );
		   }

		} // fAllChecked
	   else { // !fAllChecked
          
	      XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	      if ( p != NULL ) {
	         if ( p->type < LAST_NON_GRAPH )
		        doEdit( this, p );
			 else
				alert_box("", "Can\'t Edit Graphic Files!" );
		} // p != NULL

		} // else !fAllChecked	   
	} // SelCount > 1
    else { // SelCount == 1
	   
		XPFILE_DB *p =(XPFILE_DB *)(*ar)[nCursor];
	   if ( p != NULL ) {
	      if ( p->type < LAST_NON_GRAPH )
		     doEdit( this, p ); 
		  else
			 alert_box("", "Can\'t Edit Graphic Files!" );  
	   } // p != NULL
   } // else SelCount == 1
#endif
}


void CAstroflistView::OnUpdateFileEdit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO	
    CAstroflistDoc *pdoc = GetDocument();  
    if ( pdoc->GetType() == GRA_F )
       pCmdUI->Enable(FALSE);
	else 
	   pCmdUI->Enable(TRUE);	
  
#endif       
	
}

void CAstroflistView::OnEditSearch() 
{
#ifdef PRO
 CAstroflistDoc *pdoc = GetDocument();  
 m_findPos = pdoc->flary->findFirst(this,pdoc->GetType(),pdoc->flary->GetCurFolder());
 int cnt = pdoc->flary->getCount(pdoc->GetType(),pdoc->flary->GetCurFolder());
 if ( m_findPos != -1 ) {
    int top;
	int pos;

	if ( cnt - m_findPos > yCnt ) {
	   nCursor = m_findPos;
	   nTopItem = m_findPos;
	}
	else if (cnt > yCnt) {
	   nCursor = m_findPos;
	   nTopItem = cnt-yCnt;
	}
	else {
	  nTopItem = 0;
	  nCursor = m_findPos;
	}
	Invalidate(0);
 }

#endif
}

void CAstroflistView::OnEditSearchCont() 
{
#ifdef PRO
CAstroflistDoc *pdoc = GetDocument();  
if ( m_findPos != -1 ) {
	m_findPos = pdoc->flary->findCont(pdoc->GetType(),m_findPos+1,pdoc->flary->GetCurFolder());
    int cnt = pdoc->flary->getCount(pdoc->GetType(),pdoc->flary->GetCurFolder());
if ( m_findPos != -1 ) {
    int top;
	int pos;

	if ( cnt - m_findPos > yCnt ) {
	   nCursor = m_findPos;
	   nTopItem = m_findPos;
	}
	else if (cnt > yCnt) {
	   nCursor = m_findPos;
	   nTopItem = cnt-yCnt;
	}
	else {
	  nTopItem = 0;
	  nCursor = m_findPos;
	}
	Invalidate(0);
 }
}
#endif
}
BOOL CAstroflistView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
   if ( zDelta > 0 ) 
	   OnKeyDown(VK_UP,zDelta/120,0);
   else
	   OnKeyDown(VK_DOWN,abs(zDelta)/120,0);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CAstroflistView::OnUpdateSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CAstroflistView::OnSelectAll()
{
  CAstroflistDoc *pdoc = GetDocument(); 
  pdoc->GetFileList()->SelectAll(pdoc->GetType(),
	  pdoc->GetFileList()->GetCurFolder(),TRUE);
  Invalidate(1);
}
int CAstroflistView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CView::OnCreate(lpCreateStruct);
	return 0;
}
