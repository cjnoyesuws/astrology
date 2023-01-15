#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>
#ifdef NEW
#include <intpack\zip.hpp>
#endif
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "filelst.hpp"
#include "charcons.h"
#include "flistscr.hpp"
#include "asframe.hpp"
#include "astromn.h"
#include "inifile.hpp"
#include "resstr.hpp"

int AstroAppFrame::windCmd(zCommandEvt* Ev) {
	switch ((unsigned int)Ev->cmd()) {
	case IDM_WARRANGE:
		arrangeIcons();
		break;
	case IDM_WCASCADE:
		cascade();
		break;
	case IDM_WTILE:
		tile();
		break;
#ifndef _QDTRAN_
	case IDM_WTEXTLST :
		if ( pTextFrame == 0 ) {
		   pTextFrame = (zMDIChildFrame *)new
		       FileListFrame(this, &AstFileList, NON_GRA,
		       CResStr(_TEXTSCRNAME)/*"ASTRO Reports"*/ );
		   pTextFrame->show();
		   }
		MDImenu()->deleteItem(IDM_WTEXTLST);
		MDImenu()->update();
		break;
	case IDM_WGRAPLST :
		if ( pGraphFrame == 0 ) {
		   pGraphFrame = (zMDIChildFrame *)new
		       FileListFrame(this, &AstFileList, GRA_F,
		       CResStr(_GRAPHSCRNAME)/*"ASTRO Graphics"*/ );
		   pGraphFrame->show();
		   }
		MDImenu()->deleteItem(IDM_WGRAPLST);
		MDImenu()->update();
		break;
#endif
	case SC_MAXIMIZE :
	     WritePrivateProfileString( "Windows", "MDIMax", "1", APPNAME );
	     return(0);
	     break;
	case SC_RESTORE :
	     WritePrivateProfileString( "Windows", "MDIMax", "0", APPNAME );
	     return(0);
	     break;
	case IDM_FEXIT:
	     kill((zEvent *)Ev);
	     app->quit();
	     break;
	default:
		return 0;
	}
 return 1;
}
