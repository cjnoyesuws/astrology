#include "stdafx.h"
#include <stdlib.h>
#include "asgflags.h"
#include "graopt.hpp"
#include "inifile.hpp"

GraphOptions::getFromIni( char *sec )
{
 CWinApp *app = AfxGetApp();
 CString a;

 a.Format( "%hu", drawMode );
 a = app->GetProfileString( GraphPrintOpt_SEC, "DrawMode", a );
 sscanf( a, "%hu", &drawMode );
 a.Format( "%d", fontSize );
 a = app->GetProfileString( sec, "FontSize", a );
 sscanf( a, "%hd", &fontSize );
 if ( fontSize < 10 )
    fontSize = 100;
 return( 1 );
}

GraphOptions::saveToIni( char *sec )
{
 CWinApp *app = AfxGetApp();
 CString a;
 
 a.Format( "%hu", drawMode );
 app->WriteProfileString( GraphPrintOpt_SEC, "DrawMode", a );
 app->WriteProfileString( GraphicsOptions_SEC, "DrawMode", a );
 a.Format( "%hd", fontSize );
 app->WriteProfileString( sec, "FontSize", a );
 return( 1 );
}


/*
GraphOptionsDlgf::GraphOptionsDlgf(zWindow *pPar, GraphOptions *g, int t)
	    : FormDlgf(pPar,zResId("GRAPH_OPT"), HELPID_DLG_GRAPHOPT )
{
 gr = g;
 type = t;
 showhcd= g->getOpt(HOUSE_DEG);
 new zCheckBox( this, IDC_SHOWHCD, &showhcd );

 showhcn= g->getOpt(HOUSE_NUM);
 new zCheckBox( this, IDC_SHOWHCN, &showhcn );

 showsigl= g->getOpt(SHOW_SLIN);
 new zCheckBox( this, IDC_SHOWSIGL, &showsigl );

 showaspl= g->getOpt(SHOW_ASPT);
 new zCheckBox( this, IDC_SHOWASPL, &showaspl );

#ifdef NEW
#ifdef DELUXE
 agrid= g->getOpt(SHOW_AGRID);
 new zCheckBox( this, IDC_SHOWAGRID, &agrid );
#endif
#endif

 usegl= g->getOpt(USE_GLYPH);
 new zCheckBox( this, IDC_USEGL, &usegl );

 signtick= g->getOpt(SIGN_TICK);
 new zCheckBox( this, IDC_SIGNTICK, &signtick );

 dectick= g->getOpt(DEC_TICK);
 new zCheckBox( this, IDC_DECTICK, &dectick );

 degtick= g->getOpt(DEG_TICK);
 new zCheckBox( this, IDC_DEGTICK, &degtick );

 show_signname= g->getOpt(SIGN_NAME);
 new zCheckBox( this, IDC_SHOW_SIGNNAME, &show_signname );

 plotclass= g->getOpt(PLOT_CLASSIC);
 new zCheckBox( this, IDC_PLOTCLASS, &plotclass );

 showdegs= g->getOpt(SHOW_PDEGS);
 new zCheckBox( this, IDC_SHOWDEGS, &showdegs );

 hsnmout= g->getOpt(HOUS_OUTS);
 new zCheckBox( this, IDC_HSNMOUT, &hsnmout );
 new zIntEdit( this, IDC_FONTSIZE, &g->getFontSize() );
 run();
}

void GraphOptionsDlgf::getData()
{
 gr->setOpt(HOUSE_DEG,showhcd);
 gr->setOpt(HOUSE_NUM, showhcd);
 gr->setOpt(SHOW_SLIN, showsigl);
 gr->setOpt(SHOW_ASPT, showaspl);
 gr->setOpt(USE_GLYPH, usegl);
 gr->setOpt(SIGN_TICK, signtick);
 gr->setOpt(DEC_TICK, dectick);
 gr->setOpt(DEG_TICK, degtick);
 gr->setOpt(SIGN_NAME, show_signname);
 gr->setOpt(PLOT_CLASSIC, plotclass);
 gr->setOpt(SHOW_PDEGS, showdegs);
 gr->setOpt(HOUS_OUTS, hsnmout);
#ifdef NEW
#ifdef DELUXE
 gr->setOpt(SHOW_AGRID, agrid);
#endif
#endif
}

int GraphOptionsDlgf::command(zCommandEvt *e)
{
 switch( e->cmd() ) {
      case IDC_GFONTS :
	   {
	   GraphicFonts *pgf = new GraphicFonts();
	   if ( type )
	      pgf->getFromIni(GraphPrintOpt_SEC);
	   else
	      pgf->getFromIni(GraphicsOptions_SEC);
	   GraphicFontDlgf *gfd = new GraphicFontDlgf(this, pgf);
	   if ( gfd->completed() ) {
	      if ( type )
		 pgf->saveToIni(GraphPrintOpt_SEC);
	      else
		 pgf->saveToIni(GraphicsOptions_SEC);
	      }
	   delete pgf;
	   delete gfd;
	   }
	   break;
      case IDC_GCOLORS :
	   {
	   zDisplay *d;
	   PrinterSetup *ps=0;
	   GraphicColors *gc;
	   if ( type ) {
	      ps = new PrinterSetup();
	      ps->getFromIni(GraphPrintOpt_SEC);
	      d = new zPrinterDisplay(ps->getSpec(), ps->toDevMode(this,0));
	      gc = new GraphicColors(d);
	      }
	   else {
	      d = new zWinDisplay(this);
	      gc = new GraphicColors(d);
	      }
	   GraphicColorsDlgf *gcd = new GraphicColorsDlgf(this, gc);
	   if ( gcd->completed() ) {
	      if ( type )
		 gc->saveToIni(GraphPrintOpt_SEC);
	      else
		 gc->saveToIni(GraphicsOptions_SEC);
	      }
	   delete gc;
	   delete gcd;
	   delete d;
	   if ( ps )
	      delete ps;
	   }
	   break;
      default :
	   return( 0 );
	   break;
      }
 return( 0 );
}


GraphOptionsScreen::GraphOptionsScreen(zWindow *pPar, GraphOptions *g, int t)
{
 gp = g;
 bg = *g;

 GraphOptionsDlgf * gof = new GraphOptionsDlgf(pPar, &bg, t );
 if ( gof->completed() ) {
    gof->getData();
    *g = bg;
    delete gof;
    }
 else {
    *gp = bg;
    delete gof;
    }
}

FormApp::FormApp(char * title):zAppFrame(0,new zSizer,zSTDFRAME,title) {
	out = new zTextPane(this,new zSizeWithParent);
	out->show();
	menu(new zMenu(this));
	menu()->addStr(ID_SHOW_FORM, "&Show");
	menu()->update();
}

#define print(x) out->printf( #x "=%s,  \n", (gox.getOpt(x)?"YES":"NO"))

FormApp::command(zCommandEvt *e) {
	GraphOptions gox;

	gox.getDrawMode() = HOUSE_DEG|HOUSE_NUM|SHOW_DEGS|
	     SHOW_ASPT|USE_GLYPH;
	if (e->cmd() == ID_SHOW_FORM) {
		GraphOptionsScreen *gos = new GraphOptionsScreen((zWindow *)this, &gox);
		delete gos;
		print(HOUSE_DEG);
		print(HOUSE_NUM);
		print(SHOW_SLIN);
		print(SHOW_ASPT);
		print(USE_GLYPH);
		print(SIGN_TICK);
		print(DEC_TICK);
		print(DEG_TICK);
		print(SIGN_NAME);
		print(PLOT_CLASSIC);
		print(HOUS_OUTS);
		out->printf("FontSize =%d\n", gox.getFontSize() );
	}
	return 1;
}

void zApp::main() {
	FormApp *p=new FormApp("Form Tester");
	p->show();
	go();
	delete p;
}
*/
