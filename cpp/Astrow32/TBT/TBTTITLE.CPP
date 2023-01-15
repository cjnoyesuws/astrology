#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "acombbox.hpp"
#include "inifile.hpp"
#include "basedcs.h"
#include "title.hpp"
#include "paths.hpp"
#include "resource.h"

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#ifndef NUMEROWTBT
#define VERS "1.50"
#else
#define VERS "1.0"
#endif

extern void zYield();
typedef int (zEvH::*KeyProc)(zKeyEvt *);
typedef int (zEvH::*MouseClickProc)(zMouseClickEvt*);

int TitlePane::kbhnd(zKeyEvt *e)
{
 wait(1000);
 releaseMouse();
 setDestroyed();
 DestroyWindow( (HWND)*this );
 parent()->setDestroyed();
 DestroyWindow( (HWND)*parent() );
 return( 1 );
}

int TitlePane::mouseButtonDown( zMouseClickEvt *e )
{
 wait(1000);
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
  zBitmap *bmp = new zBitmap(zResId(IDB_BITMAP1));
  bit = bmp->size();
  x = (r.width() - bit.width())/2;
  y = (r.height() - bit.height())/2;
  y -= 30; 
  canvas()->bitmap( bmp, zPoint(x,y) );
  delete bmp;
  y+= bit.height();
  x = r.width()/2;
  pFont = new zFont(SystemVariable);
  SetTextAlign(*canvas(),TA_CENTER|TA_TOP);
  canvas()->pushFont(pFont);
  h = canvas()->getTextDim("T",1).height()+3;
#ifndef NUMEROWTBT
  canvas()->text(x, y, "TBT-Text Builder Toolkit for ASTRO");
#else
  canvas()->text(x, y, "TBT-Text Builder Toolkit for NUMERO UNO");
#endif
  y+= h;
  canvas()->text(x, y, "VERSION: " VERS );
  GetPrivateProfileString( "User", "Name", "", buf, 49, APPNAME );
  sprintf( regbuf, "Registered To: %s", buf );
  y+= h;
  canvas()->text(x, y, regbuf );
  y+= h;
  canvas()->text(x, y, "© Copyright 1993 by Christopher J. Noyes" );
  delete canvas()->popFont();
  canvas()->unlock();
  captureMouse();
  wait(1000);
  return 1;
}

int TitlePane::size(zSizeEvt *)
{
  canvas()->setDirty();
  return 1;
}

TitleFrame::TitleFrame(zWindow *dad):zPopupFrame(dad,new zSizer(105, 90, 450, 300), WS_BORDER|WS_POPUP, "ASTRO For Windows")
{
  image=new TitlePane(this);
  centerDialog( this );
  image->show();
  deleteOnClose(1);
}


TitleFrame::TitleFrame(zWindow *dad, int h):zPopupFrame(dad,new zSizer(120, 90, 400, h), WS_BORDER|WS_POPUP, "ASTRO For Windows")
{
}



