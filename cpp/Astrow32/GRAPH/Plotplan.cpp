#include "stdafx.h"
#include "stdlib.h"
#include "polar.hpp"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "asdrawbs.hpp"
#include "grlist.hpp"
#include "plotplan.hpp"


void PlanetPlotter::doPlot()
{
 CFont *old;

 setRads();
 zd->SetTextAlign(TA_CENTER|TA_BASELINE);
 old = disp()->SelectObject(glyph);
 plotGlyphs();
 disp()->SelectObject(old);
 if ( showDegs ) {
    zd->SetTextAlign(TA_CENTER|TA_TOP);
    old = disp()->SelectObject(deg);
    plotDegs();
    disp()->SelectObject(old);
	}
}


void PlanetPlotter::plotDegs()
{
 int i, r, d;
 char *pt;
 CDC *zd = disp();
 CPoint px;
 PolarCoord p(0);

 disp()->SetTextColor(getColor(BR+RISE) );
 pt = pgp->get(0, r, d);
 if ( d != -1 && r != -1 ) {
    px = p.xy(d,r);
    zd->TextOut( px.x, px.y, pt);
	}
 disp()->SetTextColor(getColor(BR+PLAN) );
 for ( i = 0; i <= (pgp->getCount()>EAST_POINT?EAST_POINT:pgp->getCount()); i++ ) {
     pt = pgp->get(i, r, d);
     if ( d == -1 || r == -1 )
        continue;
     px = p.xy(d,r);
	 zd->TextOut( px.x, px.y, pt);
     }
}


void PlanetPlotter::plotGlyphs()
{
 static char plan[][3] = { "AS", "SU", "MO", "ME", "VE", "MA", "JU", "SA", "UR",
			 "NE", "PL", "NN", "SN", "MC", "IC", "PF", "VT", "EP",
			 "CR", "PA", "JN", "VS", "CN" };
 char buf[4];
 int i, r, d;
 CDC *zd = disp();
 CPoint px;
 PolarCoord p(0);

 disp()->SetTextColor(getColor(BR+RISE) );
 for ( i = 0; i <= (pgp->getCount()>EAST_POINT?EAST_POINT:pgp->getCount()); i++ ) {
     if ( i == 1 )
	disp()->SetTextColor(getColor(BR+PLAN) );
     pgp->get(i, r, d);
     px = p.xy(d,r);
	 if ( r == -1 || d == -1 )
        continue;
     if ( pgp->getMode() & USE_GLYPH  ) {
	    buf[0] = '`' + i;
	    buf[1] = '\0';
	    zd->TextOut( px.x, px.y, buf);
	    }
     else 
	   	 zd->TextOut( px.x, px.y, plan[i]);
       	 }
}

void PlanetPlotter::setRads()
{
 int w = theWidth/2;
 int i;

 for ( i = 0; i <= pgp->getCount(); i++ )
     pgp->setRad(i,pList->checknAdd(pgp->getAdj(i))-w);
}

void PlanetPlotter::setFonts( LOGFONT *pFg, LOGFONT *pFd)
{
 CDC *zd = disp();	   
 CSize d;
 CFont *old;
 int h;

 pFontg = pFg;
 pFontd = pFd;
 if ( pFontd == 0 )
    showDegs = 0;
 else
    showDegs = 1;
 if ( createFont ) {
    glyph = new CFont();
    glyph->CreateFontIndirect(pFg);
	if ( showDegs ) {
       deg = new CFont();
	   deg->CreateFontIndirect(pFd);
	   }
    old = zd->SelectObject(glyph);
    if ( pgp->getMode() & USE_GLYPH  )
       d = zd->GetTextExtent("~");
    else
       d = zd->GetTextExtent("MO");
    zd->SelectObject(old);
	h = d.cy;
    if ( showDegs ) {
       old = zd->SelectObject(deg);
       if ( pgp->getMode() & USE_GLYPH  )
	  d = zd->GetTextExtent("29x59R");
       else                              /* x is a glyph */
	  d = zd->GetTextExtent("29SCO59R");
       theWidth = thePolarScaler.invScaleX(d.cx);
       theHeight = thePolarScaler.invScaleY(d.cy+h);
       pList->setWidth(theWidth,theHeight);
	   zd->SelectObject(old);
       }
    else {
       theWidth = thePolarScaler.invScaleX(d.cx+2);
       theHeight = thePolarScaler.invScaleY(d.cy);
       pList->setWidth(theWidth, theHeight );
       }
    }
}

