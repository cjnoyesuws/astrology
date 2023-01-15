#include "stdafx.h"
#include <string.h>
#include "asdrawbs.hpp"
#include "key.hpp"
#include "inifile.hpp"


WheelKey::WheelKey( CDC *z, CFont *f, CFont *fb,
			      int yst, int xw, int yd ) : AstDrawBase(z)
{
 int l;
 type = (getColorCount()==2);
 yStart = yst;

#ifdef DELUXE		 
 if ( ( l = (int) AfxGetApp()->GetProfileInt( GraphPrintOpt_SEC, "LabelLines", 0 ) ) ) {
    yStart -= (yd*(l+1));
    label = l+1;
    }
 else
    label = 0;
#endif
 xWidth = xw;
 yDeep = yd;
 bfnt = fb;
 fnt = f;
}

void WheelKey::title()
{
 disp()->SetTextColor(getColor(PLAN));
 if ( type )
    disp()->TextOut(0, yStart, /*CResStr(_KEY_LINE)*/"Line Key:" );
 else
    disp()->TextOut(0, yStart, /*CResStr(_KEY_COLOR)*/"Color Key:" );
}

void WheelKey::drawKeys()
{
 CWinApp *app;
 CFont *old, *old2;

 old2 = disp()->SelectObject(bfnt);
 disp()->SetTextAlign(TA_LEFT|TA_TOP);
 title();
 disp()->SelectObject(old2);
 old = disp()->SelectObject(fnt);
 if ( type )
    drawAKey(/*CResStr(_KEY_SIG)*/"Signs", SIGN, 0 );
 else
    drawAKey(/*CResStr(_KEY_SHA)*/"Signs/Hard Aspects", SIGN, 0 );
 drawAKey(/*CResStr(_KEY_HOU)*/"Houses/Soft Aspects", HOUS, 1 );
 if ( type )
    drawAKey(/*CResStr(_KEY_PHA)*/"Planets/Hard Aspects", PLAN, 2 );
 else
    drawAKey(/*CResStr(_KEY_PLA)*/"Planets", PLAN, 2 );
 drawAKey(/*CResStr(_KEY_RIS)*/"Ascend", RISE, 3 );
#ifdef NEW
#ifdef DELUXE
 if ( label ) {
    char labelbuf[10];
    CString buf;

    for ( int i = 1; i < label; i++ ) {
	if ( i == 1 )
	   old = disp()->SelectObject(bfnt);
	app = AfxGetApp();
	sprintf( labelbuf, "Label%d", i );
	buf = app->GetProfileString( GraphPrintOpt_SEC, labelbuf, "" );
	drawAKey((LPCTSTR)buf, -1, i+4 );  
	if ( i == 1 )
	   disp()->SelectObject(old);
	}
     }
#endif
#endif
 disp()->SelectObject(old2);
}

int WheelKey::lineKey(int color, int y)
{
 CPen *old;
 int hxw = xWidth/2;
 CDC *zd = disp();

 old = zd->SelectObject(getPen(color,P_THIN));
 zd->MoveTo( hxw, y );
 zd->LineTo( hxw, y+yDeep );
 zd->MoveTo( hxw-1, y );
 zd->LineTo( hxw-1, y+yDeep );
 delete zd->SelectObject(old);
 old = zd->SelectObject(getPen(color+BR,P_THIN));
 zd->MoveTo( xWidth+hxw, y );
 zd->LineTo( xWidth+hxw, y+yDeep );
 zd->MoveTo( xWidth+hxw+2, y );
 zd->LineTo( xWidth+hxw+2, y+yDeep );
 delete zd->SelectObject(old);
 return( (xWidth *2)+hxw );
}

int WheelKey::colorKey(int color, int y)
{											 
 CBrush r(getColor(color));
 disp()->FillRect(&CRect(0, y, xWidth, y+yDeep), &r);
 CBrush b(getColor(color+BR));
 disp()->FillRect(&CRect(xWidth, y, xWidth+xWidth, y+yDeep), &b);
 return( xWidth * 3 );
}



void WheelKey::drawAKey(LPCTSTR text,int color, int key )
{
 int x, y = yStart + ( yDeep * (key+1) );

 if ( color == -1 )
    x = 0;
 else {
    if ( type )
       x = lineKey(color, y);
    else
       x = colorKey(color, y);
    }
 disp()->TextOut(x, y, text);
}


StatusKey::StatusKey(CDC *z, int co, int _x, int _y, int algn, CFont *f)
							   : AstDrawBase(z)
{
 x = _x;
 y = _y;
 align = algn;
 color = co;
 fnt = f;
}

void StatusKey::draw(char *text)
{
 CFont *old;
 CDC *zd = disp();

 old = zd->SelectObject(fnt);
 zd->SetTextAlign(align);
 zd->SetTextColor(getColor(color));
 zd->TextOut(x, y, text);
 zd->SelectObject(old);
}
