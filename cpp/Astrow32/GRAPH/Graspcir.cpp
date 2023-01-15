#include "stdafx.h"
#include "asdrawbs.hpp"
#include "polar.hpp"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "graspcir.hpp"
#include "aspect.h"


static int ph, pht, ps, pst;

AspectCircle::AspectCircle(CDC *z, GR_ASPT *p,
  int cnt, int rad, int cy, int gl, int dc) : AstDrawBase(z)
{
  pc.setRad(rad);
  pAspects = p;
  asp_count = cnt;
  glyph = gl;
  draw_circ = dc;
  cyChar = cy;
 }


void AspectCircle::getPoints(GR_ASPT *p, CPoint &f, CPoint &s )
{
 f = pc.xy(p->first);
 s = pc.xy(p->second);
}

void AspectCircle::getMid(CPoint &f, CPoint &s, CPoint &m )
{
/*
 int dx, dy;

 if ( s.x() >  f.x() )
    dx = s.x() - f.x();
 else
    dx = f.x() - s.x();
 if ( s.x() >  f.x() )
    dy = s.y() - f.y();
 else
    dy = f.y() - s.y();
 dx/=2;
 dy/=2;
 m = zPoint(dx+min(f.x(), s.x()), dy+min(f.y(), s.y())-(cyChar/2) );
*/
}

int AspectCircle::draw_asp(GR_ASPT *p)
{
 CPoint fp, sp, gp;
 CDC *d = disp();
 
 if ( p->isHard() ) {
    if ( !state ) {
       state = 1;
       delete d->SelectObject( getPen(ph, pht) );
       d->SetTextColor( getColor(ph) );
       }
    }
 else {
    if ( state ) {
       state = 0;
       delete d->SelectObject( getPen(ps, pst) );
       d->SetTextColor( getColor(ph) );
       }
    }
 getPoints(p,fp,sp);
 d->MoveTo(fp);
 d->LineTo(sp);
/* if ( glyph ) {
    getMid(fp,sp,gp);
    buf[0] = (unsigned char) p->aspect+162;
    buf[1] = '\0';
    d->text(gp,(char far *)buf);
    }
 */
 return( 1 );
}


void AspectCircle::draw()
{
 int i;
 GR_ASPT *a;
 CPoint p;
 CDC *d = disp();
 CPen *old;

 if (type() == _TYPE_PRINT && getColorCount() == 2 ) {
    pht = P_THICK;
    ph = BR+PLAN;
    pst = P_THIN;
    ps = HOUS;
    }
 else if (type() == _TYPE_PRINT && getColorCount() > 2 ) {
    pht = P_APLIN;
    ph = BR+SIGN;
    pst = P_APLIN;
    ps = BR+HOUS;
    }
 else {
    pht = P_THIN;
    ph = BR+SIGN;
    pst = P_THIN;
    ps = BR+PLAN;
    }
 old = d->SelectObject(getPen(CIRC));
 state = 1;
 p = pc.asPoint();
 if ( draw_circ ) 
    d->Ellipse(-p.x, -p.y, p.x, p.y);
 delete d->SelectObject(getPen(ph, pht));
 for ( i = 0, a = pAspects; i < asp_count; i++, a++ ) {
     if ( a->getAspect() != CONJUNCT )
	draw_asp(a);
     }
delete d->SelectObject(old);
}
