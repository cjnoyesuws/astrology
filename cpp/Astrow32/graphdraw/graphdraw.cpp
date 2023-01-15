// graphdraw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"						  
#include <stdlib.h>
#include <string.h>
#include "Astrow.h"
#include "vicdefs.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "errors.fns"
#include "graphdat.hpp"
#include "paths.hpp"
#include "aspect.h"
#include "vicdefs.h"
#include <io.h>
#include <math.h>
#include "utl.h"
#include "errors.fns"
#include "radius.h"
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "dataext.h"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "plotslin.hpp"
#include "tickcirc.hpp"
#include "graspgrd.hpp"
#include "graspcir.hpp"
#include "key.hpp"
#include "datakey.hpp"
#include "plotgrtp.hpp"

void Draw(CDC* pDC)	  
{ 
int l;
CAstrographDoc* pDoc = GetDocument();
CFont *old;
data = pDoc->GetDataPtr();
ASSERT_VALID(pDoc);
if ( !pDoc->IsOk() )
   return;
//baseMetrics->newDisplay(pDC);
COLORREF bk = RGB(0,0,0);
pDC->SetBkColor(bk);
pDC->SetBkMode( TRANSPARENT );
CRect r;
pDC->GetClipBox(&r);
if (_type)
   pDC->FillRect(&rActive,pbBack);
else
   pDC->FillRect(&r,pbBack);
pDC->SelectObject(pbBack);
if ( pDC->IsPrinting() )
   pDC->SetWindowOrg( cxLeftMgn, cyTopMgn  );
else
   pDC->SetWindowOrg( cxLeftOffset, cyTopOffset  );
DataKey *pdk = new DataKey(pDC, pDataFnt, pBdDataFnt, cyChar+1, data->getData());
if ( pCurChart != NULL )
   pdk->setDate2(pCurChart->getDate());
pdk->drawKey();
delete pdk;
#ifdef DELUXE
if ( data->ncharts() == 1 ) {
   PlanetsKey *pk = new PlanetsKey(pDC, pDegFnt, cyChar+1,
		rActive.Width(), dataGroup );
   pk->draw();
   delete pk;
   }
#endif 
WheelKey *pwk = new WheelKey( pDC, pDataFnt, pBdDataFnt,
	rActive.Height()-((cyChar+1) * 5), cxChar*2, cyChar+1 );
 pwk->drawKeys();
 delete pwk;
 if ( pDC->IsPrinting() )
 	pDC->SetWindowOrg( (-radiusData.getOffset())+cxLeftMgn,
	       (-(rActive.Height()/2))+cyTopMgn );
 else
	pDC->SetWindowOrg( (-radiusData.getOffset())+cxLeftOffset,
	       (-(rActive.Height()/2))+cyTopOffset );
 if ( drawMode & SIGN_NAME ) {
    PlotSigns *pps = new PlotSigns(pDC,
	 radiusData.getOutsideCirc(),
	 (drawMode & USE_GLYPH?pGlyphFnt:pDataFnt), asc_min);
    pps->plot(drawMode);
    delete pps;
    }
 if (drawMode & (SIGN_TICK|DEC_TICK|DEG_TICK) ) {
    if ( drawMode & SIGN_TICK ) {
       
	    old = pDC->SelectObject(pTickGlyphFnt);
	    SignTickCircle *pstc = new SignTickCircle( pDC,
	        radiusData.getSignTick(),
	        radiusData.getOutsideCirc(),asc_min);
        pstc->draw();
        delete pstc;
        pDC->SelectObject(old);
       }
    if ( drawMode & DEC_TICK ) {
       DecanTickCircle *pdtc = new DecanTickCircle(pDC,
	        radiusData.getDecanTick(),
	        radiusData.getSignTick(),asc_min);
       pdtc->draw();
       delete pdtc;
       }
    if ( drawMode & DEG_TICK ) {
       DegreeTickCircle *pdetc = new DegreeTickCircle( pDC,
	       radiusData.getDegreeTick(),
	       radiusData.getDecanTick(),asc_min );
       pdetc->draw();
       delete pdetc;
       }
    }
 else {
    PlainCircle *ppc = new PlainCircle( pDC,
    	  radiusData.getMainCirc());
    ppc->draw();
    delete ppc;
    }
 if (compGroup != NULL && data->ncharts() > 1) {
    PlainCircle *ppc2 = new PlainCircle( pDC,
	      radiusData.getSecondCirc());
    ppc2->draw();
    delete ppc2;
    }
 if ( drawMode & SHOW_SLIN ) {
    SignLinePlotter *pslp = new SignLinePlotter(pDC,asc_min);
    pslp->setCirc(radiusData.getInCirc(),
        radiusData.getMainCirc());
    pslp->plot();
    }
 if ( dataGroup->getAsc() != -1 ) {
    CFont *pFnthn;
    LPLOGFONT fsp = pDegSpec;
    if ( !(drawMode & HOUS_OUTS) ) {
       fsp->lfHeight *= 3;
       fsp->lfHeight /= 4;
       fsp->lfWidth *= 3;
       fsp->lfWidth /= 4;
       pFnthn = new CFont();
	   pFnthn->CreateFontIndirect(fsp);
       }
    HousePlotter *php = new HousePlotter(pDC,
        (which_houses ? compGroup->getHouses() :
	dataGroup->getHouses()), drawMode & HOUS_OUTS, old_asc_min);
    php->setFont(pDegFnt);
    if ( !(drawMode & HOUS_OUTS) )
       php->setNumFont(pFnthn);
    php->setCirc(radiusData.getMainCirc(),
	radiusData.getOutsideCirc(),
	radiusData.getMidCirc(),
	radiusData.getInCirc() );
    php->plot(drawMode);
    if ( !(drawMode & HOUS_OUTS) )
       delete pFnthn;
    delete php;
    }
 if ( drawMode & PLOT_CLASSIC ) {
    if ( plot != NULL )
       delete plot;
    plot = (PlanetPlotter *) new PlanetPlotterClassical(pDC,
	      dataGroup->getPlanets(), radiusData.getMainCirc()
	      - (radiusData.getMargin()), WH_OUTER );
          ((PlanetPlotterClassical *)plot)->setFonts(pDegSpec);
    plot->doPlot();
    }
 else {
    if ( plot != NULL )
       delete plot;
    plot = new PlanetPlotter(pDC, dataGroup->getPlanets(),
	      radiusData.getMainCirc() - radiusData.getMargin(),
	      0, (compGroup != NULL ? radiusData.getSecondCirc()
	      : radiusData.getInCirc()), WH_OUTER );
    if ( drawMode & SHOW_PDEGS )
       plot->setFonts(pGlyphSpec,pDegSpec);
    else
       plot->setFonts(pGlyphSpec,0);
    plot->doPlot();
    }
 if (drawMode & SHOW_ASPT && data->getData()->num_aspects) {
    short cnt;
    GR_ASPT *pas = dataGroup->getAspects(cnt);
    AspectCircle *pac = new AspectCircle(pDC, pas, cnt,
	      radiusData.getAspectCirc(), cyChar );
    pac->draw();
    delete pac;
    }
 if (compGroup != NULL && data->ncharts() > 1) {
    if ( drawMode & PLOT_CLASSIC ) {
       if ( plot2 != NULL )
	      delete plot2;
       plot2 = (PlanetPlotter *) new PlanetPlotterClassical(pDC,
	        compGroup->getPlanets(), radiusData.getSecondCirc(), WH_INNER );
            ((PlanetPlotterClassical *)plot2)->setFonts(pDegSpec);
       plot2->doPlot();
       }
    else {
       if ( plot2 != NULL )
	      delete plot2;
       plot2 = new PlanetPlotter(pDC, compGroup->getPlanets(),
            radiusData.getSecondCirc(), 0, radiusData.getSecondCirc(), WH_INNER );
       if ( drawMode & SHOW_PDEGS )
	      plot2->setFonts(pGlyphSpec,pDegSpec);
       else
	      plot2->setFonts(pGlyphSpec,0);
       plot2->doPlot();
       }
    }
 if ( pDC->IsPrinting() ) 
    pDC->SetWindowOrg( cxLeftMgn, cyTopMgn  );
 else
	pDC->SetWindowOrg( cxLeftOffset, cyTopOffset  );
 l = data->getData()->type;
 if ( l == COMPATAB_GRAPH_FILE || l == PROGRESS_GRAPH_FILE ||
      l == TRANSITS_GRAPH_FILE || l == COMPTR_GRAPH_FILE ) {
    StatusKey *psk = new StatusKey( pDC, BR+HOUS,
	      rActive.Width(), 0, TA_TOP|TA_RIGHT, pDataFnt);
    psk->draw("HOUSES:");
    delete psk;
    StatusKey *psk2 = new StatusKey( pDC, BR+RISE,
	      rActive.Width(), cyChar+1, TA_TOP|TA_RIGHT, pBdDataFnt);
    if ( data->getData()->type == COMPATAB_GRAPH_FILE ) {
       if ( which_houses )
          psk2->draw(data->getData()->name2);
       else
          psk2->draw(data->getData()->name1);
       }
    if ( data->getData()->type == PROGRESS_GRAPH_FILE ) {
       if ( which_houses )
          psk2->draw("Progressed");
       else
          psk2->draw(data->getData()->name1);
       }
    if ( data->getData()->type == TRANSITS_GRAPH_FILE ) {
       if ( which_houses )
	      psk2->draw("Transits");
       else
	      psk2->draw(data->getData()->name1);
       }
    if ( data->getData()->type == COMPTR_GRAPH_FILE ) {
       if ( which_houses )
	      psk2->draw("Transits");
       else
	      psk2->draw("Composite Houses");
       }
    delete psk2;
    }
 CPoint agpt;
 CSize  agsz;
 agpt.x = rActive.Width()-1;
 agpt.y = rActive.Height()-1;
 agsz.cx = fontSize(38)+1;
 agsz.cy = fontSize(38)+1;
 
 if (drawMode & SHOW_AGRID && data->getData()->num_grid_aspects > 0 && !which_houses) {
    old = pDC->SelectObject( pGridFont );
    gridAspts = data->getGridAspects(gridCnt);
    gridMaxpt = data->getData()->maxpt;
    AspectGrid *ag = new AspectGrid(pDC, agpt, agsz, gridAspts, gridCnt, 
		     data->getData()->maxpt );
    ag->draw();
    delete ag;
    pDC->SelectObject(old);
    }
 else if (drawMode & SHOW_AGRID && data->getData()->num_other_grid_aspects > 0 && which_houses ) {
    old = pDC->SelectObject( pGridFont );
	gridAspts = data->getOtherGridAspects(gridCnt);
    gridMaxpt = data->getData()->maxpt;
    AspectGrid *ag = new AspectGrid(pDC, agpt, agsz, gridAspts, gridCnt, 
		     data->getData()->maxpt );
    ag->draw();
    delete ag;
    pDC->SelectObject(old);
	}
 else if (drawMode & SHOW_AGRID && (data->getData()->type ==
       TRANSITS_GRAPH_FILE||data->getData()->type == COMPTR_GRAPH_FILE ) &&
       pCurChart != NULL && pCurChart->aspect_count > 0 ) {
    old = pDC->SelectObject( pGridFont );
    gridAspts = pCurChart->getAspects(gridCnt);
    gridMaxpt = pCurChart->maxpt;
    AspectGrid *ag = new AspectGrid(pDC, agpt, agsz, gridAspts, gridCnt, gridMaxpt );
    ag->draw();
    delete ag;
    pDC->SelectObject(old);
    }
 else {
    gridAspts = NULL;
    gridCnt = 0;
    gridMaxpt = 0;
    }
pDC->SetWindowOrg( 0, 0 );
}			  



