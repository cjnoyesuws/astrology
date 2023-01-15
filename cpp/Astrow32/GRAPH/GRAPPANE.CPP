#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "graphdat.hpp"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "stdlib.h"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "plotslin.hpp"
#include "tickcirc.hpp"
#ifdef NEW
#ifdef DELUXE
#include "graspgrd.hpp"
#endif
#endif
#include "graspcir.hpp"
#include "key.hpp"
#include "datakey.hpp"
#include "plotgrtp.hpp"
#include "dib.hpp"
#include "grappane.hpp"
#include "asfrmdlg.hpp"
#include "graopt.hpp"
#include "astromn.h"
#include "filelst.hpp"
#include "flistscr.hpp"
#include "asframe.hpp"
#include "inifile.hpp"
#include <print.h>
#include "prntsetp.hpp"
#include "menuutl.hpp"
#ifdef PRO
#include "mrufile.hpp"
#endif
#include "helpid.h"
#include "grafont.hpp"
#include "pageopt.hpp"
#include "resstr.hpp"


extern void zYield(int i);
#ifdef DELUXE
extern void init_popup_text_report();
extern void close_text_report();
#endif

/* data that should be deleted once this module is ok */
typedef int (zEvH::*MouseClickProc)(zMouseClickEvt*);

typedef int (zEvH::*KeyProc)(zKeyEvt*);

class AstPrJobDlg : public zDefPrJobDlg {
public:
      AstPrJobDlg( zWindow *w ) : zDefPrJobDlg(w, zResId("PRINT")) {
	 setCursor( zCursor(Hourglass) ); captureMouse(); }
      ~AstPrJobDlg() { releaseMouse(); }
      void setName( char *buf ) {((zControl *) get(101))->text(buf); }
      };


int AstGraphicsPane::size( zSizeEvt *e)
{
 canvas()->setDirty();
 cxClient=e->width();
 cyClient=e->height();
 setMetrics();
 return(1);
}

void AstGraphicsPane::computeRadiusData()
{
 int x, h, w, y;
 float rad, f;

 h = rActive.height();
 w = rActive.width();
 // debug( "h = %d, w = %d", h, w );
 if ( thePolarScaler.isEnabled() ) {
    w = thePolarScaler.invScaleX(w);
    h = thePolarScaler.invScaleY(h);
    }
#ifdef NEW
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
#else
 if (w < h )
    rad = ((float)w * .44);
 else
    rad = ((float)h * .47);
#endif
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
 x = (rActive.width()/2) - thePolarScaler.scaleX(radiusData.outsideCirc);
 x /= 5;
 radiusData.offset = (rActive.width()/2) + x;
#ifdef NEW
 if ( drawMode & SHOW_AGRID )
    radiusData.offset = (rActive.width()/2) - (x/2);
 else
    radiusData.offset = (rActive.width()/2) + (x/2);
#endif
}

int AstGraphicsPane::fontSize(int div)
{
 float v = radiusData.getPoints();

 div++;
 v *= fontScale;
 v /= (float)div;
 return( (int) v);
}

void AstGraphicsPane::setMetrics()
{
 zRect r;
 GraphicFonts gf;

 if ( canvas()->type() != PrinterDisp )
    gf.getFromIni(GraphicsOptions_SEC);
 else
    gf.getFromIni(GraphPrintOpt_SEC);
 baseMetrics->newDisplay( canvas() );
 canvas()->lock();
 if ( pbBack != NULL )
    delete pbBack;
 /*
 if ( canvas()->type() != PrinterDisp ) {
 */
 pbBack = new zBrush(baseMetrics->getColor(0));
 canvas()->backColor(baseMetrics->getColor(0));
/*
    }
 else {
    pbBack = new zBrush(WhiteBrush);
    }
 */
 canvas()->getVisible(r);
 cxClient = r.width();
 cyClient = r.height();
 if ( (fToFit && canvas()->type() != PrinterDisp) || canvas()->type() == MetaDisp ) {
    rActive = zRect(0,0,r.width(), r.height());
    canvas()->setPictureArea(&rActive);
    cxClient = rActive.width();
    cyClient = rActive.height();
    cxLeftMgn = 0;
    cyTopMgn = 0;
    thePolarScaler.enable(0);
    if ( canvas()->type() == MetaDisp ) {
       rActive = zRect(0,0,1333, 1000);
       canvas()->setWindowExt(1333, 1000);
       canvas()->setPictureArea(&rActive);
       }
    }
 else if ( fToFit || canvas()->type() == PrinterDisp  ) {
    PageData pd;
    pd.getFromIni(PageOptGra_SEC);
    zRect rx = pd.getMargins();
    zLoEnglish let(rx.left(), rx.top(), canvas());
    zLoEnglish leb(rx.right(), rx.bottom(), canvas());
    // debug( "t = %d, l = %d, b = %d, r = %d", let.y(), let.x(), leb.y(), leb.x() );
    rActive = zRect(let.x(),let.y(),r.width()-leb.x(), r.height()-leb.y());
    // debug( "ractive t = %d, l = %d, b = %d, r = %d", rActive.top(),
    //   rActive.left(), rActive.bottom(), rActive.right() );
    cxLeftMgn = -let.x();
    cyTopMgn = -let.y();
    //canvas()->setPictureArea(&r);
    cxClient = rActive.width();
    cyClient = rActive.height();
    thePolarScaler.setupResolutions( canvas()->pixPerInchX(),
	  canvas()->pixPerInchY() );
    }
 else {
    cxLeftMgn = 0;
    cyTopMgn = 0;
    int w = GetSystemMetrics(SM_CXFULLSCREEN)-
	  GetSystemMetrics(SM_CXHSCROLL);
    int h = GetSystemMetrics(SM_CYFULLSCREEN)-
	  GetSystemMetrics(SM_CYHSCROLL) -
	  GetSystemMetrics(SM_CYMENU);
    rActive = zRect(0,0,(int)((float)w*scale),
         (int)((float)h * scale));
    canvas()->setPictureArea(&rActive);
    thePolarScaler.enable(0);
    }
 computeRadiusData();
 if ( pDataFnt != NULL )
    delete pDataFnt;
 pDataFnt = new zFont(gf.getDataFont(),
     zDimension(0,fontSize(32)), FW_NORMAL);
 if ( pBdDataFnt != NULL )
    delete pBdDataFnt;
 pBdDataFnt = new zFont(gf.getDataFont(),
     zDimension(0,fontSize(32)), FW_BOLD );
 if ( pGlyphSpec != NULL )
    delete pGlyphSpec;
 int fs;
 pTickGlyphSpec = new zFontSpec(gf.getGlyphFont(),
     zDimension(0,fontSize(24)), FW_NORMAL, ffDecorative,
     VariablePitch, 0, 0, 0, SymbolCharSet/*,
     DefaultOutPrec, DefaultClipPrec, DefaultQual */ );
 if ( pTickGlyphFnt != NULL )
    delete pTickGlyphFnt;
 pTickGlyphFnt = new zFont( *pTickGlyphSpec );
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
 pGlyphSpec = new zFontSpec(gf.getGlyphFont(),
     zDimension(0,fs), FW_NORMAL, ffDecorative,
     VariablePitch, 0, 0, 0, SymbolCharSet/*,
     DefaultOutPrec, DefaultClipPrec, DefaultQual*/ );
 if ( pGlyphFnt != NULL )
    delete pGlyphFnt;
 pGlyphFnt = new zFont( *pGlyphSpec );
 if ( pDegSpec != NULL )
    delete pDegSpec;
 if ( data->ncharts()==2 )
    fs = 37;
 else
    fs = 33;
 pDegSpec = new zFontSpec(gf.getGlyphFont(),
     zDimension(0,fontSize(fs)), FW_NORMAL, ffDecorative,
     VariablePitch, 0, 0, 0, SymbolCharSet/*,
     DefaultOutPrec, DefaultClipPrec, DefaultQual*/ );
 if ( pDegFnt != NULL )
    delete pDegFnt;
 pDegFnt = new zFont( *pDegSpec );
#ifdef NEW
 if ( pGridFont != NULL )
    delete pGridFont;
 pGridFont = new zFont(gf.getGlyphFont(),
     zDimension(0,fontSize(38)), FW_NORMAL, ffDecorative,
     VariablePitch, 0, 0, 0, SymbolCharSet/*,
     DefaultOutPrec, DefaultClipPrec, DefaultQual*/ );
#endif
 if ( canvas()->type() != MetaDisp ) {
    canvas()->pushFont(pDataFnt);
    zFontInfo *pFi = new zFontInfo( canvas() );
    cxChar = pFi->width();
    cyChar = pFi->height()+pFi->externLead();
    canvas()->popFont();
    delete pFi;
    }
 else {
    cxChar = fontSize(42);
    cyChar = fontSize(32)+3;
    }
 canvas()->unlock();
 if ( canvas()->type() == WinDisp ) {
    updateScroller();
    thePolarScaler.enable(0);
    }
}

