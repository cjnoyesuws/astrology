#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "fieldrng.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dialogs.h"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "rectscr.hpp"
#include "astromn.h"
static RECT_DATA rect_data;
static int rect_data_saved;

// Class to get get birth rectification information.
//
// RECT_DATA data;
// BIRTH_DB birth;
//
// FormApp::command(zCommandEvt *e) {
//         birth.birth_data.birth_time.hours = 7;
//         birth.birth_data.birth_time.minutes = 30;
//         birth.am_pm = 1;
//         if (e->cmd() == ID_SHOW_FORM) {
//            RectDataDlgf *rd = new RectDataDlgf(
//                  out, &data, &birth);
//            if ( rd->completed() ) {
//               rd->computeAngle();
//               if (data.birth_time_known )
//                  out->printf("Birth Time is Known\n" );
//               else {
//                  out->printf("Birth Time is Not Known\n" );
//                  out->printf("Rect_system = %d\n", data.rect_system );
//                  out->printf("Trial Time = %d:%d %s\n",
//                       data.trial.hours,
//                       data.trial.minutes,
//                       (data.am_pm?"PM":"AM"));
//                  out->printf( "Angle = %d\n", data.angle );
//                  out->printf( "Sign = %d, deg:min = %d:%d\n",
//                       data.sign, data.degree.degrees,
//                       data.degree.minutes );
//                  out->printf( "total_minutes = %d\n", data.total_minutes );
//                  out->printf("Birth Time = %d:%d %c\n",
//                       birth.birth_data.birth_time.hours,
//                       birth.birth_data.birth_time.minutes,
//                       (birth.am_pm?"PM":"AM"));
//                  }
//
//               }
//            delete rd;
//         }
//         return 1;
// }
/*

char *signs[] = { "ARI", "TAU", "GEM", "CAN", "LEO",
   "VIR", "LIB", "SCO", "SAG", "CAP", "AQU", "PIS", NULL };

char *rect_meth[] = { "Solar Chart Method",
    "Flat Chart Method",  "Sunrise Birth-Time",
    "Trial & Error",  "Use Known Angle", NULL };

*/

void RectDataDlgf::computeAngle()
{
 dlg_rect->total_minutes = (((dlg_rect->sign * 30)
       + dlg_rect->degree.degrees) * 60) 
       + dlg_rect->degree.minutes;
 if ( dlg_rect->am_pm && dlg_rect->trial.hours != 12)
    dlg_rect->trial.hours += 12;
 else if ( dlg_rect->trial.hours == 12 )
    dlg_rect->trial.hours = 0;
 if ( dlg_rect->rect_system == SOLARCHART
       || dlg_rect->rect_system == FLATCHART ) {
   if ( dlg_rect->trial.hours != 12 )
      dlg_rect->trial.hours = 12;
   if ( dlg_rect->trial.minutes != 0 )
      dlg_rect->trial.minutes = 0;
   if ( !dlg_rect->am_pm )
      dlg_rect->am_pm = 1;
   }

}


