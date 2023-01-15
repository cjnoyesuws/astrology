#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "tbtframe.hpp"
#include "resource.h"
#include "paths.hpp"
#include "acombbox.hpp"

class AboutDlg : public zFormDialog {
public:
      AboutDlg(zWindow *pWnd) : zFormDialog(pWnd, zResId(IDD_ABOUT)) {
		centerDialog(this);
		show();
		modal();
		}
      ~AboutDlg() {}
      };

int TbtAppFrame::helpCmd( zCommandEvt *e )
{
 char file[150];
 switch( e->cmd() ) {
       case ID_HELP_CONTENTS:
	    strcpy( file, set_path("TBT.HLP", HELP_F ) );
	    WinHelp(*app->rootWindow(), file, HELP_CONTENTS, 0L );
	    break;
       case ID_HELP_SEARCH:
	    strcpy( file, set_path("TBT.HLP", HELP_F ) );
	    WinHelp(*app->rootWindow(), file, HELP_CONTENTS, NULL );
	    WinHelp(*app->rootWindow(), file, HELP_COMMAND, (DWORD) "Search()" );
	    break;
       case ID_HELP_HELPONHELP:
	    WinHelp(*app->rootWindow(), "WINHELP.HLP", HELP_HELPONHELP, 0L );
	    break;
       case ID_HELP_ABOUT :
	    {
	    AboutDlg *ad = new AboutDlg((zWindow *)this);
	    delete ad;
	    }
	    break;
       default :
	    return( 0 );
	    break;
       }
 return( 1 );
}