void AstGraphicsPane::copyToClipboard()
{
 int ft;
 int left = cxLeftOffset, top = cyTopOffset;

 setCursor( zCursor(Hourglass) );
 captureMouse();
 zMetafileDisplay *meta = new zMetafileDisplay(canvas());
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 pushDisplay(meta);
 draw(0);
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 popDisplay();
 pClip->clear();
 pClip->add(meta);
 zBitmapDisplay *bit = new zBitmapDisplay(canvas(), 600, 400);
 ft = fToFit;
 fToFit = 1;
 cxLeftOffset = 0;
 cyTopOffset = 0;
 pushDisplay(bit);
 draw(0);
 fToFit = ft;
 cxLeftOffset = left;
 cyTopOffset = top;
 popDisplay();
 zBitmap *bm = bit->getBitmap();
 bit->setBitmap(0);
 pClip->add(bm);
 delete bit;
 delete bm;
 releaseMouse();
 setCursor( zCursor(Arrow) );
}

int AstGraphicsPane::doPrint(zEvent *)
{
 float fs;
 char buf[150];

 strcpy( buf, CResStr(_GRP_PRINTING)/*"Printing: "*/ );
 strcat( buf, data->getFileDb()->name );
 PrinterSetup psg;
 psg.getFromIni(GraphPrintOpt_SEC);
 zPrinterDisplay *pr=new zPrinterDisplay(psg.getSpec(), psg.toDevMode(0, 0));
 AstPrJobDlg *prDlg=new AstPrJobDlg(app->rootWindow());
 prDlg->setName(buf);
 zPrintJob *pj = new zPrintJob(this, pr, prDlg);
 pj->banding()=0;
 pj->setJobName(buf);
 pj->go();
 while ( app->tasks()->busy() ) {
       zYield(0);
       zYield(1);
       }
 return 1;
}

int AstGraphicsPane::print(zPrinterDisplay *pd, zRect *)
{
 GraphOptions ogd;

 float fs = fontScale;
 int dmode = drawMode;
 ogd.getFromIni(GraphPrintOpt_SEC);
 fs = fontScale;
 fontScale = (float)ogd.getFontSize();
 fontScale /= 100.0;
 pushDisplay(pd);
 draw(0);
 fontScale=fs;
 drawMode = dmode;
 popDisplay();
 draw(0);
 return 0;
}

int AstGraphicsPane::morePages()
{
return( 0 );
}