RectDataDlgf::RectDataDlgf(zWindow *pPar, RECT_DATA *pR,
       BIRTH_DB *pB ) : FormDlgf(pPar, zResId("RECT_DATA"), HELPID_DLG_RECT)
{
 dlg_birth = pB;
 dlg_rect = pR;

 if ( !dlg_rect->trial.hours ) {
    dlg_rect->trial.hours = dlg_birth->birth_data.birth_time.hours;
    dlg_rect->trial.minutes = dlg_birth->birth_data.birth_time.minutes;
    dlg_rect->am_pm = dlg_birth->am_pm;
    }
 if ( dlg_rect->trial.hours > 12 ) {
    dlg_rect->am_pm = 1;
    dlg_rect->trial.hours -= 12;
    }
 else if ( dlg_rect->trial.hours == 12 )
     dlg_rect->am_pm = 1;
 else
     dlg_rect->am_pm = 0;
 if ( dlg_rect->trial.hours == 0 )
    dlg_rect->trial.hours = 12;
 
 pCbbtk = new zCheckBox(this, IDC_RBTKNOWN);
 pCbbtk->check(dlg_rect->birth_time_known);
 pCbbtk->setNotifyClicked(this,(NotifyProc)&RectDataDlgf::btkButtonClick);

 pCbmeth = new zAstComboBoxStatic(this, IDC_RBTMETH );
 pCbmeth->addResStrings(SB_RECTM );
// for ( int i = 0; i < 5; i++ )
//     pCbmeth->add( zString(rect_meth[i]) );
 pCbmeth->selection(dlg_rect->rect_system );
 pCbmeth->setNotifySelChange(this,(NotifyProc)&RectDataDlgf::selchg);

 pCbam = new zAstComboBoxStatic(this, IDC_RBTAM );
 pCbam->addResStrings(SB_AMPM );
// pCbam->add( zString("AM" ) );
// pCbam->add( zString("PM" ) );
 pCbam->selection(dlg_rect->am_pm);
 pCbam->setNotifySelChange(this,(NotifyProc)&RectDataDlgf::selchg);

 pCbangle = new zAstComboBoxStatic(this, IDC_RANGLE );
 pCbangle->addResStrings( SB_ANGLE );
// for ( i = 0; i < 16; i++ )
//     pCbangle->add( zString(angles[i]) );
 if ( !dlg_rect->angle )
    pCbangle->selection( 0 );
 else
    pCbangle->selection( dlg_rect->angle - 1 );
 pCbangle->setNotifySelChange(this,(NotifyProc)&RectDataDlgf::selchg);

 pCbsign = new zAstComboBoxStatic(this, IDC_RSIGN );
 pCbsign->addResStrings(SB_SIGNS);
// for ( i = 0; i < 12; i++ )
//     pCbsign->add( zString(signs[i]) );
 pCbsign->selection(dlg_rect->sign );
 pCbsign->setNotifySelChange(this,(NotifyProc)&RectDataDlgf::selchg);
 new zNumFieldRng( this, IDC_RBTH, (int *)&dlg_rect->trial.hours,
         12, 1);
 new zNumFieldRng( this, IDC_RBTM, (int *)&dlg_rect->trial.minutes,
         59, 0);

 new zNumFieldRng( this, IDC_RDEG, (int *)&dlg_rect->degree.degrees,
         29, 0);
 new zNumFieldRng( this, IDC_RMIN, (int *)&dlg_rect->degree.minutes,
	     59, 0);
 enableKnownFields( (dlg_rect->rect_system == KNOWN_ANGL?1:0) );
 run();
}

int RectDataDlgf::enableKnownFields(int en )
{
 int nen = (en?0:1);

 enableField(IDC_RANGLE, en);
 enableField(IDC_RSIGN, en);
 enableField(IDC_RDEG, en);
 enableField(IDC_RMIN, en);
 enableField(IDC_RBTAM, nen);
 enableField(IDC_RBTH, nen);
 enableField(IDC_RBTM, nen);
 enableField(111, en);
 enableField(113, en);
 enableField(115, en);
 enableField(117, en);
 enableField(104, nen);
 enableField(105, nen);
 enableField(107, nen);
 enableField(109, nen);
 return( 0 );
}


int RectDataDlgf::selchg( zEvent *e )
{
 if ( e->parm1() == IDC_RBTAM ) {
    if ( pCbam->selection() != LB_ERR )
       dlg_rect->am_pm = pCbam->selection();
    else
       dlg_rect->am_pm = 0;
    }
 else if (e->parm1() == IDC_RANGLE ) {
    if ( pCbangle->selection() != LB_ERR )
       dlg_rect->angle = pCbangle->selection();
    else
       dlg_rect->angle = 0;
    }
 else if (e->parm1() == IDC_RSIGN ) {
    if ( pCbsign->selection() != LB_ERR )
       dlg_rect->sign = pCbsign->selection();
    else
       dlg_rect->sign = 0;
    }
 else {
    if ( pCbmeth->selection() != LB_ERR )
       dlg_rect->rect_system = pCbmeth->selection();
    else
       dlg_rect->rect_system = 0;

    if ( dlg_rect->rect_system == SOLARCHART ||
		       dlg_rect->rect_system == SOLARCHART ) {
       dlg_rect->trial.hours = 12;
       dlg_rect->trial.minutes = 0;
       dlg_rect->am_pm = 1;
       setControlsToDefault();
       }
    enableKnownFields( (dlg_rect->rect_system == KNOWN_ANGL?1:0) );
    }
return( 1 );
}

int RectDataDlgf::command( zCommandEvt *e )
{
 switch( e->cmd() ) {
       case IDM_ECOPY :
	    if ( !storeData() )
	       return( 1 );
	    computeAngle();
	    rect_data = *dlg_rect;
	    rect_data_saved = 1;
	    return( 1 );
	    break;
       case IDM_EPASTE :
	    *dlg_rect = rect_data;
	    setControlsToDefault();
	    return( 1 );
	    break;
 /*    case IDM_CLEAR :
	    memset( dlg_rect, 0, sizeof(RECT_DATA) );
	    setControlsToDefault();
	    return( 1 );
	    break; */
       default:
	    return( 0 );
	    break;
       }
}



int RectDataDlgf::btkButtonClick( zEvent *e )
{
 if ( pCbbtk->check() ) {
    dlg_rect->birth_time_known = 1;
    }
else {
    dlg_rect->birth_time_known = 0;
    }
return( 1 );
}
