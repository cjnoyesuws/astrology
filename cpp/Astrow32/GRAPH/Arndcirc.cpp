#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "polar.hpp"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "asdrawbs.hpp"
#include "arndcirc.hpp"
#include "datagrfa.hpp"
#include "asgflags.h"


int PlotAroundCircle::plot(int deg, char *text)
{
 CDC *dsp = disp();
 int x = circ.x(deg), y = circ.y(deg);
 int ax = abs(x), ay = abs(y);

 if ( ax < 10 && y < -10 ) {				 
    dsp->SetTextAlign(TA_CENTER|TA_BOTTOM);
    return( dsp->TextOut( x, y, text ) );
    }
 else if ( ax < 10 && y > 10 ) {
    dsp->SetTextAlign(TA_CENTER|TA_TOP);
    return( dsp->TextOut( x, y, text ) );
    }
 else if ( x < -10 && ay < 10 ) {
    dsp->SetTextAlign(TA_RIGHT|TA_BASELINE);
    return( dsp->TextOut( x, y, text ) );
    }
 else if ( x > 10 && ay < 10 ) {
    dsp->SetTextAlign(TA_LEFT|TA_BASELINE);
    return( dsp->TextOut( x, y, text ) );
    }
 else if ( x > 0 && y > 0 ) {
    dsp->SetTextAlign(TA_LEFT|TA_TOP);
    return( dsp->TextOut( x, y, text ) );
    }
 else if ( x > 0 && y < 0 ) {
    dsp->SetTextAlign(TA_LEFT|TA_BOTTOM);
    return( dsp->TextOut( x, y, text ) );
    }
 else if ( x < 0 && y > 0 ) {
    dsp->SetTextAlign(TA_RIGHT|TA_TOP);
    return( dsp->TextOut( x, y, text ) );
    }
 else {
    dsp->SetTextAlign(TA_RIGHT|TA_BOTTOM);
    return( dsp->TextOut( x, y, text ) );
    }
}

void PlotSigns::plot(int mode)
{
 CFont *old;
 char buf[25];
 int deg, d, i;
 static char *signs[] = {"Aries","Taurus","Gemini","Cancer","Leo","Virgo","Libra","Scorpio","Sagittarius","Capricorn","Aquarius","Pisces"};

 old = disp()->SelectObject(fnt);
 disp()->SetTextColor(getColor(BR+SIGN));
 for ( d = 0, i = 0; d < (360*60); d+= (30*60), i++ ) {
     deg = adj_degrees( d+(15*60), asc_min );
     if ( mode & USE_GLYPH ) {
	buf[0] = i + 'w';
	buf[1] = '\0';
	PlotAroundCircle::plot(deg, buf );
	}
     else {
	PlotAroundCircle::plot(deg,signs[i]);
	}
     }
disp()->SelectObject(old);
}
