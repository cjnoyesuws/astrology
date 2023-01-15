#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "flistscr.hpp"
#include "asframe.hpp"
#include "astromn.h"
#include "title.hpp"
#include "mrufile.hpp"
#include "dialogs.h"
#include "inifile.hpp"
#include "resstr.hpp"

extern int qdtmode;
extern void zYield(void);
extern void doComp(AstroAppFrame *apf);

extern int write_birth_data(char *file);
DWORD CALLBACK HelpMessageFilterHook(int nCode, WORD wParam, LPMSG lpMsg );

WORD   PWM_PrivateHelpMessage;
HHOOK  MessageFilterHook;
WORD   wCurrentMenuCmd;
DWORD  dwCurrentMenuBits;
FARPROC prcHelpProc;

void kill_txptps(void);

AstroAppFrame::AstroAppFrame(zSizer *pSiz):zMDIAppFrame(0,pSiz,zSTDFRAME,
	CResStr(_ASTROFORWIN)/*"ASTRO for Windows"*/,"MAINMENU", 6, 3000 )
{
 PWM_PrivateHelpMessage=RegisterWindowMessage("HelpHookMessage");

 fAllChecked = 1;
 setNumTrailingSubmenus(2);
 app->loadAccelerator(zResId("IDA_ASTRO"));
 //menu(mainm/*new zMenu(this,zResId())*/);
 setIcon(new zIcon(zResId("AstrowIcon")));
 app->setHandler(this, (NotifyProc)&AstroAppFrame::doHelp,
	  PWM_PrivateHelpMessage );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::getDataCmd,
   IDM_DBIRTHI, IDM_DRELOCD );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::fileCmd,
   IDM_FNEWFLST, IDM_FPSETUPTXT );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::doCompileCmd,
   IDM_CDEF, IDM_CPROB );
 // menu()->appendDropDown(MDImenu(),"&Window");
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::windCmd,
   IDM_WARRANGE, IDM_WTILE );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::windCmd,
   IDM_FEXIT  );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::utilCmd,
   IDM_UBATCH, IDM_USORT );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::chOptCmd,
   IDM_ONATAL, IDM_OPROB );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::OptionCmd,
   IDM_OSETUP, IDM_OEORBS );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::OptionCmd,
   IDM_OALLCK );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::OptionCmd,
   IDM_OQDT );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::helpCmd,
   IDM_HCONTENTS, IDM_HINDEX );
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::windCmd,
   IDM_WGRAPLST);
 menu()->setCommand(this,(CommandProc)&AstroAppFrame::windCmd,
   IDM_WTEXTLST);
 menu()->setHilite(this,(NotifyProc)&AstroAppFrame::menuSelect);
 pClip = new zClipboard(app->rootWindow());
 if (PWM_PrivateHelpMessage)
    prcHelpProc = MakeProcInstance( (FARPROC)HelpMessageFilterHook, app->instance() );
    MessageFilterHook=SetWindowsHookEx(WH_MSGFILTER,
       prcHelpProc, app->instance(), GetWindowTask(*this));
 AstFileList.setName("NASTFIL.LST");
 AstFileList.read();
#ifdef NEW
 zMDIMarginFrame *bottomMargin= new zMDIMarginFrame(this,
     new zGrowToFitSizer(ZGRAV_BOTTOM, sizer()));
 bottomMargin->show();
 pStatusLine = new zStatusLineEZ( bottomMargin, new zGravSizer( ZGRAV_BOTTOM,
   0, bottomMargin->sizer() ), ZSL_STANDARD );
 pStatusLine->show();
#endif
 pGraphFrame = (zMDIChildFrame *)new FileListFrame(this, &AstFileList, GRA_F, CResStr(_GRAPHSCRNAME)/*"ASTRO Graphics"*/ );
 pGraphFrame->show();
 pTextFrame = (zMDIChildFrame *)new FileListFrame(this, &AstFileList, NON_GRA, CResStr(_TEXTSCRNAME)/*"ASTRO Reports"*/ );
 pTextFrame->show();
#ifdef PRO
 AstMruList.setupMenu( menu(), this, (CommandProc)&AstroAppFrame::mruCmd );
 AstMruList.getFromIni();
#endif
}


AstroAppFrame::~AstroAppFrame()
{
 delete pClip;
}


int AstroAppFrame::doHelp(zEvent *e)
{
 char file[150];

 strcpy( file, set_path("ASTROW.HLP", HELP_F ) );
 WinHelp(*app->rootWindow(), file, HELP_CONTEXT, (long)wCurrentMenuCmd );
 return( 1 );
}

int AstroAppFrame::menuSelect(zEvent *e)
{
 zMenuHiliteEvt *ev = (zMenuHiliteEvt *)e;

 wCurrentMenuCmd = ev->id();
 dwCurrentMenuBits = ev->flags();
 return( 1 );
}


int AstroAppFrame::kill(zEvent *e)
{
 write_birth_data( set_path( "ASTRODAT.HIS", USER_F ) );
 AstFileList.quit();
#ifdef PRO
 AstMruList.saveToIni();
#endif
#ifdef DEMO
 BegFrame *bf = new BegFrame(this);
 if ( bf->getReg() )
    delete bf;
 else
    bf->show();
 while ( app->tasks()->busy() )
       zYield();
#endif
 kill_txptps();
 if (PWM_PrivateHelpMessage)
    UnhookWindowsHookEx(MessageFilterHook);
 app->removeHandler(this, (NotifyProc)&AstroAppFrame::doHelp,
    PWM_PrivateHelpMessage );
 FreeProcInstance(prcHelpProc);
 return( 0 );
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


 