int AstGraphicsPane::scroll( zEvent *e )
{
 int scrollBy;
 zRange s;

 if ( !fToFit ) {
    zScrollInfoVert *pSiv = scrollBarVert();
    zScrollInfoHoriz *pSih = scrollBarHoriz();
    switch( e->parm1() ) {
       case SB_TOP:
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
               pSih->pos(0);
               cxLeftOffset = 0;
               }
            else {
	       pSiv->pos(0);
	       cyTopOffset = 0;
	       }
	    canvas()->setDirty();
	    break;
       case SB_BOTTOM:
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
	       s = pSih->limits();
	       cxLeftOffset = s.hi();
	       pSih->pos(cxLeftOffset);
	       }
	    else {
	       s = pSiv->limits();
	       cyTopOffset = s.hi();
	       pSiv->pos(cyTopOffset);
	       }
	    canvas()->setDirty();
	    break;
       case SB_PAGEUP:
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
	       if (cxLeftOffset > cxClient)
		  cxLeftOffset -= cxClient;
	       else
		  cxLeftOffset = 0;
	       pSih->pos(cxLeftOffset);
	       }
	    else {
	       if (cyTopOffset > cyClient)
		  cyTopOffset -= cyClient;
	       else
		  cyTopOffset = 0;
	       pSiv->pos(cyTopOffset);
	       }
	    canvas()->setDirty();
	    break;
       case SB_PAGEDOWN:
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
	       s = pSih->limits();
	       if (cxLeftOffset+cxClient <= s.hi() )
		  cxLeftOffset += cxClient;
	       else
		  cxLeftOffset = s.hi();
	       pSih->pos(cxLeftOffset);
	       }
            else {
	       s = pSiv->limits();
	       if (cyTopOffset+cyClient <= s.hi())
		  cyTopOffset += cyClient;
	       else
		  cyTopOffset = s.hi();
	       pSiv->pos(cyTopOffset);
	       }
	    canvas()->setDirty();
	    break;
       case SB_THUMBPOSITION:
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
	       cxLeftOffset = pSih->pos();
	       }
	    else {
	       cyTopOffset = pSiv->pos();
	       }
	    canvas()->setDirty();
	    break;
       case SB_LINEDOWN:
	    {
	    zRect x(0, 0, cxClient, cyClient);
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
	       s = pSih->limits();
	       if (cxLeftOffset < s.hi()-10) {
		  scrollBy = 10;
		  cxLeftOffset += 10;
                  }
	       else if (cxLeftOffset < s.hi()) {
		  cxLeftOffset = s.hi();
		  scrollBy = (s.hi()-cxLeftOffset);
                  }
	       else
                  break;
	       pSih->pos(cxLeftOffset);
	       ScrollWindow( *this, -scrollBy, 0, NULL,(LPRECT) &x );
	       }
	    else {
	       s = pSiv->limits();
	       if (cyTopOffset < s.hi()-10) {
		  scrollBy = 10;
		  cyTopOffset += 10;
                  }
	       else if ( cyTopOffset < s.hi() ) {
		  scrollBy = s.hi() - cyTopOffset;
		  cyTopOffset = s.hi();
                  }
	       else
                  break;
	       pSiv->pos(cyTopOffset);
	       ScrollWindow( *this, 0, -scrollBy, NULL,(LPRECT) &x );
	       }
	    }
	    break;
       case SB_LINEUP:
	    {
	    zRect y(0, 0, cxClient, cyClient);
	    if (e->Msg == 1 || e->Msg == WM_HSCROLL) {
	       if (cxLeftOffset > 10) {
		  cxLeftOffset -= 10;
		  scrollBy = 10;
                  }
	       else if ( cxLeftOffset ) {
		  scrollBy = cxLeftOffset;
		  cxLeftOffset = 0;
                  }
	       else
	          break; 
	       pSih->pos(cxLeftOffset);
	       ScrollWindow( *this, scrollBy, 0, NULL, NULL );
	       y = zRect(0, 0, scrollBy, cyClient );
	       }
	    else {
	       if (cyTopOffset > 10) {
		  scrollBy = 10;
		  cyTopOffset -= 10;
                  }
	       else if ( cyTopOffset ) {
		  scrollBy = cyTopOffset;
		  cyTopOffset = 0;
                  }
	       else
                  break;
	       pSiv->pos(cyTopOffset);
	       ScrollWindow( *this, 0, scrollBy, NULL, NULL );
	       }
	    }
	    break;
       default :
	    return( 0 );
	    break;
       }
    }
 else
    return( 0 );
 return( 1 );
}

void AstGraphicsPane::updateGrfas()
{
 dataGroup->doGrfs(data->getData()->natal_minutes,
     data->getData()->maxpt, data->getData()->natal_house_cusps,
     drawMode, old_asc_min );
 asc_min = dataGroup->getAsc();
 if ( data->ncharts() == 1 && data->getData()->num_aspects ) {
    int n;
    GR_ASPT *as;
    as = data->getAspects(n); 
    dataGroup->doAspects(as, n);
    }
 if ( compGroup == NULL ) {
    canvas()->setDirty();
    return;
    }
 if ( data->getData()->type == TRANSITS_GRAPH_FILE ||
		data->getData()->type == COMPTR_GRAPH_FILE  ) {
#ifdef NEW
    compGroup->doGrfs( ( data->getData()->num_charts > 0 ?
       pCurChart->getChartMinutes() :
       data->getData()->other_minutes ),
       data->getData()->num_charts > 0 ? pCurChart->maxpt :
	  data->getData()->maxpt, data->getData()->other_house_cusps,
      drawMode, old_asc_min );
#else
    compGroup->doGrfs( ( data->getData()->num_charts > 0 ?
       pCurChart->getChartMinutes() : data->getData()->other_minutes ),
       data->getData()->maxpt, data->getData()->other_house_cusps,
      drawMode, old_asc_min );
#endif
    }
 else {
    compGroup->doGrfs(data->getData()->other_minutes,
    data->getData()->maxpt, data->getData()->other_house_cusps,
    drawMode, old_asc_min );
    }
 canvas()->setDirty();
}

