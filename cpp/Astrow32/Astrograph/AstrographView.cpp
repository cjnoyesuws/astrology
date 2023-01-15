// AstrographView.cpp : implementation of the CAstrographView class
//

#include "stdafx.h"						  
#include <stdlib.h>
#include <string.h>
#ifndef GRAVIEWER
#include "astrow.h"
#else
#include "Astrograph.h"
#endif
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
#include "graopt.hpp"
#include "inifile.hpp"
#include "AstrographDoc.h"
#include "AstrographView.h"
#include "popuped.h"
#include "gracolor.hpp"
#include "grafont.hpp"
#include "grafont.h"
#include "gracolor.h"
#include "graphopts.h"
#include "direc.hpp"
#include "directories.h"


#ifdef PRO
#include "grafilop.hpp"
#include "graphfileopts.h"
#include "grconv.hpp"



extern void setMono(int i);
extern void swapMonoClr(int i);

extern int fixupMetafile( char *temp, char *name );

#endif
int wasToFit;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void init_popup_text_report();
extern void close_text_report();
extern int get_aspect_text( char *file, int, int, int, int );
extern int get_text( char *file, int planet, int house, int sign, int psign, int min, int type );


/////////////////////////////////////////////////////////////////////////////
// CAstrographView

IMPLEMENT_DYNCREATE(CAstrographView, CView)

BEGIN_MESSAGE_MAP(CAstrographView, CView)
	//{{AFX_MSG_MAP(CAstrographView)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_VIEW_FITWIN, OnViewFitwin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FITWIN, OnUpdateViewFitwin)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_VIEW_LARGERFONT, OnViewLargerfont)
	ON_COMMAND(ID_VIEW_SMALLERFONT, OnViewSmallerfont)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGERFONT, OnUpdateView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALLERFONT, OnUpdateView)
	ON_COMMAND(ID_GRAPHICS_SIGNTICKWHEEL, OnGraphicsSigntickwheel)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_SIGNTICKWHEEL, OnUpdateGraphicsSigntickwheel)
	ON_COMMAND(ID_GRAPHICS_DECANTICKWHEEL, OnGraphicsDecantickwheel)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_DECANTICKWHEEL, OnUpdateGraphicsDecantickwheel)
	ON_COMMAND(ID_GRAPHICS_DEGREETICKWHEEL, OnGraphicsDegreetickwheel)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_DEGREETICKWHEEL, OnUpdateGraphicsDegreetickwheel)
	ON_COMMAND(ID_GRAPHICS_PLOTCLASSICALLY, OnGraphicsPlotclassically)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_PLOTCLASSICALLY, OnUpdateGraphicsPlotclassically)
	ON_COMMAND(ID_GRAPH_SHOWHOUSEDEGREES, OnGraphShowhousedegrees)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SHOWHOUSEDEGREES, OnUpdateGraphShowhousedegrees)
	ON_COMMAND(ID_GRAPH_SHOWHOUSENUMBERS, OnGraphShowhousenumbers)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SHOWHOUSENUMBERS, OnUpdateGraphShowhousenumbers)
	ON_COMMAND(ID_GRAPH_SHOWSIGNLINES, OnGraphShowsignlines)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SHOWSIGNLINES, OnUpdateGraphShowsignlines)
	ON_COMMAND(ID_GRAPH_SHOWSIGNNAME, OnGraphShowsignname)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SHOWSIGNNAME, OnUpdateGraphShowsignname)
	ON_COMMAND(ID_GRAPHICS_INNEROUTERHOUSECUSPS, OnGraphicsInnerouterhousecusps)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_INNEROUTERHOUSECUSPS, OnUpdateGraphicsInnerouterhousecusps)
	ON_COMMAND(ID_GRAPHICS_HOUSENUMBERSOUTSIDE, OnGraphicsHousenumbersoutside)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_HOUSENUMBERSOUTSIDE, OnUpdateGraphicsHousenumbersoutside)
	ON_COMMAND(ID_GRAPHICS_SHOWPLANETDEGREES, OnGraphicsShowplanetdegrees)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_SHOWPLANETDEGREES, OnUpdateGraphicsShowplanetdegrees)
	ON_COMMAND(ID_GRAPH_SHOWASPECTGRID, OnGraphShowaspectgrid)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SHOWASPECTGRID, OnUpdateGraphShowaspectgrid)
	ON_COMMAND(ID_GRAPH_SHOWASPECTS, OnGraphShowaspects)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_SHOWASPECTS, OnUpdateGraphShowaspects)
	ON_COMMAND(ID_GRAPHICS_DECREASEHOUSECUSPS, OnGraphicsDecreasehousecusps)
	ON_COMMAND(ID_GRAPHICS_INCREASEHOUSECUSPS, OnGraphicsIncreasehousecusps)
	ON_COMMAND(ID_GRAPHICS_NORMALHOUSECUSPS, OnGraphicsNormalhousecusps)
	ON_COMMAND(ID_GRAPH_USEGLYPHS, OnGraphUseglyphs)
	ON_UPDATE_COMMAND_UI(ID_GRAPH_USEGLYPHS, OnUpdateGraphUseglyphs)
	ON_COMMAND(ID_GRAPHICS_USEFIRSTCHART, OnGraphicsUsefirstchart)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_USEFIRSTCHART, OnUpdateGraphicsUsefirstchart)
	ON_COMMAND(ID_GRAPHICS_USENEXTCHART, OnGraphicsUsenextchart)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_USENEXTCHART, OnUpdateGraphicsUsenextchart)
	ON_COMMAND(ID_GRAPHICS_USEPREVCHART, OnGraphicsUseprevchart)
	ON_UPDATE_COMMAND_UI(ID_GRAPHICS_USEPREVCHART, OnUpdateGraphicsUseprevchart)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_OPTIONS_GRAPHICOPTIONS, OnOptionsGraphicoptions)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_GRAPHICOPTIONS, OnUpdateOptionsGraphicoptions)
	ON_COMMAND(ID_OPTIONS_DIRECTORIES, OnOptionsDirectories)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_OPTIONS_GRAPHICFILECONVERSIONOPTIONS, OnOptionsGraphicfileconversionoptions)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)     
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrographView construction/destruction

