#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include "dialogs.h"
#include "asfrmdlg.hpp"
#include "quit.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "acombbox.hpp"
//   Quit Dialog Box Function
//   Useage: save is an int, out is a zWindow *
//
//    QuitDlgf* qd = new QuitDlgf(out, &save );
//    if ( qd->is_OK() )
//       out->printf("OK or NO Button Pressed\n", save );
//    else
//       out->printf("Cancel Button Pressed\n", save );
//    out->printf("Save = %d\n\n", save );
//    delete qd;
//


QuitDlgf::QuitDlgf(zWindow *par, int *save)
	    : FormDlgf(par,zResId("QUIT"), HELPID_DLG_DEFAULT )
{
 _save = save;
 centerDialog(this);
 show();
 modal();
}


int QuitDlgf::command( zCommandEvt *e )
{
switch( e->cmd() ) {
      case IDOK:
           *_save = 1;
	   ok = TRUE;
      	   break;
      case IDC_NO:
           *_save = 0;
	   ok = TRUE;
      	   break;
      default :
           ok = FALSE;
	   break;
      }
 shutdown();
 return( e->cmd() );
}


/* function to either kill the que if wanted or save it. Returns
   0 if user hit Cancel Button. or 1 for NO or OK Buttons */

int FileListArray::quit()
{
 int save = 1, ok = 1;

 QuitDlgf* qd = new QuitDlgf(app->rootWindow(), &save );
 if ( qd->is_OK() && !save ) {
    killWholeFileList();
    free();
    }
 else if ( qd->is_OK() && save ) {
    write();
    free();
    }
 else {
    free();
    ok = 0;
    }
 delete qd;
 return ok;
}
