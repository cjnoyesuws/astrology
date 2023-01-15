#include <stdio.h>
#include <zapp.hpp>
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "utlduad.h"
#include "msg.hpp"
#include "setup.hpp"
#include "compile.hpp"
#include "astromn.h"
#include "direc.hpp"
#include "filelst.hpp"

#include "setup.hpp"

/* data that should be deleted once this module is ok */

Directories theDirectories;

PROGR_DATA progress_data;
TRANS_DATA transit_data;
RECT_DATA birth_rectd, comp_rectd, trans_rectd;
RETURN_DATA return_data;
BIRTH_DB birth_rec, comp_rec, trans_rec;
LOC_DB reloc_data;
int birth_ok, birth_rect_ok = 1, comp_ok, comp_rect_ok = 1,
    trans_ok, trans_data_ok, prog_ok;
AS_INF near birth_inf[18], near alt_inf[18];
AS_INF_EXT near birth_ext[18], near alt_ext[18];
DATA_PACKET birth_dp = { NATAL_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
comp_dp = { COMPA_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
trans_dp = { TRANS_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, NULL },
progr_dp = { PROGR_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
return_dp = { RETUR_CH, &birth_rectd, NULL, &progress_data, &return_data, NULL, &reloc_data, NULL },
reloc_dp = { RELOC_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
compos_dp = { COMPO_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
fixed_dp = { FIXED_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
arabp_dp = { ARABP_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
comptr_dp = { COMPO_CH|TRANS_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, &comp_rectd };
FileListArray AstFileList;

#define ID_LOAD 101

extern int do_load_birth_data( zWindow *pPar );

class TestApp : public zAppFrame {
	zTextPane* out;
public:
	TestApp(char * title);
	virtual int command(zCommandEvt *);
	~TestApp() { delete out; }
};


TestApp::TestApp(char * title):zAppFrame(0,new zSizer,zSTDFRAME,title) {
	out = new zTextPane(this,new zSizeWithParent);
	menu(new zMenu(this, zResId("TEST")));
	menu()->update();
	out->show();
}



void zApp::main() {
	theDirectories.getFromIni("test.ini");
	TestApp *p=new TestApp("Form Tester");
	AstFileList.setName("NASTFIL.LST");
	AstFileList.read();
	p->show();
	go();
	delete p;
}

TestApp::command( zCommandEvt *e )
{
 ChartCompiler *cc;
 enum ChartType ct;

 switch( e->cmd() ) {
       case ID_LOAD :
	    do_load_birth_data( this );
            return( 1 );
	    break;
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
       case IDM_CCMPBASM :
	    if ( e->cmd() == IDM_CCMPBASM )
	       ct = CompleteBMid;
       case IDM_CCMPFLM :
	    if ( e->cmd() == IDM_CCMPFLM )
	       ct = CompleteFMid;
       case IDM_CNUMERIC :
	    if ( e->cmd() == IDM_CNUMERIC )
	       ct = Numeric;
	    cc = new NatalChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CCOMPAT :
	    ct = Compatibility;
       case IDM_CCOMPOS :
	    if ( e->cmd() == IDM_CCOMPOS )
	       ct = Compos;
	    cc = new CompChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CTRANS :
	    ct = Transits;
	    cc = new TransChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CPROGR :
	    ct = Progress;
	    cc = new ProgChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CCMTR :
	    ct = ComposTrans;
	    cc = new ComTrnChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CRELOC :
	    ct = Reloc;
	    cc = new NatalChartCompiler( app->rootWindow(), ct );
	    break;
       case IDM_CRETURN :
	    ct = CReturn;
	    cc = new ReturnChartCompiler( app->rootWindow(), ct );
	    break;
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
       default:
	    break;
       }
 cc->runChart();
 delete cc;
 return( 1 );
}


