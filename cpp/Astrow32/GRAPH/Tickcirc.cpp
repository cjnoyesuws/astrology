#include "stdafx.h"
#include "asdrawbs.hpp"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"					
#include "polar.hpp"
#include "tickcirc.hpp"
#include "datagrfa.hpp"

void SignTickCircle::drawCirc()
{
 CPen *old;

 old = disp()->SelectObject(getPen(CIRC));
 CPoint o = out.asPoint();
 disp()->Ellipse(-o.x, -o.y, o.x, o.y);
 delete disp()->SelectObject(old);
}


SignTickCircle::SignTickCircle(CDC *zd, int ir, int or, int asc) : AstDrawBase(zd)
{
 asc_min = asc;
 out.setRad(or);
 in.setRad(ir);
 inradius = ir;
}

void SignTickCircle::draw()
{
 CDC *zd = disp();
 unsigned char buf[5];
 int i, d, m, x, y, z;
 CPoint o1, o2, i1, i2;
 CPen *old;

 zd->SetTextAlign(TA_LEFT|TA_TOP);
 old = disp()->SelectObject(getPen(CIRC));
 o1 = out.asPoint();
 disp()->Ellipse(-o1.x,-o1.y,o1.x,o1.y);
 i1 = in.asPoint();
 disp()->Ellipse(-i1.x,-i1.y,i1.x,i1.y);
 ++out;
 for ( z = d = adj_degrees(0,asc_min), i = 0; i < 12; i++, d += 30 ) {
     if ( d > 360 )
	d -= 360;
     zd->MoveTo(out.xy(d));
     zd->LineTo(in.xy(d));
     }
 COLORREF oc = zd->GetTextColor();
 zd->SetTextColor(getColor(BR+SIGN));
 for ( i = 0, m = (15*60); i < 12; i++, m += (30 * 60) ) {
     buf[0] = i+'w';
     buf[1] = '\0';
     CSize gs = zd->GetTextExtent((char *)buf);
     d = adj_degrees(m,asc_min);
     x = in.x(d);
     y = in.y(d);
     if ( x < 0 )
	x -= gs.cx;
     if ( y < 0 )
	y -= gs.cy;
     zd->TextOut( x, y, (char *)buf );
     }
 zd->SetTextColor(oc);
 i1 = in.asPoint();
 disp()->Ellipse(-i1.x,-i1.y,i1.x,i1.y);
 delete zd->SelectObject(old);
}

void DecanTickCircle::draw()
{
 CDC *zd = disp();
 int i, d;
 CPoint ip;
 CPen *old = NULL;

 drawCirc();
 if ( getPixels() > 1 ) 
    old = zd->SelectObject(getPen(CIRC,P_THIN) );
 else
	old = disp()->SelectObject(getPen(CIRC)); 

 ++out;
 for ( i = 0, d = adj_degrees(0,asc_min); i < 36; i++, d += 10 ) {
     if ( d > 360 )
	d -= 360;
     zd->MoveTo(out.xy(d));
     zd->LineTo(in.xy(d));
     }
 if ( getPixels() > 1 ) {
    delete zd->SelectObject(getPen(CIRC) );
    }
 ip = in.asPoint();
 disp()->Ellipse(-ip.x,-ip.y,ip.x,ip.y);
 if ( old != NULL )
    delete zd->SelectObject(old);
}

void DegreeTickCircle::draw()
{
 CDC *zd = disp();
 int d, x;
 CPen *old = NULL;
 CPoint ip;

 drawCirc();
 if ( getPixels() > 1 ) {
    old = zd->SelectObject(getPen(CIRC, P_THIN) );
    }
 else
 	old = disp()->SelectObject(getPen(CIRC)); 
 ++out;
 x = adj_degrees(0,asc_min);
 for ( d = x; d < 360; d += incrmnt ) {
     zd->MoveTo(out.xy(d));
     zd->LineTo(in.xy(d));
     }
 for ( d = 0; d < x; d += incrmnt ) {
     zd->MoveTo(out.xy(d));
     zd->LineTo(in.xy(d));
     }
 if ( getPixels() > 1 ) {
    delete zd->SelectObject(getPen(CIRC));
    }
ip = in.asPoint();
disp()->Ellipse(-ip.x,-ip.y,ip.x,ip.y);
if ( old != NULL )
   delete zd->SelectObject(old);
}



DegreeTickCircle::DegreeTickCircle( CDC *zd,int inrad, int outrad, int asc) : SignTickCircle(zd, inrad, outrad, asc)
{
 if ( getRes() >= 140 )
    incrmnt = 1;
 else if ( getRes() >= 90 )
    incrmnt = 2;
 else
    incrmnt = 5;
}


void DecanDegreeTickCircle::draw()
{
 CDC *zd = disp();
 int i, d, md, ta, td, bk;
 CPoint ip;
 CPen *old = NULL;
 CBrush *oldb = NULL;
 COLORREF cr = getColor(CIRC);
 PolarCoord mid;
 mid.setRad(inradius+2);
 char buf[5];

 drawCirc();
 ip = in.asPoint();
 zd->Ellipse(-ip.x,-ip.y,ip.x,ip.y);
 if ( getPixels() > 1 ) 
    old = zd->SelectObject(getPen(CIRC,P_THIN) );
 else
	old = zd->SelectObject(getPen(CIRC)); 

 ++out;
 oldb = zd->SelectObject(pBrush);
 bk = zd->GetBkMode();
 zd->SetBkMode(TRANSPARENT);
 ta = zd->GetTextAlign();
 zd->SetTextAlign(TA_TOP|TA_LEFT);
 for ( i = 0, d = adj_degrees(0,asc_min); i < 36; i++, d += 10 ) {
     if ( d > 360 )
	    d -= 360;
     md = d + 5;
	 td = d + 4;
	 if ( td > 360 )
		 td -= 360;
	 if ( md > 360 )
		 md -= 360;
	 sprintf(buf,"%d", d );
	 zd->MoveTo(out.xy(d));
     zd->LineTo(in.xy(d));
     //if ( i % 2 ) 
	 //	 zd->ExtFloodFill(mid.x(md),mid.y(md),cr, FLOODFILLBORDER );
     zd->TextOut(out.x(td),out.y(td),CString(buf));
     }
 zd->SetBkMode(bk);
 oldb = disp()->SelectObject(oldb);
 if ( getPixels() > 1 ) {
    delete zd->SelectObject(getPen(CIRC) );
    }
 disp()->SetTextAlign(ta);
 if ( old != NULL )
    delete zd->SelectObject(old);
}
