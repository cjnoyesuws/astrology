#include "stdafx.h"
#include "asdrawbs.hpp"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "plotgrtp.hpp"


void GraphTextPlotter::plotItem( GR_TEXT *g )
{
 char buf[100], bf[5];
 static unsigned char arrows[] = "\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f";
 int w;
 CSize d, ad;
 CPoint a;
 CDC *zd = disp();
 CFont *old;

 zd->SetTextColor(getColor(g->getColor()));
 strcpy( buf, g->getText() );
 old = zd->SelectObject(pText);
 d = zd->GetTextExtent(buf);
 zd->SelectObject(old);
 old = zd->SelectObject(pArrow);
 if ( g->getArrow() != NoArrow ) {
    bf[0] = ' ';
    bf[1] = arrows[g->getArrow()];
    bf[2] = ' ';
    bf[3] = '\0';
    }
 else {
    bf[0] = ' ';
    bf[1] = '\0';
    }
 ad = zd->GetTextExtent(bf);
 w = ad.cx + d.cx;
 g->at(a);
 switch( g->align ) {
       case TopRight:
	    a.x -= w;
	    break;
       case BottomLeft:
	    a.y += d.cy;
	    break;
       case BottomRight:
	    a.x -= (d.cx + ad.cx);
	    a.y -= (d.cy + ad.cy);
	    break;
       case Center:
	    a.x -= ((d.cx + ad.cx)/2);
	    a.y -= ((d.cy + ad.cy)/2);
	    break;
       default :
	    break;
       }
 switch(g->getArrow()) {
       case NoArrow:
	    old = zd->SelectObject(pText);
	    zd->TextOut(a.x, a.y, buf);
	    break;
       case Left:
       case Top:
       case Bottom:
       case ULdiag:
       case DLdiag:
	    old = zd->SelectObject(pArrow);
	    zd->TextOut(a.x, a.y, bf);
	    a.x += ad.cx;
	    zd->SelectObject(pText);
	    zd->TextOut(a.x, a.y, buf);
	    break;
       case Right:
       case URdiag:
       case DRdiag:
	    zd->SelectObject(pText);
	    zd->TextOut(a.x, a.y, buf);
	    zd->SelectObject(pArrow);
	    a.x += d.cx;
	    zd->TextOut(a.x, a.y, bf);
	    break;
       default :
	    break;
       }
}

void GraphTextPlotter::plot()
{
 GR_TEXT **p;
 int i;

 for ( i = 0, p =text_array; i < items; i++, p++ )
     plotItem(*p);
}
