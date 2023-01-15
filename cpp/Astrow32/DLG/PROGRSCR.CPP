#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "astro.h"
#include "dataext.h"
#include "dialogs.h"
#include "fieldrng.hpp"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "progrscr.hpp"


// Progression Data Screen
//
// Useage of these classes
// where parent is a zWindow and progress_data is data 
// ProgressDlgf* pf = new ProgressDlgf(
//          &progress_data, parent );
// if ( pf->completed )
//    return value was IDOK
//delete pf;
//



char *progsys[] = { "Secondary (Day for a Year)",
   "Tertiary (Day for a Lunar Month)",
   "Minor (Lunar Month for a Year)" };

ProgressDlgf::ProgressDlgf(PROGR_DATA *pPd, zWindow *par)
		     : FormDlgf(par,zResId("PROGRESS_DATA"), HELPID_DLG_PROGR )
{
 dlg_data = pPd;

 if ( dlg_data->progress_system >= 100 ) {
    target = 1;
    dlg_data->progress_system -= 100;
    }
 else
    target = 0;
 pCb = new zAstComboBoxStatic(this, IDC_PRSYS );
 pCb->addResStrings(PROG_SYS); /*( zString(progsys[i]) );*/
 pCb->selection(dlg_data->progress_system );
 pCb->setNotifySelChange(this,(NotifyProc)&ProgressDlgf::selchg);
 new zNumFieldRng(this, IDC_PRYR, (int *)&dlg_data->offset.year,
      2100, 0);
 new zNumFieldRng(this, IDC_PRMO, (int *)&dlg_data->offset.month,
      11, 0);
 new zNumFieldRng(this, IDC_PRDAY, (int *)&dlg_data->offset.day,
      31, 0);
 zCheckBox *pcb = new zCheckBox( this, IDC_PRTARGET, &target );
 run();
}

int ProgressDlgf::selchg( zEvent *e )
{
 if ( pCb->selection() != LB_ERR )
    dlg_data->progress_system = pCb->selection();
 else
    dlg_data->progress_system = 0;
return( 1 );
}
