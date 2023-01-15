// SplashWin.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "SplashWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashWin


CSplashWin::CSplashWin(CWnd *pPar) : CFrameWnd()
{


hTimer = 0;
/*
CREATESTRUCT cs; 
PreCreateWindow(cs);
WNDCLASS
AFXRegisterClass

CreateEx(0L,cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, pPar->GetSafeHwnd(), NULL, NULL );
*/
}

CSplashWin::~CSplashWin()
{
 if ( hTimer != 0 )
	KillTimer(hTimer);
}


BEGIN_MESSAGE_MAP(CSplashWin, CFrameWnd)
	//{{AFX_MSG_MAP(CSplashWin)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashWin message handlers

BOOL CSplashWin::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
return TRUE;	
}

void CSplashWin::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	DestroyWindow();
}

void CSplashWin::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	DestroyWindow();
}

void CSplashWin::OnPaint() 
{
 CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CFrameWnd::OnPaint() for painting messages
 BITMAP b;
 CBitmap cb;
 cb.LoadBitmap(IDB_TITLE);
 CDC *tmp = new CDC();
 tmp->CreateCompatibleDC(&dc);
 tmp->SelectObject(&cb);
 tmp->SetMapMode(dc.GetMapMode());
 CPoint si(258,171);
 CPoint org(0,0);
 dc.DPtoLP(&si,1);
 tmp->DPtoLP(&org,1);
 int x = (350 - 258)/2;
 int y = 10;
 dc.BitBlt(x,y,si.x,si.y,tmp,org.x,org.y,SRCCOPY);
 SetTimer( 0xabcd, 750, NULL );
}

BOOL CSplashWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDC *dc = new CDC;
	dc->CreateIC("DISPLAY", 0, 0, 0 );
	int w, h;
	w = dc->GetDeviceCaps(HORZRES);
	h = dc->GetDeviceCaps(VERTRES);
	cs.cx = 250;
	cs.cy = 350;
	cs.x = (w-250)/2;
	cs.y = (h-350)/2;
	cs.style = WS_BORDER|WS_VISIBLE;
	delete dc;
	return CFrameWnd::PreCreateWindow(cs);
}
