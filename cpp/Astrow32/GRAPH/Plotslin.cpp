#include "stdafx.h"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "polar.hpp"
#include "datagrfa.hpp"
#include "AsDrawBs.hpp"
#include "plotslin.hpp"


void SignLinePlotter::setCirc(int ir, int or)
{
 outside.setRad(or);
 inside.setRad(ir);
}

void SignLinePlotter::plot()
{
 CDC *zd = disp();
 CPen *old;

 outside++;
 old = zd->SelectObject(getPen(SIGN,P_THIN));
 for ( int m = 0; m < (360*60); m += (30*60) ) {
     int d = adj_degrees( m, asc );
     zd->MoveTo(inside.xy(d));
     zd->LineTo(outside.xy(d));
     }
 delete zd->SelectObject(old);
}