CAstrographView::CAstrographView()	   
{
	// TODO: add construction code here
 GraphOptions ogd;

 ogd.getFromIni(GraphicsOptions_SEC);
 fontScale = (float)ogd.getFontSize();
 fontScale /= 100.0;
 fToFit = 0;
 scale = 1.0;
 plot = NULL;
 plot2 = NULL;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 which_houses = 0;
 pCurChart = NULL;
 drawMode = ogd.getDrawMode();
 dataGroup = new GraphicDataGroup();
 compGroup = NULL;
 baseMetrics = NULL;
 pbBack = NULL;
 pDataFnt = NULL;
 pGlyphSpec = NULL;
 pTickGlyphSpec = NULL;
 pDegSpec = NULL;
 cxClient = 640;
 cyClient = 480;
 asc_min = 0;
 offset = 0;
 old_asc_min = 0;
 defaultSize.cx = GetSystemMetrics(SM_CXFULLSCREEN);
 defaultSize.cy = GetSystemMetrics(SM_CYFULLSCREEN);
 _type = 0;
#ifndef GRAVIEWER
 init_popup_text_report();
#endif
pTickGlyphSpec = NULL;
pBdDataFnt = NULL;
pGlyphFnt = NULL;
pTickGlyphFnt = NULL;
pDegFnt = NULL;
pGridFont = NULL;
plot = NULL;
plot2 = NULL;
}

CAstrographView::~CAstrographView()
{
 if (baseMetrics != NULL) 
    delete baseMetrics;
 if (pGlyphSpec != NULL) 
    delete pGlyphSpec;
 if (pDegSpec != NULL) 
    delete pDegSpec;
 if (pTickGlyphSpec != NULL) 
    delete pTickGlyphSpec;
 if (pTickGlyphFnt != NULL) 
    delete pTickGlyphFnt;
 if (pDataFnt != NULL) 
   delete pDataFnt;
if (pBdDataFnt != NULL)  
   delete pBdDataFnt;
if (pGlyphFnt != NULL)  
   delete pGlyphFnt;
if ( pDegFnt != NULL)  
   delete pDegFnt;
if (pbBack != NULL)  
   delete pbBack;
if ( pGridFont != NULL)  
   delete pGridFont;
 if ( plot != NULL )
    delete plot;
 if ( plot2 != NULL )
    delete plot2;
#ifndef GRAVIEWER
close_text_report();
#endif
 delete dataGroup;
 if ( compGroup != NULL )
    delete compGroup;
}

BOOL CAstrographView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs				  
	cs.style |= (WS_HSCROLL|WS_VSCROLL|CS_DBLCLKS);
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAstrographView drawing