int AstGraphicsPane::menuCommand( zCommandEvt *e )
{
 if ( (HWND)*this != GetFocus() )
    return( 0 );
 switch( (unsigned int)e->cmd() ) {
      case IDM_SIGN_NAME :
	   drawMode ^= SIGN_NAME;
	   pgMenu->checkItem(IDM_SIGN_NAME,drawMode & SIGN_NAME );
	   break;
      case IDM_HOUSE_DEG :
	   drawMode ^= HOUSE_DEG;
	   pgMenu->checkItem(IDM_HOUSE_DEG,drawMode & HOUSE_DEG );
	   break;
      case IDM_HOUSE_NUM :
	   drawMode ^= HOUSE_NUM;
	   pgMenu->checkItem(IDM_HOUSE_NUM,drawMode & HOUSE_NUM );
	   break;
      case IDM_SHOW_ASPT :
	   drawMode ^= SHOW_ASPT;
	   pgMenu->checkItem(IDM_SHOW_ASPT,drawMode & SHOW_ASPT );
	   break;
      case IDM_USE_GLYPH :
	   drawMode ^= USE_GLYPH;
	   pgMenu->checkItem(IDM_USE_GLYPH,drawMode & USE_GLYPH );
           updateGrfas();
	   break;
      case IDM_SHOW_SLIN :
	   drawMode ^= SHOW_SLIN;
	   pgMenu->checkItem(IDM_SHOW_SLIN,drawMode & SHOW_SLIN );
	   break;
#ifdef NEW
#ifdef DELUXE
      case IDM_SHOW_AGRID :
	   drawMode ^= SHOW_AGRID;
	   pgMenu->checkItem(IDM_SHOW_AGRID,drawMode & SHOW_AGRID );
	   break;
#endif
#endif
      case IDM_USE_INHC :
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
	       }
	   pgMenu->checkItem(IDM_USE_INHC, which_houses );
	   break;
      case IDM_SIGN_TICK :
	   drawMode ^= SIGN_TICK;
	   pgMenu->checkItem(IDM_SIGN_TICK,drawMode & SIGN_TICK );
	   break;
      case IDM_DEC_TICK :
	   drawMode ^= DEC_TICK;
	   pgMenu->checkItem(IDM_DEC_TICK,drawMode & DEC_TICK );
	   break;
      case IDM_DEG_TICK :
	   drawMode ^= DEG_TICK;
	   pgMenu->checkItem(IDM_DEG_TICK,drawMode & DEG_TICK );
	   break;
      case IDM_HOUS_OUTS :
           drawMode ^= HOUS_OUTS;
	   pgMenu->checkItem(IDM_HOUS_OUTS,drawMode & HOUS_OUTS );
	   break;
      case IDM_PLOT_CLASSIC :
	   drawMode ^= PLOT_CLASSIC;
	   pgMenu->checkItem(IDM_PLOT_CLASSIC,drawMode & PLOT_CLASSIC );
	   break;
      case IDM_SHOW_DEGS :
	   drawMode ^= SHOW_PDEGS;
	   pgMenu->checkItem(IDM_SHOW_DEGS,drawMode & SHOW_PDEGS );
	   break;
      case IDM_GNEXTC :
	   pCurChart = data->getNextChart();
	   updateGrfas();
	   break;
      case IDM_GSHPREVC :
	   pCurChart = data->getPrevChart();
	   updateGrfas();
	   break;
      case IDM_GSHFIRST :
	   pCurChart = data->getFirstChart();
	   updateGrfas();
	   break;
      case IDM_GDECHSE :
	   dataGroup->decreaseHouses();
	   if ( compGroup != NULL )
	      compGroup->decreaseHouses();
	   updateGrfas();
	   break;
      case IDM_GINCHSE :
	   dataGroup->increaseHouses();
	   if ( compGroup != NULL )
	      compGroup->increaseHouses();
	   updateGrfas();
	   break;
      case IDM_GREGHSE :
	   dataGroup->resetHouses();
	   if ( compGroup != NULL )
	      compGroup->resetHouses();
	   offset = 0;
	   updateGrfas();
	   break;
      case IDM_ZOOMIN:
            scale *= 1.3333;
	    cxLeftOffset *= 4;
	    cxLeftOffset /= 3;
	    cyTopOffset *= 4;
	    cyTopOffset /= 3;
            setMetrics();
	    updateScroller();
	    canvas()->setDirty();
	    break;
       case IDM_ZOOMOUT :
            if ( scale > .4444 ) {
               scale *= .75;
	       cxLeftOffset *= 3;
	       cxLeftOffset /= 4;
	       cyTopOffset *= 3;
	       cyTopOffset /= 4;
	       updateScroller();
	       setMetrics();
	       canvas()->setDirty();
               }
            break;
       case IDM_FITWIN :
	    if ( fToFit ) {
	       fToFit = 0;
	       scale = 1.0;
	       cxLeftOffset = 0;
	       cyTopOffset = 0;
               }
	    else {
	       fToFit = 1;
	       cxLeftOffset = 0;
	       cyTopOffset = 0;
	       }
	    pgMenu->checkItem(IDM_FITWIN, fToFit );
	    updateScroller();
	    setMetrics();
	    canvas()->setDirty();
	    break;
#ifdef NEW
      case IDM_FCLOSE :
	   //PostMessage((HWND)(*this),WM_CLOSE,0,0L);
	   PostMessage((HWND)(*parent()),WM_CLOSE,0,0L);
	   break;
#endif
       case IDM_FPRINT:
	    doPrint(NULL);
	    break;
#ifdef PRO
       case IDM_FEXPORT:
	    export();
	    break;
#endif
       case IDM_ECOPY:
	    copyToClipboard();
	    break;
       default :
	   return( 0 );
	   break;
      }
 pgMenu->update();
 setMetrics();
 canvas()->setDirty();
 return( 1 );
}

typedef int (zEvH::*MouseClickProc)(zMouseClickEvt*);

int AstGraphicsPane::kbhnd(zKeyEvt *e)
{
 zEvent ev;

 ev.Msg = 0;
 if ( !fToFit ) {
    switch( (unsigned char)e->ch() ) {
          case VK_PRIOR:
	       ev.wParam = SB_PAGEUP;
	       return( scroll(&ev) );
	       break;
          case VK_NEXT:
	       ev.wParam = SB_PAGEDOWN;
	       return( scroll(&ev) );
	       break;
          case VK_UP:
	       ev.wParam = SB_LINEUP;
	       return( scroll(&ev) );
	       break;
          case VK_DOWN:
	       ev.wParam = SB_LINEDOWN;
	       return( scroll(&ev) );
	       break;
          case VK_HOME:
	       if ( !e->ctrl() )
		  ev.Msg = 1;
	       ev.wParam = SB_TOP;
	       return( scroll(&ev) );
	       break;
          case VK_END:
	       if ( !e->ctrl() )
		  ev.Msg = 1;
	       ev.wParam = SB_BOTTOM;
	       return( scroll(&ev) );
	       break;
          case VK_LEFT :
	       if ( e->ctrl() )
		  ev.wParam = SB_PAGEUP;
	       else
		  ev.wParam = SB_LINEUP;
	       ev.Msg=1;
	       return( scroll(&ev) );
	       break;
	  case VK_RIGHT :
	       if ( e->ctrl() )
		  ev.wParam = SB_PAGEDOWN;
	       else
		  ev.wParam = SB_LINEDOWN;
	       ev.Msg=1;
	       return( scroll(&ev) );
	       break;
	  case 0xdb :   /* [ */
	       if ( !e->shift() ) {
		  pCurChart = data->getNextChart();
		  updateGrfas();
		  }
	       break;
	  case 0xdd :  /* ] */
	       if ( !e->shift() ) {
		  pCurChart = data->getPrevChart();
		  updateGrfas();
		  }
	       break;
	  case 0xbb :  /* = */
	       if ( !e->shift() ) {
		  pCurChart = data->getFirstChart();
		  updateGrfas();
		  }
	       break;
	  case 0xbc :   /* < */
	       if ( e->shift() ) {
		  dataGroup->decreaseHouses();
		  if ( compGroup != NULL )
		     compGroup->decreaseHouses();
		  updateGrfas();
		  }
	       break;
	  case 0xbe :   /* > */
	       if ( e->shift() ) {
		  dataGroup->increaseHouses();
		  if ( compGroup != NULL )
		     compGroup->increaseHouses();
		  updateGrfas();
		  }
	       break;
	  case '2' :   /* @ */
	       if ( e->shift() ) {
		  dataGroup->resetHouses();
		  if ( compGroup != NULL )
		     compGroup->resetHouses();
		  updateGrfas();
		  }
	       break;
	  case VK_F1:
	       WinHelp(*this, set_path("ASTROW.HLP", HELP_F ),
					    HELP_CONTEXT, HELPID_GRAPHICS );
	       break;

	  default :
	       return( 0 );
	       break;
	       }
	  }
 return(1);
}

