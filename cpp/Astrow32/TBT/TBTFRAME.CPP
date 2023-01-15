#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#include "tbtframe.hpp"
#include "d:\msvc\mfc\include\afxres.h"
#include "resource.h"
#include "title.hpp"
#include "paths.hpp"
#include "menuutl.hpp"
#include "asfrmdlg.hpp"
#include "acombbox.hpp"
#include "tbtoptn.hpp"
#include <dos.h>

void zYield(int y=1);

DWORD CALLBACK HelpMessageFilterHook(int nCode, WORD wParam, LPMSG lpMsg );

WORD   PWM_PrivateHelpMessage;
HHOOK  MessageFilterHook;
WORD   wCurrentMenuCmd;
DWORD  dwCurrentMenuBits;
FARPROC prcHelpProc;

TbtAppFrame::TbtAppFrame(zSizer *pSiz):zMDIAppFrame(0,pSiz,zSTDFRAME,
	"Text Builder Toolkit",MAKEINTRESOURCE(IDR_MENU1), 5 )
{
 PWM_PrivateHelpMessage=RegisterWindowMessage("HelpHookMessage");

 setNumTrailingSubmenus(2);
 app->loadAccelerator(zResId(IDR_ACCELERATOR1));
 //menu(mainm/*new zMenu(this,zResId())*/);
 setIcon(new zIcon(zResId("IDI_ICON_1")));
 app->setHandler(this, (NotifyProc)&TbtAppFrame::doHelp,
	  PWM_PrivateHelpMessage );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::fileCmd,
   ID_FILES_SAVE, ID_FILES_OPEN_REPORTSOURCEFILE );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::fileCmd,
   ID_FILES_RESTORE );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::windCmd,
   ID_FILES_EXIT  );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::windCmd,
   ID_WINDOWS_TILE, ID_WINDOWS_ARRANGE );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::helpCmd,
   ID_HELP_CONTENTS, ID_HELP_ABOUT );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::compile,
   ID_COMPILE_CHANGEDTEXTFILES, ID_COMPILE_CHANGEDREPORTFILES );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::compile,
   ID_COMPILE_COPYCHANGEDTEXTFILES, ID_COMPILE_COPYCHANGEDREPORTFILES );

 menu()->setCommand(this,(CommandProc)&TbtAppFrame::convert,
   ID_CONVERT_TEXTFILESTOFORMAT, ID_CONVERT_CONVERTEDREPORTSBACKTOAST );
// menu()->setCommand(this,(CommandProc)&TbtAppFrame::utilitiesCmd,
//   ID_UTILITIES_SPELLCHECKFILE, ID_UTILITIES_UPDATEASTROFILES );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::optionCmd,
   ID_OPTIONS_SETUP );
 menu()->setCommand(this,(CommandProc)&TbtAppFrame::optionCmd,
   ID_OPTIONS_DIRECTORIES );
 menu()->setHilite(this,(NotifyProc)&TbtAppFrame::menuSelect);
 pClip = new zClipboard(app->rootWindow());
 if (PWM_PrivateHelpMessage)
    prcHelpProc = MakeProcInstance( (FARPROC)HelpMessageFilterHook, app->instance() );
    MessageFilterHook=SetWindowsHookEx(WH_MSGFILTER,
       prcHelpProc, app->instance(), GetWindowTask(*this));
 checkConvertSettings();
}


TbtAppFrame::~TbtAppFrame()
{
 delete pClip;
}


int TbtAppFrame::doHelp(zEvent *e)
{
 char file[150];

 strcpy( file, set_path("TBT.HLP", TEXT_F ) );
 WinHelp(*app->rootWindow(), file, HELP_CONTEXT, (long)wCurrentMenuCmd );
 return( 1 );
}

int TbtAppFrame::menuSelect(zEvent *e)
{
 zMenuHiliteEvt *ev = (zMenuHiliteEvt *)e;

 wCurrentMenuCmd = ev->id();
 dwCurrentMenuBits = ev->flags();
 return( 1 );
}


int TbtAppFrame::kill(zEvent *e)
{
 while ( app->tasks()->busy() )
       zYield();
 if (PWM_PrivateHelpMessage)
    UnhookWindowsHookEx(MessageFilterHook);
 app->removeHandler(this, (NotifyProc)&TbtAppFrame::doHelp,
    PWM_PrivateHelpMessage );
 FreeProcInstance(prcHelpProc);
 return( 0 );
}