void CAstrographView::OnDraw(CDC* pDC)	  
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
 if (compGroup != NULL ) {
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
	delete pslp;
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
 if (compGroup != NULL ) {
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

/////////////////////////////////////////////////////////////////////////////
// CAstrographView printing

BOOL CAstrographView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	CAstrographDoc* pDoc = GetDocument();
    pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CAstrographView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
 setupGrfas();
 GraphOptions ogd;
 ogd.getFromIni(GraphicsOptions_SEC);
 fontScale = (float)ogd.getFontSize();
 fontScale /= 100.0;
 wasToFit = fToFit;
 fToFit = 1;
 scale = 1.0;
 drawMode = ogd.getDrawMode();

	// TODO: add extra initialization before printing
}

void CAstrographView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
// TODO: add cleanup after printing
CRect rct;

CAstrographDoc* pDoc = GetDocument();
fToFit = wasToFit;
GetClientRect(&rct);
cxClient = rct.Width();
cyClient = rct.Height();
setupGrfas();
Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CAstrographView diagnostics

#ifdef _DEBUG
void CAstrographView::AssertValid() const
{
	CView::AssertValid();
}

void CAstrographView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAstrographDoc* CAstrographView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstrographDoc)));
	return (CAstrographDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrographView message handlers

void CAstrographView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
 CRect r;
 CSize s;							
 GraphicFonts gf;

 CAstrographDoc* pDoc = GetDocument();
 
 if ( pInfo != NULL && pInfo->m_nCurPage <= 1)
       pInfo->m_bContinuePrinting = TRUE;
 else if ( pInfo != NULL && pDoc->HasMoreFiles() ) {
	pDoc->DoNextFile();
    pInfo->m_bContinuePrinting = TRUE;
    }
 else if (pInfo != NULL && !pDoc->HasMoreFiles() )
 	pInfo->m_bContinuePrinting = FALSE;
 if ( !pDoc->IsOk() ) {
	CView::OnPrepareDC(pDC, pInfo);
	return;
    }
 if ( pInfo == NULL )
    gf.getFromIni(GraphicsOptions_SEC);
 else
    gf.getFromIni(GraphPrintOpt_SEC);
 if ( baseMetrics == NULL ) {
	 if ( pInfo == NULL && _type )
	   baseMetrics = new AstDrawBase( pDC, _type );
	 else if (pInfo == NULL )
       baseMetrics = new AstDrawBase( pDC );
	else if (pInfo != NULL && pInfo->m_bContinuePrinting == TRUE )
	   baseMetrics = new AstDrawBase( pDC, _TYPE_PRINT );
 	else
	   baseMetrics = new AstDrawBase( pDC );
	}
 else {
    if ( pInfo == NULL && _type )
	   baseMetrics->newDisplay( pDC, _type );
	else if (pInfo == NULL )
       baseMetrics->newDisplay( pDC );
    else if (pInfo != NULL && pInfo->m_bContinuePrinting == TRUE )
	   baseMetrics->newDisplay( pDC, _TYPE_PRINT );	
	else
	   baseMetrics->newDisplay( pDC );
	}
 if ( pbBack != NULL )
    delete pbBack;
 /*
 if ( canvas()->type() != PrinterDisp ) {
 */
 pbBack = new CBrush(baseMetrics->getColor(0));
 pDC->SetBkColor(baseMetrics->getColor(0));
/*
    }
 else {
    pbBack = new zBrush(WhiteBrush);
    }
 */
if ( fToFit && pInfo == NULL && !_type ) {
   rActive = CRect(0,0,cxClient,cyClient);
   cxLeftOffset = 0;
   cyTopOffset = 0;
   thePolarScaler.enable(0);
   }
else if (!_type && pInfo == NULL ) {
   rActive = CRect(0,0,defaultSize.cx*scale,defaultSize.cy*scale);
   SetScrollRange( SB_HORZ, 0, rActive.Width()-cxClient, TRUE ); 
   SetScrollRange( SB_VERT, 0, rActive.Height()-cyClient, TRUE );
   thePolarScaler.enable(0);
   }
else if ( pInfo != NULL ) {
   int ym = pDC->GetDeviceCaps(LOGPIXELSY);
   int xm = pDC->GetDeviceCaps(LOGPIXELSX);
   ym *= 3;
   ym /= 2;
   xm *= 3;
   xm /= 2;
	
   CRect r(0, 0, pDC->GetDeviceCaps(HORZRES)-(xm), 
	   pDC->GetDeviceCaps(VERTRES)-(ym));
   rActive = r; 
   cxLeftMgn = -(xm/2);
   cyTopMgn = -(ym/2);
   cxClient = rActive.Width();
   cyClient = rActive.Height();
   thePolarScaler.setupResolutions( pDC->GetDeviceCaps(LOGPIXELSX),
	  pDC->GetDeviceCaps(LOGPIXELSY) );
   }
else if ( _type && pInfo == NULL ) {
   rActive = rOther;
   cxClient = rActive.Width();
   cyClient = rActive.Height();
   }
else {
}
updateGrfas();
computeRadiusData();
if ( pDataFnt != NULL )
    delete pDataFnt;
 pDataFnt = new CFont();	 
 pDataFnt->CreateFont(fontSize(32),0,0,0,FW_NORMAL,
	 0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
	 DEFAULT_QUALITY,VARIABLE_PITCH|FF_DONTCARE, gf.getDataFont());
 if ( pBdDataFnt != NULL )
    delete pBdDataFnt;
 pBdDataFnt = new CFont();
 pBdDataFnt->CreateFont(fontSize(32),0,0,0,FW_BOLD,
	 0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
	 DEFAULT_QUALITY,VARIABLE_PITCH|FF_DONTCARE, gf.getDataFont());
int fs;
if ( pTickGlyphSpec != NULL )
   delete pTickGlyphSpec;
pTickGlyphSpec = (LPLOGFONT) new char[sizeof(LOGFONT)+100];
pTickGlyphSpec->lfHeight=fontSize(24);
pTickGlyphSpec->lfWidth=0;
pTickGlyphSpec->lfEscapement=0;
pTickGlyphSpec->lfOrientation=0;
pTickGlyphSpec->lfWeight=FW_NORMAL;
pTickGlyphSpec->lfItalic=FALSE;
pTickGlyphSpec->lfUnderline=FALSE;
pTickGlyphSpec->lfStrikeOut=FALSE;
pTickGlyphSpec->lfCharSet=SYMBOL_CHARSET;
pTickGlyphSpec->lfOutPrecision=OUT_DEFAULT_PRECIS;
pTickGlyphSpec->lfClipPrecision=CLIP_DEFAULT_PRECIS;
pTickGlyphSpec->lfQuality=DEFAULT_QUALITY;
pTickGlyphSpec->lfPitchAndFamily=FF_DECORATIVE|VARIABLE_PITCH;
strcpy( pTickGlyphSpec->lfFaceName,gf.getGlyphFont());
if ( pTickGlyphFnt != NULL )
    delete pTickGlyphFnt;
pTickGlyphFnt = new CFont();
pTickGlyphFnt->CreateFontIndirect( pTickGlyphSpec );
 
if ( drawMode & SHOW_PDEGS || drawMode & PLOT_CLASSIC ) {
    if ( data->ncharts()==2 )
       fs = fontSize(25);
    else
       fs = fontSize(23);
    }
 else {
    if ( data->ncharts()==2 )
       fs = fontSize(20);
    else
       fs = fontSize(16);
    }
 if ( fs < 7 )
    fs = 8;
 else if ( fs < 8 )
    fs = 9;
 else if ( fs < 10 )
    fs += 1;
 else if ( fs < 11 )
    fs += 1;
 else if ( fs < 12 )
    fs += 1;
 if ( pGlyphSpec != NULL )
    delete pGlyphSpec;
pGlyphSpec = (LPLOGFONT) new char[sizeof(LOGFONT)+100];
pGlyphSpec->lfHeight=fs;
pGlyphSpec->lfWidth=0;
pGlyphSpec->lfEscapement=0;
pGlyphSpec->lfOrientation=0;
pGlyphSpec->lfWeight=FW_NORMAL;
pGlyphSpec->lfItalic=FALSE;
pGlyphSpec->lfUnderline=FALSE;
pGlyphSpec->lfStrikeOut=FALSE;
pGlyphSpec->lfCharSet=SYMBOL_CHARSET;
pGlyphSpec->lfOutPrecision=OUT_DEFAULT_PRECIS;
pGlyphSpec->lfClipPrecision=CLIP_DEFAULT_PRECIS;
pGlyphSpec->lfQuality=DEFAULT_QUALITY;
pGlyphSpec->lfPitchAndFamily=FF_DECORATIVE|VARIABLE_PITCH;
strcpy( pGlyphSpec->lfFaceName,gf.getGlyphFont());
if ( pGlyphFnt != NULL )
    delete pGlyphFnt;
pGlyphFnt = new CFont();
pGlyphFnt->CreateFontIndirect( pGlyphSpec );
if ( pDegSpec != NULL )
    delete pDegSpec;
 if ( data->ncharts()==2 )
    fs = 37;
 else
    fs = 33;
pDegSpec = (LPLOGFONT) new char[sizeof(LOGFONT)+100];
pDegSpec->lfHeight=fontSize(fs);
pDegSpec->lfWidth=0;
pDegSpec->lfEscapement=0;
pDegSpec->lfOrientation=0;
pDegSpec->lfWeight=FW_NORMAL;
pDegSpec->lfItalic=FALSE;
pDegSpec->lfUnderline=FALSE;
pDegSpec->lfStrikeOut=FALSE;
pDegSpec->lfCharSet=SYMBOL_CHARSET;
pDegSpec->lfOutPrecision=OUT_DEFAULT_PRECIS;
pDegSpec->lfClipPrecision=CLIP_DEFAULT_PRECIS;
pDegSpec->lfQuality=DEFAULT_QUALITY;
pDegSpec->lfPitchAndFamily=FF_DECORATIVE|VARIABLE_PITCH;
strcpy( pDegSpec->lfFaceName,gf.getGlyphFont());
if ( pDegFnt != NULL )
    delete pDegFnt;
pDegFnt = new CFont();
pDegFnt->CreateFontIndirect( pDegSpec );
if ( pGridFont != NULL )
    delete pGridFont;
pGridFont = new CFont();
pGridFont->CreateFont(fontSize(38),0,0,0,FW_NORMAL,
	 0,0,0,SYMBOL_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
	 DEFAULT_QUALITY,VARIABLE_PITCH|FF_DECORATIVE, gf.getGlyphFont());
CFont *old;
TEXTMETRIC tm;
old = pDC->SelectObject(pDataFnt);
pDC->GetTextMetrics(&tm);
pDC->SelectObject(old);
cxChar = tm.tmAveCharWidth; 
cyChar = tm.tmHeight + tm.tmInternalLeading;
}

