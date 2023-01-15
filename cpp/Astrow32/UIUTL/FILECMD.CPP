#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "asframe.hpp"
#include "astromn.h"
#include "inifile.hpp"
#include "asfrmdlg.hpp"
#include "pageopt.hpp"
#include <print.h>
#include "prntsetp.hpp"
#include "paths.hpp"
#include "filelst.hpp"
#include "flistscr.hpp"
#include "uflstscr.hpp"
#include "mrufile.hpp"
#include "resstr.hpp"
#include "errors.fns"

extern int do_load_birth_data( zWindow *pPar );
extern int do_save_birth_data( zWindow *pPar );

int AstroAppFrame::fileCmd( zCommandEvt *e )
{
 char buf[100];
 static char *types[] = { "Astro File Lists (*.AFL)", "*.AFL",
		       "All Files (*.*)", "*.*", 0, 0 };

 switch( e->cmd() ) {
       case IDM_FOPENBDAT :
	    do_load_birth_data( this );
	    break;
       case IDM_FSAVE :
       case IDM_FSAVEAS :
	    do_save_birth_data( this );
	    break;
#ifdef PRO
       case IDM_FNEWFLST :
	    {
	    UserFileListFrame *uflf = new UserFileListFrame(this, "UNTITLED");
	    uflf->show();
	    }
	    break;
       case IDM_FOPENFLST :
	    {
	    strcpy( buf, "USER.AFL" );
	    zFileOpenForm *fof = new zFileOpenForm( this,
		  "Open ASTRO File List.", buf, types );
	    if ( !fof->completed() ) {
	       delete fof;
	       return( 0 );
	       }
	    strcpy( buf, fof->name() );
	    delete fof;
	    AstMruList.check(buf,_FLIST_);
	    UserFileListFrame *uflfo = new UserFileListFrame(this, buf );
	    uflfo->show();
	    }
	    break;
       case IDM_FNEWCPG :
       case IDM_FNEWCFL :
       case IDM_FOPENCPG :
       case IDM_FOPENCFL :
       case IDM_FEDIT :
#endif
       case IDM_FVIEW :
       case IDM_FKILL :
       case IDM_FPRINT :
	    {
	    alert_box(_FIC_SELECT);
	    //zMessage *mp = new zMessage(this,
	    //   "Select Files From File List First!", "Error!", MB_OK );
	    //delete mp;
	    }
	    break;
       case IDM_FGRPAGESETUP :
	    {
	    PageData pd;
	    pd.getFromIni(PageOptGra_SEC);
	    PageDataDlgf  *pdd = new PageDataDlgf(this, &pd);
	    if (pdd->completed() )
	      pdd->getData();
	    pd.saveToIni(PageOptGra_SEC);
	    }
	    break;
       case IDM_FPRPAGESETUP :
	    {
	    PageData pd;
	    pd.getFromIni(PageOpt_SEC);
	    PageDataDlgf  *pdd = new PageDataDlgf(this, &pd);
	    if (pdd->completed() )
	      pdd->getData();
	    pd.saveToIni(PageOpt_SEC);
	    }
	    break;
       case IDM_FPSETUPTXT :
	    {
	    PrinterSetup pst;
	    pst.getFromIni(PrintData_SEC);
	    PrinterSetupDlgf *psdt = new PrinterSetupDlgf(this, &pst, 1);
	    if ( psdt->completed() )
	       pst.saveToIni(PrintData_SEC);
	    delete psdt;
	    }
	    break;
       case IDM_FPSETUPGRA :
	    {
	    PrinterSetup psg;
	    psg.getFromIni(GraphPrintOpt_SEC);
	    PrinterSetupDlgf *psdg = new PrinterSetupDlgf(this, &psg, 0);
	    if ( psdg->completed() )
	       psg.saveToIni(GraphPrintOpt_SEC);
	    delete psdg;
	    }
	    break;
       default :
	    return( 0 );
	    break;
       }
 return( 1 );
}
