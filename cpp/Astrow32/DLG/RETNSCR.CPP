#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "fieldrng.hpp"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "dialogs.h"
#include "acombbox.hpp"
#include "asfrmdlg.hpp"
#include "retnscr.hpp"

//
//  Classes to get Return information.
//  out is a zTextPane *, data is a RETURN_DATA struct
//
//  ReturnDataForm *rd = new ReturnDataForm(new ReturnDataDlgf( out, &data), &data ) ;
//  if ( rd->completed() ) {
//     out->printf("Planet = %d\n", data.planet );
//     out->printf("Start = %d/%d/%d\n", data.start.month,
//       data.start.day, data.start.year );
//     out->printf("End = %d/%d/%d\n", data.end.month,
//       data.end.day, data.end.year );
//     if (data.is_prog ) {
//        out->printf( "Progressed\n" );
//        out->printf( "System = %d\n",
// 	  data.prog.progress_system );
//        out->printf("Prog Offset = %d/%d/%d\n", data.prog.offset.month,
// 	  data.prog.offset.day, data.prog.offset.year );
//        }
//     }
//  delete rd;
//

/*

static char *progsys[] = { "Secondary (Day for a Year)",
   "Tertiary (Day for a Lunar Month)",
   "Minor (Lunar Month for a Year)" };

char *bdy[] = { "Sun", "Moon", NULL };
*/

ReturnDataDlgf::ReturnDataDlgf(zWindow *par, RETURN_DATA *pRd)
		: FormDlgf(par,zResId("RETURN_DATA"), HELPID_DLG_RETURN )
{
 dlg_data = pRd;

 if ( dlg_data->prog.progress_system >= 100 ) {
    target = 1;
    dlg_data->prog.progress_system -= 100;
    }
 else
    target = 0;
 pCbB = new zAstComboBoxStatic(this, IDC_RBODY );
 pCbB->addResStrings(SB_BODY);
// for ( int i = 0; i < 2; i++ )
//     pCbB->add( zString(bdy[i]) );
 pCbB->selection(dlg_data->planet );
 pCbB->setNotifySelChange(this,(NotifyProc)&ReturnDataDlgf::selchg);
 pCbP = new zAstComboBoxStatic(this, IDC_RPROGSYS );
// for ( i = 0; i < 3; i++ )
//     pCbP->add( zString(progsys[i]) );
 pCbP->addResStrings(PROG_SYS);
 pCbP->selection(dlg_data->prog.progress_system );
 pCbP->setNotifySelChange(this,(NotifyProc)&ReturnDataDlgf::selchg);
 if ( dlg_data->is_prog )
    enableProgFlds( 1 );
 else
    enableProgFlds( 0 );
 pCbip = new zCheckBox( this, IDC_RPROG );
 pCbip->check(dlg_data->is_prog );
 pCbip->setNotifyClicked(this,(NotifyProc)&ReturnDataDlgf::progButtonClick);
 new zNumFieldRng(this, IDC_RSMO, (int *)&dlg_data->start.month,
      12, 1);
 new zNumFieldRng(this, IDC_RSDAY, (int *)&dlg_data->start.day,
	  31, 1);
 new zNumFieldRng(this, IDC_RSYR, (int *)&dlg_data->start.year,
      2300, 0);
  
  new zNumFieldRng(this, IDC_REMO, (int *)&dlg_data->end.month,
      12, 1);
  new zNumFieldRng(this, IDC_REDAY, (int *)&dlg_data->end.day,
	  31, 0);
  new zNumFieldRng(this, IDC_REYR, (int *)&dlg_data->end.year,
      2300, 0);

  new zNumFieldRng(this, IDC_RPYR, (int *)&dlg_data->prog.offset.year,
      2100, 0);
  new zNumFieldRng(this, IDC_RPMO, (int *)&dlg_data->prog.offset.month,
      11, 0);
  new zNumFieldRng(this, IDC_RPDAY, (int *)&dlg_data->prog.offset.day,
	  31, 0);
  zCheckBox *pcb = new zCheckBox( this, IDC_RPTARGET, &target );
  run();
 }


void ReturnDataDlgf::enableProgFlds( int en )
{
 enableField(IDC_RPROGSYS, en );
 enableField(IDC_RPYR, en );
 enableField(IDC_RPMO, en );
 enableField(IDC_RPDAY, en );
 enableField(IDC_RPTARGET, en );
 enableField(119, en );
 enableField(121, en );
 enableField(122, en );
 enableField(124, en );
 enableField(126, en );
}


int ReturnDataDlgf::progButtonClick( zEvent *e )
{
 if ( pCbip->check() ) {
    dlg_data->is_prog = 1;
    enableProgFlds( 1 );
    }
else {
    dlg_data->is_prog = 0;
    enableProgFlds( 0 );
    }
return( 1 );
}

int ReturnDataDlgf::selchg( zEvent *e )
{
 if ( e->parm1() == IDC_RPROGSYS ) {
    if ( pCbP->selection() != LB_ERR )
       dlg_data->prog.progress_system = pCbP->selection();
    else
       dlg_data->prog.progress_system = 0;
    }
 else {
    if ( pCbB->selection() != LB_ERR )
       dlg_data->planet = pCbB->selection();
    else
       dlg_data->planet = 0;}
return( 1 );
}