void CAstrographView::OnInitialUpdate() 
{
	// TODO: Add your specialized code here and/or call the base class
}

void CAstrographView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
setupGrfas();
Invalidate(TRUE);
}

void CAstrographView::computeRadiusData()
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
 if ( data->ncharts() == 2 || compGroup != NULL ) {
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

int CAstrographView::fontSize(int div)
{
 
 float v = radiusData.getPoints();
 
 div++;
 v *= fontScale;
 v /= (float)div;
 return( (int) v);

}

void CAstrographView::updateGrfas()
{
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
if ( compGroup != NULL ) {
   if ( data->getData()->type == TRANSITS_GRAPH_FILE ||
     	data->getData()->type == COMPTR_GRAPH_FILE  ) {
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
       compGroup->doGrfs(data->getData()->other_minutes,
       data->getData()->maxpt, (short *)data->getData()->other_house_cusps,
       drawMode, old_asc_min );
       }
   }
} 



void CAstrographView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	cxClient = cx;
    cyClient = cy;
    pageDelta.cy = cy/4;
	pageDelta.cx = cx/4;
	lineDelta.cy = cy/16;
	lineDelta.cx = cx/16;
	Invalidate(TRUE);	
}

void CAstrographView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int p;
	// TODO: Add your message handler code here and/or call default
	
	CView::OnVScroll(nSBCode, nPos, pScrollBar);

    switch( nSBCode ) {
       case SB_TOP:		 
		cyTopOffset = 0;
		SetScrollPos(SB_VERT,0,TRUE);
		break;
       case SB_BOTTOM:
	    cyTopOffset = rActive.Height()-cyClient;
		SetScrollPos(SB_VERT,cyTopOffset,TRUE);
		break;
       case SB_PAGEUP:
		p = GetScrollPos(SB_VERT);
		cyTopOffset = p - pageDelta.cy;
		if (cyTopOffset < 0 )
		   cyTopOffset = 0;
		SetScrollPos(SB_VERT,cyTopOffset,TRUE);
	    break;
       case SB_PAGEDOWN:
	    p = GetScrollPos(SB_VERT);
		cyTopOffset = p + pageDelta.cy;
		if ( cyTopOffset > rActive.Height()-cyClient )
		   cyTopOffset = rActive.Height()-cyClient;
		SetScrollPos(SB_VERT,cyTopOffset,TRUE);
		break;
       case SB_THUMBPOSITION:
	    cyTopOffset = nPos;
		SetScrollPos(SB_VERT,nPos,TRUE);
		break;
       case SB_LINEDOWN:
	    p = GetScrollPos(SB_VERT);
		cyTopOffset = p + lineDelta.cy;
		if ( cyTopOffset > rActive.Height()-cyClient )
		   cyTopOffset = rActive.Height()-cyClient;
		SetScrollPos(SB_VERT,cyTopOffset,TRUE);
		break;
       case SB_LINEUP:
		p = GetScrollPos(SB_VERT);
		cyTopOffset = p - lineDelta.cy;
		if (cyTopOffset < 0 )
		   cyTopOffset = 0;
		SetScrollPos(SB_VERT,cyTopOffset,TRUE);
		break;
       default :
	    break;
       }
Invalidate(TRUE);
}

void CAstrographView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int p;
	CView::OnHScroll(nSBCode, nPos, pScrollBar); 

    switch( nSBCode ) {
       case SB_TOP:
		cxLeftOffset = 0;
		SetScrollPos(SB_HORZ,0,TRUE);
		break;
       case SB_BOTTOM:
	    cxLeftOffset = rActive.Width()-cxClient;
		SetScrollPos(SB_HORZ,cxLeftOffset,TRUE);
		break;
       case SB_PAGEUP:
		p = GetScrollPos(SB_HORZ);
		cxLeftOffset = p - pageDelta.cx;
		if (cxLeftOffset < 0 )
		   cxLeftOffset = 0;
		SetScrollPos(SB_HORZ,cxLeftOffset,TRUE);
	    break;
       case SB_PAGEDOWN:
		p = GetScrollPos(SB_HORZ);
		cxLeftOffset = p + pageDelta.cx;
		if ( cxLeftOffset > rActive.Width()-cxClient )
		   cxLeftOffset = rActive.Width()-cxClient;
		SetScrollPos(SB_HORZ,cxLeftOffset,TRUE);
	    break;
       case SB_THUMBPOSITION:
		cxLeftOffset=nPos;
		SetScrollPos(SB_HORZ,nPos,TRUE);
	    break;
       case SB_LINEDOWN:
		{
		CRect x(0, 0, cxClient, cyClient);
		p = GetScrollPos(SB_HORZ);
		cxLeftOffset = p + lineDelta.cx;
		if ( cxLeftOffset > rActive.Width()-cxClient )
		   cxLeftOffset = rActive.Width()-cxClient;
		SetScrollPos(SB_HORZ,cxLeftOffset,TRUE);
	    ScrollWindow( -lineDelta.cx, 0, NULL,(LPRECT) &x );
		}
		break;
       case SB_LINEUP:
		{
		CRect y(0, 0, cxClient, cyClient);
		p = GetScrollPos(SB_HORZ);
		cxLeftOffset = p - lineDelta.cx;
		if (cxLeftOffset < 0 )
		   cxLeftOffset = 0;
		SetScrollPos(SB_HORZ,cxLeftOffset,TRUE);
		ScrollWindow( lineDelta.cx, 0, NULL,(LPRECT) &y );
		}
		break;
       default :
	    break;
       }
