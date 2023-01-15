#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <stdlib.h>
#include "astro.h"
#include "ASPECT.h"
#include "dialogs.h"
#include "fielddgm.hpp"
#include "paths.hpp"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "orbedit.hpp"


#define NUM_ASPECT 12

/* Temporary for testing purposes.


#define d2m(d) ((d)*60)
#define MAX_ASPECTS 20

extern int near max_asp;
int high_asp;
int inc_hscsp;

ASP near aspect_def[NUM_ASPECT+1] = {
	 CONJUNCT,     0,         d2m(7),
	 SEXTILE,      d2m(60),   d2m(7),
	 TRINE,        d2m(120),  d2m(7),
	 OPPOSITION,   d2m(180),  d2m(7),
	 SQUARED,      d2m(90),   d2m(7),
	 SEMISEXT,     d2m(30),   d2m(2),
	 SEMISQUARE,   d2m(45),   d2m(2),
	 SEMISESQUAD,  d2m(135),  d2m(2),
	 QUINCUNX,     d2m(150),  d2m(2),
	 BIQUINTILE,   d2m(144),  d2m(2),
	 QUINTILE,     d2m(72),   d2m(2),
	 TREDECILE,    d2m(108),  d2m(2),
	 DECILE,       d2m(36),   d2m(2)
       /*  SEPTILE,      d2m(51),   d2m(2)
	 };

int other_orb = d2m(5);
int hscsp_orb = d2m(1);

char asp_map[] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

 end of temporary section. */
/*
static char *contexts[] = { "Natal Charts",
 	"Relocation Charts", "Compatability Charts",
	"Composite Charts", "Transit Charts",
	"Progressed Charts", "Arabic Charts",
	"Fixed Charts" };
*/
#define _ORB_OTHER 13
#define _ORB_HOUSE 14

int OrbData::changeContext(int cnt)
{
 int oldCnt = context;

 context = cnt;
 loadData();
 setupArrays();
 return( oldCnt );
}

void OrbData::setupArrays()
{
 for ( int i = 0; i < NUM_ASPECT; i++ ) {
     orbs[i] = aspect_def[i].orb;
     inc[i] = asp_map[i];
     }
 orbs[_ORB_OTHER] = other_orb;
 orbs[_ORB_HOUSE] = hscsp_orb;
 inc[_ORB_HOUSE] = inc_hscsp;
}

void OrbData::getData()
{
 for ( int i = 0; i < NUM_ASPECT; i++ ) {
     aspect_def[i].orb = orbs[i];
     asp_map[i] = inc[i];
     }
 other_orb = orbs[_ORB_OTHER];
 hscsp_orb = orbs[_ORB_HOUSE];
 inc_hscsp = inc[_ORB_HOUSE];
}

AspectOrbDlgf::AspectOrbDlgf(zWindow *pPar, OrbData *pOrb )
			 : FormDlgf( pPar,zResId("ORB_EDIT"), HELPID_DLG_EDITORB )
{
 int i, j;

 pOrbData = pOrb;
 pCb = new zAstComboBoxStatic( this, IDC_OECONTEXT);
 pCb->addResStrings(SB_CONTEXT);
// for ( i = 0; i < 8; i++ )
//     pCb->add(contexts[i]);     
 pCb->selection(0);
 pCb->setNotifySelChange(this,(NotifyProc)&AspectOrbDlgf::selchg);
 pOrb->changeContext(0);
 // A Control was left out of original dialog box. Need to add 3 to
 // end control ids.
 for ( i = IDC_OEDGM1, j = 0; i <= IDC_OEDGM13; i+= 3, j++ ) {
     new zDegMinField( this, i, pOrb->getOrb(j) ); 
     /*new zIntEdit( this, i, pOrb->getOrb(j), "99:99" );*/
     new zCheckBox( this, i+1, pOrb->getInc(j) );
     }
 new zDegMinField( this, IDC_OEDGMNP, pOrb->getOrb(_ORB_OTHER) );
 new zDegMinField( this, IDC_OEDGMHS, pOrb->getOrb(_ORB_HOUSE) );
 new zCheckBox( this, IDC_OEINCHS, pOrb->getInc(_ORB_HOUSE) );
 run();
}

void AspectOrbDlgf::getData()
{
 pOrbData->getData();
}


int AspectOrbDlgf::selchg( zEvent *e )
{
if ( pCb->selection() != LB_ERR )
   pOrbData->changeContext( pCb->selection() );
else
   pOrbData->changeContext( 0 );
setControlsToDefault();
return( 1 );
}


AspectOrbScreen::AspectOrbScreen(zWindow *pPar)
{
 AspectOrbDlgf *gof = new AspectOrbDlgf(pPar, &Orbs );
 if ( gof->completed() ) {
    Orbs.getData();
    Orbs.saveData();
    }
 delete gof;
}
/*

FormApp::FormApp(char * title):zAppFrame(0,new zSizer,zSTDFRAME,title) {
	out = new zTextPane(this,new zSizeWithParent);
	out->show();
	menu(new zMenu(this));
	menu()->addStr(ID_SHOW_FORM, "&Show");
	menu()->update();
}

#define print(x) out->printf( #x "=%d, Orb = %d, inc = %d  \n", \
       i, aspect_def[i].orb, asp_map[i] )


FormApp::command(zCommandEvt *e)
{
 if (e->cmd() == ID_SHOW_FORM) {
    AspectOrbScreen *gos = new AspectOrbScreen((zWindow *)this);
    delete gos;
    for ( int i = 0; i < NUM_ASPECT; i++ ) {
	print(i);
	}
    out->printf( "Other: Orb = %d\n", other_orb );
    out->printf( "House: Orb = %d, inc = %d  \n", hscsp_orb, inc_hscsp );
    }
 return 1;
}

void zApp::main() {
	FormApp *p=new FormApp("Form Tester");
	theDirectories.getFromIni("test.ini");
	p->show();
	go();
	delete p;
}
*/