#ifndef NEW
int AstGraphicsPane::mouseButtonDown( zMouseClickEvt *e )
{
 return( 1 );
}
#endif

void AstGraphicsPane::updateScroller()
{
 zRange s;
 zScrollInfoVert *pSiv = scrollBarVert();
 zScrollInfoHoriz *pSih = scrollBarHoriz();
 if ( pSiv == NULL || pSih == NULL )
    return;
 pSih->pageDelta(cxClient);
 pSiv->pageDelta(cyClient);
 pSih->moveDelta(10);
 pSiv->moveDelta(10);
 s.lo() = 0;
 s.hi() = rActive.width()-cxClient;
 pSih->limits(s);
 s.lo() = 0;
 s.hi() = rActive.height()-cyClient;
 pSiv->limits(s);
 pSiv->pos(cyTopOffset);
 pSih->pos(cxLeftOffset);
}

int AstGraphicsPane::draw( zDrawEvt *e )
{
 int l;

 if ( !isOk() )
    return( 1 );
 canvas()->lock();
 if ( canvas()->type() != PrinterDisp )
    canvas()->backColor(zColor());
 if ( canvas()->type() != WinDisp )
     canvas()->setWindowOrg( cxLeftMgn, cyTopMgn );
 else
     canvas()->setWindowOrg( cxLeftOffset, cyTopOffset );
 SetBkMode( *canvas(), TRANSPARENT );
 zRect r;
 canvas()->getDirty(r);
 canvas()->fill(r,pbBack);
 zBrush *pB = new zBrush(NullBrush);
 canvas()->pushBrush(pB);
 DataKey *pdk = new DataKey(canvas(), pDataFnt, pBdDataFnt, cyChar+1, data->getData());
 if ( pCurChart != NULL )
    pdk->setDate2(pCurChart->getDate());
 pdk->drawKey();
 delete pdk;
#ifdef NEW
#ifdef DELUXE
 if ( data->ncharts() == 1 ) {
    PlanetsKey *pk = new PlanetsKey(canvas(), pDegFnt, cyChar+1,
		rActive.width(), dataGroup );
    pk->draw();
    delete pk;
    }
#endif
#endif
 WheelKey *pwk = new WheelKey( canvas(), pDataFnt, pBdDataFnt,
	rActive.height()-((cyChar+1) * 5), cxChar*2, cyChar+1 );
 pwk->drawKeys();
 delete pwk;
 if ( canvas()->type() != WinDisp )
    canvas()->setWindowOrg( (-radiusData.getOffset())+cxLeftMgn, (-rActive.height()/2)+cyTopMgn );
 else
    canvas()->setWindowOrg( (-radiusData.getOffset())+cxLeftOffset,
	       (-(rActive.height()/2))+cyTopOffset );
 if ( drawMode & SIGN_NAME ) {
    PlotSigns *pps = new PlotSigns(canvas(),
	 radiusData.getOutsideCirc(),
	 (drawMode & USE_GLYPH?pGlyphFnt:pDataFnt), asc_min);
    pps->plot(drawMode);
    delete pps;
    }
 if (drawMode & (SIGN_TICK|DEC_TICK|DEG_TICK) ) {
    if ( drawMode & SIGN_TICK ) {
       canvas()->pushFont(pTickGlyphFnt);
       SignTickCircle *pstc = new SignTickCircle( canvas(),
	  radiusData.getSignTick(),
	  radiusData.getOutsideCirc(),asc_min);
       pstc->draw();
       delete pstc;
       canvas()->popFont();
       }
    if ( drawMode & DEC_TICK ) {
       DecanTickCircle *pdtc = new DecanTickCircle( canvas(),
	  radiusData.getDecanTick(),
	  radiusData.getSignTick(),asc_min);
       pdtc->draw();
       delete pdtc;
       }
    if ( drawMode & DEG_TICK ) {
       DegreeTickCircle *pdetc = new DegreeTickCircle( canvas(),
	  radiusData.getDegreeTick(),
	  radiusData.getDecanTick(),asc_min );
       pdetc->draw();
       delete pdetc;
       }
    }
 else {
    PlainCircle *ppc = new PlainCircle( canvas(),
    	radiusData.getMainCirc());
    ppc->draw();
    delete ppc;
    }
 if ( drawMode & SHOW_SLIN ) {
    SignLinePlotter *pslp = new SignLinePlotter(canvas(),asc_min);
    pslp->setCirc(radiusData.getInCirc(),
        radiusData.getMainCirc());
    pslp->plot();
    }
 if ( dataGroup->getAsc() != -1 ) {
    zFont *pFnthn;
    zFontSpec fsp = *pDegSpec;
    if ( !(drawMode & HOUS_OUTS) ) {
       LPLOGFONT pfsp = (LPLOGFONT)fsp;
       pfsp->lfHeight *= 3;
       pfsp->lfHeight /= 4;
       pfsp->lfWidth *= 3;
       pfsp->lfWidth /= 4;
       pFnthn = new zFont(fsp);
       }
    HousePlotter *php = new HousePlotter(canvas(),
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
#ifdef NEW
 if ( drawMode & PLOT_CLASSIC ) {
    if ( plot != NULL )
       delete plot;
    plot = (PlanetPlotter *) new PlanetPlotterClassical(canvas(),
	 dataGroup->getPlanets(), radiusData.getMainCirc()
	 - (radiusData.getMargin()), WH_OUTER );
    ((PlanetPlotterClassical *)plot)->setFonts(pDegSpec);
    plot->doPlot();
    }
 else {
    if ( plot != NULL )
       delete plot;
    plot = new PlanetPlotter(canvas(), dataGroup->getPlanets(),
	radiusData.getMainCirc() - radiusData.getMargin(),
	0, (compGroup != NULL ? radiusData.getSecondCirc()
	: radiusData.getInCirc()), WH_OUTER );
    if ( drawMode & SHOW_PDEGS )
       plot->setFonts(pGlyphSpec,pDegSpec);
    else
       plot->setFonts(pGlyphSpec,0);
    plot->doPlot();
    }
#else
 if ( drawMode & PLOT_CLASSIC ) {
    PlanetPlotterClassical *pppc = new PlanetPlotterClassical(canvas(),
	 dataGroup->getPlanets(), radiusData.getMainCirc()
	 - radiusData.getMargin(), WH_OUTER );
    pppc->setFonts(pDegSpec);
    pppc->doPlot();
    delete pppc;
    }
 else {
    PlanetPlotter *ppp = new PlanetPlotter(canvas(), dataGroup->getPlanets(),
        radiusData.getMainCirc() - radiusData.getMargin(),
	0, (compGroup != NULL ? radiusData.getSecondCirc()
	: radiusData.getInCirc()), WH_OUTER );
    if ( drawMode & SHOW_PDEGS )
       ppp->setFonts(pGlyphSpec,pDegSpec);
    else
       ppp->setFonts(pGlyphSpec,0);
    ppp->doPlot();
    delete ppp;
    }
#endif
 if (drawMode & SHOW_ASPT && data->getData()->num_aspects) {
    int cnt;
    GR_ASPT *pas = dataGroup->getAspects(cnt);
    AspectCircle *pac = new AspectCircle(canvas(), pas, cnt,
	radiusData.getAspectCirc(), cyChar );
    pac->draw();
    delete pac;
    }
 if (compGroup != NULL && data->ncharts() > 1) {
    PlainCircle *ppc2 = new PlainCircle( canvas(),
	radiusData.getSecondCirc());
    ppc2->draw();
    delete ppc2;
#ifdef NEW
    if ( drawMode & PLOT_CLASSIC ) {
       if ( plot2 != NULL )
	  delete plot2;
       plot2 = (PlanetPlotter *) new PlanetPlotterClassical(canvas(),
	  compGroup->getPlanets(), radiusData.getSecondCirc(), WH_INNER );
       ((PlanetPlotterClassical *)plot2)->setFonts(pDegSpec);
       plot2->doPlot();
       }
    else {
       if ( plot2 != NULL )
	  delete plot2;
       plot2 = new PlanetPlotter(canvas(), compGroup->getPlanets(),
	 radiusData.getSecondCirc(), 0,
	 radiusData.getSecondCirc(), WH_INNER );
       if ( drawMode & SHOW_PDEGS )
	  plot2->setFonts(pGlyphSpec,pDegSpec);
       else
	  plot2->setFonts(pGlyphSpec,0);
       plot2->doPlot();
       }
#else
    if ( drawMode & PLOT_CLASSIC ) {
       PlanetPlotterClassical *pppc2 = new PlanetPlotterClassical(canvas(),
	  compGroup->getPlanets(), radiusData.getSecondCirc()
	  - radiusData.getMargin(), WH_INNER );
       pppc2->setFonts(pDegSpec);
       pppc2->doPlot();
       delete pppc2;
       }
    else {
       PlanetPlotter *ppp2 = new PlanetPlotter(canvas(), compGroup->getPlanets(),
	 radiusData.getSecondCirc(), 0,
	 radiusData.getSecondCirc(), WH_INNER );
       if ( drawMode & SHOW_PDEGS )
	  ppp2->setFonts(pGlyphSpec,pDegSpec);
       else
	  ppp2->setFonts(pGlyphSpec,0);
       ppp2->doPlot();
       delete ppp2;
       }
#endif
    }
 canvas()->setWindowOrg( cxLeftOffset+cxLeftMgn, cyTopOffset+cyTopMgn  );
 l = data->getData()->type;
 if ( l == COMPATAB_GRAPH_FILE || l == PROGRESS_GRAPH_FILE ||
      l == TRANSITS_GRAPH_FILE || l == COMPTR_GRAPH_FILE ) {
    StatusKey *psk = new StatusKey( canvas(), BR+HOUS,
	rActive.width(), 0, TA_TOP|TA_RIGHT, pDataFnt);
    psk->draw(CResStr(_GRP_HOUSES)/*"HOUSES:"*/);
    delete psk;
    StatusKey *psk2 = new StatusKey( canvas(), BR+RISE,
	rActive.width(), cyChar+1, TA_TOP|TA_RIGHT, pBdDataFnt);
    if ( data->getData()->type == COMPATAB_GRAPH_FILE ) {
       if ( which_houses )
          psk2->draw(data->getData()->name2);
       else
          psk2->draw(data->getData()->name1);
       }
    if ( data->getData()->type == PROGRESS_GRAPH_FILE ) {
       if ( which_houses )
          psk2->draw(CResStr(_GRP_PROGR)/*"Progressed"*/);
       else
          psk2->draw(data->getData()->name1);
       }
    if ( data->getData()->type == TRANSITS_GRAPH_FILE ) {
       if ( which_houses )
	  psk2->draw(CResStr(_GRP_TRANS)/*"Transits"*/);
       else
	  psk2->draw(data->getData()->name1);
       }
    if ( data->getData()->type == COMPTR_GRAPH_FILE ) {
       if ( which_houses )
	  psk2->draw(CResStr(_GRP_TRANS)/*"Transits"*/);
       else
	  psk2->draw(CResStr(_GRP_COMPH)/*"Composite Houses"*/);
       }
    delete psk2;
    }
#ifdef NEW
#ifdef DELUXE
 if (drawMode & SHOW_AGRID && data->getData()->num_grid_aspects > 0 && !which_houses) {
    canvas()->pushFont( pGridFont );
    gridAspts = data->getGridAspects(gridCnt);
    gridMaxpt = data->getData()->maxpt;
    AspectGrid *ag = new AspectGrid(canvas(), zPoint(rActive.width()-1,rActive.height()-1),
	 zDimension(fontSize(38)+1,fontSize(38)+1), gridAspts, gridCnt, data->getData()->maxpt );
    ag->draw();
    delete ag;
    canvas()->popFont();
    }
 else if (drawMode & SHOW_AGRID && data->getData()->num_other_grid_aspects > 0 && which_houses ) {
    canvas()->pushFont( pGridFont );
    gridAspts = data->getOtherGridAspects(gridCnt);
    gridMaxpt = data->getData()->maxpt;
    AspectGrid *ag = new AspectGrid(canvas(), zPoint(rActive.width()-1,rActive.height()-1),
	 zDimension(fontSize(38)+1,fontSize(38)+1), gridAspts, gridCnt, data->getData()->maxpt );
    ag->draw();
    delete ag;
    canvas()->popFont();
    }
 else if (drawMode & SHOW_AGRID && (data->getData()->type ==
       TRANSITS_GRAPH_FILE||data->getData()->type == COMPTR_GRAPH_FILE ) &&
       pCurChart != NULL && pCurChart->aspect_count > 0 ) {
    canvas()->pushFont( pGridFont );
    gridAspts = pCurChart->getAspects(gridCnt);
    gridMaxpt = pCurChart->maxpt;
    AspectGrid *ag = new AspectGrid(canvas(), zPoint(rActive.width()-1,rActive.height()-1),
	 zDimension(fontSize(38)+1,fontSize(38)+1), gridAspts, gridCnt, gridMaxpt );
    ag->draw();
    delete ag;
    canvas()->popFont();
    }
 else {
    gridAspts = NULL;
    gridCnt = 0;
    gridMaxpt = 0;
    }
#endif
#endif
 canvas()->setWindowOrg( 0, 0 );
 delete canvas()->popBrush();
 canvas()->unlock();
 return(1);
}

AstGraphicsPane::~AstGraphicsPane()
{
 baseMetrics->deInit();
 delete baseMetrics;
 delete pGlyphSpec;
 delete pDegSpec;
 delete pTickGlyphSpec;
 delete pDataFnt;
 delete pBdDataFnt;
 delete pGlyphFnt;
 delete pTickGlyphFnt;
 delete pDegFnt;
 delete pbBack;
#ifdef NEW
#ifdef DELUXE
 delete pGridFont;
 if ( plot != NULL )
    delete plot;
 if ( plot2 != NULL )
    delete plot2;
 close_text_report();
#endif
#endif
 if ( isOk() ) {
    delete data;
    delete dataGroup;
    if ( compGroup != NULL )
       delete compGroup;
    }
}

void AstGraphicsPane::setupMenu()
{
 if ( drawMode & SIGN_NAME )
    pgMenu->checkItem(IDM_SIGN_NAME, TRUE );
 if ( drawMode & HOUSE_DEG )
    pgMenu->checkItem(IDM_HOUSE_DEG, TRUE );
 if ( drawMode & HOUSE_NUM )
    pgMenu->checkItem(IDM_HOUSE_NUM, TRUE );
 if ( drawMode & SHOW_ASPT )
    pgMenu->checkItem(IDM_SHOW_ASPT, TRUE );
 if ( drawMode & USE_GLYPH )
    pgMenu->checkItem(IDM_USE_GLYPH, TRUE );
 if ( drawMode & SHOW_SLIN )
    pgMenu->checkItem(IDM_SHOW_SLIN, TRUE );
 if ( which_houses )
    pgMenu->checkItem(IDM_USE_INHC, TRUE );
 if ( drawMode & SIGN_TICK )
    pgMenu->checkItem(IDM_SIGN_TICK, TRUE );
 if ( drawMode & DEC_TICK )
    pgMenu->checkItem(IDM_DEC_TICK, TRUE );
 if ( drawMode & DEG_TICK )
    pgMenu->checkItem(IDM_DEG_TICK, TRUE );
 if ( drawMode & HOUS_OUTS )
    pgMenu->checkItem(IDM_HOUS_OUTS, TRUE );
 if ( drawMode & PLOT_CLASSIC )
    pgMenu->checkItem(IDM_PLOT_CLASSIC, TRUE );
 if ( drawMode & SHOW_PDEGS )
    pgMenu->checkItem(IDM_SHOW_DEGS, TRUE );
#ifdef NEW
#ifdef DELUXE
 if ( data->getData()->num_grid_aspects ||
      data->getData()->num_other_grid_aspects ||
	  (( data->getData()->type == TRANSITS_GRAPH_FILE ||
	   data->getData()->type == COMPTR_GRAPH_FILE ) &&
	  pCurChart != NULL && pCurChart->aspect_count > 0 )) {
       enableMenuItems(pgMenu, IDM_SHOW_AGRID );
       if (drawMode & SHOW_AGRID)
	  pgMenu->checkItem(IDM_SHOW_AGRID, TRUE );
       }
  else {
      if ( drawMode & SHOW_AGRID )
         drawMode ^= SHOW_AGRID;
      }
#endif
#endif
 if ( data->ncharts() > 1 && data->getData()->type != TRANSITS_GRAPH_FILE )
    enableMenuItems(pgMenu, IDM_USE_INHC );
 else {
    if ( data->getData()->num_aspects ) {
       enableMenuItems(pgMenu, IDM_SHOW_ASPT );
       if (drawMode & SHOW_ASPT)
	  pgMenu->checkItem(IDM_SHOW_ASPT, TRUE );
       }
    }
 if (data->getData()->type == TRANSITS_GRAPH_FILE ||
	      data->getData()->type == COMPTR_GRAPH_FILE  ) {
    if ( data->getData()->num_charts > 0 )
       enableMenuItems(pgMenu, IDM_GNEXTC, IDM_GSHFIRST );
    }
 enableMenuItems(parMenu, IDM_ECOPY );
#ifdef PRO
 enableMenuItems(parMenu, IDM_FEXPORT );
#endif
#ifdef NEW
 enableMenuItems(parMenu, IDM_FCLOSE );
#endif
 enableMenuItems(parMenu, IDM_FPRINT );
 pgMenu->update();
 parMenu->update();
}

AstGraphicsPane::AstGraphicsPane(char *pName, zWindow *w, int dir) : zPane(w,new zSizeWithParent,zSCROLLV|zSCROLLH)
{
 GraphOptions ogd;

 ogd.getFromIni(GraphicsOptions_SEC);
 fontScale = (float)ogd.getFontSize();
 fontScale /= 100.0;
 fToFit = 0;
 scale = 1.0;
#ifdef NEW
 plot = NULL;
 plot2 = NULL;
#endif
 cxLeftOffset = 0;
 cyTopOffset = 0;
 which_houses = 0;
 data = new GraphData();
 pCurChart = NULL;
 if ( data && !data->read(pName,dir) )
    _isOk = 0;
 else
    _isOk = 1;
 asc_min = data->getData()->natal_minutes[0];
 old_asc_min = data->getData()->natal_minutes[0];
 if ( _isOk ) {
    if ( data->getData()->type == TRANSITS_GRAPH_FILE ||
	    data->getData()->type == COMPTR_GRAPH_FILE )
       pCurChart = data->getFirstChart();
    drawMode = ogd.getDrawMode();
    dataGroup = new GraphicDataGroup();
    dataGroup->doGrfs(data->getData()->natal_minutes,
       data->getData()->maxpt, data->getData()->natal_house_cusps,
       drawMode, asc_min );
    if ( data->ncharts() == 1 && data->getData()->num_aspects ) {
       int n;
       GR_ASPT *as;
       as =data->getAspects(n);
       dataGroup->doAspects(as, n);
       }
    if ( data->ncharts() > 1 && data->getData()->type != TRANSITS_GRAPH_FILE
	  && data->getData()->type != COMPTR_GRAPH_FILE ) {
       compGroup = new GraphicDataGroup();
       compGroup->doGrfs(data->getData()->other_minutes,
	  data->getData()->maxpt, data->getData()->other_house_cusps,
	  drawMode, asc_min );
       }
    else if (data->getData()->type == TRANSITS_GRAPH_FILE ||
	      data->getData()->type == COMPTR_GRAPH_FILE ) {
       compGroup = new GraphicDataGroup();
#ifdef NEW
       compGroup->doGrfs( ( data->getData()->num_charts > 0 ?
	  pCurChart->getChartMinutes() :
	  data->getData()->other_minutes ),
	  data->getData()->num_charts > 0 ? pCurChart->maxpt :
	     data->getData()->maxpt, data->getData()->other_house_cusps,
	 drawMode, asc_min );
#else
       compGroup->doGrfs( ( data->getData()->num_charts > 0 ?
	  pCurChart->getChartMinutes() :
	  data->getData()->other_minutes ), data->getData()->maxpt,
	  data->getData()->other_house_cusps,
	  drawMode, asc_min );
#endif
       }
    else
       compGroup = NULL;
    }
 pbBack = NULL;
 pDataFnt = NULL;
 pGlyphSpec = NULL;
 pDegSpec = NULL;
 baseMetrics = new AstDrawBase(canvas());
 setMetrics();
 backgroundColor(baseMetrics->getColor(0));
 setHandler(this, (NotifyProc)(KeyProc)&AstGraphicsPane::kbhnd, WM_KEYDOWN);
#ifdef NEW
#ifdef DELUXE
 dblclkTime=GetDoubleClickTime();
 init_popup_text_report();
#endif
#endif
}

int AstGraphicsFrame::MDIActivate(zActivateEvt *actEvt)
{
 if ( (actEvt->active()) && (pane!=0) ) {
    pane->updateScroller();
    pane->setFocus();
    pane->setupMenu();
#ifdef NEW
    ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, 
      CResStr(_GRP_STATUS)/*"Double Click Within Wheel or Aspect Grid For Interpretations."*/);
#endif
    }
 else {
    disableMenuItems(pane->pgMenu, IDM_ECOPY );
    disableMenuItems(pane->pgMenu, IDM_FPRINT );
#ifdef NEW
    ((AstroAppFrame *)app->rootWindow())->pStatusLine->text(ZSL_MAINITEM, "");
    disableMenuItems(pane->pgMenu, IDM_FCLOSE );
#endif
#ifdef PRO
    disableMenuItems(pane->pgMenu, IDM_FEXPORT );
#endif
    }
 return 0;
}


AstGraphicsFrame::focus(zFocusEvt *focEvt)
{
 char buf[150];

 if ( (focEvt->gainFocus()) && pane != 0 ) {
    pane->updateScroller();
    pane->setFocus();
    pane->setDirty();
    strcpy( buf, CResStr(_GRP_VIEWGRPH)/*"View Graph: "*/ );
    strcat( buf, pane->data->getFileDb()->name );
    strcat( buf, ", " );
    strcat( buf, pane->data->getFileDb()->comment );
    caption( zString( buf ) );
    }
 return 0;
}

int AstGraphicsPane::command(zCommandEvt *e)
{
 return( 0 );
}

int AstGraphicsFrame::kill(zEvent *e)
{
#ifdef PRO
 AstMruList.check(set_path((char *)name, _dir), _GRAPH_);
#endif
 removeHandler(this, (NotifyProc)(KeyProc)&AstGraphicsPane::kbhnd, WM_KEYDOWN);
 pane->pgMenu->removeCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand );
 pane->parMenu->removeCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand);
 return( 0 );
}



