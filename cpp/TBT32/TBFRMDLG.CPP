#include "zapp.hpp"
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "d:\msvc\mfc\include\afxres.h"
#include "resource.h"
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include "paths.hpp"

int FormDlgf::doHelp(zEvent *e)
{
 char file[150];

 strcpy( file, set_path("TBT.HLP", TEXT_F ) );
 WinHelp(*app->rootWindow(), file, HELP_CONTEXT, dlgid );
 return( 1 );
}

void FormDlgf::enableField( int fld, int en )
{
 zControl *pC;

 pC = (zControl *)get(fld);
 if ( en )
    pC->enable();
 else
    pC->disable();
}

FormDlgf::FormDlgf( zWindow *pPar, zResId &r, long id ) :
			  zFormDialog(pPar, r )
{   
 dlgid = id;
 zPushButton *pbh = new zPushButton( this, ID_CONTEXT_HELP );
 pbh->setNotifyClicked(this, (NotifyProc)&FormDlgf::doHelp );
}

void FormDlgf::run()
{
 centerDialog(this);
 show();
 modal();
}

int FormDlgf::command(zCommandEvt *e)
{
 if ( e->cmd() == IDC_HELP )
    return( doHelp( e ) );
 /*else if ( e->cmd() == IDOK ) {
    endOk( e );
    return( 1 );
    }
 else if ( e->cmd() == IDCANCEL ) {
    endCancel( e );
    return( 1 );
    } */
 else
    return( 1 );
}