int checkSourceExist( char *ext, int path, char *ex )
{
 struct _find_t f;
 char bf[10];
 char buf[100];

 strcpy( bf, "*" );
 strcat( bf, ext );
 strcpy( buf, set_path( bf, path ) );
 if ( _dos_findfirst( buf, _A_NORMAL, &f ) )
    return( 0 );
 else if ( ex != NULL && !strcmpi(f.name, ex ) && _dos_findnext( &f ) )
    return( 0 );
 else
    return( 1 );
}

void TbtAppFrame::checkConvertSettings()
{
 static int menitms[] = { ID_CONVERT_TEXTFILESTOFORMAT,
   ID_CONVERT_HELPFILESTOFORMAT, ID_CONVERT_REPORTFILESTOFORMAT, 0 };
 static int menitmso[] = { ID_CONVERT_OLDTEXTFILESTOFORMAT,
   ID_CONVERT_OLDHELPFILESTOFORMAT, 0 };
 static int menitmsb[] = {
   ID_CONVERT_CONVERTTEXTFILESBACKTOAST, ID_CONVERT_CONVERTHELPFILESBAC,
   ID_CONVERT_CONVERTEDREPORTSBACKTOAST, 0 };

 if ( theTbtOptions.getTextSourceExt() != (const char *)".AST" &&
       theTbtOptions.getTextFormatKey() != (const char *)"AST" ) {
    enableMenuItems( menu(), menitms );
    if ( checkSourceExist((char *)theTbtOptions.getTextSourceExt(), EDIT_F, NULL) )
       enableMenuItems( menu(), menitmsb );
    else
       disableMenuItems( menu(), menitmsb );
    }
 else {
    disableMenuItems( menu(), menitms );
    disableMenuItems( menu(), menitmsb );
    }   
 if ( checkSourceExist(".SRC", TEXT_F, NULL ) && theTbtOptions.getTextSourceExt() != (const char *)".SRC" )
    enableMenuItems( menu(), ID_CONVERT_OLDHELPFILESTOFORMAT );
 else
    disableMenuItems( menu(), ID_CONVERT_OLDHELPFILESTOFORMAT );
 if ( checkSourceExist(".ASC", TEXT_F, NULL) && theTbtOptions.getTextSourceExt() != (const char *)".ASC" )
    enableMenuItems( menu(), ID_CONVERT_OLDTEXTFILESTOFORMAT );
 else
    disableMenuItems( menu(), ID_CONVERT_OLDTEXTFILESTOFORMAT );
 if ( checkSourceExist(".TBL", EDIT_F, NULL ) )
    enableMenuItems( menu(), ID_COMPILE_COPYCHANGEDREPORTFILES );
 else
    disableMenuItems( menu(), ID_COMPILE_COPYCHANGEDREPORTFILES );
 if ( checkSourceExist(".HLP", EDIT_F, "TBT.HLP") )
    enableMenuItems( menu(), ID_COMPILE_COPYCHANGEDHELPFILES );
 else
    disableMenuItems( menu(), ID_COMPILE_COPYCHANGEDHELPFILES );
 if ( checkSourceExist(".NDX", EDIT_F, NULL) )
    enableMenuItems( menu(), ID_COMPILE_COPYCHANGEDTEXTFILES );
 else
    disableMenuItems( menu(), ID_COMPILE_COPYCHANGEDTEXTFILES );

}
/****************************************************************************
	HelpMessageFilterHook():
****************************************************************************/

DWORD __export CALLBACK HelpMessageFilterHook(int nCode, WORD wParam, LPMSG lpMsg )
{
 if (nCode < 0)
    goto DefHook;
 if (!lpMsg)
    goto DefHook;
 if (nCode==MSGF_DIALOGBOX) {
    if (lpMsg->message==WM_KEYDOWN && lpMsg->wParam==VK_F1) {
       HWND hTemp=NULL;
       HWND hParent=lpMsg->hwnd;

       while (hParent != NULL) {
	     hTemp=hParent;
	     if (!(GetWindowLong(hTemp, GWL_STYLE) & WS_CHILD))
		break;
	     hParent=GetWindowWord(hParent, GWW_HWNDPARENT);
	     }

       if (hTemp)
	  PostMessage(hTemp, WM_COMMAND, IDC_HELP, 0L);
       return TRUE;
       }
    }

 if (nCode==MSGF_MENU) {
    if (lpMsg->message==WM_KEYDOWN && lpMsg->wParam==VK_F1)
       PostMessage(*app->rootWindow(), PWM_PrivateHelpMessage, nCode,
			MAKELONG((WORD)lpMsg->hwnd,0));
    }

 DefHook:
    return CallNextHookEx(MessageFilterHook, nCode, wParam, (LONG)lpMsg);
}