AstGraphicsFrame::AstGraphicsFrame(zFrameWin *pPar, char *pName, int dir):zMDIChildFrame(pPar,new zSizer,zSTDFRAME,CResStr(_GRP_GRVW)/*"Graphics Viewer"*/)
{
 static char *types[] = { "ASTRO Reports (*.GRA)", "*.GRA", 0, 0 };

 if ( GetPrivateProfileInt( "Windows", "GraphMax", 0, APPNAME ))
    maximize(1);
 pane = 0;
 if ( pName == NULL ) {
    zFileOpenForm *fof = new zFileOpenForm(this, "Graphics Wheel to View", "*.GRA", types );
    if ( fof->completed() )
       pane=new AstGraphicsPane(fof->name(), this, -1);
    delete fof;
    }
 else
    pane=new AstGraphicsPane(pName, this, dir);
 _dir = dir;
 name = pName;
 if ( pane )
    _isOk = pane->isOk();
 else
    _isOk = 0;
 setIcon(new zIcon(zResId("GraphIcon")));
 pane->addVertScrollBar();
 pane->addHorzScrollBar();
 pane->updateScroller();
 pane->pgMenu = new zMenu(this, zResId("GRAPH"));
 menu(pane->pgMenu);
 pane->pgMenu->setCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand,
   IDM_SIGN_NAME, IDM_SHOW_AGRID );
 pane->parMenu = pPar->menu();
 pane->parMenu->setCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand,
   IDM_FPRINT );
#ifdef PRO
 pane->parMenu->setCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand,
   IDM_FEXPORT );
#endif
 pane->pgMenu->setCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand,
   IDM_ZOOMIN, IDM_FITWIN );
 pane->parMenu->setCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand,
   IDM_ECOPY );
#ifdef NEW
 pane->parMenu->setCommand(pane,(CommandProc)&AstGraphicsPane::menuCommand,
   IDM_FCLOSE );
#endif
 pane->pClip = ((AstroAppFrame *)pPar)->getClipboard();
 pane->setupMenu();
 pane->show();
 pane->setFocus();
 deleteOnClose(TRUE);
}
/*
void zApp::main()
{
   debugOn(1);
   AstGraphicsFrame* pFrame=new AstGraphicsFrame(app->rootWindow(), NULL, 0);
   if ( pFrame->isOk() ) {
      pFrame->show();
      go();
      }
   delete pFrame;
}
*/




