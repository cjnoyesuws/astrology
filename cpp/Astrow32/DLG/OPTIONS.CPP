#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "astro.h"
#include "inifile.hpp"
#include "setup.hpp"
#include "dataext.h"
#include "dialogs.h"
#include "flags.h"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "options.hpp"


// Classes to get setup for Astrological Charts.
//
// /* macros */
// #define print(x) out->printf( #x "=%d,  ", is_set(mydata.getFlags(), x))
// #define printcc(x) out->printf( #x "=%d,  ", is_set(mydata.getChartCode(), x))
// #define printch(x) out->printf( #x "=%d,  ", is_set(mydata.getCharts(), x))
//
// /* Data */
//  Options mydata.set(HOUSES|ASPECTS,1,TEXTF|GRAPH,NATAL_CH|RELOC_CH);
//
//   CustomDlgf *cf = new CustomDlgf( out, "Birth Options", &mydata, 1);
//   if ( cf->completed() ) {
//      cf->buildFlags();
//      out->printf( "house_proc = %d\n", mydata.getHouseMode() );
//      out->printf( "sidereal = %d\n", mydata.getFlags() & SIDEREAL );
//
//      printcc(RELOC_CH);
//      printcc(PROGR_CH);
//      printcc(PRGCS_CH);
//
//      out->printf("\n" );
//      printch( TEXTF );
//      printch( GRAPH );
//      printch( (DATAB|DATAC) );
//      printch( DATAB );
//      printch( DATAC );
//      out->printf("\n" );
//
//      print(HOUSES);
//      print(ASPECTS);
//      print(EXT_ASPECTS);
//      print(SUMMARY);
//      out->printf("\n" );
//      print(MISCELL);
//      print(EXT_CALCS);
//      print(VERT_EAST);
//      print(TEXT);
//      out->printf("\n" );
//      print(BASE_MID);
//      print(HALF_MID);
//      print(MID_ASPECT);
//      out->printf("\n" );
//      }
//  delete cf;
//
//  Useage of OptionsForm Class can be used on its own
//
//  if ( e->cmd() == IDC_CSGETOPTS ) {
//     // do options screen.
//     optf = new OptionsDlgf((zWindow *) this,
//         _title, &pOptions->house_mode);
//            if ( optf->completed() ) {
//               optf->buildFlags();
//               }
//     delete optf;
//     return( 1 );
//


/* char *hous_proc[] = { "Equal House", "Koch", "Placidus",
            "M House", "Campanus",
            "Regiomantanus", "Morinus", NULL };

static char *dbts[] = { "Comma Delimited", "Binary File", NULL };

*/
CustomDlgf::CustomDlgf(zWindow *pPar, char *title, Options *op,
    int cst ) :  FormDlgf(pPar,zResId("CUSTOM"), HELPID_DLG_CUSTOMIZE )
{
 pOptions = op;
 _title = title;
 caption(zString(_title) );
 zControl *ok, *pcst;

 pCbdf = new zAstComboBoxStatic(this, IDC_CSDFT);
 pCbdf->addResStrings( SB_DATFILE );
// for ( int i = 0; i < 2; i++ )
//     pCbdf->add( zString(dbts[i]) );
 if ( is_set(pOptions->getCharts(), DATAB ) )
    pCbdf->selection( 1 );
 else
    pCbdf->selection( 0 );
 pCbdf->setNotifySelChange(this,(NotifyProc)&CustomDlgf::selchg);
/* if ( cst ) {  // make IDC_CSGETOPTS the default
    // this will have to be modified for another gui
    SendMessage(HANDLE((HWND)get(IDOK)),BM_SETSTYLE, (WORD)BS_PUSHBUTTON, FALSE );
    SendMessage(HANDLE((HWND)get(IDC_CSGETOPTS)),
       BM_SETSTYLE, (WORD)BS_DEFPUSHBUTTON, FALSE );
    } */
 reset_value = pOptions->getChartCode() & (RELOC_CH|PROGR_CH );

 reloc = is_set( pOptions->getChartCode(), RELOC_CH );
 new zCheckBox( this, IDC_CSRELOC, &reloc );

 prog = is_set( pOptions->getChartCode(), PROGR_CH );
 new zCheckBox( this, IDC_CSPROGR, &prog );

 prhs = is_set( pOptions->getChartCode(), PRGCS_CH );
 new zCheckBox( this, IDC_CSPROGCUSP, &prhs );

 text = is_set( pOptions->getCharts(), TEXTF );
 new zCheckBox( this, IDC_CSTEXT, &text );

 graph = is_set( pOptions->getCharts(), GRAPH );
 new zCheckBox( this, IDC_CSGRAPH, &graph );

 data = is_set( pOptions->getCharts(), DATAB|DATAC );
 new zCheckBox( this, IDC_CSDATAFILE, &data );
 run();
 }

int CustomDlgf::selchg( zEvent *e )
{
 if ( pCbdf->selection() != LB_ERR )
    _datafile = pCbdf->selection();
 else
    _datafile = 0;
 return( 1 );
}


