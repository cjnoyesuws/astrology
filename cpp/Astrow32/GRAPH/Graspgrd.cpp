#include "stdafx.h"
#include "asdrawbs.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "paths.hpp"
#include "graphdat.hpp"
#include "graspgrd.hpp"
#include "aspect.h"
#include "polar.hpp"
#include <stdio.h>



AspectGrid::AspectGrid(CDC *z, CPoint p, CSize c,
			 GR_ASPT *pt, int cnt, int pl ) : AstDrawBase( z )
{
 at = p;
 cellh = thePolarScaler.invScaleY(c.cy);
 cellw = thePolarScaler.invScaleX(c.cx);
 hfcell = thePolarScaler.invScaleX(c.cx/2);
 thcell = thePolarScaler.invScaleY((c.cy+5)/10);
 data = pt;
 count = cnt;
 planets = pl;
 
}

CPoint AspectGrid::loc( int p1, int p2, int key )
{
 int x = (p2+1+key) * cellw;
 int y = ((p1+1+key) * cellh)-thcell;
 CPoint p = at;
 
 p.x -= (x - (hfcell));
 p.y -= y;
  return( p );
}


AspectGrid::draw()
{
 int i;				   
 GR_ASPT *pt;
 CRect r;
 CDC *zd = disp();	  
 
 
 CRect g( at.x-(planets*cellw), at.y-(planets*cellh), at.x, at.y );
 if ( !zd->RectVisible(g) ) {
    return( 1 );
	}
 drawGrid();
 zd->SetTextAlign(TA_CENTER|TA_TOP);
 zd->SetTextColor( getColor(BR+PLAN) );
 drawGridKey();
 for ( i = 0, pt = data; i < count; i++, pt++ )
     drawOne(pt);
 return(1);
}

AspectGrid::drawGridKey()
{
 char buf[5];
 CPoint p, p2;
 int x;
 CDC *zd = disp();
 
 for ( x = 1; x <= planets; x++ ) {
     p = loc( x, 0, 0 );
     p2 = loc( 0, planets-x+1, 0 );
     buf[0] = '`' + x -1;   
     buf[1] = '\0';
     zd->TextOut( p.x, p.y, buf, 1);
     zd->TextOut( p2.x, p2.y, buf, 1);
     }
 return( 1 );
}

int AspectGrid::drawGrid()
{
 int i, x, y, c = 4;      
 CPoint p;
 CPen *old;
 CPoint *arp, *ar = new CPoint[((planets+2)*2)+5];
 CDC *zd = disp();
 
 arp = ar;
 p = at;
 *arp++ = p;
 p -= CPoint(0,(planets+1)*cellh);
 *arp++ = p;
 p -= CPoint(cellw+cellw,0);
 *arp++ = p;
 p += CPoint(0,cellh);
 *arp++ = p;
 for ( i = planets+1; i > 2; i-- ) {
     p -= CPoint(cellw,0);
     *arp++ = p;
     p += CPoint(0,cellh);
     *arp++ = p;
     c+=2;
     }
 p.y = at.y ;
 *arp++ = p;
 *arp++ = at;
 c+=2;
 old = zd->SelectObject(getPen(CIRC, P_THICK));
 zd->MoveTo(at);
 zd->Polyline(ar,c);
 delete []ar;
 delete zd->SelectObject(old);
 old = zd->SelectObject(getPen(CIRC, P_THIN));
 for ( i = 2, y = at.y-(cellh * planets);
		   i <= planets+1; i++, y += cellh ) {
     zd->MoveTo(at.x, y);
     zd->LineTo(at.x-(i*cellw), y);
		   }
 for ( i = 3, x = at.x-(cellw * planets);
		   i <= planets+2; i++, x += cellw ) {
     if ( i == planets+2 ) {
        zd->MoveTo(x, at.y);
	zd->LineTo(x, at.y-((planets+1)*cellh));
        }
     else {   
        zd->MoveTo(x, at.y);
        zd->LineTo(x, at.y-(i*cellh));
        
		}
     }
delete zd->SelectObject(old); 
return( 1 );
}

AspectGrid::drawOne(GR_ASPT *pt)
{
 int p1, p2, t;
 char buf[5];
 
 if ( pt->getAspect() > SQUARED )
	 return( 1 );
 p1 = pt->getFirst();
 p2 = pt->getSecond();
 if (p1 > p2) {
    t = p1;
    p1 = p2;
    p2 = t;
    }
 p2 = planets-p2-1;
 if ( p1 > planets || p2 > planets-1 || p2 < 0 || p1 < 0 )
    return( 1 );
 CPoint p = loc(p1, p2);
 buf[0] = (unsigned char) pt->getAspect()+'ƒ';
 buf[1] = '\0';
 disp()->TextOut(p.x, p.y, buf, 1);
 return( 1 );
}



