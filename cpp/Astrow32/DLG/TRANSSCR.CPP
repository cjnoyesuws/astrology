#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "fieldrng.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dialogs.h"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "transcr.hpp"

// Class to get Transits Data.
//
// useage out is a zTextPane, and data is working data.
//
// TRANS_DATA data;
//
// FormApp::command(zCommandEvt *e) {
//         if (e->cmd() == ID_SHOW_FORM) {
//            TransDataForm *td = new TransDataForm(
//               new TransDataDlgf( out, &data),&data ) ;
//            if ( td->completed() ) {
//               out->printf( "num_transits = %d\n", data.num_transits );
//               out->printf( "start_planet = %d\n", data.start_planet );
//               out->printf( "end_planet = %d\n", data.end_planet );
//               out->printf( "interval = %d mo %d day\n",
//                   data.interval_date.month,
//                   data.interval_date.day );
//               }
//            delete td;
//         }
//         return 1;
// }
//
//
/*
char *pl[] = { "Ascendant", "Sun", "Moon", "Mercury", "Venus", "Mars",
               "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto",
	       "North Node", "South Node", "Medium Coeli",
               "Immum Coeli", "Part Of Fortune", "Vertex", 
               "East Point", NULL };
*/
TransDataDlgf::TransDataDlgf(zWindow *pPar, TRANS_DATA *pT )
		   : FormDlgf(pPar, zResId("TRANS_DATA"), HELPID_DLG_TRANSD)
{
 dlg_data = pT;

 if ( !dlg_data->end_planet && !dlg_data->start_planet ) {
    dlg_data->end_planet = PLUTO;
    dlg_data->start_planet = SUN;
    }
 pCbsp = new zAstComboBoxStatic(this, IDC_TDSP);
// for ( int i = 0; i < 18; i++ )
//     pCbsp->add( zString(pl[i]) );
 pCbsp->addResStrings(SB_PLANET);

 pCbsp->selection(dlg_data->start_planet );
 pCbsp->setNotifySelChange(this,(NotifyProc)&TransDataDlgf::selchg);

 pCbep = new zAstComboBoxStatic(this, IDC_TDEP);
// for ( i = 0; i < 18; i++ )
//     pCbep->add( zString(pl[i]) );
 pCbep->addResStrings(SB_PLANET);
 pCbep->selection(dlg_data->end_planet );
 pCbep->setNotifySelChange(this,(NotifyProc)&TransDataDlgf::selchg);
 if ( !dlg_data->num_transits )
    dlg_data->num_transits = 1;
 new zNumFieldRng(this, IDC_TDCNT, (int *)&dlg_data->num_transits,
	 365, 1);
 if ( !dlg_data->interval_date.month
       && !dlg_data->interval_date.day )
    dlg_data->interval_date.day = 1;
 new zNumFieldRng(this, IDC_TDMO, (int *)&dlg_data->interval_date.month,
	 12, 0);
 new zNumFieldRng(this, IDC_TDDAY, (int *)&dlg_data->interval_date.day,
	 31, 0);
 run();
}

int TransDataDlgf::selchg( zEvent *e )
{
 if ( e->parm1() == IDC_TDSP ) {
    if ( pCbsp->selection() != LB_ERR )
       dlg_data->start_planet = pCbsp->selection();
    else
       dlg_data->start_planet = 0;
    }
 else {
    if ( pCbep->selection() != LB_ERR )
       dlg_data->end_planet = pCbep->selection();
    else
       dlg_data->end_planet = 0;
    }
 if ( dlg_data->end_planet < dlg_data->start_planet ) {
    MessageBeep(MB_ICONASTERISK );
    dlg_data->end_planet = dlg_data->start_planet;
    pCbep->selection(dlg_data->end_planet);
    }

 return( 1 );
}