Invalidate(TRUE);
}

void CAstrographView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	 switch( nChar ) {
          case VK_PRIOR:
			OnVScroll(SB_PAGEUP, 0, NULL );
		    break;
          case VK_NEXT:
	       	OnVScroll(SB_PAGEDOWN, 0, NULL );
			break;
          case VK_UP:
	        OnVScroll(SB_LINEUP, 0, NULL );
			break;
          case VK_DOWN:
	       	OnVScroll(SB_LINEDOWN, 0, NULL );
			break;
          case VK_HOME:
	        if ( !(GetAsyncKeyState(VK_CONTROL)&0x8000) )
		       OnHScroll(SB_TOP, 0, NULL );
	        break;
          case VK_END:
	       if ( !(GetAsyncKeyState(VK_CONTROL)&0x8000) )
		      OnHScroll(SB_BOTTOM, 0, NULL );
	       break;
          case VK_LEFT :
	       if ( GetAsyncKeyState(VK_CONTROL)&0x8000 )
		      OnHScroll(SB_PAGEUP, 0, NULL );
	       else
		      OnHScroll(SB_LINEUP, 0, NULL );
	       break;
	  case VK_RIGHT :
	       if ( GetAsyncKeyState(VK_CONTROL)&0x8000 )
		      OnHScroll( SB_PAGEDOWN, 0, NULL );
	       else
		      OnHScroll( SB_LINEDOWN, 0, NULL );
	       break;
	  default :
	       break;
	       }
	 
}

void CAstrographView::OnViewFitwin() 
{
	// TODO: Add your command handler code here
fToFit^=0xffff;
if (fToFit) {
   scale = 1;
   cxLeftOffset=0;
   cyTopOffset=0;
   }
else
   scale = 1;
Invalidate(TRUE);	
}

void CAstrographView::OnUpdateViewFitwin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 pCmdUI->Enable(TRUE);
 if(fToFit)	
  pCmdUI->SetCheck(1);
else
  pCmdUI->SetCheck(0);
}

void CAstrographView::OnViewZoomin() 
{
	// TODO: Add your command handler code here
scale*=1.25;
Invalidate(TRUE);
}

void CAstrographView::OnViewZoomout() 
{
	// TODO: Add your command handler code here
scale *=.8;	
Invalidate(TRUE);
}

void CAstrographView::OnViewLargerfont() 
{
	// TODO: Add your command handler code here
	fontScale *= 1.1;
	Invalidate(TRUE);
}

void CAstrographView::OnViewSmallerfont() 
{
	// TODO: Add your command handler code here
	fontScale *= .9090909;
	Invalidate(TRUE);
}

void CAstrographView::OnGraphicsSigntickwheel() 
{
	// TODO: Add your command handler code here
	drawMode ^= SIGN_TICK;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsSigntickwheel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & SIGN_TICK );
}

void CAstrographView::OnGraphicsDecantickwheel() 
{
	// TODO: Add your command handler code here
	drawMode ^= DEC_TICK;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsDecantickwheel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck( drawMode & DEC_TICK );	
}

void CAstrographView::OnGraphicsDegreetickwheel() 
{
	// TODO: Add your command handler code here
	drawMode ^= DEG_TICK;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsDegreetickwheel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck( drawMode & DEG_TICK );	
}	


void CAstrographView::OnGraphicsPlotclassically() 
{
	// TODO: Add your command handler code here
	drawMode ^= PLOT_CLASSIC;
	Invalidate(TRUE);
}	

void CAstrographView::OnUpdateGraphicsPlotclassically(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & PLOT_CLASSIC );	
}

