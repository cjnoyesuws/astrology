#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "asframe.hpp"
#include "astromn.h"
#include "mselist.hpp"
#include "paths.hpp"
#include "asthlper.hpp"
#include "acombbox.hpp"

class AboutDlg : public zFormDialog {
public:
      AboutDlg(zWindow *pWnd) : zFormDialog(pWnd, zResId("ABOUT_BOX")) {
		centerDialog(this);
		show();
		modal();
		}
      ~AboutDlg() {}
      };

int AstroAppFrame::helpCmd( zCommandEvt *e )
{
 char file[150];
 switch( e->cmd() ) {
       case IDM_HCONTENTS:
	    strcpy( file, set_path("ASTROW.HLP", HELP_F ) );
	    WinHelp(*app->rootWindow(), file, HELP_CONTENTS, 0L );
	    break;
       case IDM_HSEARCH:
	    strcpy( file, set_path("ASTROW.HLP", HELP_F ) );
	    WinHelp(*app->rootWindow(), file, HELP_CONTENTS, NULL );
	    WinHelp(*app->rootWindow(), file, HELP_COMMAND, (DWORD) "Search()" );
	    break;
       case IDM_HHOWTO:
	    WinHelp(*app->rootWindow(), "WINHELP.HLP", HELP_HELPONHELP, 0L );
	    break;
       case IDM_HINDEX:
	    break;
       case IDM_HASTROL :
	    {
	    AstHelperFormDialog *pah = new AstHelperFormDialog((zFrameWin *)this);
	    pah->show();
	    pah->setFocus();
	    }
	    break;
       case IDM_HABOUT :
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

