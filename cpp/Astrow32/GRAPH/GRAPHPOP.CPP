#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "paths.hpp"
#include "fptr.h"
#include "filelst.hpp"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "graspgrd.hpp"
#include "key.hpp"
#include "datakey.hpp"
#include "dib.hpp"
#include "grappane.hpp"
#include "astromn.h"
#include "dialogs.h"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "inifile.hpp"
#include "graopt.hpp"
#include "math.h"
#include "utl.h"
#ifdef DELUXE
#include "grpoped.hpp"

extern int get_aspect_text( char *file, int, int, int, int );
extern int get_text( char *file, int planet, int house, int sign, int psign, int min, int type );
#endif

GR_ASPT *AstGraphicsPane::findAspect( zPoint &p )
{
#ifdef DELUXE
 int gSize = fontSize(38)+1;
 int f = ((rActive.height()-1 - gSize - p.y() - cyTopOffset) / gSize);
 int s = ((rActive.width()-1 - gSize - p.x() - cxLeftOffset)  / gSize);
 s = gridMaxpt - s - 1;
 if ( f < 0 || f >= gridMaxpt )
    return( NULL );
 if ( s < 0 || s >= gridMaxpt )
    return(  NULL );
 int cnt;
 GR_ASPT * grasp = gridAspts;
 if ( !gridCnt )
    return( NULL );
 for ( int i = 0; i < gridCnt; i++, grasp++ ) {
       if ( ( grasp->getFirst() == f && grasp->getSecond() == s ) ||
	    ( grasp->getFirst() == s && grasp->getSecond() == f ) )
          return( grasp );   
       }
#endif
return( NULL );
}

int AstGraphicsPane::toDegrees( zPoint &p, int &rad )
{
#ifdef DELUXE
 zPoint ap = p;
 ap.x() -= radiusData.getOffset();
 ap.y() -= rActive.height()/2;
 ap.x() += cxLeftOffset;
 ap.y() += cyTopOffset;
 int abx = abs(ap.x());
 int aby = abs(ap.y());
 long t = ((long)abx * abx) + ((long)aby * aby);
 double drd = (int)sqrt((double)t);
 rad = (int) drd;
 if ( drd == 0.0 )
    return( 0 );
 double sn = (double) -ap.y() / drd;
 sn = (asin( sn ) * 180) /PI;
 if ( ap.y() < 0 && ap.x() < 0 )
    return( (int)(sn));
 else if ( ap.y() < 0 && ap.x() >= 0 )
    return( (int)(90.0-sn+90.0));
 else if ( ap.y() >= 0 && ap.x() >= 0 )
    return( (int)(90.0-sn+90.0));
 else 
    return( (int) (sn + 360.0) );
#endif
 return( 0 ); 
}

int AstGraphicsPane::doPop( zPoint &p, char *file )
{
#ifdef DELUXE
 int degrees, rads, planet = -1, sign = -1, house = -1, psign = -1, min = -1, circ = 0;
 int type;

 degrees = toDegrees( p, rads );
 if ( radiusData.isInAspectCirc(rads) )
    return( 0 );
 if ( !radiusData.isInOusideCirc(rads) ) {
    if ( drawMode & SHOW_AGRID ) {
       GR_ASPT *pa = findAspect( p );
       if ( pa != NULL ) {
	  int tp = data->getData()->type;
	  if ( !which_houses && data->getData()->type == PROGRESS_GRAPH_FILE )
	     tp = NATAL_GRAPH_FILE;
	  return( get_aspect_text( file, pa->getFirst(), pa->getSecond(), pa->getAspect(), tp ) );
	  }
       else
	  return( 0 );
       }
    else
       return( 0 );
    }
 if ( plot2 != NULL && radiusData.isInSecondCirc(rads) ) {
    circ = 1;
    planet = plot2->find( degrees, rads, psign, min );
    }
 else {
    circ = 0;
    planet = plot->find( degrees, rads, psign, min );
    }
 if ( !planet )
    degrees = 0;

 type = data->getData()->type;
 if ( type == COMPATAB_GRAPH_FILE ) {
    if (which_houses && !circ )
       house = compGroup->getHouse(degrees, sign);
    else if ( plot2 == NULL || (!which_houses && circ) )
       house = dataGroup->getHouse(degrees, sign);
    else
       house = -2;
    }
 else if ( plot2 != NULL ) {
    if ( !circ && !which_houses ) {
       house = dataGroup->getHouse(degrees, sign);
       type = NATAL_GRAPH_FILE;
       }
    else if ( !which_houses && circ )
       house = dataGroup->getHouse(degrees, sign);
    else
       house = -2;
    }
 else
    house = dataGroup->getHouse(degrees, sign);
 degrees += ((asc_min+30)/60);
 if ( planet == MED_COELI )
    house = 10;
 else if ( !planet )
    house = 1;
 else if ( planet == IM_COELI )
    house = 4;
 return( get_text( file, planet, house, sign, psign, min, type ) );
#else
 return( 0 );
#endif
}

AstGraphicsPane::mouseButtonDown(zMouseClickEvt *e)
{
#ifdef DELUXE
 unsigned long t;
 zPoint p = *e;
 static unsigned long lastClk;

 if ( e->isButtonDown(1) ) {
    t=GetCurrentTime();
    if (lastClk+dblclkTime>=t) {
       if ( !_access("$$CLICK$.TMP", 4) )
	  unlink("$$CLICK$.TMP");
       doPop( p, "$$CLICK$.TMP" );
       if ( !_access("$$CLICK$.TMP", 4) ) {
	  GrPopView *gpv = new GrPopView((zFrameWin *)parent(), "$$CLICK$.TMP" );
	  gpv->show();
	  unlink("$$CLICK$.TMP");
	  }
       }
    }
 lastClk = t;
#endif
 return( 1 );
}