void CAstrographView::OnGraphShowhousedegrees() 
{
	// TODO: Add your command handler code here
	drawMode ^= HOUSE_DEG;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphShowhousedegrees(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck( drawMode & HOUSE_DEG );		
}

void CAstrographView::OnGraphShowhousenumbers() 
{
	// TODO: Add your command handler code here
	drawMode ^= HOUSE_NUM;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphShowhousenumbers(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & HOUSE_NUM );	
}

void CAstrographView::OnGraphShowsignlines() 
{
	// TODO: Add your command handler code here
	drawMode ^= SHOW_SLIN;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphShowsignlines(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck( drawMode & SHOW_SLIN );		
}

void CAstrographView::OnGraphShowsignname() 
{
	// TODO: Add your command handler code here
	drawMode ^= SIGN_NAME;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphShowsignname(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & SIGN_NAME );
}

void CAstrographView::OnGraphicsInnerouterhousecusps() 
{
	// TODO: Add your command handler code here
	unsigned short bits = drawMode & USE_INHC;
    if ( !bits )
		drawMode |= USE_INHC;
	else
		drawMode &= (0xffff^USE_INHC);
	if ( compGroup != NULL ) {
	   dataGroup->resetHouses();
	   compGroup->resetHouses();
	   if ( which_houses ) {
	      which_houses = 0;
	      old_asc_min = asc_min = data->getData()->natal_minutes[0];
	      offset = 0;
	      }
	   else {
		  which_houses = 1;
		  old_asc_min = asc_min = data->getData()->other_minutes[0];
		  offset = 0;
		  }
	   updateGrfas();
	   Invalidate(TRUE);
	   }

}

void CAstrographView::OnUpdateGraphicsInnerouterhousecusps(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((data->ncharts() > 1 && data->getData()->type 
		    != TRANSITS_GRAPH_FILE)?TRUE:FALSE); 
	pCmdUI->SetCheck( drawMode & USE_INHC );
}

void CAstrographView::OnGraphicsHousenumbersoutside() 
{
	// TODO: Add your command handler code here
	drawMode ^= HOUS_OUTS;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsHousenumbersoutside(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & HOUS_OUTS );
}


void CAstrographView::OnGraphicsShowplanetdegrees() 
{
	// TODO: Add your command handler code here
	drawMode ^= SHOW_PDEGS;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsShowplanetdegrees(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & SHOW_PDEGS );
}

void CAstrographView::OnGraphShowaspectgrid() 
{
	// TODO: Add your command handler code here
	drawMode ^= SHOW_AGRID;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphShowaspectgrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if ( data->getData()->num_grid_aspects || data->getData()->num_other_grid_aspects ||
	   (( data->getData()->type == TRANSITS_GRAPH_FILE || data->getData()->type == 
	     COMPTR_GRAPH_FILE ) &&	pCurChart != NULL && pCurChart->aspect_count > 0 )) {
       pCmdUI->Enable(TRUE);
	   pCmdUI->SetCheck( drawMode & SHOW_AGRID);
       }
  else {
      pCmdUI->Enable(FALSE);
	  if ( drawMode & SHOW_AGRID )
         drawMode ^= SHOW_AGRID;
      }
	
}

void CAstrographView::OnGraphShowaspects() 
{
	// TODO: Add your command handler code here
	drawMode ^= SHOW_ASPT;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphShowaspects(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(data->getData()->num_aspects?TRUE:FALSE);
	pCmdUI->SetCheck( drawMode & SHOW_ASPT );
}

void CAstrographView::OnGraphicsDecreasehousecusps() 
{
	// TODO: Add your command handler code here
	dataGroup->decreaseHouses();
	if ( compGroup != NULL )
	   compGroup->decreaseHouses();
	updateGrfas();
	Invalidate(TRUE);
}

void CAstrographView::OnGraphicsIncreasehousecusps() 
{
	// TODO: Add your command handler code here
	dataGroup->increaseHouses();
	if ( compGroup != NULL )
	   compGroup->increaseHouses();
	updateGrfas();
	Invalidate(TRUE);
}

void CAstrographView::OnGraphicsNormalhousecusps() 
{
	// TODO: Add your command handler code here
    dataGroup->resetHouses();
	if ( compGroup != NULL )
	   compGroup->resetHouses();
	updateGrfas();	
	Invalidate(TRUE);
}

void CAstrographView::OnGraphUseglyphs() 
{
	// TODO: Add your command handler code here
	drawMode ^= USE_GLYPH;
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphUseglyphs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( drawMode & USE_GLYPH );
}

void CAstrographView::OnGraphicsUsefirstchart() 
{
	// TODO: Add your command handler code here
    pCurChart = data->getFirstChart();
	updateGrfas();	
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsUsefirstchart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (data->getData()->type == TRANSITS_GRAPH_FILE ||
	      data->getData()->type == COMPTR_GRAPH_FILE  ) 
 	   pCmdUI->Enable( data->getData()->num_charts > 0?TRUE:FALSE );
	else 
	   pCmdUI->Enable( FALSE );
}

void CAstrographView::OnGraphicsUsenextchart() 
{
	// TODO: Add your command handler code here
	pCurChart = data->getNextChart();
	updateGrfas();
	Invalidate(TRUE);
}

void CAstrographView::OnUpdateGraphicsUsenextchart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (data->getData()->type == TRANSITS_GRAPH_FILE ||
	      data->getData()->type == COMPTR_GRAPH_FILE  ) 
 	   pCmdUI->Enable( data->getData()->num_charts > 0?TRUE:FALSE );
	else 
	   pCmdUI->Enable( FALSE );
}

void CAstrographView::OnGraphicsUseprevchart() 
{
	// TODO: Add your command handler code here
	pCurChart = data->getPrevChart();
	updateGrfas();
	Invalidate(TRUE);
}


void CAstrographView::OnUpdateGraphicsUseprevchart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (data->getData()->type == TRANSITS_GRAPH_FILE ||
	      data->getData()->type == COMPTR_GRAPH_FILE  ) 
 	   pCmdUI->Enable( data->getData()->num_charts > 0?TRUE:FALSE );
	else 
	   pCmdUI->Enable( FALSE );
}

void CAstrographView::setupGrfas()
{
CAstrographDoc* pDoc = GetDocument();
data = pDoc->GetDataPtr();
asc_min = data->getData()->natal_minutes[0];
old_asc_min = data->getData()->natal_minutes[0];
dataGroup->doGrfs(data->getData()->natal_minutes,
     data->getData()->maxpt, data->getData()->natal_house_cusps,
     drawMode, old_asc_min );
asc_min = dataGroup->getAsc();
if ( data->getData()->num_aspects ) {
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
	 if ( compGroup == NULL && data->getData()->num_other>0) {
	   compGroup = new GraphicDataGroup();
	   compGroup->doGrfs(data->getData()->other_minutes,
       data->getData()->maxpt, (short *)data->getData()->other_house_cusps,
       drawMode, old_asc_min );
	 }
    }
}


GR_ASPT *CAstrographView::findAspect( CPoint &p )
{
 int gSize = fontSize(38)+1;
 int f = ((rActive.Height()-1 - gSize - p.y - cyTopOffset) / gSize);
 int s = ((rActive.Width()-1 - gSize - p.x - cxLeftOffset)  / gSize);
 s = gridMaxpt - s - 1;
 if ( f < 0 || f >= gridMaxpt )
    return( NULL );
 if ( s < 0 || s >= gridMaxpt )
    return(  NULL );
 GR_ASPT * grasp = gridAspts;
 if ( !gridCnt )
    return( NULL );
 for ( int i = 0; i < gridCnt; i++, grasp++ ) {
       if ( ( grasp->getFirst() == f && grasp->getSecond() == s ) ||
	    ( grasp->getFirst() == s && grasp->getSecond() == f ) )
          return( grasp );   
       }
return( NULL );
}

int CAstrographView::doPop( CPoint &p, char *file)
{
#ifndef GRAVIEWER
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

void CAstrographView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
#ifndef GRAVIEWER
	if ( !_access("$$CLICK$.TMP", 4) )
       unlink("$$CLICK$.TMP");
       doPop( point, "$$CLICK$.TMP" );
       if ( !_access("$$CLICK$.TMP", 4) ) {
          CPopupEd ed;
		  ed.load("$$CLICK$.TMP");
		  ed.DoModal();
		  unlink("$$CLICK$.TMP");
	      }
#endif        			   
}

int CAstrographView::toDegrees( CPoint &p, int &rad )
{
 CPoint ap = p;
 ap.x -= radiusData.getOffset();
 ap.y -= rActive.Height()/2;
 ap.x += cxLeftOffset;
 ap.y += cyTopOffset;
 int abx = abs(ap.x);
 int aby = abs(ap.y);
 long t = ((long)abx * abx) + ((long)aby * aby);
 double drd = (int)sqrt((double)t);
 rad = (int) drd;
 if ( drd == 0.0 )
    return( 0 );
 double sn = (double) -ap.y / drd;
 sn = (asin( sn ) * 180) /PI;
 if ( ap.y < 0 && ap.x < 0 )
    return( (int)(sn));
 else if ( ap.y < 0 && ap.x >= 0 )
    return( (int)(90.0-sn+90.0));
 else if ( ap.y >= 0 && ap.x >= 0 )
    return( (int)(90.0-sn+90.0));
 else 
    return( (int) (sn + 360.0) );
 return( 0 ); 
}

void CAstrographView::OnOptionsGraphicoptions() 
{
	// TODO: Add your command handler code here
    int fontSize = fontScale * 100.0;
	GraphOptions go;
    go.getFromIni(GraphicsOptions_SEC);
    GraphicColors gc(GetDC());
    gc.getFromIni(GraphicsOptions_SEC);
    GraphicFonts gf;
    gf.getFromIni(GraphicsOptions_SEC);
    CGraphOpts god;
    god.SetGraphicFonts(&gf);
    god.SetGraphicColors(&gc);
    god.SetData(drawMode,fontSize); 
    go.getDrawMode()=drawMode;
	if ( god.DoModal() == IDOK ) {
	   god.GetData(drawMode,fontSize); 
	   fontScale = fontSize / 100.0;
	   go.getFontSize()=fontSize;
	   go.getDrawMode()=drawMode;	   
       go.saveToIni(GraphicsOptions_SEC);
       gc.saveToIni(GraphicsOptions_SEC);
       gf.saveToIni(GraphicsOptions_SEC);
       }
 Invalidate(TRUE);
}

void CAstrographView::OnUpdateOptionsGraphicoptions(CCmdUI* pCmdUI) 
{
pCmdUI->Enable(TRUE);
}

void CAstrographView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
 GraphOptions ogd;	
 ogd.getFromIni(GraphicsOptions_SEC);
 fontScale = (float)ogd.getFontSize();
 fontScale /= 100.0;
 fToFit = 1;
 scale = 1.0;
 drawMode = ogd.getDrawMode();
 OnDraw(pDC);
}