void computeRadiusData()
{
 int x, h, w, y;
 float rad, f;

 h = rActive.Height();
 w = rActive.Width();
 if ( thePolarScaler.isEnabled() ) {
    w = thePolarScaler.invScaleX(w);
    h = thePolarScaler.invScaleY(h);
    }
 if ( drawMode & SHOW_AGRID ) {
    if (w < h )
       rad = ((float)w * .42);
    else
       rad = ((float)h * .44);
    }
 else {
    if (w < h )
       rad = ((float)w * .43);
    else
       rad = ((float)h * .46);
    }
 radiusData.points = (int)rad * 2;
 if ( drawMode & SHOW_PDEGS )
    radiusData.margin =(int) rad * .008;
 else
    radiusData.margin =(int) rad * .015;
 radiusData.midCirc = (int) rad/20.0;
 radiusData.inCirc = 0 ;
 radiusData.outsideCirc= (int)rad;
 if ( drawMode & SIGN_TICK ) {
    f = rad * .093;
    rad -= f;
    radiusData.signTick = (int) rad;
    }
 else
    radiusData.signTick = rad;
 if ( drawMode & DEC_TICK ) {
    f = rad * .03;
    rad -= f;
    radiusData.decanTick = (int) rad;
    }
 else
    radiusData.decanTick = rad;
 if ( drawMode & DEG_TICK ) {
    f = rad * .03;
    rad -= f;
    radiusData.degreeTick = (int) rad;
    }               
 else
    radiusData.degreeTick = rad;
 radiusData.mainCirc = rad;
 if ( data->ncharts() == 2 ) {
    f = rad * .55;
    rad = f; 
    radiusData.secondCirc = (int) rad;
    }
 else if (drawMode & SHOW_ASPT &&
       data->getData()->num_aspects) {
    f = rad * .35;
    rad = f; 
    radiusData.aspectCirc = (int) rad;
    radiusData.midCirc = rad;
    radiusData.inCirc = rad;
    }
 else {
    radiusData.midCirc = (int) rad/20.0;
    radiusData.inCirc = 0;
    }
 x = (rActive.Width()/2) - thePolarScaler.scaleX(radiusData.outsideCirc);
 x /= 5;
 radiusData.offset = (rActive.Width()/2) + x;
 if ( drawMode & SHOW_AGRID )
    radiusData.offset = (rActive.Width()/2) - (x/2);
 else
    radiusData.offset = (rActive.Width()/2) + (x/2);
}

