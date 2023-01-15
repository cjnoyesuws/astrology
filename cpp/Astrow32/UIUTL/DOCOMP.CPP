#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "astromn.h"
#include "utlduad.h"
#include "msg.hpp"
#include "inifile.hpp"
#include "setup.hpp"
#include "compile.hpp"
#include "astromn.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "asframe.hpp"

int AstroAppFrame::doCompileCmd( zCommandEvt *e )
{
 ChartCompiler *cc;
 enum ChartType ct;

 switch( e->cmd() ) {
       case IDM_CDEF :
	    ct = Default;
       case IDM_CBSO :
	    if ( e->cmd() == IDM_CBSO )
	       ct = BirthSgnOnly;
       case IDM_CBSH :
	    if ( e->cmd() == IDM_CBSH )
	       ct = BirthSgnHse;
       case IDM_CBSHA :
	    if ( e->cmd() == IDM_CBSHA )
	       ct = SgnHseAsp;
       case IDM_CCOMPLETE :
	    if ( e->cmd() == IDM_CCOMPLETE )
	       ct = Complete;
#ifdef DELUXE
       case IDM_CCMPBASM :
	    if ( e->cmd() == IDM_CCMPBASM )
	       ct = CompleteBMid;
       case IDM_CCMPFLM :
	    if ( e->cmd() == IDM_CCMPFLM )
	       ct = CompleteFMid;
       case IDM_CNUMERIC :
	    if ( e->cmd() == IDM_CNUMERIC )
	       ct = Numeric;
#endif
	    cc = new NatalChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CCOMPAT :
	    ct = Compatibility;
#ifdef DELUXE
       case IDM_CCOMPOS :
	    if ( e->cmd() == IDM_CCOMPOS )
	       ct = Compos;
#endif
	    cc = new CompChartCompiler( app->rootWindow(), ct );
	    break;

       case IDM_CTRANS :
	    ct = Transits;
	    cc = new TransChartCompiler( app->rootWindow(), ct );
	    break;
#ifdef DELUXE
       case IDM_CPROGR :
	    ct = Progress;
	    cc = new ProgChartCompiler( app->rootWindow(), ct );
	    break;
#endif
#ifdef PRO
       case IDM_CCMTR :
	    ct = ComposTrans;
	    cc = new ComTrnChartCompiler( app->rootWindow(), ct );
	    break;
#endif
#ifdef DELUXE
       case IDM_CRELOC :
	    ct = Reloc;
	    cc = new NatalChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CRETURN :
	    ct = CReturn;
	    cc = new ReturnChartCompiler( app->rootWindow(), ct );
	    break;
#endif
#ifdef PRO
       case IDM_CFIXED :
	    ct = Fixed;
       case IDM_CARABIC :
	    if ( e->cmd() == IDM_CARABIC )
	       ct = Arabic;
       case IDM_CHELIO :
	    if ( e->cmd() == IDM_CHELIO )
	       ct = Helio;
       case IDM_CPROB :
	    if ( e->cmd() == IDM_CPROB )
	       ct = Problem;
	    cc = new OtherChartCompiler( app->rootWindow(), ct );
	    break;
#endif
       default:
	    return( 0 );
	    break;
       }
 cc->runChart();
 if ( getQdtMode() )
    doQdtView(cc->getOutFp(), cc->getGraphFp());
 delete cc;
 return( 1 );
}
