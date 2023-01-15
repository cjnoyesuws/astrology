#include "stdafx.h"
#include "asgflags.h"
#include "polar.hpp"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "AsDrawBs.hpp"
#include "arndcirc.hpp"
#include "plothous.hpp"

HousePlotter::HousePlotter(CDC *d, HouseGrfa *h, 
			int ho, int a) : AstDrawBase(d)
{
 hs = h; 
 zd = d; 
 house_out = ho; 
 asc = a; 
 cNum = new PlotAroundCircle(d);
 cDeg = new PlotAroundCircle(d);
 cNum->setAscMin(a);
 cDeg->setAscMin(a);
}

void HousePlotter::setCirc(int ir, int or, int mid, int inc)
{
 outside.setRad(or+3);
 inside.setRad(ir);
 middle.setRad(mid);
 midpoint.setRad(inc);
 cDeg->setCirc(or+3);
 if ( house_out )
    cNum->setCirc(or+3);
 else
    cNum->setCirc((mid<10?mid+15:mid+5));
}


void HousePlotter::plotHouseLines()
{
 CDC *zd = disp();
 CPen *old;
 int i;

 ++inside;
 for ( i = 1; i < 12; i++ ) {
     if ( i!=0 || i != 6 || ( i == 0 && hs->getAdj(0) != asc )
		 || ( ( i == 6 && hs->getAdj(6) != asc+180 &&
			    hs->getAdj(6) != asc-180 )) ) {
	zd->MoveTo(inside.xy(hs->getAdj(i)));
	zd->LineTo(midpoint.xy(hs->getAdj(i)));
	}
     }
 old = zd->SelectObject(getPen(BR+RISE,P_THIN) );
 zd->MoveTo(inside.xy(0));
 zd->LineTo(midpoint.xy(0));
 zd->MoveTo(midpoint.xy(180));
 zd->LineTo(inside.xy(180));
 delete zd->SelectObject( old );
 }

void HousePlotter::plotHouseDegrees()
{
 int i;

 disp()->SetTextColor(getColor(BR+HOUS));
 for ( i = 0; i < hs->getCount(); i++ )
     cDeg->plot(hs->getAdj(i), hs->getGrfa(i) );
}

void HousePlotter::plotHouseNumbers()
{
 static char hsn[12][3] = { "1", "2", "3", "4", "5", "6", "7",
		      "8", "9", "10", "11", "12" };
 int i;

 disp()->SetTextColor(getColor(BR+HOUS));
 for ( i = 0; i < hs->getCount(); i++ )
     cNum->plot(hs->getMhp(i), hsn[i] );
}

void HousePlotter::plot(int mode)
{
 CDC *zd = disp();
 CPen *old;
 CFont *oldf;

 old = zd->SelectObject(getPen(HOUS,P_THIN));
 if ( hs->getAdj(0) == -1 ) {
    delete zd->SelectObject(old);
	return;
    }
 plotHouseLines();
 delete zd->SelectObject(old);
 oldf = zd->SelectObject(pNumFnt);
 if ( mode & HOUSE_NUM )
    plotHouseNumbers();
 zd->SelectObject(oldf);
 oldf = zd->SelectObject(pFnt);
 old = zd->SelectObject(getPen(BR+HOUS,P_THIN));
 if ( mode & HOUSE_DEG )
    plotHouseDegrees();
 zd->SelectObject(oldf);
 delete zd->SelectObject(old);
}