int fontSize(int div)
{
 
 float v = radiusData.getPoints();
 
 div++;
 v *= fontScale;
 v /= (float)div;
 return( (int) v);

}


void setupGrfas()
{
CAstrographDoc* pDoc = GetDocument();
data = pDoc->GetDataPtr();
asc_min = data->getData()->natal_minutes[0];
old_asc_min = data->getData()->natal_minutes[0];
dataGroup->doGrfs(data->getData()->natal_minutes,
     data->getData()->maxpt, data->getData()->natal_house_cusps,
     drawMode, old_asc_min );
asc_min = dataGroup->getAsc();
if ( data->ncharts() == 1 && data->getData()->num_aspects ) {
    short n;
    GR_ASPT *as;
    as = data->getAspects(n); 
    dataGroup->doAspects(as, n);
    }
if ( data->getData()->type == TRANSITS_GRAPH_FILE ||
		data->getData()->type == COMPTR_GRAPH_FILE  ) {
	if ( compGroup == NULL )
	   compGroup = new GraphicDataGroup();
	if ( pCurChart == NULL )
       pCurChart = data->getFirstChart();
	compGroup->doGrfs( ( data->getData()->num_charts > 0 ?
       pCurChart->getChartMinutes() :
       data->getData()->other_minutes ),
       data->getData()->num_charts > 0 ? pCurChart->maxpt :
	  data->getData()->maxpt, (short *)data->getData()->other_house_cusps,
      drawMode, old_asc_min );
    }
 else {
    if ( compGroup == NULL )
	   compGroup = new GraphicDataGroup();
	compGroup->doGrfs(data->getData()->other_minutes,
    data->getData()->maxpt, (short *)data->getData()->other_house_cusps,
    drawMode, old_asc_min );
    }
}



int main(int argc, char* argv[])
{
	return 0;
}