void CAstrographView::OnOptionsDirectories() 
{
	// TODO: Add your command handler code here
	CDirectories cdd;
	cdd.SetData(theDirectories);
	if ( cdd.DoModal() == IDOK ) {
	   cdd.GetData(theDirectories);
	   theDirectories.saveToIni();
	   }
}


#pragma pack(8)
typedef struct tagMYBITMAPINFOHEADER{ // bmih 
   DWORD  biSize; 
   LONG   biWidth; 
   LONG   biHeight; 
   WORD   biPlanes; 
   WORD   biBitCount; 
   DWORD  biCompression; 
   DWORD  biSizeImage; 
   LONG   biXPelsPerMeter; 
   LONG   biYPelsPerMeter; 
   DWORD  biClrUsed; 
   DWORD  biClrImportant; 
   RGBQUAD bmiColors[16];
 } MYBITMAPINFOHEADER; 

#pragma pack()
extern COLORREF colors[];


void CAstrographView::OnEditCopy() 
{
	// TODO: Add your command handler code here
int top, left, i;
METAFILEPICT mfp, *pmf;
HANDLE hmem;
HMETAFILE hmf;
MYBITMAPINFOHEADER bmh;
HBITMAP hbit;

CDC *pscDC;
	
if ( !OpenClipboard() )
   return;
EmptyClipboard();
// First lets do a WMF
top = cyTopOffset;
left = cxLeftOffset;
cyTopOffset = 0;
cxLeftOffset = 0;
CMetaFileDC *pDC = new CMetaFileDC();
pDC->Create(NULL);
pscDC = GetDC();
pDC->SetAttribDC(pscDC->GetSafeHdc());
rOther = CRect(0,0,800,600);
_type = _TYPE_WMF;
OnPrepareDC(pDC, NULL );
OnDraw(pDC);
hmf = pDC->Close();
mfp.hMF = hmf;
mfp.mm = MM_ISOTROPIC;
mfp.xExt = 800;
mfp.yExt = 600;
hmem = GlobalAlloc(GMEM_DDESHARE, sizeof(METAFILEPICT));
pmf = (METAFILEPICT *)GlobalLock(hmem);
*pmf = mfp;
GlobalUnlock(hmem);
SetClipboardData(CF_METAFILEPICT,hmem);
delete pDC;
// lets Now do a dib 

bmh.biSize = sizeof(BITMAPINFOHEADER);
bmh.biWidth =640;
bmh.biHeight =480;
bmh.biPlanes = 1;
bmh.biBitCount=8;
bmh.biCompression=BI_RGB;
bmh.biXPelsPerMeter=2000;
bmh.biYPelsPerMeter=1800; 
bmh.biClrUsed=16;
bmh.biClrImportant=16;
bmh.biSizeImage=0;
CDC *pcDC = new CDC();
pcDC->CreateCompatibleDC(pscDC);
_type = _TYPE_BMPC;
rOther = CRect(0,0,640,480);
OnPrepareDC(pcDC, NULL );
for ( i = 0; i < 16; i++ ) {
    bmh.bmiColors[i].rgbRed = GetRValue(colors[i]);
    bmh.bmiColors[i].rgbBlue = GetBValue(colors[i]);
	bmh.bmiColors[i].rgbGreen = GetGValue(colors[i]);
	}
hbit = CreateDIBSection(pcDC->GetSafeHdc(),(BITMAPINFO *) &bmh, DIB_RGB_COLORS, NULL, NULL, 0L );
CBitmap *pbm= new CBitmap();
HGDIOBJ hbold =::SelectObject(pcDC->GetSafeHdc(),hbit);
OnDraw(pcDC);
GdiFlush();
::SelectObject(pcDC->GetSafeHdc(),hbold);
SetClipboardData(CF_BITMAP,hbit);
delete pcDC;
_type = 0;
cyTopOffset = top;
cxLeftOffset = left;
CloseClipboard(); 
ReleaseDC(pscDC);
}


