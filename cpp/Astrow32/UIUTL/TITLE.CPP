#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "acombbox.hpp"
#include "inifile.hpp"
#include "basedcs.h"
#include "title.hpp"
#include "paths.hpp"
#include "resstr.hpp"

#ifdef DEMO
static char BCS PW1[]= {"1&Natal&9"};
static char BCS PW2[]= {"2!Astrology!8"};
static char BCS PW3[]= {"3@Planets@6"};
static char BCS PW4[]= {"4=Placidus=7"};
#endif

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#ifdef NEW
#define VERS "1.28"
#else
#define VERS "1.16"
#endif
extern void zYield();
typedef int (zEvH::*KeyProc)(zKeyEvt *);
typedef int (zEvH::*MouseClickProc)(zMouseClickEvt*);

int TitlePane::kbhnd(zKeyEvt *e)
{
#ifdef DEMO
 if ( !getReg() )
    wait(3000);
 else
    wait(500);
#else
 wait(500);
#endif
 releaseMouse();
 setDestroyed();
 DestroyWindow( (HWND)*this );
 parent()->setDestroyed();
 DestroyWindow( (HWND)*parent() );
 return( 1 );
}

int TitlePane::mouseButtonDown( zMouseClickEvt *e )
{
#ifdef DEMO
 if ( !getReg() )
    wait(3000);
 else
    wait(1000);
#else
 wait(1000);
#endif
 releaseMouse();
 setDestroyed();
 DestroyWindow( (HWND)*this );
 parent()->setDestroyed();
 DestroyWindow( (HWND)*parent() );
 return( 1 );
}

void TitlePane::wait( int wt )
{
 DWORD tick;

 tick = GetTickCount();
 while (GetTickCount() - tick < wt );
}


TitlePane::TitlePane(zWindow *dad):zPane(dad,new zSizeWithParent)
{
#ifdef DEMO
  char buf[100];

  GetPrivateProfileString( "Shareware", "Reg", "", buf, 49, APPNAME );
  if ( !strcmpi(buf, PW1) || !strcmpi(buf, PW2) ||
       !strcmpi(buf, PW3) ||!strcmpi(buf, PW4) )
     getReg() = 1;
#endif
 setHandler(this, (NotifyProc)(KeyProc)&TitlePane::kbhnd, WM_KEYDOWN);
}

int TitlePane::draw(zDrawEvt *de)
{
  zDimension bit;
  zRect r;
  int x, y, h, reg=0;
  zFont *pFont;
  MSG msg;
  char buf[50];
  char regbuf[100];
  
  canvas()->lock();
  getInterior(r);
  zBitmap *bmp = new zBitmap(zResId("ASTROBMP"));
  bit = bmp->size();
  x = (r.width() - bit.width())/2;
  y = (r.height() - bit.height())/2;
#ifdef DEMO
  if ( getReg() )
     y -= 20;
  else
     y -= 45; 
#else  
  y -= 30; 
#endif  
  canvas()->bitmap( bmp, zPoint(x,y) );
  delete bmp;
  y+= bit.height();
  x = r.width()/2;
  pFont = new zFont(SystemVariable);
  SetTextAlign(*canvas(),TA_CENTER|TA_TOP);
  canvas()->pushFont(pFont);
  h = canvas()->getTextDim("T",1).height()+3;
  canvas()->text(x, y, CResStr(_TIT_TITLE)/*"ASTRO-The Program For Astrological Analysis"*/);
  y+= h;
#ifndef DEMO
#if defined( DELUXE ) && !defined( PRO )
  canvas()->text(x, y, CResStr(_TIT_DELUXE)/*"DELUXE VERSION: " VERS*/  );
#endif
#if defined( PRO ) && defined( DELUXE )
  canvas()->text(x, y, CResStr(_TIT_PRO)/*"PROFESSIONAL VERSION: " VERS*/ );
#endif
#ifndef DELUXE
  canvas()->text(x, y, CResStr(_TIT_LIT)/*"LIGHT VERSION: " VERS */);
#endif  
  GetPrivateProfileString( "User", "Name", "", buf, 49, APPNAME );
  sprintf( regbuf, CResStr(_TIT_REG)/*"Registered To: %s"*/, buf );
  y+= h;
  canvas()->text(x, y, regbuf );
  y+= h;
  canvas()->text(x, y, CResStr(_TIT_CPYW)/*"© Copyright 1993 by Christopher J. Noyes"*/ );
  delete canvas()->popFont();
  canvas()->unlock();
#else
  if ( !reg ) {
     canvas()->textColor(zColor(0xff,0, 0));
#ifndef DELUXE  
     canvas()->text(x, y, CResStr(_TIT_SW)/*"SHAREWARE DEMO VERSION: " VERS */);
#endif     
#if defined( DELUXE ) && !defined( PRO )
     canvas()->text(x, y, CResStr(_TIT_DELUXE)/*"DELUXE VERSION: " VERS */);
#endif
#if defined( PRO ) && defined( DELUXE )
    canvas()->text(x, y, CResStr(_TIT_PRO)/*"PROFESSIONAL VERSION: " VERS*/ );
#endif
     y+= h;
     canvas()->text(x, y, CResStr(_TIT_SW1)/*"THIS IS FOR FOR TRIAL USE ONLY,"*/ );
     y+= h;
     canvas()->text(x, y, CResStr(_TIT_SW2)/*"IF YOU FIND THIS USEFUL, YOU MUST REGISTER!"*/ );
     canvas()->textColor(zColor());
     }
  else {
     canvas()->text(x, y, CResStr(_TIT_SWREG)/*"REGISTERED SHAREWARE VERSION: " VERS */);
     }
  y+= h;
  canvas()->text(x, y, CResStr(_TIT_CPYW)/*"© Copyright 1993 by Christopher J. Noyes"*/ );
  delete canvas()->popFont();
  canvas()->unlock();
  MessageBeep(MB_ICONHAND);
#endif
  captureMouse();
#ifdef DEMO
  wait(3000);
#else
  wait(1000);
#endif  
  return 1;
}

