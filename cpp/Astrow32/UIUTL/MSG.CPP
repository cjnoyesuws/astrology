#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "msg.hpp"
#include "acombbox.hpp"


ProcMessage::ProcMessage( char *text, int *pbrk )
		       : zFormDialog( (zWindow *)app->rootWindow(), zResId("MESSAGE_BOX") )
{
 _break = pbrk;
 pT = new zStaticText( this, 101 );
 pT->text(zString(text) );
 setCursor( zCursor(Hourglass) );
 isShutDown = 0;
 clipCursor(0);
 zDefPushButton *b = new zDefPushButton(this, IDCANCEL );
 b->setNotifyClicked(this,(NotifyProc)&ProcMessage::doCmd);
 centerDialog(this);
 show();
 captureMouse();
}

int ProcMessage::doCmd( zEvent *e )
{
 *_break = 1;
 isShutDown = 1;
 endOk(e);
 return( 1 );
}

void ProcMessage::update()
{
 UpdateWindow( (HWND) *this );
 setFocus();
}


void ProcMessage::setText(char *text)
{ 
 DWORD tick;
 
 tick = GetTickCount();
 pT->text(zString(text)); 
 while (GetTickCount() - tick < 300);
}