void CAstrographView::OnOptionsGraphicfileconversionoptions() 
{
	// TODO: Add your command handler code here
#ifdef PRO	
	CGraphFileOpts gfo;
	GraphFileData gfd;
	gfd.getFromIni();
	gfo.SetData(gfd);
	if ( gfo.DoModal() == IDOK ) {
	   gfo.GetData(gfd);
	   gfd.saveToIni();
	   }
#endif
}


void CAstrographView::OnUpdateView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 pCmdUI->Enable(TRUE);
}

void CAstrographView::toWMF(char *name, int place, int color, int rev)
{
#ifdef PRO
 char buf[255];
 int ft;
 int left = cxLeftOffset, top = cyTopOffset;
 CMetaFileDC *meta;

 if ( !color )
    setMono(1);
 if ( rev )
    swapMonoClr(1);
 if ( place ) {
    GetTempFileName( ".", "ASTW", 0, buf );
    meta = new CMetaFileDC();
	meta->Create(buf);
	}
 else {
    meta = new CMetaFileDC();
    meta->Create(name);
	}
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 CDC *pscDC = GetDC();
 meta->SetAttribDC(pscDC->GetSafeHdc());
 rOther = CRect(0,0,800,600);
 _type = _TYPE_WMF;
 OnPrepareDC(meta, NULL );
 OnDraw(meta);
 meta->Close();
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 _type = 0;	 
 delete meta;
 if ( !color )
    setMono(0);
 if ( rev )
    swapMonoClr(0);
 if ( place )
    fixupMetafile( buf, name );
 ReleaseDC(pscDC);
#endif
 }

void CAstrographView::toDib( imgdes *image, int color, int rev, int dib )
{
#ifdef PRO 
 extern COLORREF colors[];
 COLORREF bwclr[2];
 int ft;
 int left = cxLeftOffset, top = cyTopOffset;

 if ( rev && !color ) {
    bwclr[1] = RGB(0,0,0);
    bwclr[0] = RGB(0xff,0xff,0xff);
    }
 else {
    bwclr[0] = RGB(0,0,0);
    bwclr[1] = RGB(0xff,0xff,0xff);
    }
 if ( rev )
    swapMonoClr(1);
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;  
 CDC *pscDC = GetDC();
 CDC *pcDC = new CDC();
 pcDC->CreateCompatibleDC(pscDC);
 if ( dib==1 )
    _type = _TYPE_DIB;
 else if ( dib == -1 )
    _type = _TYPE_BMPJ;
 else
    _type = _TYPE_BMPC;
 rOther = CRect(0,0,image->bmh->biWidth,image->bmh->biHeight);
 OnPrepareDC(pcDC, NULL );
 int i;
 HBITMAP hbold=(HBITMAP)::SelectObject(pcDC->GetSafeHdc(),image->hBitmap);
 OnDraw(pcDC);
 GdiFlush();
 ::SelectObject(pcDC->GetSafeHdc(),hbold);
 if ( _type != _TYPE_BMPC && _type != _TYPE_BMPJ ) {
    if ( color ) {
	   for ( i = 0; i < 16; i++ ) {
	   	 image->palette[i].rgbRed = GetRValue(colors[i]);
		 image->palette[i].rgbBlue = GetBValue(colors[i]);
		 image->palette[i].rgbGreen = GetGValue(colors[i]);
		 }
	   }
    else {
	   for ( i = 0; i < 2; i++ ) {
	    	image->palette[i].rgbRed = GetRValue(bwclr[i]);
		    image->palette[i].rgbBlue = GetBValue(bwclr[i]);
		    image->palette[i].rgbGreen = GetGValue(bwclr[i]);
		    }
	   }
   }
 _type = 0;	 
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 if ( rev )
    swapMonoClr(0);
 delete pcDC;
 baseMetrics->newDisplay(pscDC);
 ReleaseDC(pscDC);
#endif
}


void CAstrographView::OnFileExport()
{
#ifdef PRO
#ifndef GRAVIEWER
CAstrographDoc* pDoc = GetDocument();
GraphicFileConverter *gfc;

 gfc = new GraphicFileConverter(this);
 if ( !gfc->getSetup() ) {
    delete gfc;
    return;
    }
 if ( !gfc->getFile()  ) {
    delete gfc;
    return;
    }
 gfc->setView(this);
 if ( !gfc->doConvert() ) {
    delete gfc;
    return;
    }
 delete gfc;
Invalidate(TRUE);
#endif
#endif
}


void CAstrographView::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
#ifdef PRO
pCmdUI->Enable(TRUE);
#endif
}

#ifndef GRAVIEWER

void CAstrographView::DoPrint()
{
CAstrographDoc* pDoc = GetDocument();
setupGrfas();
pDoc->SetCanClose(0);
GraphOptions ogd;
ogd.getFromIni(GraphicsOptions_SEC);
fontScale = (float)ogd.getFontSize();
fontScale /= 100.0;
fToFit = 1;
scale = 1.0;
drawMode = ogd.getDrawMode();
CView::OnFilePrint();
//CDC *dc =GetDC();
//baseMetrics->newDisplay(dc);
//ReleaseDC(dc);
//Invalidate(TRUE);

((CAstrowApp *)AfxGetApp())->_Yield(4);
pDoc->SetCanClose(1);
}

#endif
int CAstrographView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CView::OnCreate(lpCreateStruct);
	return 0;
}