int TitlePane::size(zSizeEvt *)
{
  canvas()->setDirty();
  return 1;
}

TitleFrame::TitleFrame(zWindow *dad):zPopupFrame(dad,new zSizer(120, 90, 400, 300), WS_BORDER|WS_POPUP, "ASTRO For Windows")
{
  image=new TitlePane(this);
  centerDialog( this );
  image->show();
  deleteOnClose(1);
}


TitleFrame::TitleFrame(zWindow *dad, int h):zPopupFrame(dad,new zSizer(120, 90, 400, h), WS_BORDER|WS_POPUP|WS_EX_TOPMOST, "ASTRO For Windows")
{
}



#ifdef DEMO
BegFrame::BegFrame(zWindow *dad):TitleFrame(dad,300)
{
  image=new BegPane(this);
  centerDialog( this );
  image->show();
  deleteOnClose(1);
}

BegPane::BegPane( zWindow *dad ) : TitlePane(dad)
{
 okKill=0;
}


int BegPane::draw(zDrawEvt *de)
{
  zDimension bit;
  zRect r;
  int x, y, h, reg=0;
  zFont *pFont;
  MSG msg;
  char buf[50];
  char regbuf[100];

  canvas()->lock();
  getInterior(r);
  zBitmap *bmp = new zBitmap(zResId("ASTROBMP"));
  bit = bmp->size();
  x = (r.width() - bit.width())/2;
  y = 20;
  canvas()->bitmap( bmp, zPoint(x,y) );
  delete bmp;
  y+= bit.height()+20;
  x = r.width()/2;
  pFont = new zFont(SystemVariable);
  SetTextAlign(*canvas(),TA_CENTER|TA_TOP);
  canvas()->pushFont(pFont);
  h = canvas()->getTextDim("T",1).height()+3;
  canvas()->textColor(zColor(0xff,0, 0));
  canvas()->text(x, y, CResStr(_TIT_SW3)/*"This Version of ASTRO is for Trial Purposes"*/);
  y+= h;
  canvas()->text(x, y, CResStr(_TIT_SW4)/*"Only. If You Find It Useful, You Must Register!"*/);
  y+= h;
  canvas()->text(x, y, CResStr(_TIT_SW5)/*"See Manual, README.WRI or REGISTER.WRI file for"*/);
  y+= h;
  canvas()->text(x, y, CResStr(_TIT_SW6)/*"Further Information..."*/);
  y+= h;
  delete canvas()->popFont();
  canvas()->unlock();
  MessageBeep(MB_ICONHAND);
  captureMouse();
  wait(3000);
  MessageBeep(MB_ICONHAND);
  releaseMouse();
  return 1;
}


#endif