int CustomDlgf::command( zCommandEvt *e )
{
 if ( e->cmd() == IDC_CSGETOPTS ) {
    // do options screen.
    OptionsDlgf *optf = new OptionsDlgf((zWindow *) this,
    _title, (short *)&pOptions->getHouseMode(),(unsigned int *)&pOptions->getFlags() );
       if ( optf->completed() ) {
              optf->buildFlags();
          }
    delete optf;
    setFocus();
    return( 1 );
    }
 else
    return( zFormDialog::command(e) );
}

void CustomDlgf::buildFlags()
{
 short code, ch;

 code = pOptions->getChartCode();
 code ^= reset_value;
 set_it(code,RELOC_CH,reloc);
 set_it(code,PROGR_CH,prog);
 set_it(code,PRGCS_CH,prhs);
 ch = 0;
 set_it(ch,GRAPH,graph);
 set_it(ch,TEXTF,text);
 if ( data && _datafile )
    set_it(ch,DATAB,data);
 else if ( data )
    set_it(ch,DATAC,data);
 pOptions->setOpt( pOptions->getFlags(), pOptions->getHouseMode(), ch, code );
}


void OptionsDlgf::buildFlags()
{
 *pOptions = 0;
 if ( side == IDC_OPSIDEREAL )
    *pOptions = 1;
 set_it( *pOptions, HOUSES, house );
 set_it( *pOptions, ASPECTS, aspects );
 set_it( *pOptions, EXT_ASPECTS, ext_asp );
 set_it( *pOptions, SUMMARY, summary );
 set_it( *pOptions, MISCELL, misc );
 set_it( *pOptions, EXT_CALCS, extc );
 set_it( *pOptions, VERT_EAST, ver_east );
 set_it( *pOptions, TEXT, text );
#ifdef DELUXE
 set_it( *pOptions, BASE_MID, bas_mid );
 set_it( *pOptions, HALF_MID, half_mid );
 set_it( *pOptions, FULL_MID, full_mid );
 set_it( *pOptions, MID_ASPECT, mid_asp );
#endif
}

int OptionsDlgf::selchg( zEvent *e )
{
 if ( pCbhpr->selection() != LB_ERR )
    *pHouse_proc = pCbhpr->selection();
 else
    *pHouse_proc = 0;
 return( 1 );
}


OptionsDlgf::OptionsDlgf(zWindow *pPar, char *title, short *hsprc, unsigned int *pOpt )
	       : FormDlgf(pPar, zResId("OPTIONS"), HELPID_DLG_CHTOPT )
{
 zRadioButton *pR;

 pOptions = pOpt;
 pHouse_proc = hsprc;

 caption( zString(title) );
 pCbhpr = new zAstComboBoxStatic(this, IDC_OPHOUSEPROC);
 pCbhpr->addResStrings(SB_HOUSE);
// for ( int i = 0; i < 7; i++ )
//     pCbhpr->add( zString(hous_proc[i]) );
 pCbhpr->selection(*pHouse_proc );
 pCbhpr->setNotifySelChange(this,(NotifyProc)&OptionsDlgf::selchg);
 side = (*pOptions & SIDEREAL);

 if ( side )
    side = IDC_OPSIDEREAL;
 else
    side = IDC_OPTROPIC;
 new zRadioGroup(this, IDC_OPTROPIC, IDC_OPSIDEREAL, &side );
 
 house = is_set( *pOptions, HOUSES );
 new zCheckBox( this, IDC_OPFHOUSE, &house );

 aspects = is_set( *pOptions, ASPECTS );
 new zCheckBox( this, IDC_OPFASPECT, &aspects );

 ext_asp = is_set( *pOptions, EXT_ASPECTS );
 new zCheckBox( this, IDC_OPFXASPECT, &ext_asp );

 summary = is_set( *pOptions, SUMMARY );
 new zCheckBox( this, IDC_OPSUMMARY, &summary );

 misc = is_set( *pOptions, MISCELL );
 new zCheckBox( this, IDC_OPFMISC, &misc );

 extc = is_set( *pOptions, EXT_CALCS );
 new zCheckBox( this, IDC_OPFXMISC, &extc );

 ver_east = is_set( *pOptions, VERT_EAST );
 new zCheckBox( this, IDC_OPFVERTEAST, &ver_east );

 text = is_set( *pOptions, TEXT );
 new zCheckBox( this, IDC_OPPRTEXT, &text );
#ifdef DELUXE
 bas_mid = is_set( *pOptions, BASE_MID );
 new zCheckBox( this, IDC_OPFBMID, &bas_mid );

 half_mid = is_set( *pOptions, HALF_MID );
 new zCheckBox( this, IDC_OPFHMID, &half_mid );

 full_mid = is_set( *pOptions, FULL_MID );
 new zCheckBox( this, IDC_OPFFMID, &full_mid );

 mid_asp = is_set( *pOptions, MID_ASPECT );
 new zCheckBox( this, IDC_OPFAMID, &mid_asp );
#endif
 run();
}
