// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "SplashWnd.h"
#include "inifile.hpp"
#include "basedcs.h"
#include "paths.hpp"
#include <string.h>
#include <stdlib.h>
#include "astro.h"
#include "datetime.fns"
#include <time.h>

extern CAstrowApp theApp;

#ifdef DEMO
static char PW1[]= {"1&Natal&9"};
static char PW2[]= {"2!Astrology!8"};
static char PW3[]= {"3@Planets@6"};
static char PW4[]= {"4=Placidus=7"};
#endif

#define VERS "2.28"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long times =99L;
/////////////////////////////////////////////////////////////////////////////
// CSplashWnd

CSplashWnd::CSplashWnd(CWnd *pPar)
{
 #ifdef DEMO
  DATES installdate;
  DATES nowdate;
  char dtbuf2[25];
  double insjdt;
  double nowjdt;
  char dtbuf[25];
  CString buf;
  CString date;
  
  date = AfxGetApp()->GetProfileString( "Shareware", "key", "" );
  sscanf( date, "AsT%hd$%hd@%hdRoW", &installdate.day, &installdate.year, &installdate.month );
  installdate.day -= 100;
  installdate.month -= 500;
  installdate.year+= 1000;
  insjdt = base_julian_date(&installdate);
  _strdate( dtbuf );
  sscanf( dtbuf, "%hd/%hd/%hd", &nowdate.month, &nowdate.day, &nowdate.year );
  nowdate.year+=2000;
  nowjdt= base_julian_date(&nowdate);
  days_elapsed = (int) (nowjdt-insjdt);
  buf = AfxGetApp()->GetProfileString( "Shareware", "Reg", "" );
  if ( buf == PW1 ||  buf == PW2 || buf ==PW3 || buf==PW4 )
     getReg() = 1;
  else
	 getReg() = 0;
#endif
 TimerElapsed = 0;
 CreateEx(WS_EX_NOPARENTNOTIFY, AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
	NULL, WS_BORDER | WS_VISIBLE | WS_POPUP, 0,0, 350, 300, *pPar, NULL);
}

CSplashWnd::~CSplashWnd()
{
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplashWnd message handlers

BOOL CSplashWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CSplashWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
 #ifdef DEMO
 if ( !getReg() && TimerElapsed < 1 )
	return;
 #endif
 KillTimer(m_timerid);
 delete this;
}

void CSplashWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
#ifdef DEMO
 if ( !getReg() && TimerElapsed < 1 )
	return;
 #endif
 KillTimer(m_timerid);
 delete this;
}

void CSplashWnd::OnPaint() 
{
 #if (defined(DEMO) )
  char daysbuf[50];
  
  if ( days_elapsed < 30 )
     sprintf( daysbuf, "You have %d, more days to try it", 30-days_elapsed );
  else
     strcpy( daysbuf, "Sorry You are out of trial uses, You must register!" );
#endif  
 CPaintDC dc(this); // device context for painting
 BITMAP b;
 CBitmap cb;
 	
 // TODO: Add your message handler code here
	
 // Do not call CWnd::OnPaint() for painting messages
 CBrush *pbr = new CBrush;
 COLORREF bkc = RGB(0xff,0xff,0xff);
 pbr->CreateSolidBrush(bkc);
 CRect r(0,0, 350, 300);
 dc.FillRect(&r, pbr);
 delete pbr;
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
 int y = 25;
 dc.BitBlt(x,y,si.x,si.y,tmp,org.x,org.y,SRCCOPY);
 dc.SetTextAlign(TA_CENTER|TA_TOP);
 delete tmp;
 CFont *pFold, *pFont = new CFont();
 pFont->CreatePointFont(110,"MS Sans Serif", &dc);
 pFold = dc.SelectObject(pFont);
 COLORREF txc = RGB(0x0,0x0,0x0);
 dc.SetTextColor(txc);
 CSize sz = dc.GetTextExtent("T");
 x = 175;
 y = 201;
 dc.TextOut(x, y, "ASTRO-The Program For Astrological Analysis");
 y+= sz.cy+3;
#ifndef DEMO
#if defined( DELUXE ) && !defined( PRO )
 dc.TextOut(x, y, "DELUXE VERSION: " VERS  );
#endif
#if defined( PRO ) && defined( DELUXE )
 dc.TextOut(x, y, "PROFESSIONAL VERSION: " VERS );
#endif
#ifndef DELUXE
 dc.TextOut(x, y, "LIGHT VERSION: " VERS );
#endif  
  y+= sz.cy+3;
  CString u = AfxGetApp()->GetProfileString( "User", "Name", "" );
  CString rtn = "Registered To: "+ u;
  dc.TextOut(x, y, rtn );
  y+= sz.cy+3;
#else
  COLORREF txrc = RGB(0xff,0x0,0x0);
  if ( !reg ) {
     dc.SetTextColor(txrc);
#ifndef DELUXE  
     dc.TextOut(x, y, "SHAREWARE DEMO VERSION: " VERS );
#endif     
#if defined( DELUXE ) && !defined( PRO )
     dc.TextOut(x, y, "DELUXE VERSION: " VERS );
#endif
#if defined( PRO ) && defined( DELUXE )
    dc.TextOut(x, y, "PROFESSIONAL VERSION: " VERS );
#endif
     y+= sz.cy+3;
     dc.TextOut(x, y, "THIS IS FOR FOR TRIAL USE ONLY," );
     y+= sz.cy+3;
     dc.TextOut(x, y, "IF YOU FIND THIS USEFUL, YOU MUST BUY IT!" );
     
#if (defined(DEMO) )
	 y+= sz.cy+3;
     dc.TextOut(x, y, daysbuf );
#endif	 
	 dc.SetTextColor(txc);
     }
  else {
     dc.TextOut(x, y, "REGISTERED SHAREWARE VERSION: " VERS );
     }
#endif 
  y+= sz.cy+3;
  dc.TextOut(x, y, "© Copyright 2006 by Christopher J. Noyes" );
  delete dc.SelectObject(pFold);
  MessageBeep(MB_ICONINFORMATION); 

}

void CSplashWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
 TimerElapsed++;
#ifdef DEMO
 if ( !getReg() && days_elapsed >= 30 ) {
	if ( TimerElapsed == 1 )
		return;
	::PostQuitMessage(-1);	
	}
#endif
 KillTimer(m_timerid);	
 delete this;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CWnd::OnCreate(lpCreateStruct);
    CenterWindow();

	// Set a timer to destroy the splash screen.
	m_timerid = SetTimer(1, 3500, NULL);

	// TODO: Add your specialized creation code here	
	return 0;
}