PlanetPlotter::PlanetPlotter(CDC *z, PlanGrfa *p, int init, int failolp, int min, int wh )
							  : AstDrawBase(z)
{
 static short outvar[10] = { 10, 9, 8, 7, 6, 7, 9, 11, 13, 13 };
 static short invar[10] = { 16, 15, 15, 14, 12, 12, 13, 14, 16, 17 };

  pgp = p; createFont = 1;
  pList = new PlanetList(init, min,
	 ( wh==WH_INNER ? invar:outvar), failolp);
}

PlanetPlotter::~PlanetPlotter()
{
  delete pList;
  if (createFont ) {
     delete glyph;
     if ( showDegs )
	    delete deg;
     }
}

		  

void PlanetPlotterClassical::setFonts( LOGFONT *pFd )
{
 CSize d;
 CFont *f, *old;
 CDC *zd = disp();
 
 f = new CFont();
 f->CreateFontIndirect(pFd);
 old = zd->SelectObject(f);
 if ( pgp->getMode() & USE_GLYPH  )
    d = zd->GetTextExtent("x 29x59R");
 else
   d = zd->GetTextExtent("AS 29SCO59R");  
 theHeight = thePolarScaler.invScaleX(d.cy);
 theWidth = thePolarScaler.invScaleX(d.cx);
 pList->setWidth(theWidth, theHeight);
 delete zd->SelectObject(old);
 pFontd = pFd;
}

void PlanetPlotterClassical::plotOne( int i)
{
 char buf[25], *p;
 CFont *fnt, *old;
 CPoint px;
 int d, dd, r;
 static char plan[][3] = { "AS", "SU", "MO", "ME", "VE", "MA", "JU", "SA", "UR",
			 "NE", "PL", "NN", "SN", "MC", "IC", "PF", "VT", "EP",
			 "CR", "PA", "JN", "VS", "CN" };
 p = pgp->get(i, r, d);
 r = pList->checknAdd(d);
 pgp->setRad(i,r);
 if ( d <= 90 || d >= 270 ) {
    dd = d;
    dd = 360-dd;
    }
 else {
    dd = d;
    dd -= 180;
    if ( dd < 0 )
       dd += 360;
    dd = 360-dd;
    r -= theWidth;
    }
 PolarCoord pc(r);
 if ( pgp->getMode() & USE_GLYPH  ) {
    buf[0] = '`' + i;
    buf[1] = ' ';
    strcpy( &buf[2], p );
    }
 else {
    strcpy( buf, plan[i] );
    strcat( buf, " " );
    strcat( buf, p );
    }
 pFontd->lfEscapement = dd*10;
 fnt = new CFont();
 fnt->CreateFontIndirect(pFontd);
 old = zd->SelectObject(fnt);
 d -= 2;
 if ( d < 0 )
    d += 360;
 px = pc.xy(d);
 zd->TextOut(px.x, px.y, buf);
 delete zd->SelectObject(old);
}

void PlanetPlotterClassical::setRads()
{
 /*int i;

 for ( i = 0; i <= pgp->getCount(); i++ )
     pgp->setRad(i,theWidth);
 */
}

void PlanetPlotterClassical::doPlot()
{
 int i;
 CDC *zd = disp();
 
 zd->SetTextAlign(TA_LEFT|TA_BASELINE);
 zd->SetTextColor(getColor(BR+RISE) );
 plotOne(0);
 zd->SetTextColor(getColor(BR+PLAN) );
 setRads();
 for ( i = 1; i <= (pgp->getCount()>EAST_POINT?EAST_POINT:pgp->getCount()); i++ )
     plotOne(i);
    
}
