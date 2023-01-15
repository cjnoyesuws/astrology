#include "stdafx.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "asdrawbs.hpp"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "datakey.hpp"
#include "asgflags.h"



DataKey::DataKey(CDC *z, CFont *f, CFont *fb,
			int yd, GR_DAT *d ) : AstDrawBase(z)
{
 zd = z;
 fnt = f;
 bfnt = fb;
 yDeep = yd;
 data = d;
 date2 = NULL;
 fudge = 0;
 if (data->version != XP_WIN_GRAPH )
	 fudge = NEW_GRA_DIFF;
 }

void DataKey::drawKey()
{
CFont *old;
 
 int tp = type();

 zd->SetTextAlign(TA_LEFT|TA_TOP);
 old = disp()->SelectObject(bfnt);
 title();
 old = disp()->SelectObject(fnt);
 nameDateTime(0);
 if ( tp != OLD ) {
    nameDateTime(tp);
    if ( strlen( data->trop_side ) )
       tropSideHpc(0);
    }
 if ( tp == CPT )
    compTran();
}

void DataKey::tropSideHpc(int y)
{
 zd->TextOut(0, y+(yDeep * 7), data->trop_side);
 zd->TextOut(0, y+(yDeep * 8), data->house_proc);
}

void DataKey::title()
{
 char *title;
 int tp;
 tp = data->type + fudge;
 if ( fudge )
	 tp++;
 
 switch( tp ) {
       case NATAL_GRAPH_FILE :
	    title = "NATAL HOROSCOPE:";
	    break;
       case COMPATAB_GRAPH_FILE :
	    title = "COMPATIBILITY:";
	    break;
       case TRANSITS_GRAPH_FILE :
	    title = "TRANSITS HOROSCOPE:";
	    break;
       case PROGRESS_GRAPH_FILE :
	    title = "PROGRESSIONS:";
	    break;
       case NUMERIC_GRAPH_FILE :
	    title = "NUMERIC NATAL HOROSCOPE:";
	    break;
       case RELOC_GRAPH_FILE :
	    title = "RELOCATED NATAL HOROSCOPE:";
	    break;
       case COMPOS_GRAPH_FILE :
	    title = "COMPOSITE HOROSCOPE:";
	    break;
       case COMPTR_GRAPH_FILE :
	    title = "COMPOSITE TRANSITS:";
	    break;
	   case SOLAR_GRAPH_FILE :
		title = "SOLAR DIRECTED CHART";
	    break;
	   case HARMONIC_GRAPH_FILE :
	    title = "HARMONIC CHART";
	   break;
	   default :
	    title = "Unknown";
		break;
       }
 zd->SetTextColor( getColor(RISE+BR) );
 zd->TextOut(0,0, title );
}	   

void DataKey::nameDateTime(int w)
{
 char buf[150];
 int y;

 zd->SetTextColor( getColor(PLAN+BR) );
 if ( w )
    y =  4 * yDeep;
 else
    y = yDeep;
 if ( w == TWO || w == 0 || w == CPT || w == PRX ) {
    if ( w == 0 || w == CPT || w == TWO ) {
       zd->SetTextColor( getColor(HOUS+BR) );
       sprintf( buf, "Name: %s", (w?data->name2:data->name1) );
       }
    else
       sprintf( buf, "Location: %s", data->name2 );
    zd->TextOut(0, y, buf);
    zd->SetTextColor( getColor(PLAN+BR) );
    if ( w == 0 || w == CPT || w == TWO )
       sprintf( buf, "Birth Date: %s", (w?data->date2:data->date1) );
    else
       sprintf( buf, "Long: %s", data->date2 );
    zd->TextOut(0, y+yDeep, buf);
    if ( w == 0 || w == CPT || w == TWO )
       sprintf( buf, "Time: %s", (w?data->time2:data->time1) );
    else
       sprintf( buf, "Lat: %s", data->time2);
    zd->TextOut(0, y+yDeep+yDeep,buf);
    }
 else if ( w == PRG ) {
    zd->TextOut(0, y,"Progressed:");
    zd->TextOut(0, y+yDeep, data->date2);
    }
 else if ( w == TRN && date2 != NULL ) {
    zd->TextOut(0, y,"Transits:");
    zd->TextOut(0, y+yDeep,date2);
    }
 else if ( w == TRN && date2 == NULL ) {
    zd->TextOut(0, y,"Transits:");
    zd->TextOut(0, y+yDeep,data->date2);
    }
  else if ( w == SOL && date2 == NULL ) {
    zd->TextOut(0, y,"Direction:");
    zd->TextOut(0, y+yDeep,data->date2);
    }
   else if ( w == HRM && date2 == NULL ) {
    zd->TextOut(0, y,"Harmonic:");
    zd->TextOut(0, y+yDeep,data->date2);
    }
}

int DataKey::type()
{
 static int ar[] = { 0, OLD, TWO, TRN, PRG, OLD, 0, 0, OLD, TWO, 0, 0, 0, OLD, CPT, SOL, HRM };
 int tp, tpx;
 tpx = data->type - (LAST_NON_GRAPH-fudge);
 if ( fudge )
	 tpx++;
 tp = ar[tpx];
 if ( tp == OLD && strlen( data->time2 ) )
    return( PRX );
 else
    return( tp );
}

void DataKey::compTran()
{
 int y;
 if ( strlen(data->trop_side) )
    y = 9 * yDeep;
 else
    y = 4 * yDeep;
 zd->TextOut(0, y,"Transits:");
 zd->TextOut(0, y+yDeep,date2);
}

#ifdef DELUXE
PlanetsKey::PlanetsKey(CDC *z, CFont *f, int yd, int x, GraphicDataGroup *d ) : AstDrawBase(z)
{
 zd = z;
 fnt = f;
 yDeep = yd;
 xClient = x;
 p = d->getPlanets();
}


void PlanetsKey::draw()
{
 int i, c, y, a, b, wg, wd, gap, xg, xd;
 char buf[20];
 static char plan[][3] = { "AS", "SU", "MO", "ME", "VE", "MA", "JU", "SA", "UR",
			 "NE", "PL", "NN", "SN", "MC", "IC", "PF", "VT", "EP",
			 "CR", "PA", "JN", "VS", "CN" };

 if ( p->getMode() & USE_GLYPH ) {
    buf[0] = '`' + 2;
    buf[1] = '\0';
    wg = zd->GetTextExtent(buf).cx;
    wd = zd->GetTextExtent("29x59R").cx;
    gap = wg;
    }				
 else {
    wg = zd->GetTextExtent(plan[2]).cx;
    wd = zd->GetTextExtent("29SCO59R").cx;
    gap = wg/2;
    }
 xg = xClient - wd - wg - gap;
 xd = xClient - wd;
 zd->SetTextColor( getColor(CIRC) );
 c = p->getCount();
 zd->SetTextAlign(TA_LEFT|TA_TOP);
 zd->SelectObject(fnt);
 for ( i = 0, y = 0; i < c; i++, y += yDeep ) {
     if ( p->getMode() & USE_GLYPH ) {
	buf[0] = '`' + i;
	buf[1] = '\0';
	zd->TextOut(xg, y, buf);
	}
     else
	zd->TextOut(xg, y, plan[i]);
     char *deg = p->get(i, a, b);
     zd->TextOut(xd, y, deg );
     }
}
#endif

